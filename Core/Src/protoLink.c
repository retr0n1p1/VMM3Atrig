#include <stdio.h>
#include "main.h"
#include "protoLink.h"
#include "vmm3a.h"

extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef  htim5;
extern spill_t 			  Spill;
extern uint8_t  stressTestState;
extern uint8_t    calibRunState;
extern uint8_t  adcMonitorState;
extern uint8_t  dataTakingState;

const spill_t EmptySpill = {0};

uint8_t buff[256] = {0};
uint8_t linkState = 0;


void protoLink_Start(void) {
	HAL_UART_Receive_IT(&huart1, &buff[0], 220);
	linkState = 1;
}

void processBuff(void) {

	uint8_t message[5] = {0};

	message[0] = START;
	message[1] = 0x05;
	message[2] = 0xCC;
	message[3] = buff[1] | FLAG;
	message[4] = STOP;

	switch(buff[1]) {
	case RUN :
		dataTaking(buff[2]);
		break;
	case PULS :
		setPeriod((uint32_t *)&buff[2]);
		break;
	case ADC :
		adcMonitorState = buff[2];
		break;
	case CAL :
		calibRunState = buff[2];
		break;
	case TEST :
		stressTestState = buff[2];
		break;
	case CONF :
		VMM3A_init(&buff[2]);
		break;
	default :
		message[2] = 0xFF;

	}

	HAL_UART_Transmit(&huart1, &message[0], 5, 100);
}

void processErr(void) {
//	HAL_UART_Transmit(&huart1, &buff[0], 220, 100);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//	HAL_UART_Transmit(huart, &data, 1, 100);

	if(buff[0] == START) {
		if(buff[219] == STOP) {
			processBuff();
		}
		else {
			processErr();
		}
	}

	for(int i = 0; i < 256; i++) buff[i] = 0;

//	HAL_UART_Transmit(huart, &data, 1, 100);
	HAL_UART_Receive_IT(huart, buff, 220);
}

void setLatency(uint16_t latency);

void setPeriod (uint32_t * value) {
	uint32_t period = *value;
	if(period) {
		TIM5->ARR = period;
		TIM5->CNT = 0;
		HAL_TIM_Base_Start_IT(&htim5);
	}
	else {
		TIM5->ARR = 0xFFFF;
		TIM5->CNT = 0;
		HAL_TIM_Base_Stop_IT(&htim5);
	}
}

void setLength (uint16_t length);

void dataTaking(uint8_t state) {
	if(state) {
		VMM3A_stop();
		VMM3A_readout();
		NVIC_EnableIRQ(EXTI9_5_IRQn);
		dataTakingState = 1;
		VMM3A_start();
	}
	else {
		NVIC_DisableIRQ(EXTI9_5_IRQn);
		dataTakingState = 0;
		VMM3A_readout();
		VMM3A_stop();
	}
}

void ADC_transmit(int16_t value) {

	uint8_t measurement[6] = {0};

	measurement[0] = START;
	measurement[1] = 0x06;
	measurement[2] = 0xAD;
	measurement[3] = value & 0x00FF;
	measurement[4] = (value & 0xFF00) >> 8;
	measurement[5] = STOP;

	HAL_UART_Transmit(&huart1, measurement, 6, 100); //Function to send text on UART

}

__IO void DAQ_transmit(spill_t * spill, uint8_t len) {

	HAL_UART_Transmit(&huart1, (uint8_t *)&spill->hits, Spill.hitCount * 16, 1000); //Function to send text on UART

//	HAL_IWDG_Refresh(&hiwdg);
//	Spill = EmptySpill;
}

void DAQ_dummy_transmit(spill_t * spill, uint8_t len) {
	for(int i = 0; i < len; i++) {
		//board:spill:channel:charge:time
		char buffer[34];

		sprintf(buffer, "%03d, %05d, %03d, %05d, %05d\r\n", 35, spill->spillCount, spill->hits[i].channel,
												spill->hits[i].charge, spill->hits[i].time);
		HAL_UART_Transmit(&huart1, (uint8_t *)&buffer, 31, 100); //Function to send text on UART
	}
//	HAL_Delay(1);
}
