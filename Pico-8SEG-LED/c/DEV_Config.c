/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V3.0
* | Date        :   2019-07-31
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of theex Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "DEV_Config.h"

#define SPI_PORT 0

#define LED_8SEG_RCLK_PIN  50




void DEV_SPI_WriteByte(uint8_t Value)
{
   wiringXSPIDataRW(SPI_PORT, &Value,1);
}

void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len)
{
	 wiringXSPIDataRW(SPI_PORT, pData,Len);
   
}


void DEV_GPIO_Init(void)
{
   if(wiringXValidGPIO(LED_8SEG_RCLK_PIN) != 0) {
        printf("Invalid GPIO %d\n", LED_8SEG_RCLK_PIN);
    }
	pinMode(LED_8SEG_RCLK_PIN, PINMODE_OUTPUT);

    digitalWrite(LED_8SEG_RCLK_PIN, HIGH);
}
/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
uint8_t DEV_Module_Init(void)
{
    
    
    
     int fd_spi;

    
    if(wiringXSetup("milkv_duos", NULL) == -1) {
        wiringXGC();
        return -1;
    }

	DEV_GPIO_Init();

	


    if ((fd_spi = wiringXSPISetup(SPI_PORT, 10000 * 1000)) <0) {
        printf("SPI Setup failed: %d\n", fd_spi);
        wiringXGC();
        return -1;
    }
     
	
    
    
    
    printf("DEV_Module_Init OK \r\n");
    return 0;
}



