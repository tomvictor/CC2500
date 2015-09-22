#include "include.h"
#include <msp430.h>
#include "lcd.h"
#include "lcd1.h"

extern char paTable[];
extern char paTableLen;
char txBuffer[6];
char rxBuffer[6];
unsigned int x,y; //accelarometer
unsigned int i=0,j=0,c=0,mm,c_upper_byte,c_lower_byte;
unsigned int adc[11] = {0};	// This will hold the x,y and temp axis values
int test[8];
long temp;
long IntDegC;
unsigned char x_upper_byte,x_lower_byte,y_upper_byte,y_lower_byte;
void lcdfn(void);
void confi(void);
void delay(int);

void configWDT();
void configIO();
void configIR();
void configT();
void disableT();
void int_char();
void number(int);
void Setup_HW(void);		// Setup watchdog timer, clockc, ADC ports
void Read_Acc(void);	// This function reads the ADC and stores the x, y and z values


char str[4],str1[6];

void main(void)
{	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT


  // confi();
   //lcdfn();
    // 5ms delay to compensate for time to startup between MSP430 and CC1100/2500
    	__delay_cycles(1000000);
    	/* Port 1 Port Select 2 Register */
    	P1SEL2 = BIT5 | BIT6 | BIT7;
  	    /* Port 1 Port Select Register */
    	P1SEL = BIT5 | BIT6 | BIT7;
    	P2SEL &= ~(BIT6 | BIT7);
    	  Setup_HW();//adc config
    	TI_CC_SPISetup();                         // Initialize SPI port
    	TI_CC_PowerupResetCCxxxx();               // Reset CCxxxx
    	__delay_cycles(1000000);
    	writeRFSettings();                        // Write RF settings to config reg
    	TI_CC_SPIWriteBurstReg(TI_CCxxx0_PATABLE, paTable, paTableLen);//Write PATABLE
       test[0]=TI_CC_SPIReadReg(TI_CCxxx0_IOCFG2);
       test[1]=TI_CC_SPIReadReg(TI_CCxxx0_IOCFG0);
       test[2]=TI_CC_SPIReadReg(TI_CCxxx0_PKTLEN);
       test[3]=TI_CC_SPIReadReg(TI_CCxxx0_PKTCTRL1);
       test[4]=TI_CC_SPIReadReg(TI_CCxxx0_PKTCTRL0);
       test[5]= TI_CC_SPIReadReg(TI_CCxxx0_ADDR);
       test[6]=TI_CC_SPIReadStatus(TI_CCxxx0_PARTNUM);
       test[7]=TI_CC_SPIReadStatus(TI_CCxxx0_VERSION);
       //configWDT();
       configIO();
       configIR();
       InitializeLcm();
       ClearLcmScreen();
       PrintStr("      www    ");
   	LcmSetCursorPosition(0,0);
   	__delay_cycles(1000000);
   	LcmSetCursorPosition(0,0);
       PrintStr("       .     ");
      	LcmSetCursorPosition(0,0);
   	__delay_cycles(1000000);
       PrintStr("     build     ");
      	LcmSetCursorPosition(0,0);
   	__delay_cycles(1000000);
       PrintStr("     from    ");
      	LcmSetCursorPosition(0,0);
   	__delay_cycles(1000000);
       	PrintStr("     zero    ");
   	    LcmSetCursorPosition(0,0);
   	__delay_cycles(1000000);
   	    PrintStr("       .    ");
      	LcmSetCursorPosition(0,0);
   	__delay_cycles(1000000);
         PrintStr("      com    ");
     __delay_cycles(1000000);
   	LcmSetCursorPosition(0,0);
         PrintStr("Build from zero    ");
       LcmSetCursorPosition(2,0);
       PrintStr("by Tomvictor");
    __delay_cycles(3000000);

    if(test[0]==41)
       {
        ClearLcmScreen();
    	PrintStr("cc2500");
       	LcmSetCursorPosition(2,0);
       	PrintStr("initialised");
    	__delay_cycles(3000000);

       	}
    else
    {
    	ClearLcmScreen();
    	PrintStr("cc2500 not");
    	LcmSetCursorPosition(2,0);
    	PrintStr("initialised");
    	__delay_cycles(5000000);
    }
  //  TI_CC_GDO0_PxIES |= TI_CC_GDO0_PIN;       // Int on falling edge (end of pkt)
    //TI_CC_GDO0_PxIFG &= ~TI_CC_GDO0_PIN;      // Clear flag
   // TI_CC_GDO0_PxIE |= TI_CC_GDO0_PIN;        // Enable int on end of packet
    ClearLcmScreen();
while(1)
{
	//ClearLcmScreen();
	  //  	PrintStr("packet");
	 //   	LcmSetCursorPosition(2,0);
	//    	PrintStr("generating");
	   // 	__delay_cycles(500000);

	    	Read_Acc();	// This function reads the ADC and stores the x, y and z values
	        temp = adc[0];
	        IntDegC = ((temp - 673) * 423) / 1024;
	        x=adc[9];
	        y=adc[8];
	        number(IntDegC);
	    	//ClearLcmScreen();
	    	PrintStr("temp ");
	    	PrintStr(str1);
	    	LcmSetCursorPosition(2,0);
	        number(x);
	    	PrintStr("x:");
	    	PrintStr(str1);
	    	PrintStr("  y:");
	    	number(y);
	    	PrintStr(str1);
	    	x_upper_byte=x & 0xFF;
	    	x_lower_byte= x >> 8;
	    	y_upper_byte=y & 0xFF;
	    	y_lower_byte= y >> 8;
	    	c_upper_byte=c & 0xFF;
	    	c_lower_byte= c >> 8;
	    	/*
	    	unsigned short MyShort;
	    	unsigned char Char1; // lower byte
	    	unsigned char Char2; // upper byte
	    	// Split short into two char
	    	Char1 = MyShort & 0xFF;
	    	Char2 = MyShort >> 8;
	    	// merge two char into short
	    	MyShort = (Char2 << 8) | Char1;
	    	*/

	   TI_CC_SPIStrobe(TI_CCxxx0_SIDLE);
       TI_CC_SPIStrobe(TI_CCxxx0_STX);
       txBuffer[0] = 8;                           // Packet length
       txBuffer[1] = 1;                        // Packet address
       txBuffer[2] = x_upper_byte;     // (~TI_CC_SW_PxIN) & 0x0F;     // Load four switch inputs
       txBuffer[3] = x_lower_byte;
       txBuffer[4] = y_upper_byte;
       txBuffer[5] = y_lower_byte;
       txBuffer[6] = IntDegC;
       txBuffer[7] = c_upper_byte;
       txBuffer[8] = c_lower_byte;
       mm=txBuffer[2];
       RFSendPacket(txBuffer, 9);                 // Send value over RF
       c++;
    	//PrintStr("packet");
    	//LcmSetCursorPosition(2,0);
    	//PrintStr("send");
    	number(c);
       LcmSetCursorPosition(0,11);
        PrintStr(str1);
    	//__delay_cycles(500000);

}
//while
}//main

