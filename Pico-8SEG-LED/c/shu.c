#include "shu.h"
#include <wiringx.h>
#include "unistd.h"

#define KILOBIT   0XFE //KiloBit
#define HUNDREDS  0XFD //hundreds
#define TENS      0XFB //tens
#define UNITS     0XF7 //units
#define Dot       0x80 //decimal separator

#define LED_8SEG_RCLK_PIN  50
int number = 0;
void main()
{

DEV_Module_Init();



while(1)
{

LED_8SEG_stopwatch();
//Increment();// 个位0-9

}





}


uint8_t SEG8Code[] ={
        0x3F, // 0
        0x06, // 1
        0x5B, // 2
        0x4F, // 3
        0x66, // 4
        0x6D, // 5
        0x7D, // 6
        0x07, // 7
        0x7F, // 8
        0x6F, // 9
        0x77, // A
        0x7C, // b
        0x39, // C
        0x5E, // d
        0x79, // E
        0x71, // F
    };

/******************************************************************************
function:	Send Command
parameter: 
    Num: bit select
    Seg：segment select
Info:The data transfer
******************************************************************************/

void LED_8SEG_SendCommand(uint8_t Num, uint8_t Seg) 
{
    digitalWrite(LED_8SEG_RCLK_PIN, HIGH);
    DEV_SPI_WriteByte(Num);
    DEV_SPI_WriteByte(Seg);
    digitalWrite(LED_8SEG_RCLK_PIN, LOW);
    sleep(0.002);
    digitalWrite(LED_8SEG_RCLK_PIN, HIGH);
}

/******************************************************************************
function:	Stop watch
parameter: 
Info:99 seconds watch
******************************************************************************/

void LED_8SEG_stopwatch()
{
    
    for (int o = 0; o < 99999; o++)
    {
        sleep(0.8);
        LED_8SEG_SendCommand(UNITS, SEG8Code[o%10]);
        sleep(0.8);
        LED_8SEG_SendCommand(TENS, SEG8Code[(o%100)/10]);
        sleep(0.8);
        LED_8SEG_SendCommand(HUNDREDS, SEG8Code[(o%1000)/100] | Dot);
        sleep(0.8);
        LED_8SEG_SendCommand(KILOBIT, SEG8Code[(o%10000)/1000]);
    }
    
     //时间可以自己进行调试
    
   


}

void Increment()
{
        LED_8SEG_SendCommand(UNITS, SEG8Code[number]);
        sleep(1);

        number +=1;

        if(number>9)

        number=0;


}