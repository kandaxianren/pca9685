#include"pca9685.h"

int pca9685_init(unsigned char addr)
{
	int fd;
	unsigned char mode1[] = {MODE1,0x20};
	fd = open("/dev/i2c-1",O_RDWR);
	ioctl(fd,I2C_SLAVE,addr);
	write(fd,mode1,2); //initialize register mode1
	return fd;
}
unsigned char read_one_reg(int fd,unsigned char addr)
{
	unsigned char data;
	write(fd,&addr,1);
	read(fd,&data,1);
	return data;
}
int setPwmFreq(int fd,int freq)
{
	unsigned char prescale[] = {PRE_SCALE,0x00};
	unsigned char mode1[] = {MODE1,0x00};
	mode1[1] = read_one_reg(fd,MODE1);
	prescale[1] = round(CLOCK_FREQ/(4096 * freq)) - 1;
	mode1[1] = mode1[1] | 0x10;
	write(fd,mode1,2);
	write(fd,prescale,2);
	mode1[1] = mode1[1] & 0xEF;
	write(fd,mode1,2);
	return 0;
}
void setDutyCycle(int fd,int channel,float delay,float on)
{
	unsigned char data[]  = {LED0_ON_L + 4*channel,0x00,0x00,0x00,0x00};
	unsigned short on_click,off_click;
	if(delay + on <= 1)
	{
		on_click = round(4096 * delay) - 1;
		off_click = round(4096 * on) + on_click;
	}
	else
	{
		on_click = round(4096 * delay) - 1;
		off_click = round(4096 * on) + on_click - 4096;
	}
	data[1] = on_click;
	data[2] = on_click >> 8;
	data[3] = off_click;
	data[4] = off_click >> 8;
	write(fd,data,5);
	return;
}
int disable_one_channel(int fd,int channel)
{
	unsigned char addr = LED0_ON_L + channel * 4 + 3;
	unsigned char led_off_h[] = {addr,0x00};
	led_off_h[1] = read_one_reg(fd,addr);
	led_off_h[1] |= 0x10;
	write(fd,led_off_h,2);
	return 0;
}
int enable_one_channel(int fd,int channel)
{
	unsigned char addr = LED0_ON_L + channel * 4 + 3;
	unsigned char led_off_h[] = {addr,0x00};
	led_off_h[1] = read_one_reg(fd,addr);
	led_off_h[1] &= 0xEF;
	write(fd,led_off_h,2);
	return 0;
}
