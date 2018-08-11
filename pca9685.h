#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/i2c-dev.h>
#include<unistd.h>
#include<math.h>

#define MODE1 0x00
#define MODE2 0x01
#define SUBADDR1 0x02
#define SUBADDR2 0x03
#define SUBADDR3 0x04
#define ALLCALLADDR 0x05
#define LED0 0x06
#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LEN0_OFF_H 0x09
#define ALLLEN_ON_L 0xFA
#define ALLLEN_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALL_LEN_OFF_H 0xFD
#define PRE_SCALE 0xFE
#define TestMode 0xFF
#define CLOCK_FREQ 25000000.0

int pca9685_init(unsigned char);
int setPwmFreq(int,int);
void setDutyCycle(int,int,float,float);
unsigned char read_reg(int,unsigned char);
int disable_one_channel(int fd,int channel);
int enable_one_channel(int fd,int channel);

