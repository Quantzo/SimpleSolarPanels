#include "InterruptManager.h"



#define     TARGET_SECTOR    7      
#define     TARGET_EEPROM_ADDRESS   64





InterruptManager::InterruptManager(PinName configurationButton, PinName upButton, PinName downButton):configurationButton(configurationButton,PullUp), upButton(upButton,PullUp), downButton(downButton,PullUp)
{
  char* savedValues = sector_start_adress[ TARGET_SECTOR ];
  this->configurationMode = false;
  this->screen = true;
  this->state = hysteresis;
  IAP iap;
  int r   = iap.blank_check( TARGET_SECTOR, TARGET_SECTOR );
  if ( r == SECTOR_NOT_BLANK )
  {
    this->hysteresisValue = savedValues[0];
    this->minTemp = savedValues[2];
    this->diffrenceInTemp = savedValues[1];
  }
  else
  {
    this->hysteresisValue = 2;
    this->minTemp = 65;
    this->diffrenceInTemp = 10;
  }
  this->lcdRefreshTicker.attach_us(this, &InterruptManager::lcdRefresh, 40000);
  this->screenTicker.attach(this, &InterruptManager::screenSwitch, 5.0);
  this->configurationButton.attach_asserted(this, &InterruptManager::configurationButtonHandler);
  this->upButton.attach_asserted(this, &InterruptManager::upButtonHandler);
  this->downButton.attach_asserted(this, &InterruptManager::downButtonHandler);
  this->configurationButton.setSampleFrequency();
  this->upButton.setSampleFrequency();
  this->downButton.setSampleFrequency();
}

void InterruptManager::screenSwitch()
{
  this->screen = !(this->screen);
}

void InterruptManager::lcdRefresh()
{
  this->lcdText = true;
}
void InterruptManager::configurationButtonHandler()
{
  if(this->configurationMode)
  {
    switch(this->state)
    {
      case hysteresis:
      {
        this->state = diffrence;
        break;
      }
      case diffrence:
      {
        this->state = minTempInTank1;
        break;
      }
      case minTempInTank1:
      {
        this->state = hysteresis;
        this->configurationMode = false;
        
        IAP iap;        
        char tableToSaveInFlash[256] ={};
        tableToSaveInFlash[0] = this->hysteresisValue;
        tableToSaveInFlash[1] = this->diffrenceInTemp;
        tableToSaveInFlash[2] = this->minTemp;
        int r   = iap.blank_check( TARGET_SECTOR, TARGET_SECTOR );
        if ( r == SECTOR_NOT_BLANK )
        {
          iap.prepare( TARGET_SECTOR, TARGET_SECTOR );
          r   = iap.erase( TARGET_SECTOR, TARGET_SECTOR );
        }
        iap.prepare( TARGET_SECTOR, TARGET_SECTOR );
        r   = iap.write( tableToSaveInFlash, sector_start_adress[ TARGET_SECTOR ], 256 );
        break;
        
      }
    }
  }
  else
  {
    this->configurationMode = true;
  }
}
void InterruptManager::upButtonHandler()
{
  if(this->configurationMode)
  {
    switch(this->state)
    {
      case hysteresis:
      {
        if(this->hysteresisValue < 100)
        {
          this->hysteresisValue++;
        }
        break;        
      }
      case diffrence:
      {
        if(this->diffrenceInTemp < 100)
        {
          this->diffrenceInTemp++;
        }
        break;
      }
      case minTempInTank1:
      {
        if(this->minTemp < 100)
        {
          this->minTemp++;
        }
        break;
      }
    }
  }
}

void InterruptManager::downButtonHandler()
{
  if(this->configurationMode)
  {
    switch(this->state)
    {
      case hysteresis:
        if(this->hysteresisValue > 0)
        {
          this->hysteresisValue--;
        }        
        break;
      case diffrence:
      {
        if(this->diffrenceInTemp > 0)
        {
          this->diffrenceInTemp--;
        }
       break;
      }
      case minTempInTank1:
      {
        if(this->minTemp > 0)
        {
          this->minTemp--;
        }
        break;
      }
    }
  }  
}

bool InterruptManager::getLcdRefresh()
{
  return this->lcdText;
}
bool InterruptManager::getConfigurationMode()
{
  return this->configurationMode;
}
bool InterruptManager::getScreen()
{
  return this->screen;
}
configurarationEnum InterruptManager::getState()
{
  return this->state;
}
int InterruptManager::getHysteresisValue()
{
  return this->hysteresisValue;
}
int InterruptManager::getMinTempInTank1()
{
  return this->minTemp;
}
int InterruptManager::getDiffrenceInTemp()
{
  return this->diffrenceInTemp;
}

void InterruptManager::setLcdRefresh(bool lcdText)
{
  this->lcdText = lcdText;
}