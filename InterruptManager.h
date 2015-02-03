#ifndef INTERRUPTMANAGER_H
#define INTERRUPTMANAGER_H
#include "mbed.h"
#include "PinDetect.h"
#include "IAP.h"
#include "configurationEnum.h"
class InterruptManager
{
  public:
  InterruptManager(PinName configurationButton, PinName upButton, PinName downButton);
  bool getConfigurationMode();
  bool getScreen();
  bool getLcdRefresh();
  configurarationEnum getState();
  int getHysteresisValue();
  int getMinTempInTank1();
  int getDiffrenceInTemp();
  void setLcdRefresh(bool lcdText);
  
  private:
  volatile bool configurationMode;
  volatile bool screen;
  volatile bool lcdText;
  volatile configurarationEnum state;
  volatile int hysteresisValue;
  volatile int minTemp;
  volatile int diffrenceInTemp;
  PinDetect configurationButton;
  PinDetect upButton;
  PinDetect downButton;
  Ticker screenTicker;
  Ticker lcdRefreshTicker;
  

  
  void configurationButtonHandler();
  void upButtonHandler();
  void downButtonHandler();
  void screenSwitch();
  void lcdRefresh();
  
};
#endif