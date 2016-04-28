// 0.Documentation Section 
// SoftSound.c
// Runs on LM4F120 or TM4C123
// Use the SysTick timer to request interrupts at 500Hz.
// Jonathan Valvano
// November 3, 2013

#include "PLL.h"
#include "tm4c123gh6pm.h"
// Constant declarations to access port registers using 
// symbolic names instead of addresses

void SysTick_Wait10ms(unsigned long delay);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
void PortA_Init(void);        // start sound output
void PortB_Init(void);
void PortD_Init(void);
void SysInit(void);
void SysLoad(unsigned long period);
unsigned int i=0;
// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void){
  PLL_Init(); 
  SysInit();
 PortB_Init();
  	 PortA_Init();        // start sound output
      PortD_Init();

	while(1)
	{ if((GPIO_PORTD_DATA_R&0x01)== 0 &&(GPIO_PORTB_DATA_R&0x01)== 0 )
{ GPIO_PORTA_DATA_R&=0x00;
	GPIO_PORTA_DATA_R|=0x14;
}



if((GPIO_PORTD_DATA_R&0x01)== 1 && (GPIO_PORTB_DATA_R&0x01)==0 )
{   GPIO_PORTA_DATA_R&=0x00; 
	GPIO_PORTA_DATA_R|=0x18     ;      
SysTick_Wait10ms(10);
	
}
	
  	
	if((GPIO_PORTD_DATA_R&0x01)== 0 && (GPIO_PORTB_DATA_R&0x01)==1 )
{   GPIO_PORTA_DATA_R&=0x00;
	
	GPIO_PORTA_DATA_R|=0x24;      
	
  SysTick_Wait10ms(10);}
	
	
      
	 	if((GPIO_PORTD_DATA_R&0x01)== 1 && (GPIO_PORTB_DATA_R&0x01)==1 )
{   GPIO_PORTA_DATA_R&=0x00;
	
	GPIO_PORTA_DATA_R|=0x28;      
	
  SysTick_Wait10ms(10);}
	
}


}


void PortB_Init(void)
{
unsigned long volatile delay;
   SYSCTL_RCGC2_R |= 0x02;           // 1) activate clock for Port A
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
                                    // 2) no need to unlock PA2
  GPIO_PORTB_PCTL_R &= ~0x00000F00; // 3) regular GPIO
  GPIO_PORTB_AMSEL_R &= ~0x04;      // 4) disable analog function on PA2
  GPIO_PORTB_DIR_R&= 0x00;         // 5) set direction to output
  GPIO_PORTB_AFSEL_R &= ~0x04;      // 6) regular port function
  GPIO_PORTB_DEN_R |= 0x01;         // 7) enable digital port
}






void PortA_Init(void)
	
{ unsigned long volatile delay;
   SYSCTL_RCGC2_R |= 0x01;           // 1) activate clock for Port A
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
                                    // 2) no need to unlock PA2
  GPIO_PORTA_PCTL_R &= ~0x00000F00; // 3) regular GPIO
  GPIO_PORTA_AMSEL_R &= ~0x04;      // 4) disable analog function on PA2
  GPIO_PORTA_DIR_R |= 0x3c;         // 5) set direction to output
  GPIO_PORTA_AFSEL_R &= ~0x04;      // 6) regular port function
  GPIO_PORTA_DEN_R |= 0x3c;         // 7) enable digital port
}

void PortD_Init(void)

{unsigned long volatile delay;
SYSCTL_RCGC2_R |= 0x08;           // 1) activate clock for Port A
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
                                    // 2) no need to unlock PA2
  GPIO_PORTD_PCTL_R &= ~0x00000F00; // 3) regular GPIO
  GPIO_PORTD_AMSEL_R &= ~0x04;      // 4) disable analog function on PA2
  GPIO_PORTD_DIR_R &= 0x00;         // 5) set direction to output
  GPIO_PORTD_AFSEL_R &= ~0x04;      // 6) regular port function
  GPIO_PORTD_DEN_R |= 0x03;         // 7) enable digital port
}



void SysLoad(unsigned long period){

	
	NVIC_ST_RELOAD_R = period-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
	
}

void SysInit(void){
	
	NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;
          
} 

void SysTick_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<=delay; i++){
    SysLoad(8000);  // wait 10ms
  }
}




