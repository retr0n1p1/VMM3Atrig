#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "protoLink.h"
#include "vmm3a.h"

spill_t testSpill = {0};

hit_t getRandomHit(uint8_t size, uint16_t event, uint32_t bcid) {
	hit_t hit = {0};

	hit.board   = 0;
    hit.channel = random() | 0x03; //setting up THL and FLAG
    hit.charge  = random() % 4096;
    hit.time    = random() % 4096;
    hit.event   = event;
    hit.bcid    = bcid;
    hit.footer  = 0xAAAAAAAA;

    return hit;
}

void getRandomSpill(uint8_t size) {
	if (size == 0) size = (random() % 63) + 1;


	for(int i = 0; i < 64; i++)
			testSpill.hits[i] = getRandomHit(size, testSpill.spillCount, TIM2->CNT);

	testSpill.hitCount = size;
	testSpill.spillCount += 1;
}
