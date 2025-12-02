#include <stdio.h>
#include "main.h"
#include "vmm3a.h"

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi3;
extern SPI_HandleTypeDef huart1;

extern spill_t 			 Spill;

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

//	HAL_ADC_Start(&hadc1);
//	HAL_ADC_Start(&hadc2);

//	ADC1->CR |= ADC_CR_ADEN;
//	ADC2->CR |= ADC_CR_ADEN;
//	ADC1->CR |= ADC_CR_ADEN;
//	ADC2->CR |= ADC_CR_ADEN;
	//ADC1->CR |= ADC_CR_ADEN;
	//ADC2->CR |= ADC_CR_ADEN;
	//ADC1->CR |= ADC_CR_ADEN;
	//ADC2->CR |= ADC_CR_ADEN;

	uint8_t channel = 0;

//	*(volatile uint8_t *)&SPI1->DR = (uint8_t)0;
//	channel = SPI1->DR;

	HAL_SPI_Receive(&hspi1, &channel, 1, HAL_MAX_DELAY);

//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

    hit.charge  = ADC1->DR; //HAL_ADC_GetValue(&hadc1);
    hit.time    = ADC2->DR; //HAL_ADC_GetValue(&hadc2);

    ADC1->CR |= ADC_CR_ADSTART;
    ADC2->CR |= ADC_CR_ADSTART;

    while ((ADC1->ISR & ADC_ISR_EOC)==0);
    while ((ADC2->ISR & ADC_ISR_EOC)==0);

    //HAL_ADC_PollForConversion(&hadc1, 1000);
	//HAL_ADC_PollForConversion(&hadc2, 1000);

	hit.board   = BOARD_ID;
    hit.channel = channel;
    hit.charge  = *(volatile uint16_t *)&ADC1->DR; //HAL_ADC_GetValue(&hadc1);
    hit.time    = *(volatile uint16_t *)&ADC2->DR; //HAL_ADC_GetValue(&hadc2);
    hit.event   = Spill.spillCount;
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

	Spill.hitCount = counts;
	Spill.spillCount += 1;

//	HAL_IWDG_Refresh(&hiwdg);

	return counts;
}

