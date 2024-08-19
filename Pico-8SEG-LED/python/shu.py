import spidev
import time
import os



KILOBIT   = 0xFE
HUNDREDS  = 0xFD
TENS      = 0xFB
UNITS     = 0xF7
Dot       = 0x80



SEG8Code = [
    0x3F, # 0
    0x06, # 1
    0x5B, # 2
    0x4F, # 3
    0x66, # 4
    0x6D, # 5
    0x7D, # 6
    0x07, # 7
    0x7F, # 8
    0x6F, # 9
    0x77, # A
    0x7C, # b
    0x39, # C
    0x5E, # d
    0x79, # E
    0x71  # F
    ] 




class GPIO:
    INPUT = "in"
    OUTPUT = "out"
    HIGH = "1"
    LOW = "0"

    def __init__(self, pin):
        self.pin = pin
        self.export()

    def export(self):
        try:
            with open("/sys/class/gpio/export", "w") as f:
                f.write(str(self.pin))
        except OSError as e:
            if e.errno == 16:  # Resource busy
                print(f"GPIO {self.pin} is already exported.")

    def set_mode(self, mode):
        with open(f"/sys/class/gpio/gpio{self.pin}/direction", "w") as f:
            f.write(mode)

    def write(self, value):
        with open(f"/sys/class/gpio/gpio{self.pin}/value", "w") as f:
            f.write(value)

    def read(self):
        with open(f"/sys/class/gpio/gpio{self.pin}/value", "r") as f:
            return f.read().strip()

    def cleanup(self):
        try:
            with open("/sys/class/gpio/unexport", "w") as f:
                f.write(str(self.pin))
        except OSError:
            print(f"Failed to unexport GPIO {self.pin}")

RCLK_PIN = GPIO(449)#B1


class LED_8SEG():
    def __init__(self):
        RCLK_PIN.set_mode(GPIO.OUTPUT)
        RCLK_PIN.write(GPIO.HIGH)
        self.spi = spidev.SpiDev()
        self.spi.open(0, 0)  # 打开 SPI 端口 0, 设备 0
        self.spi.max_speed_hz = 1000_000
        self.spi.mode = 0b00
        self.SEG8=SEG8Code
       
   
        
    '''
    function: Send Command
    parameter: 
        Num: bit select
        Seg：segment select       
    Info:The data transfer
    '''
    def write_cmd(self, Num, Seg):    
        RCLK_PIN.write(GPIO.HIGH)
        self.spi.xfer2(bytearray([Num]))
        self.spi.xfer2(bytearray([Seg]))
        RCLK_PIN.write(GPIO.LOW)
        time.sleep(0.002)
        RCLK_PIN.write(GPIO.HIGH)

    def cleanup(self):
        self.spi.close()
        RCLK_PIN.cleanup()
        
if __name__=='__main__':
    LED = LED_8SEG()
    #color BRG
    for o in range(99999):
            time.sleep(0.0005)
            LED.write_cmd(UNITS,LED.SEG8[o%10])
            time.sleep(0.0005)
            LED.write_cmd(TENS,LED.SEG8[(o%100)//10])
            time.sleep(0.0005)
            LED.write_cmd(HUNDREDS,LED.SEG8[(o%1000)//100]|Dot)
            time.sleep(0.0005)
            LED.write_cmd(KILOBIT,LED.SEG8[(o%10000)//1000])

    
    LED.cleanup()

        