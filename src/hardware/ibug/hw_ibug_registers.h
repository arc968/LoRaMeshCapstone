
//////////////////////RAK4600 Registers////////////////////////////
//RAK4600 Datasheet: https://dl-docs.rakwireless.com/api/render/?emulateScreenMedia=false&pdf.format=legal&url=https%3A%2F%2Fdocs.rakwireless.com%2FProduct-Categories%2FWisDuo%2FRAK4600-Module%2FDatasheet%2F
//Seen in the RAK4600 datasheet on page 2, the RAK4600 is split into two seperate processors:The SX1276-7-8 and the nRF52832

//////////SX1276-7-8 Registers///////////////
// SX1276-7-8 Datasheet: https://www.mouser.com/datasheet/2/761/sx1276-1278113.pdf

//Base Adresses
#define REGFIFO		 	0x00	//FIFO read/write access
#define REGOPMODE	 	0x01	//Operating mode & LoRaTM / FSK selection
#define REGBITRATEMSB	0x02	//Bit Rate setting, Most Significant Bits
#define REGBITRATELSB	0x03	//Bit Rate setting, Least Significant Bits
#define REGFDEVMSB		0x04	//Frequency Deviation setting, Most Significant Bits
#define REGFDEVLSB		0x05	//Frequency Deviation setting, Least Significant Bits


//Mode Definitions




//Configuration Macros





///////////nRF52832////////////////////////////
//nRF52832 Datasheet: https://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.0.pdf

//Base Adresses




//Mode Definitions




//Configuration Macros