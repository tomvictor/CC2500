//------------------------------------------------------------------------------
//  Description:  This file contains functions that configure the CC1100/2500
//  device.
//
//  Demo Application for MSP430/CC1100-2500 Interface Code Library v1.0
//
//  K. Quiring
//  Texas Instruments, Inc.
//  July 2006
//  IAR Embedded Workbench v3.41
//------------------------------------------------------------------------------
#include "include.h"
#include "TI_CC_CC1100-CC2500.h"
#include "cc2500_REG.h"
#include "cc2500_VAL.h"
//------------------------------------------------------------------------------
//  void writeRFSettings(void)
//
//  DESCRIPTION:
//  Used to configure the CCxxxx registers.  There are five instances of this
//  function, one for each available carrier frequency.  The instance compiled
//  is chosen according to the system variable TI_CC_RF_FREQ, assigned within
//  the header file "TI_CC_hardware_board.h".
//
//  ARGUMENTS:
//      none
//------------------------------------------------------------------------------

// Product = CC2500
// Crystal accuracy = 40 ppm
// X-tal frequency = 26 MHz
// RF output power = 0 dBm
// RX filterbandwidth = 540.000000 kHz
// Deviation = 0.000000
// Return state:  Return to RX state upon leaving either TX or RX
// Datarate = 250.000000 kbps
// Modulation = (7) MSK
// Manchester enable = (0) Manchester disabled
// RF Frequency = 2433.000000 MHz
// Channel spacing = 199.950000 kHz
// Channel number = 0
// Optimization = Sensitivity
// Sync mode = (3) 30/32 sync word bits detected
// Format of RX/TX data = (0) Normal mode, use FIFOs for RX and TX
// CRC operation = (1) CRC calculation in TX and CRC check in RX enabled
// Forward Error Correction = (0) FEC disabled
// Length configuration = (1) Variable length packets, packet length configured by the first received byte after sync word.
// Packetlength = 255
// Preamble count = (2)  4 bytes
// Append status = 1
// Address check = (0) No address check
// FIFO autoflush = 0
// Device address = 0
// GDO0 signal selection = ( 6) Asserts when sync word has been sent / received, and de-asserts at the end of the packet
// GDO2 signal selection = (11) Serial Clock
void writeRFSettings(void)
{
    // Write register settings
	TI_CC_SPIWriteReg(REG_IOCFG2,VAL_IOCFG2);
	      TI_CC_SPIWriteReg(REG_IOCFG1,VAL_IOCFG1);
	      TI_CC_SPIWriteReg(REG_IOCFG0,VAL_IOCFG0);

	      TI_CC_SPIWriteReg(REG_FIFOTHR,VAL_FIFOTHR);
	      TI_CC_SPIWriteReg(REG_SYNC1,VAL_SYNC1);
	      TI_CC_SPIWriteReg(REG_SYNC0,VAL_SYNC0);
	      TI_CC_SPIWriteReg(REG_PKTLEN,VAL_PKTLEN);
	      TI_CC_SPIWriteReg(REG_PKTCTRL1,VAL_PKTCTRL1);
	      TI_CC_SPIWriteReg(REG_PKTCTRL0,VAL_PKTCTRL0);
	      TI_CC_SPIWriteReg(REG_ADDR,VAL_ADDR);
	      TI_CC_SPIWriteReg(REG_CHANNR,VAL_CHANNR);
	      TI_CC_SPIWriteReg(REG_FSCTRL1,VAL_FSCTRL1);
	      TI_CC_SPIWriteReg(REG_FSCTRL0,VAL_FSCTRL0);
	      TI_CC_SPIWriteReg(REG_FREQ2,VAL_FREQ2);
	      TI_CC_SPIWriteReg(REG_FREQ1,VAL_FREQ1);
	      TI_CC_SPIWriteReg(REG_FREQ0,VAL_FREQ0);
	      TI_CC_SPIWriteReg(REG_MDMCFG4,VAL_MDMCFG4);
	      TI_CC_SPIWriteReg(REG_MDMCFG3,VAL_MDMCFG3);
	      TI_CC_SPIWriteReg(REG_MDMCFG2,VAL_MDMCFG2);
	      TI_CC_SPIWriteReg(REG_MDMCFG1,VAL_MDMCFG1);
	      TI_CC_SPIWriteReg(REG_MDMCFG0,VAL_MDMCFG0);
	      TI_CC_SPIWriteReg(REG_DEVIATN,VAL_DEVIATN);
	      TI_CC_SPIWriteReg(REG_MCSM2,VAL_MCSM2);
	      TI_CC_SPIWriteReg(REG_MCSM1,VAL_MCSM1);
	      TI_CC_SPIWriteReg(REG_MCSM0,VAL_MCSM0);
	      TI_CC_SPIWriteReg(REG_FOCCFG,VAL_FOCCFG);

	      TI_CC_SPIWriteReg(REG_BSCFG,VAL_BSCFG);
	      TI_CC_SPIWriteReg(REG_AGCCTRL2,VAL_AGCCTRL2);
	      TI_CC_SPIWriteReg(REG_AGCCTRL1,VAL_AGCCTRL1);
	      TI_CC_SPIWriteReg(REG_AGCCTRL0,VAL_AGCCTRL0);
	      TI_CC_SPIWriteReg(REG_WOREVT1,VAL_WOREVT1);
	      TI_CC_SPIWriteReg(REG_WOREVT0,VAL_WOREVT0);
	      TI_CC_SPIWriteReg(REG_WORCTRL,VAL_WORCTRL);
	      TI_CC_SPIWriteReg(REG_FREND1,VAL_FREND1);
	      TI_CC_SPIWriteReg(REG_FREND0,VAL_FREND0);
	      TI_CC_SPIWriteReg(REG_FSCAL3,VAL_FSCAL3);
	      TI_CC_SPIWriteReg(REG_FSCAL2,VAL_FSCAL2);
	      TI_CC_SPIWriteReg(REG_FSCAL1,VAL_FSCAL1);
	      TI_CC_SPIWriteReg(REG_FSCAL0,VAL_FSCAL0);
	      TI_CC_SPIWriteReg(REG_RCCTRL1,VAL_RCCTRL1);
	      TI_CC_SPIWriteReg(REG_RCCTRL0,VAL_RCCTRL0);
	      TI_CC_SPIWriteReg(REG_FSTEST,VAL_FSTEST);
	      TI_CC_SPIWriteReg(REG_PTEST,VAL_PTEST);
	      TI_CC_SPIWriteReg(REG_AGCTEST,VAL_AGCTEST);
	      TI_CC_SPIWriteReg(REG_TEST2,VAL_TEST2);
	      TI_CC_SPIWriteReg(REG_TEST1,VAL_TEST1);
	      TI_CC_SPIWriteReg(REG_TEST0,VAL_TEST0);
}

