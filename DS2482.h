#include "mbed.h"

#define DS2482_RESET     0xF0    //< DS2482 Device Reset
#define DS2482_CMD_WCFG     0xD2    //< DS2482 Write Configuration

//OneWire Commands
#define ONEWIRE_RESET          0xB4    //< DS2482 1-Wire Reset
#define ONEWIRE_WRITE_BYTE     0xA5    //< DS2482 1-Wire Write Byte
#define ONEWIRE_READ_BYTE      0x96    //< DS2482 1-Wire Read Byte
#define ONEWIRE_SINGLE_BIT     0x87    //< DS2482 1-Wire Single Bit
#define ONEWIRE_TRIPLET        0x78    //< DS2482 1-Wire Triplet

#define ONEWIRE_BUSY           0x01

class DS2482
{
  public:
  DS2482(PinName sda, PinName scl, int adress);
  void oneWireSearch();
  bool initialize();
  bool reset();
  bool busy();
  
	void issueMeasureTempCommand();
  
  float getSolarTemperature();
  float getFirstTankTemperature();
  float getSecondTankTemperature();
  
  
  private:
  int adress;  
  I2C i2c;
	

  
  //One wire commands
  bool oneWireReset();
  void oneWireWriteBit(char sendbit);
  int oneWireReadBit();
	int oneWireTouchBit(char sendbit);
  void oneWireWriteByte(char sendbyte);
  char oneWireReadByte();
  float readFromROMadress(char* rom);
  
};