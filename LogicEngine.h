#ifndef LOGIC_H
#define LOGIC_H
#include "mbed.h"
class LogicEngine
{
	public:
	LogicEngine(PinName Pump1Relay, PinName Pump2Relay);
	void exexute(int diffrenceTemp, int minTempInTank1, int histeresis, bool &pump1State, bool &pump2State, float SolarTemp, float Tank1Temp, float Tank2Temp);
	private:
	DigitalOut Pump1Relay;
	DigitalOut Pump2Relay;
	void pump1Logic(bool &pump1State, int diffrenceTemp, int histeresis, float SolarTemp, float Tank1Temp);
	void pump2Logic(bool &pump2State, int diffrenceTemp, int minTempInTank2,int histeresis, float Tank1Temp, float Tank2Temp);
};


#endif