// PATABLE (0 dBm output power)
extern char paTable[] = {0xFF};
extern char paTableLen = 1;

//-----------------------------------------------------------------------------
//  void RFSendPacket(char *txBuffer, char size)
//
//  DESCRIPTION:
//  This function transmits a packet with length up to 63 bytes.  To use this
//  function, GD00 must be configured to be asserted when sync word is sent and
//  de-asserted at the end of the packet, which is accomplished by setting the
//  IOCFG0 register to 0x06, per the CCxxxx datasheet.  GDO0 goes high at
//  packet start and returns low when complete.  The function polls GDO0 to
//  ensure packet completion before returning.
//
//  ARGUMENTS:
//      char *txBuffer
//          Pointer to a buffer containing the data to be transmitted
//
//      char size
//          The size of the txBuffer
//-----------------------------------------------------------------------------
void RFSendPacket(char *txBuffer, char size)
{
  TI_CC_SPIWriteBurstReg(TI_CCxxx0_TXFIFO, txBuffer, size); // Write TX data
  TI_CC_SPIStrobe(TI_CCxxx0_STX);           // Change state to TX, initiating
                                            // data transfer
  __delay_cycles(1000000);

  //while (!(TI_CC_GDO0_PxIN&TI_CC_GDO0_PIN));
                                            // Wait GDO0 to go hi -> sync TX'ed
  //while (TI_CC_GDO0_PxIN&TI_CC_GDO0_PIN);
                                            // Wait GDO0 to clear -> end of pkt
 // TI_CC_GDO0_PxIFG &= ~TI_CC_GDO0_PIN;      // After pkt TX, this flag is set.
                                            // Has to be cleared before existing
}



//-----------------------------------------------------------------------------
//  char RFReceivePacket(char *rxBuffer, char *length)
//
//  DESCRIPTION:
//  Receives a packet of variable length (first byte in the packet must be the
//  length byte).  The packet length should not exceed the RXFIFO size.  To use
//  this function, APPEND_STATUS in the PKTCTRL1 register must be enabled.  It
//  is assumed that the function is called after it is known that a packet has
//  been received; for example, in response to GDO0 going low when it is
//  configured to output packet reception status.
//
//  The RXBYTES register is first read to ensure there are bytes in the FIFO.
//  This is done because the GDO signal will go high even if the FIFO is flushed
//  due to address filtering, CRC filtering, or packet length filtering.
//
//  ARGUMENTS:
//      char *rxBuffer
//          Pointer to the buffer where the incoming data should be stored
//      char *length
//          Pointer to a variable containing the size of the buffer where the
//          incoming data should be stored. After this function returns, that
//          variable holds the packet length.
//
//  RETURN VALUE:
//      char
//          0x80:  CRC OK
//          0x00:  CRC NOT OK (or no pkt was put in the RXFIFO due to filtering)
//-----------------------------------------------------------------------------
char RFReceivePacket(char *rxBuffer, char *length)
{
  char status[2];
  char pktLen;

  if ((TI_CC_SPIReadStatus(TI_CCxxx0_RXBYTES) & TI_CCxxx0_NUM_RXBYTES))
  {
    pktLen = TI_CC_SPIReadReg(TI_CCxxx0_RXFIFO); // Read length byte

    if (pktLen <= *length)                  // If pktLen size <= rxBuffer
    {
      TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, rxBuffer, pktLen); // Pull data
      *length = pktLen;                     // Return the actual size
      TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, status, 2);
                                            // Read appended status bytes
      return (char)(status[TI_CCxxx0_LQI_RX]&TI_CCxxx0_CRC_OK);
    }                                       // Return CRC_OK bit
    else
    {
      *length = pktLen;                     // Return the large size
      TI_CC_SPIStrobe(TI_CCxxx0_SFRX);      // Flush RXFIFO
      return 0;                             // Error
    }
  }
  else
      return 0;                             // Error
}




