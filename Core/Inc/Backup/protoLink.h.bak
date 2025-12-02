/*
 * protoLink.h
 *
 *  Created on: Feb 26, 2025
 *      Author: vital
 */

#include "main.h"
#include "vmm3a.h"
#include "spi.h"
//#include "tim.h"
#include "gpio.h"

#ifndef INC_PROTOLINK_H_
#define INC_PROTOLINK_H_

#define START	0xAA
#define STOP 	0xBB
#define RUN		0x11 //0x11
#define PULS	0x22
#define ADC		0x33
#define TEST	0x44
#define CONF 	0x55
#define CAL 	0x66 //0x66
#define FLAG 	0x80

void setLatency(uint16_t latency);
void setPeriod (uint32_t * period);
void setLength (uint16_t length);

void protoLink_Start(void);
__IO void ADC_transmit(int16_t value);
__IO void DAQ_transmit(spill_t * spill, uint8_t len);

#endif /* INC_PROTOLINK_H_ */
