#include "include.h"
#include <msp430.h>
#include "lcd1.h"
extern char paTable[];
extern char paTableLen;
char txBuffer[6];
char rxBuffer[6]={0};
char len=8;
unsigned int x,y,c,buffer[9]; //accelarometer
unsigned int i=0,j=0,c=0,mm,p;
unsigned int adc[11] = {0};	// This will hold the x,y and temp axis values
unsigned char x_upper_byte,x_lower_byte,y_upper_byte,y_lower_byte,c_upper_byte,c_lower_byte;

int test[10],rssi_dec=0,rssi_dbm=0,range=0;
long temp;
long IntDegC;
void confi(void);
void number(int);
char str1[6];

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
    while(TRUE)
        {
            TI_CC_SPIStrobe(TI_CCxxx0_SIDLE);
            TI_CC_SPIStrobe(0x34);           // Initialize CCxxxx in RX mode.
            	  	//send_string("rx");
            	  	//char len=2;                               // Len of pkt to be RXed (only addr
            	  	                                            // plus data; size byte not incl b/c
            	  	                                            // stripped away within RX function)
            	  p= RFReceivePacket(rxBuffer,&len);      // Fetch packet from CCxxxx
            	  for(c=0;c<9;c++){
            	  	buffer[c]=rxBuffer[c];
            	  }

                  test[8]=TI_CC_SPIReadStatus(TI_CCxxx0_LQI);
                  test[9]=TI_CC_SPIReadStatus(TI_CCxxx0_RSSI);
                  rssi_dec= test[9];
                  if( rssi_dec >= 128)
                  {
                	 rssi_dbm =  (rssi_dec-256)/2;
                	 rssi_dbm = rssi_dbm - 71 ;
                  }
                  else if(rssi_dec < 128)
                  {
                	  rssi_dbm =  (rssi_dec/2);
                	  rssi_dbm = rssi_dbm - 71 ;
                  }
            	  	  	  	x_upper_byte=buffer[1];
            	 	    	x_lower_byte= buffer[2];
            	 	    	y_upper_byte=buffer[3];
            	 	    	y_lower_byte= buffer[4];
            	 	    	c_upper_byte=buffer[6];
            	 	    	c_lower_byte= buffer[7];
            	 	    	x = (x_lower_byte << 8) | x_upper_byte;
            	 	    	y = (y_lower_byte << 8) | y_upper_byte;
            	 	    	c = (c_lower_byte << 8) | c_upper_byte;
range =1000-(rssi_dbm+1000);
				//TI_CC_SPIStrobe(TI_CCxxx0_SFRX);
            	  number(range);
            	  PrintStr("rssi");
            	  LcmSetCursorPosition(0,4);
            	  PrintStr(str1);
            	  LcmSetCursorPosition(0,4);
            	  PrintStr(" -");
            	  LcmSetCursorPosition(2,0);
        	      number(x);
            	  PrintStr("x:");
            	  PrintStr(str1);
            	  PrintStr("  y:");
            	  number(y);
            	  PrintStr(str1);
            	  number(c);
            	  LcmSetCursorPosition(0,11);
            	  PrintStr(str1);
        	   // TI_CC_GDO0_PxIFG &= ~TI_CC_GDO0_PIN;      // After pkt TX, this flag is set.
        	                                             // Clear it.
            	  __delay_cycles(1000000);
        		//TI_CC_SPIStrobe(TI_CCxxx0_SRES);
        		// TI_CC_SPIStrobe(TI_CCxxx0_SFRX);
        }        //__bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts
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
//lcd
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