/*
#pragma vector=PORT1_VECTOR
__interrupt void port_ISR (void)
{
	if(P2IFG & TI_CC_GDO0_PIN)
	{
  char len=2;                               // Len of pkt to be RXed (only addr
                                            // plus data; size byte not incl b/c
                                            // stripped away within RX function)
  if (RFReceivePacket(rxBuffer,&len))       // Fetch packet from CCxxxx
	 vv = rxBuffer[1];         // Toggle LEDs according to pkt data

  TI_CC_GDO0_PxIFG &= ~TI_CC_GDO0_PIN;                 // Clear flag
}
}


*/


void confi(void)
{	        /* Port 1 Port Select 2 Register */
	        P1SEL2 = BIT5 | BIT6 | BIT7;
	        /* Port 1 Output Register */
	        P1OUT = 0;
	        /* Port 1 Port Select Register */
	        P1SEL = BIT5 | BIT6 | BIT7;
            /* Port 1 Direction Register */
	        P1DIR = BIT0|BIT2 | BIT4 | BIT5 | BIT7;
	        /* Port 1 Interrupt Edge Select Register */
	        //P1IES = BIT3;
	        /* Port 1 Interrupt Flag Register */
	       // P1IFG = BIT3;
	        /* Port 1 Interrupt Enable Register */
	       // P1IE = BIT3;
	        /* Port 2 Output Register */
	        P2OUT = 0;
	        /* Port 2 Port Select Register */
	        P2SEL &= ~(BIT6 | BIT7);
	        /* Port 2 Direction Register */
	        P2DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7;
	        /* Port 2 Interrupt Edge Select Register */
	        P2IES = 0;
	        /* Port 2 Interrupt Flag Register */
	        P2IFG = 0;
	        /* Port 2 Interrupt Enable Register */
	        P2IE = BIT1;
	        /* Port 3 Output Register */
	        P3OUT = 0;
	        /* Port 3 Direction Register */
	        P3DIR = 0;
}
void configWDT()
  {
	  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  }
