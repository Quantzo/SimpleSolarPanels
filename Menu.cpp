#include "Menu.h"




void Menu::menu(InterruptManager &interruptManager, TextLCD &lcd, bool configurationMode, bool screen, float solarTemp, float tank1Temp, float tank2Temp, bool pump1State, bool pump2State, configurarationEnum state, int hysteresisValue, int minTemp, int diffrenceInTemp)
{
  if(interruptManager.getLcdRefresh())
  { 
    interruptManager.setLcdRefresh(false);
    lcd.cls();
    if(!configurationMode)
    {
      standardMenu(lcd,screen,solarTemp,tank1Temp,tank2Temp,pump1State,pump2State);
    }
    else
    {
      configurationMenu(lcd,state,hysteresisValue,minTemp,diffrenceInTemp);
    }
  }
}
void Menu::standardMenu(TextLCD &lcd, bool screen, float solarTemp, float tank1Temp, float tank2Temp, bool pump1State, bool pump2State)
{	
	if(screen)
	{
		lcd.printf("Sl:%3.1f T1:%2.1f ", solarTemp, tank1Temp);
		if(pump1State)
		{
			lcd.printf("Pump1 ON");			
		}
		else
		{
			lcd.printf("Pump1 OFF");
		}
	}
	else //second screen with tank1 and tank 2
		{
		lcd.printf("T1:%2.1f T2:%2.1f ", tank1Temp, tank2Temp);
		if(pump2State)
		{
			lcd.printf("Pump2 ON");			
		}
		else
		{
			lcd.printf("Pump2 OFF");
		}
	}
}
void Menu::configurationMenu(TextLCD &lcd, configurarationEnum state, int hysteresisValue, int minTemp, int diffrenceInTemp)
{
  switch(state)
  {
    case hysteresis:
      lcd.printf("Hysteresis: %i",hysteresisValue);
      break;
    case diffrence:
      lcd.printf("Diffrence: %i",diffrenceInTemp);
      break;
    case minTempInTank1:
      lcd.printf("Min temp in T1: %i",minTemp);
      break;  
  }


}
	


