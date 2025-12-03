/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "vmm3a.h"
#include "stress.h"
#include "protoLink.h"
#include <stdlib.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t VMM3A_LG_config[216] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5F, 0xEE, 0x00, 0x00, 0x00, 0x21, 0xD9, 0xC4, 0x24, 0x2E, 0xB8};
uint8_t VMM3A_HG_config[216] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5F, 0xEE, 0x00, 0x00, 0x00, 0x21, 0xDC, 0x24, 0x1F, 0x2E, 0xB8};
uint8_t VMM3A_TP_config[216] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x5F, 0xEE, 0x00, 0x00, 0x00, 0x21, 0xCD, 0x24, 0x1F, 0x2E, 0xB8};


uint8_t   calibRunState = 0;
uint8_t stressTestState = 0;
uint8_t adcMonitorState = 0;
uint8_t dataTakingState = 0;


extern uint8_t buff[256];
extern uint8_t flag;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */



int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  initGlobals(); //!Инициализируем буфер, попутно на все спилы в нем вешаем term=1, чтобы при обработке игнорировались, пока пусты
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC5_Init();
  MX_SPI3_Init();
  MX_SPI1_Init();
  MX_DAC1_Init();
  MX_TIM1_Init();
  MX_TIM5_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();//!Понятно
  MX_TIM20_Init();
  /* USER CODE BEGIN 2 */
  hspi1.Instance->CR1 |= SPI_CR1_SPE;
  hspi1.Instance->CR2 |= 0x1000;

  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);

  HAL_ADC_Start(&hadc1);
  HAL_ADC_Start(&hadc2);
  HAL_ADC_Start(&hadc5);

  HAL_ADCEx_Calibration_Start(&hadc1, ADC_DIFFERENTIAL_ENDED);
  HAL_ADCEx_Calibration_Start(&hadc2, ADC_DIFFERENTIAL_ENDED);
  HAL_ADCEx_Calibration_Start(&hadc5, ADC_DIFFERENTIAL_ENDED);

  HAL_Delay(100);


  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);

  HAL_ADC_Start(&hadc1);
  HAL_ADC_Start(&hadc2);
  HAL_ADC_Start(&hadc5);

  HAL_Delay(100);

  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);

  HAL_DAC_Start(&hdac1,DAC_CHANNEL_1);
  HAL_DAC_Start(&hdac1,DAC_CHANNEL_2);

  HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2048);
  HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 1024);

  HAL_Delay(100);

  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);

  HAL_TIM_Base_Start(&htim2); // BCID Counter
//  HAL_TIM_Base_Start_IT(&htim1); // Calib Counter

//  HAL_NVIC_EnableIRQ(USART3_IRQn);
  dataTaking(0);

  HAL_Delay(100);

  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);

  protoLink_Start();

  HAL_Delay(100);

//  VMM3A_init(&VMM3A_LG_config[0]);

//  VMM3A_start();

  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);

uint32_t trigcou = 1;

hit_t testH = {0};
spill_t testsp = {0};

