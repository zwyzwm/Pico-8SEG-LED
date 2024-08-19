#ifndef __SHU_H
#define __SHU_H

#include "DEV_Config.h"
#include <stdlib.h>



void Increment(void);
void LED_8SEG_SendCommand(uint8_t Reg,uint8_t Seg);
void LED_8SEG_stopwatch(void);


#endif