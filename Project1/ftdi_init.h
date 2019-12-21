#pragma once
/*
 * Неправильно работает исправить. Положил 1 микросхему уже.
 */

extern const BYTE AA_ECHO_CMD_1;
extern const BYTE AB_ECHO_CMD_2;
extern const BYTE BAD_COMMAND_RESPONSE;

extern const BYTE MSB_VEDGE_CLOCK_IN_BIT;
extern const BYTE MSB_EDGE_CLOCK_OUT_BYTE;
extern const BYTE MSB_EDGE_CLOCK_IN_BYTE;


extern const BYTE MSB_FALLING_EDGE_CLOCK_BIT_OUT;
extern const BYTE MSB_FALLING_EDGE_CLOCK_BYTE_IN;
extern const BYTE MSB_FALLING_EDGE_CLOCK_BYTE_OUT;
extern const BYTE MSB_DOWN_EDGE_CLOCK_BIT_IN;
extern const BYTE MSB_UP_EDGE_CLOCK_BYTE_IN;
extern const BYTE MSB_UP_EDGE_CLOCK_BYTE_OUT;
extern const BYTE MSB_RISING_EDGE_CLOCK_BIT_IN;

extern FT_STATUS ftStatus;			//Status defined in D2XX to indicate operation result
extern FT_HANDLE ftHandle;			//Handle of FT2232H device port 
extern BYTE OutputBuffer[1024];		//Buffer to hold MPSSE commands and data to be sent to FT2232H
extern BYTE InputBuffer[1024];		//Buffer to hold Data bytes to be read from FT2232H
//DWORD dwClockDivisor = 0x004A;  	//Value of clock divisor, SCL Frequency = 60/((1+0x004A)*2) (MHz) = 400khz
extern DWORD dwClockDivisor;   //200khz
extern DWORD dwNumBytesToSend; 	//Index of output buffer
extern DWORD dwNumBytesSent, dwNumBytesRead, dwNumInputBuffer;

extern BYTE ByteDataRead;//ByteAddress
extern BYTE ByteAddresshigh, ByteAddresslow;		//EEPROM address is '0x0080'
extern BYTE ByteDataToBeSend;							//data programmed and read

void ClearBuffers();

void HighSpeedSetI2CStart(void);

void HighSpeedSetI2CStop(void);

bool I2C_SendByteGetACK(byte DataByte);

byte I2C_ReadByteSendACK();

byte I2C_ReadByteSendNACK();

//свиснуто из документации
BOOL FTDI_init(System::Windows::Forms::ToolStripStatusLabel ^ts);



bool i2c_send_byte_ftdi(int Testn, int ProdNum, I2CParams^ ParmsI2c, bool checked, bool synchrCheck, System::Windows::Forms::ToolStripStatusLabel ^ ts);

String^ i2c_read_ftdi(int testn, int ProdNum, double(*CABLE_KOEF)[2][3], double(*POWER_KOEF)[3], double(*POWER_CORRECT)[2][3], I2CParams^i2cp);