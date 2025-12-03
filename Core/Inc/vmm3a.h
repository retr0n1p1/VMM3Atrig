/*
 * spectra.h
 *
 *  Created on: Nov 23, 2023
 *      Author: vital
 */

#include "main.h"
#include "adc.h"
#include "spi.h"
//#include "tim.h"
#include "gpio.h"

#ifndef VMM3A_H

#define VMM3A_H

//Settings

#define BOARD_ID 135 
#define sizeeFIFO 5 //!Длина статического массива для спилов
#define filter 1 //!Режим фильтрации событий в буффуре 0 - только по окну,
		 //                                    1 - окно + предпочтительное время,
		 //                                    2 - отправка последнего события из буффера
#define window 4000 //!Окно для поиска события для отправки (для режима 0, 1)
#define trigDelay 1000 //!Примерная реальная задержка тригера, по ней будем отбирать ближайшее (режим 1)

#define sendTrig 0 //!Отправлять пустое событие на свободный канал при каждом срабатывании тригера
		   //для упращения синхронизации нескольких детекторов на этапе обработки
#define chTrig 32 //!Канал для отправки пустых событий при срабатывании тригера


#define VMM3A_START  GPIOB->BSRR = GPIO_BSRR_BR0 | GPIO_BSRR_BS9  //GPIOB->ODR |=  GPIO_ODR_ODR_9

#define VMM3A_STOP   GPIOB->BSRR = GPIO_BSRR_BS0 | GPIO_BSRR_BR9

typedef struct
{
	uint8_t  board;
	uint8_t  channel;
	uint16_t event;
	uint16_t charge;
	uint16_t time;
	uint32_t bcid;
	uint32_t footer;
} hit_t;

typedef struct
{
	uint16_t REGISTERS[10];
	uint16_t spillCount;
	uint16_t hitCount;
	uint32_t bcidd;
	_Bool term;
	hit_t 	 hits[64];
} spill_t;

extern const uint8_t sizeFIFO; //!Делаем глобальные переменные для FIFO буффера
extern uint8_t posFIFO;

typedef struct //!Просто массив из спилов
{
        spill_t  spills[sizeeFIFO];
} FIFO_t;

extern FIFO_t FIFO;


/*
REGISTERS[ 0] = UID
REGISTERS[ 1] = MODE ( 0 - Stop, 1- Internal, 2 -External)
REGISTERS[ 2] = super cycle (0.1mS)
REGISTERS[ 3] = spill length (6.25ns)
REGISTERS[ 4] = pulser delay (6.25ns)
REGISTERS[ 5] =
REGISTERS[ 6] =
REGISTERS[ 7] = NONA Config (29 Registers)
REGISTERS[ 8] = Monitor ADC
REGISTERS[ 9] = spill state (0 -- out, 1 -- in)
REGISTERS[10] = spill counter
REGISTERS[11] = hits in spill
REGISTERS[12] = hit.channel;
REGISTERS[13] = hit.charge;
REGISTERS[14] = hit.time;
*/

hit_t getHit(void);

void monitoringADC(uint8_t state);
void testPulser(uint8_t state);
void dataTaking(uint8_t state);

void initGlobals();
void VMM3A_start(void);
void VMM3A_pulse(void);
void VMM3A_stop(void);
void VMM3A_reset(void);
int VMM3A_readout(void); //!Тут раньше было int, но не использовалось
void VMM3A_init(uint8_t * config);

#endif // VMM3A_H
