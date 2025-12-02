#include <stdio.h>
#include "main.h"
#include "vmm3a.h"
#include "protoLink.h"

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi3;
extern SPI_HandleTypeDef huart1;
//!Инициализируем локальные для этого файла
spill_t Spill = {0};
const spill_t ClearSpill = {0};

uint8_t posFIFO = 0;
FIFO_t FIFO = {0}; //!Инициализируем глобальные

void initGlobals(void){ 
	uint8_t posFIFO = 0;
	FIFO_t FIFO = {0};
	spill_t s = { .term = 1 }; //!Поднимаем флаг на игнор (пока пуст)
	for(int i = 0; i<sizeeFIFO; i++)
		FIFO.spills[i] = s;
}

void VMM3A_init(uint8_t * config){
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0); //ENA !

  for (int i = 0; i < 18; i++) { //init channels
  	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, 0); //CS

  	  HAL_SPI_Transmit(&hspi3, &config[12 * i], 12, 400); //init bank 2 (L0 Mode not used)

  	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, 1); //CS
	}
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1); //ENA !
}

void VMM3A_start(void){
	  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1); //ENA
	 //GPIOB->ODR |= GPIO_ODR_ODR_9;
	VMM3A_START;
}

void VMM3A_stop(void){
	  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0); //ENA !
	//GPIOB->ODR &= ~GPIO_ODR_ODR_9;
	VMM3A_STOP;
}


static inline hit_t VMM3A_getHit(void){
	hit_t hit = {0};

	uint8_t channel = 0;

	HAL_SPI_Receive(&hspi1, &channel, 1, HAL_MAX_DELAY);

    hit.charge  = ADC1->DR; //HAL_ADC_GetValue(&hadc1);
    hit.time    = ADC2->DR; //HAL_ADC_GetValue(&hadc2);

    ADC1->CR |= ADC_CR_ADSTART;
    ADC2->CR |= ADC_CR_ADSTART;

    while ((ADC1->ISR & ADC_ISR_EOC)==0);
    while ((ADC2->ISR & ADC_ISR_EOC)==0);

    //
	
	hit.board   = BOARD_ID;
    hit.channel = channel;
    hit.charge  = *(volatile uint16_t *)&ADC1->DR; //HAL_ADC_GetValue(&hadc1);
    hit.time    = *(volatile uint16_t *)&ADC2->DR; //HAL_ADC_GetValue(&hadc2);
    hit.bcid    = TIM2->CNT;
    hit.footer  = 0xAAAAAAAA;

    return hit;
}

void Dummy_Receive(uint8_t *pData)
{
//	*(volatile uint8_t *)&hspi1.Instance->DR = 0;
	*pData = *(volatile uint8_t *)&hspi1.Instance->DR;
}

int  VMM3A_readout(void){
	uint8_t counts = 0;
//	if(!(GPIOB->IDR & GPIO_IDR_15)) break;

	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1); //TKI
	GPIOB->ODR |= GPIO_ODR_ODR_7;
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1); //CKTK
	GPIOB->ODR |=  GPIO_ODR_ODR_6;

	for(int i = 0; i < 64; i++){

		if(GPIOC->IDR & GPIO_PIN_8) { //D0

			if(i == 0) {Spill.bcidd = TIM2->CNT;} //!Ловим время прилета по первому событию через второй таймер
			Spill.hits[i] = VMM3A_getHit();
			//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1); //CKTK !
			GPIOB->ODR &= ~GPIO_ODR_ODR_6;
			//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1); //TKI !
			GPIOB->ODR &= ~GPIO_ODR_ODR_7; ////////////////////// <<--- For TKI always ON test !!!
		}
		else {
				//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1); //CKTK !
				GPIOB->ODR &= ~GPIO_ODR_ODR_6;
				//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1); //TKI !
				GPIOB->ODR &= ~GPIO_ODR_ODR_7; ////////////////////// <<--- For TKI always ON test !!!
			counts = i;
			break;
		}
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1); //CKTK
		GPIOB->ODR |=  GPIO_ODR_ODR_6;
	}

	//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1); //CKTK
		GPIOB->ODR |=  GPIO_ODR_ODR_6;
	//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1); //CKTK !
		GPIOB->ODR &= ~GPIO_ODR_ODR_6;
	//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1); //CKTK
		GPIOB->ODR |=  GPIO_ODR_ODR_6;
	//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1); //CKTK !
		GPIOB->ODR &= ~GPIO_ODR_ODR_6;
	//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1); //CKTK
		GPIOB->ODR |=  GPIO_ODR_ODR_6;
	//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1); //CKTK !
		GPIOB->ODR &= ~GPIO_ODR_ODR_6;
     
	Spill.term = 0; //!Опускаем флаг на игнор
	Spill.hitCount = counts; 
        if(posFIFO == sizeeFIFO - 1){ //!Кольцевая запись
		FIFO.spills[0] = Spill;
		posFIFO = 0;
	}
	else{
		FIFO.spills[posFIFO+1] = Spill;
		posFIFO++;
	}
	Spill = ClearSpill; //! Очищаем локальную переменную

//	HAL_IWDG_Refresh(&hiwdg);
 	return counts;
}

