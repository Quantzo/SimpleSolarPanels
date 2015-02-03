#include "LogicEngine.h"

void LogicEngine::pump1Logic(bool &pump1State, int diffrenceTemp, int histeresis, float SolarTemp, float Tank1Temp)
{
	if((SolarTemp-Tank1Temp)>(diffrenceTemp + histeresis))
	{
		this->Pump1Relay = 0;
		pump1State = true;
	}
	else if((SolarTemp-Tank1Temp)<(diffrenceTemp - histeresis))
	{
		this->Pump1Relay = 1;
		pump1State =  false;
	}
}

void LogicEngine::pump2Logic(bool &pump2State, int diffrenceTemp, int minTempInTank1,int histeresis, float Tank1Temp, float Tank2Temp)
{
	if(Tank1Temp > minTempInTank1)
	{
		if((Tank1Temp-Tank2Temp)>(diffrenceTemp + histeresis))
		{
			this->Pump2Relay = 0;
			pump2State = true;
		}
		else if((Tank1Temp-Tank2Temp)<(diffrenceTemp - histeresis))
		{
			this->Pump2Relay = 1;
			pump2State = false;
		}
	}
	else
	{
		if(Tank1Temp < minTempInTank1 - histeresis)
		{
		  this->Pump2Relay = 1;
			pump2State = false;
		}		
	}
}

void LogicEngine::exexute(int diffrenceTemp, int minTempInTank1, int histeresis, bool &pump1State, bool &pump2State, float SolarTemp, float Tank1Temp, float Tank2Temp)
{
	pump1Logic(pump1State,diffrenceTemp,histeresis,SolarTemp,Tank1Temp);
	pump2Logic(pump2State,diffrenceTemp,minTempInTank1,histeresis,Tank1Temp,Tank2Temp);
}

LogicEngine::LogicEngine(PinName Pump1Relay, PinName Pump2Relay):Pump1Relay(Pump1Relay),Pump2Relay(Pump2Relay)
{
  this->Pump1Relay = 1;
  this->Pump2Relay = 1;
}