if(sendTrig == 1){
	testH.board = BOARD_ID;
	testH.channel = chTrig * 4;
	testH.charge = 10;
	testH.footer = 0xAAAAAAAA;
	testsp.hitCount = 1; //!Тригерный хит
	testsp.term = 0;
} 

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
while (1)
{
	if((trigcou != 1)&&(dataTakingState == 0)) {trigcou = 1;}
//	HAL_IWDG_Refresh(&hiwdg);
	if(stressTestState){
		getRandomSpill(0);
	  	DAQ_transmit(&testSpill);
	}

	if(adcMonitorState){
		HAL_ADC_Start(&hadc5);
		HAL_ADC_Start(&hadc5);
		HAL_ADC_PollForConversion(&hadc5, 1000);
		int16_t voltage = HAL_ADC_GetValue(&hadc5);
	  	ADC_transmit(voltage);
	}

	if(calibRunState){
                  GPIOB->BSRR = GPIO_BSRR_BS8;
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();

                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();

                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();

                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();

		  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();

                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();

                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();

                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();
                  __NOP();

                  VMM3A_STOP;
                  VMM3A_readout();
                  GPIOB->BSRR = GPIO_BSRR_BR8;
		  FIFO.spills[posFIFO].hitCount = 64;
                  DAQ_transmit(&FIFO.spills[posFIFO]);
                  VMM3A_START;
          }
   	
						//!Фильтрация только по окну
	if (is_trigger_detected() && filter == 0){ //!Отлавливаем флаг тригера
		__disable_irq(); 
		spill_t tempo;
		int spIndex = sizeeFIFO;
		uint32_t moment = get_last_trigger_time(); //!Берем время срабатывания тригера по второму таймеру
		for(int i = 0; i<sizeeFIFO; i++){
			int j = posFIFO + 1 + i; //!Шагаем по буфферу, начиная с самого старого элемента
			if(j>sizeeFIFO-1) {j = j - sizeeFIFO;}
			if(FIFO.spills[j].term == 0){
				uint32_t deltaa = moment - FIFO.spills[i].bcidd; 
				if(deltaa < window){ //!Посчитали разницу, если меньше окна отправляем
				spIndex = j;
				break;	 
				}
			}
		}
		if(spIndex != sizeeFIFO){ //!Если что-то нашли
			tempo = FIFO.spills[spIndex];
			FIFO.spills[spIndex].term = 1; //!Поднимаем флаг на игнор этого спила
			tempo.spillCount = trigcou; //!Указываем счетчик спилов по тригеру
			if(sendTrig == 1){
				testH.time = tempo.hits[0].time;
				testH.bcid = tempo.hits[0].bcid;
				tempo.hits[tempo.hitCount] = testH;
				tempo.hitCount++;
			}
			for(int i = 0; i<tempo.hitCount; i++){
				tempo.hits[i].event = trigcou; //!Прописываем его же в каждый хит
			}
			__enable_irq(); //!Возобновляем прерывания
			DAQ_transmit(&tempo);
			trigcou++;
		}
		else{
			if(sendTrig == 1){
				tempo = FIFO.spills[posFIFO];
				testH.event = trigcou;
				testH.time = tempo.hits[0].time;
				testH.bcid = get_last_trigger_time();
				testsp.spillCount = trigcou;
				testsp.hits[0]=testH;  
				trigcou++;
			}
			__enable_irq(); //!Возобновляем прерывания
			if(sendTrig == 1) {DAQ_transmit(&testsp);}
		}
		clear_trigger_flag(); 
	}
	       //!Фильтрация по оконному времени и выборка наиболее подходящего
	if (is_trigger_detected() && filter == 1) { //!Отлавливаем флаг тригера
		__disable_irq(); 
		spill_t tempo;
		uint32_t delta_min = window + 10;
		uint8_t min = 0;
		uint32_t moment = get_last_trigger_time(); //!Берем время срабатывания тригера по второму таймеру
		for(int i = 0; i<sizeeFIFO; i++){
			if(FIFO.spills[i].term == 0){
				uint32_t deltaa = moment - FIFO.spills[i].bcidd; 
				if(deltaa < window){ //!Посчитали разницу, если больше окна игнорируем
					if(deltaa<trigDelay){ //!Далее сравниваем с предполагаемой задержкой и выбираем что поближе
						if(trigDelay - deltaa < delta_min){
							delta_min = trigDelay - deltaa;
							min = i;		
						}
					}
					else{
						if(deltaa - trigDelay < delta_min){
							delta_min = deltaa - trigDelay;
							min = i;
						}
					}
				}
			}
		}
		if(delta_min != window + 10){ //!Если что-то нашли
			tempo = FIFO.spills[min];
			FIFO.spills[min].term = 1; //!Поднимаем флаг на игнор этого спила
			tempo.spillCount = trigcou; //!Указываем счетчик спилов по тригеру
			if(sendTrig == 1){
				testH.time = tempo.hits[0].time;
				testH.bcid = tempo.hits[0].bcid;
				tempo.hits[tempo.hitCount] = testH;
				tempo.hitCount++;
			}
			for(int i = 0; i<tempo.hitCount; i++){
				tempo.hits[i].event = trigcou; //!Прописываем его же в каждый хит
			}
			__enable_irq(); 
			DAQ_transmit(&tempo);
			trigcou++;
		}
		else{
			if(sendTrig == 1){
				tempo = FIFO.spills[posFIFO]; 
				testH.event = trigcou;
				testH.time = tempo.hits[0].time;
				testH.bcid = get_last_trigger_time();
				testsp.spillCount = trigcou;
				testsp.hits[0]=testH;  
				trigcou++;
			}
			__enable_irq(); //!Возобновляем прерывания
			if(sendTrig == 1) {DAQ_transmit(&testsp);}
		}
		clear_trigger_flag(); 
	}

		   //!Без фильтрации по времени, чисто отправка последнего из буффера (для тестов)
	if (is_trigger_detected() && filter == 2) {
		__disable_irq();
		spill_t tempo;
		tempo = FIFO.spills[posFIFO];
		tempo.spillCount = get_trigger_count();
		if(sendTrig == 1){
				testH.time = tempo.hits[0].time;
				testH.bcid = tempo.hits[0].bcid;
				tempo.hits[tempo.hitCount] = testH;
				tempo.hitCount++;
		}
		for(int i = 0; i<tempo.hitCount; i++){
			tempo.hits[i].event = get_trigger_count();
		}
		__enable_irq();
		DAQ_transmit(&tempo);
		// Сбросить флаг триггера
		clear_trigger_flag();
	}
}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