void configIO()
{
	P2OUT=0x00;
P2DIR |=BIT3     ; //(BIT0 + BIT6);		// P1.0 output
}
void configIR() //sw
{
	  P1REN |= BIT0; // P2 Enable Pullup/Pulldown
	  P1OUT |= BIT0; // P2 pullup
	  P1IE |= BIT0; // P2 interrupt enabled
	  P1IES |= BIT0; // P2 Hi/lo falling edge
	  P1IFG &= ~(BIT0); // P2 IFG cleared just in case
	  _EINT();
}
void enablePulseIR() //inut
{
	  P2REN |= BIT0; // P2 Enable Pullup/Pulldown
	  P2OUT |= BIT0; // P2 pullup
	  P2IE |= BIT0; // P2 interrupt enabled
	  P2IES |= BIT0; // P2 Hi/lo falling edge
	  P2IFG &= ~(BIT0); // P2 IFG cleared just in case
//	  _EINT();
}
void disablePulseIR()//input
{
	  P2REN &= ~BIT0; // P2 Enable Pullup/Pulldown
	  P2OUT &= ~BIT0; // P2 pullup
	  P2IE &= ~BIT0; // P2 interrupt enabled
	  P2IES &= ~BIT0; // P2 Hi/lo falling edge
	  P2IFG |= (BIT0); // P2 IFG cleared just in case
}
void configT()
{
	CCTL0 = CCIE;                             // CCR0 interrupt enabled
	CCR0 = 50000;
	TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
}
void disableT()
{
	  TACTL = 0X00;
}
void delay(int a)
{
   	for(;a>0;a++)
   	_delay_cycles(7);
}
void printResult()
{
	int_char();
	ClearLcmScreen();
	PrintStr("HeartBeat/min :");
	LcmSetCursorPosition(2,0);
	PrintStr(str);
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	if(i<350) i++;
	else
	{
		P2OUT &= (~BIT3);                            // Toggle P1.0
		disableT();
		configIR();
		disablePulseIR();
		j=j*4;
		printResult();
		i=0;
		j=0;
	}
}
#pragma vector=PORT1_VECTOR  //sw
__interrupt void Port_1(void)
{
	if((P1IFG & 0x01) == 0x01)
	{
		P2OUT |= BIT3;
		configT();
		enablePulseIR();
		P1IFG &= ~BIT0;  //sw
		ClearLcmScreen();

		PrintStr("Please wait :");
}
}
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
			P2IE &= ~BIT0;
			j++;
			P2IE |= BIT0;
			P2IFG &= ~BIT0;
}
void int_char()
{
	int s;
	s=j%10;
	str[2]=(char)(s+48);
	j=j/10;
	s=j%10;
	str[1]=(char)(s+48);
	j=j/10;
	s=j%10;
	str[0]=(char)(s+48);
	str[3]='\0';
}

void number(int q)
{
int s;

	s=q%10;
	str1[4]=(char)(s+48);
	q=q/10;
	s=q%10;
	str1[3]=(char)(s+48);
	q=q/10;
	s=q%10;
	str1[2]=(char)(s+48);
	q=q/10;
	s=q%10;
	str1[1]=(char)(s+48);
	q=q/10;
	s=q%10;
	str1[0]=(char)(s+48);
	str1[5]='\0';
}

//adc
void Setup_HW(void)
{
	  ADC10CTL1 = INCH_10 + CONSEQ_1 +ADC10SSEL_2;            // A2/A1/A0, single sequence
	  ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + MSC + ADC10ON;
	  ADC10DTC1 = 0x0B;                         // 3 conversions
	  ADC10AE0 |= 0x0B;                         // Disable digital I/O on P1.0 to P1.2
}
void Read_Acc(void)
{
    ADC10CTL0 &= ~ENC;
    __delay_cycles(100);
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active

    __delay_cycles(100);
ADC10SA = (unsigned int)adc;			// Copies data in ADC10SA to unsigned int adc array
__delay_cycles(100);

ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
__delay_cycles(100);
}

void lcdfn(void)
{
lcd_init();
__delay_cycles(50000);
send_string("Medical Internet");
send_command(0xC0);
send_string("of Things");
__delay_cycles(50000000);
send_command(0x01);
__delay_cycles(50000);
send_string("Group Members");
__delay_cycles(30000000);
send_command(0x01);
__delay_cycles(50000);
send_string("Tom Victor,");
__delay_cycles(10000000);
send_string("Grace");
__delay_cycles(10000000);
send_command(0xc0);
send_string("Nithish,");
__delay_cycles(10000000);
send_string("Chippy");
__delay_cycles(30000000);
send_command(0x01);
__delay_cycles(50000);
send_string("Initializing");
send_command(0xC0);
send_string("CC2500");
__delay_cycles(5000000);
send_string(" .");
__delay_cycles(5000000);
send_string(" .");
__delay_cycles(5000000);
send_string(" .");
__delay_cycles(5000000);
send_string(" .");
__delay_cycles(5000000);
send_string(" .");
__delay_cycles(5000000);
send_command(0x01); // clear the screen
__delay_cycles(50000);
}
