#include "DS2482.h"

DS2482::DS2482(PinName sda, PinName scl, int adress) : i2c(sda, scl)
{
  this->adress = adress ;
}


bool DS2482::reset()
{
  char buf[1];
  buf[0] = DS2482_RESET;
  
  i2c.write(this->adress,buf,1);
  i2c.read(this->adress,buf,1);
  
  return ((buf[0] & 0xF7) == 0x10);
    
}
bool DS2482::oneWireReset()
{
	char buf[2];
	buf[0] = ONEWIRE_RESET;
	int poll_count = 0;
	
	i2c.write(this->adress,buf,1);
	do 
	{
		i2c.read(this->adress,buf,1);
	}
	while((buf[0] & ONEWIRE_BUSY) &&(poll_count++ < 300));
	if(buf[0] & 0x02)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int DS2482::oneWireTouchBit(char sendbit)
{
	char buf[2];
	
	buf[0] = ONEWIRE_SINGLE_BIT;
	buf[1] = sendbit ? 0x80 : 0x00;
	
	i2c.write(this->adress, buf, 2);
	
	do
	{
		i2c.read(this->adress, buf, 1);
	}
	while((buf[0] & ONEWIRE_BUSY));
	
	if(buf[0] & 0x20)
	{
		return 1;
	}
	else return 0;	
	
}

int DS2482::oneWireReadBit()
{
	return oneWireTouchBit(0x01);
}

void DS2482::oneWireWriteBit(char sendbit)
{
	oneWireTouchBit(sendbit);
}

void DS2482::oneWireWriteByte(char sendbyte)
{
	char buf[2];
	
	buf[0] = ONEWIRE_WRITE_BYTE;
	buf[1] = sendbyte;
	
	i2c.write(this->adress, buf, 2);
	
	do
	{
		i2c.read(this->adress, buf, 1);
	}
	while((buf[0] & ONEWIRE_BUSY));
}

char DS2482::oneWireReadByte()
{
  char buf[2];
	
	buf[0] = ONEWIRE_READ_BYTE;
	
	
	i2c.write(this->adress, buf, 1);
	
	do
	{
		i2c.read(this->adress, buf, 1);
	}
	while((buf[0] & ONEWIRE_BUSY));
	
	buf[0] = 0xE1;
	buf[1] = 0xE1;
	
	i2c.write(this->adress, buf, 2);
	i2c.read(this->adress, buf, 1);
	
	return buf[0];
}
//Not fully implemented 
void DS2482::oneWireSearch()
{
	char rom[8];
	if(!this->oneWireReset())
	{
		return;
	}

	this->oneWireWriteByte(0x33);
	for(int i = 0; i< 8; i++)
	{
		rom[i] = this->oneWireReadByte();
	}
	return;
	
}


void DS2482::issueMeasureTempCommand()
{
  if(!this->oneWireReset())
	{
		return;
	}
	this->oneWireWriteByte(0xCC); //skip rom command
	this->oneWireWriteByte(0x44); //Convert_T command
	while(this->oneWireReadBit() == 0); //wait for temp
}


float DS2482::readFromROMadress(char rom[])
{
	if(!this->oneWireReset())
	{
		return -1;
	}
	this->oneWireWriteByte(0x55); //MATCH ROM
	for(int i = 0; i < 8; i++)
	{
		this->oneWireWriteByte(rom[i]); // sedn rom to activate device
	}
	this->oneWireWriteByte(0xBE); //Read_ScratchPad
	unsigned LSB = this->oneWireReadByte();
  unsigned MSB = this->oneWireReadByte();
  this->oneWireReset();
	return (float((int)((int16_t)((MSB << 8) | LSB))))/16.0;
}


float DS2482::getSolarTemperature()
{
	char rom[8] = {0x28,  0xFF, 0xE7, 0xD9, 0x11, 0x14, 0x00, 0x67};
	return this->readFromROMadress(rom);	
}


float DS2482::getFirstTankTemperature()
{
	char rom[8] = {0x28, 0xFF, 0x68, 0xBF, 0x12, 0x14, 0x00, 0xBE};
	return this->readFromROMadress(rom);	
}

float DS2482::getSecondTankTemperature()
{
	char rom[8] = {0x28, 0xFF, 0xB5, 0x4C, 0x12, 0x14, 0x00, 0xF5};
	return this->readFromROMadress(rom);	
}

