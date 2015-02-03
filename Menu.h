#ifndef Menu_H
#define Menu_H
#include "TextLCD.h"
#include "InterruptManager.h"
#include "configurationEnum.h"

class Menu
{
	public:
	static void menu(InterruptManager &interruptManager, TextLCD &lcd, bool configurationMode, bool screen, float solarTemp, float tank1Temp, float tank2Temp, bool pump1State, bool pump2State, configurarationEnum state, int hysteresisValue, int minTemp, int diffrenceInTemp);
	private:
  static void standardMenu(TextLCD &lcd, bool screen, float solarTemp, float tank1Temp, float tank2Temp, bool pump1State, bool pump2State);	
	static void configurationMenu(TextLCD &lcd, configurarationEnum state, int hysteresisValue, int minTemp, int diffrenceInTemp);
	
	
	
};


#endif