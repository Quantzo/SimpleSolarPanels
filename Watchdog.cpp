#include "Watchdog.h"
void Watchdog::setUp(float s)
{
  LPC_SYSCON->SYSAHBCLKCTRL = LPC_SYSCON->SYSAHBCLKCTRL|(1<<15);
  LPC_SYSCON->WDTCLKSEL = 0x1;                // Set CLK src to Main Clock
  LPC_SYSCON->WDTCLKUEN = 0x01;       /* Update clock */
  LPC_SYSCON->WDTCLKUEN = 0x00;       /* Toggle update register once */
  LPC_SYSCON->WDTCLKUEN = 0x01;
  LPC_SYSCON->WDTCLKDIV = 0x10;
  uint32_t clk = SystemCoreClock/16;    // WD has a fixed /4 prescaler, PCLK default is /4
  LPC_WDT->TC = s * (float)clk;
  LPC_WDT->MOD = 0x3;                   // Enabled and Reset
  this->kick();
}

void Watchdog::kick()
{
  LPC_WDT->FEED = 0xAA;
  LPC_WDT->FEED = 0x55;
}