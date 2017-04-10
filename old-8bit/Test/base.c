#include "base.h"

/**********************************************
//Delay with software
**********************************************/
void delay(uint32_t t)
{
	uint8_t i, j;
	uint32_t k;

	for (k = t; k > 0; k--) {
		i = 35;
		j = 8;
		do
		{
			while (--j);
		} while (--i);
	}
}

/**********************************************
//Delay microseconds with software
**********************************************/
void delayMicroseconds(uint32_t t)
{
	uint8_t i;
	uint32_t k;

	for (k = t; k > 0; k--) {
		;
		i = 6;
		while (--i);
	}
}

/**********************************************
//Math pow
**********************************************/
uint32_t pow(uint32_t x, uint32_t a) 
{
	if (a > 1) return x * pow(x, a - 1);
	else if(a == 1) return x;
	else return 1;
}

/**********************************************
//IIC Set Address
**********************************************/
void IIC_Set_Address(uint8_t IIC_Address)
{
	IIC_ADDRESS = IIC_Address;
}

/**********************************************
//IIC Get Address
**********************************************/
uint8_t IIC_Get_Address()
{
	return IIC_ADDRESS;
}

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
	IIC_SCL_Set();
	IIC_SDA_Set();
	IIC_SDA_Clr();
	IIC_SCL_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
	IIC_SCL_Set();
	IIC_SDA_Clr();
	IIC_SDA_Set();

}

void IIC_Wait_Ack()
{
	IIC_SCL_Set();
	IIC_SCL_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m, da;
	da = IIC_Byte;
	IIC_SCL_Clr();
	for (i = 0; i < 8; i++)
	{
		m = da;
		m = m & 0x80;
		if (m == 0x80)
		{
			IIC_SDA_Set();
		}
		else IIC_SDA_Clr();
		da = da << 1;
		IIC_SCL_Set();
		IIC_SCL_Clr();
	}


}
/**********************************************
// IIC Write Command
**********************************************/
void IIC_Command(unsigned char IIC_Command)
{
	IIC_Start();
	IIC_Byte(IIC_ADDRESS);  //Slave address,SA0=0
	IIC_Wait_Ack();
	IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();
	IIC_Byte(IIC_Command);
	IIC_Wait_Ack();
	IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void IIC_Data(unsigned char IIC_Data)
{
	IIC_Start();
	IIC_Byte(IIC_ADDRESS);	//D/C#=0; R/W#=0
	IIC_Wait_Ack();
	IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();
	IIC_Byte(IIC_Data);
	IIC_Wait_Ack();
	IIC_Stop();
}
void IIC_WR_Byte(unsigned dat, unsigned cmd)
{
	if (cmd) {
		IIC_Data(dat);
	}
	else {
		IIC_Command(dat);
	}
}