#include "TextLCD.h"
#include "mbed.h"
#include "DS3231.h"
#include "DS2482.h"
#include "Menu.h"
#include "LogicEngine.h"
#include "InterruptManager.h"
#include "Watchdog.h"
#include "PinDetect.h"






int main() {
  LogicEngine logicEngine(dp25,dp26);
  DS3231 rtc(dp5,dp27);
  DS2482 onewire(dp5,dp27,0x30);
  TextLCD lcd(dp13,dp14,dp15,dp16,dp17,dp18);
  InterruptManager interrups(dp9,dp10,dp11);
  Watchdog watchdoge;
  bool pump1State = false;
  bool pump2State = false;
 	watchdoge.setUp(1);
  while(1){
    onewire.reset();
		onewire.issueMeasureTempCommand();
		float tempSol = onewire.getSolarTemperature();
		float tempTankOne = onewire.getFirstTankTemperature();
		float tempTankTwo = onewire.getSecondTankTemperature();
    int hysteresis = interrups.getHysteresisValue();
    int diffrence = interrups.getDiffrenceInTemp();
    int minTempInTank1 = interrups.getMinTempInTank1();
    logicEngine.exexute(diffrence, minTempInTank1, hysteresis, pump1State, pump2State, tempSol, tempTankOne, tempTankTwo);
    Menu::menu(interrups, lcd, interrups.getConfigurationMode(), interrups.getScreen(), tempSol, tempTankOne, tempTankTwo, pump1State, pump2State, interrups.getState(), hysteresis, minTempInTank1, diffrence);
    watchdoge.kick();
	}
};








	
