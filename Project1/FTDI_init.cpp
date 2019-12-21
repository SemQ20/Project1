#include "stdafx.h"
#include <windows.h>
#include "namespaces.h"
#include "arrays.h"
//============================================================================
//  Use of FTDI D2XX library:
//----------------------------------------------------------------------------
//  Include the following 2 lines in your header-file
#pragma comment(lib, "ftd2xx.lib")
//============================================================================
#include "ftd2xx.h"
#include "ConvertResI2C.h"
#include "PowerCorrect.h"
#include "IPZO2Tests.h"
#include "IPZO3Tests.h"
#include "IPZO4Tests.h"
#include "IPZO5Tests.h"
#include "ftdi_init.h"

const BYTE AA_ECHO_CMD_1 = 0xAA;
const BYTE AB_ECHO_CMD_2 = 0xAB;
const BYTE BAD_COMMAND_RESPONSE = 0xFA;

const BYTE MSB_VEDGE_CLOCK_IN_BIT = 0x22;
const BYTE MSB_EDGE_CLOCK_OUT_BYTE = 0x11;
const BYTE MSB_EDGE_CLOCK_IN_BYTE = 0x24;

const BYTE MSB_FALLING_EDGE_CLOCK_BIT_OUT = 0x13;
const BYTE MSB_FALLING_EDGE_CLOCK_BYTE_IN = 0x24;
const BYTE MSB_FALLING_EDGE_CLOCK_BYTE_OUT = 0x11;
const BYTE MSB_DOWN_EDGE_CLOCK_BIT_IN = 0x26;
const BYTE MSB_UP_EDGE_CLOCK_BYTE_IN = 0x20;
const BYTE MSB_UP_EDGE_CLOCK_BYTE_OUT = 0x10;
const BYTE MSB_RISING_EDGE_CLOCK_BIT_IN = 0x22;

FT_STATUS ftStatus;
FT_HANDLE ftHandle;
BYTE OutputBuffer[1024];
BYTE InputBuffer[1024];

DWORD dwClockDivisor = 0x0095;
DWORD dwNumBytesToSend = 0;
DWORD dwNumBytesSent = 0, dwNumBytesRead=0, dwNumInputBuffer=0;
BYTE ByteDataRead;
BYTE ByteAddresshigh = 0x00, ByteAddresslow = 0x80;
BYTE ByteDataToBeSend = 0x5A;

void ClearBuffers()
{
	dwNumBytesToSend = 0; //Index of output buffer
	dwNumBytesSent = 0;
	dwNumBytesRead = 0;
	dwNumInputBuffer = 0;
	for (int i = 0; i < 1024; i++)
		InputBuffer[i] = 0;
	for (int i = 0; i < 1024; i++)
		OutputBuffer[i] = 0;
}

void HighSpeedSetI2CStart(void)
{
	DWORD dwCount;
	for (dwCount = 0; dwCount < 4; dwCount++)	// Repeat commands to ensure the minimum period of the start hold time ie 600ns is achieved
	{
		OutputBuffer[dwNumBytesToSend++] = 0x80;	//Command to set directions of lower 8 pins and force value on bits set as output
		OutputBuffer[dwNumBytesToSend++] = 0x03;  //Set SDA, SCL high, WP disabled by SK, DO at bit Ў®1ЎЇ, GPIOL0 at bit Ў®0ЎЇ
		OutputBuffer[dwNumBytesToSend++] = 0x13;	//Set SK,DO,GPIOL0 pins as output with bit ЎЇ1ЎЇ, other pins as input with bit Ў®0ЎЇ
	}
	for (dwCount = 0; dwCount < 4; dwCount++)	// Repeat commands to ensure the minimum period of the start setup time ie 600ns is achieved
	{
		OutputBuffer[dwNumBytesToSend++] = 0x80; 	//Command to set directions of lower 8 pins and force value on bits set as output
		OutputBuffer[dwNumBytesToSend++] = 0x01; 	//Set SDA low, SCL high, WP disabled by SK at bit Ў®1ЎЇ, DO, GPIOL0 at bit Ў®0ЎЇ
		OutputBuffer[dwNumBytesToSend++] = 0x13;	//Set SK,DO,GPIOL0 pins as output with bit ЎЇ1ЎЇ, other pins as input with bit Ў®0ЎЇ
	}
	OutputBuffer[dwNumBytesToSend++] = 0x80; 	//Command to set directions of lower 8 pins and force value on bits set as output
	OutputBuffer[dwNumBytesToSend++] = 0x00; 	//Set SDA, SCL low high, WP disabled by SK, DO, GPIOL0 at bit Ў®0ЎЇ
	OutputBuffer[dwNumBytesToSend++] = 0x13;	//Set SK,DO,GPIOL0 pins as output with bit ЎЇ1ЎЇ, other pins as input with bit Ў®0ЎЇ
}

void HighSpeedSetI2CStop(void)
{
	DWORD dwCount;
	for (dwCount = 0; dwCount < 4; dwCount++)	// Repeat commands to ensure the minimum period of the stop setup time ie 600ns is achieved
	{
		OutputBuffer[dwNumBytesToSend++] = 0x80; 	//Command to set directions of lower 8 pins and force value on bits set as output
		OutputBuffer[dwNumBytesToSend++] = 0x01; 	//Set SDA low, SCL high, WP disabled by SK at bit Ў®1ЎЇ, DO, GPIOL0 at bit Ў®0ЎЇ
		OutputBuffer[dwNumBytesToSend++] = 0x03;	//Set SK,DO,GPIOL0 pins as output with bit ЎЇ1ЎЇ, other pins as input with bit Ў®0ЎЇ
	}
	for (dwCount = 0; dwCount < 4; dwCount++)	// Repeat commands to ensure the minimum period of the stop hold time ie 600ns is achieved
	{
		OutputBuffer[dwNumBytesToSend++] = 0x80; 	//Command to set directions of lower 8 pins and force value on bits set as output
		OutputBuffer[dwNumBytesToSend++] = 0x03; 	//Set SDA, SCL high, WP disabled by SK, DO at bit Ў®1ЎЇ, GPIOL0 at bit Ў®0ЎЇ
		OutputBuffer[dwNumBytesToSend++] = 0x03;	//Set SK,DO,GPIOL0 pins as output with bit ЎЇ1ЎЇ, other pins as input with bit Ў®0ЎЇ
	}
	//Tristate the SCL, SDA pins
	OutputBuffer[dwNumBytesToSend++] = 0x80; 	//Command to set directions of lower 8 pins and force value on bits set as output
	OutputBuffer[dwNumBytesToSend++] = 0x00; 	//Set WP disabled by GPIOL0 at bit 0ЎЇ
	OutputBuffer[dwNumBytesToSend++] = 0x00;	//Set GPIOL0 pins as output with bit ЎЇ1ЎЇ, SK, DO and other pins as input with bit Ў®0ЎЇ
}

bool I2C_SendByteGetACK(byte DataByte)
{
	//Preset buffer to ouput mode
	// [MPSSE Set data bits low Byte(==SK,DO,DI,CS,GPIOL1...)
	// + 0x00 = All other pins Low-GND(0)
	// + 0x13 = SK+DO+GPIOL1(Output),all other pins(Input)]
	OutputBuffer[dwNumBytesToSend] = 0x80;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x13;
	dwNumBytesToSend += 1;

	//Add commands to buffer.
	//[MPSSE Send byte command + 2 bytes for count(0x0000=1byte to send) + DataByte to send]
	OutputBuffer[dwNumBytesToSend] = MSB_FALLING_EDGE_CLOCK_BYTE_OUT;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = DataByte;
	dwNumBytesToSend += 1;

	//Add another command to buffer. Need to check for ACK
	//Set Pin states for input mode, send get bit command.
	// [MPSSE Set data bits low Byte(==SK,DO,DI,CS,GPIOL1...)
	// + 0x00 = All pins Low-GND(0)
	// + 0x11 = SK+GPIOL1(Output),all other pins(Input)]
	//Check for ACK
	OutputBuffer[dwNumBytesToSend] = 0x80;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x11;
	dwNumBytesToSend += 1;

	//MPSSE Get 1 Bit command. 0x00 = 1Bit to get.
	OutputBuffer[dwNumBytesToSend] = MSB_RISING_EDGE_CLOCK_BIT_IN; ;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	//MPSSE command. Process and return data immediately.
	OutputBuffer[dwNumBytesToSend] = 0x87;
	dwNumBytesToSend += 1;

	//Buffer is complete with all commands. Ready to fire down the wire.
	//FT_STATUS = WriteFTDIAsBytes();
	ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
	if (ftStatus != FT_OK)
		return false;


	dwNumBytesToSend = 0;/////////////////////////    
	System::Threading::Thread::Sleep(20);
	if (dwNumInputBuffer == 0)
		//FT_STATUS = GetRXBytesInputBuffer();
		ftStatus = FT_Read(ftHandle, InputBuffer, dwNumInputBuffer, &dwNumBytesRead);

	if ((ftStatus != FT_OK) || (dwNumInputBuffer == 0))
	{ /*Error, can't get the ACK bit from EEPROM */

		return false;
	}
	else
		if (((InputBuffer[0] & (byte)(0x1)) != (byte)(0x0))) //Check ACK bit 0 on data byte read out
		{
			return false; /*Error, can't get the ACK bit from EEPROM */
		}

	return true;
	ClearBuffers();
}

byte I2C_ReadByteSendACK()
{
	byte returnByte = 0;

	//Set Pins for Input mode. Set command to read Byte.
	// [MPSSE Set data bits low Byte(==SK,DO,DI,CS,GPIOL1...)
	// + 0x00 = All pins Low-GND(0)
	// + 0x11 = SK+GPIOL1(Output),all other pins(Input)]
	OutputBuffer[dwNumBytesToSend] = 0x80;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x11;
	dwNumBytesToSend += 1;

	//MPSSE Command get byte.
	// [0x0000 == Get 1 Byte] Send Low byte, then High byte for command.
	OutputBuffer[dwNumBytesToSend] = MSB_FALLING_EDGE_CLOCK_BYTE_IN;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;

	//We received our byte, lets ACK to the EEPROM.
	//Setup Pins for Output mode.
	//SCL=OUTPUT[________]low
	//SDA=OUTPUT[________]low
	OutputBuffer[dwNumBytesToSend] = 0x80;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x13;
	dwNumBytesToSend += 1;

	//MPSSE Send 1 Bit command. 0x00 = 1Bit to send, 0x00 = The bit value to send.
	//ACK = 0, NACK = 1. If we wanted to NACK we would send [Command(Send 1 BIT), 0x00(Num of Bits(0x00=1)), 0x80(0b10000000)] Command sends MSB FIRST!!! Hence 0x80....
	//(Command clocks MSB FIRST of bit value. so 0x00 = 0b00000000. I'm sending 1 bit. SDO will = 0/0v/LOW == I2C ACK)
	OutputBuffer[dwNumBytesToSend] = MSB_FALLING_EDGE_CLOCK_BIT_OUT;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;

	//MPSSE command. Process and return data immediately.
	OutputBuffer[dwNumBytesToSend] = 0x87;
	dwNumBytesToSend += 1;

	//Send buffer and see if we get a byte.
	ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
	if (ftStatus != FT_OK)
		return 0;

	if (dwNumInputBuffer == 0)
		//FT_STATUS = GetRXBytesInputBuffer();
		ftStatus = FT_Read(ftHandle, InputBuffer, dwNumInputBuffer, &dwNumBytesRead);

	if ((ftStatus != FT_OK) || (dwNumInputBuffer == 0))
	{ /*Error, can't get the ACK bit from EEPROM */
		return 0;
	}

	returnByte = InputBuffer[0];
	ClearBuffers();
	return returnByte;
}

byte I2C_ReadByteSendNACK()
{
	byte returnByte = 0;

	//Set Pins for Input mode. Set command to read Byte.
	// [MPSSE Set data bits low Byte(==SK,DO,DI,CS,GPIOL1...)
	// + 0x00 = All pins Low-GND(0)[________]
	// + 0x11 = SK+GPIOL1(Output),all other pins(Input)]
	OutputBuffer[dwNumBytesToSend] = 0x80;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x11;
	dwNumBytesToSend += 1;

	//MPSSE Command get byte.
	// [0x0000 == Get 1 Byte] Send Low byte, then High byte for command.
	OutputBuffer[dwNumBytesToSend] = MSB_FALLING_EDGE_CLOCK_BYTE_IN;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;

	//We received our byte, lets NACK to the EEPROM. Dont send any more data...
	//Setup Pins for Output mode.
	//SCL=OUTPUT[________]low
	//DA=OUTPUT[________]low
	OutputBuffer[dwNumBytesToSend] = 0x80;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x13;
	dwNumBytesToSend += 1;

	//MPSSE Send 1 Bit command. 0x00 = 1Bit to send, 0x80 = The bit value to send.
	//ACK = 0, NACK = 1. If we wanted to NACK we would send [Command(Send 1 BIT), 0x00(Num of Bits(0x00=1)), 0x80(0b10000000)] Command sends MSB FIRST!!! Hence 0x80....
	//(Command clocks MSB FIRST of bit value. so 0x80 = 0b10000000. I'm sending 1 bit. SDO will = 1/3.3v/HIGH == I2C NACK)
	OutputBuffer[dwNumBytesToSend] = MSB_FALLING_EDGE_CLOCK_BIT_OUT;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x0;
	dwNumBytesToSend += 1;
	OutputBuffer[dwNumBytesToSend] = 0x80;
	dwNumBytesToSend += 1;

	//MPSSE command. Process and return data immediately.
	OutputBuffer[dwNumBytesToSend] = 0x87;
	dwNumBytesToSend += 1;

	//Send buffer and check if we get a byte.
	ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
	if (ftStatus != FT_OK)
		return 0;

	ClearBuffers();
	while (dwNumInputBuffer == 0)
		//FT_STATUS = GetRXBytesInputBuffer();
		ftStatus = FT_Read(ftHandle, InputBuffer, dwNumInputBuffer, &dwNumBytesRead);

	if ((ftStatus != FT_OK) || (dwNumInputBuffer == 0))
	{ /*Error, can't get the ACK bit from EEPROM */
		return 0;
	}

	returnByte = InputBuffer[0];
	ClearBuffers();
	return returnByte;
}

BOOL FTDI_init(System::Windows::Forms::ToolStripStatusLabel ^ ts)
{
	DWORD dwCount;
	DWORD devIndex = 0;
	char Buf[64];
	DWORD numDevs;
	ftStatus = FT_ListDevices(&numDevs, NULL, FT_LIST_NUMBER_ONLY);
	ftStatus = FT_ListDevices((PVOID)devIndex, &Buf, FT_LIST_BY_INDEX | FT_OPEN_BY_SERIAL_NUMBER);
	ftStatus = FT_OpenEx(&Buf, FT_OPEN_BY_SERIAL_NUMBER, &ftHandle);

	if (ftStatus != FT_OK)
	{
		ts->Text = "Can't open FT2232H device!";
		return false;
	}
	else
	{      // Port opened successfully
		ts->Text = "Successfully open FT2232H device!";
	}

	//FT_HANDLE ftHandle2;
	//FT_STATUS ftStatus2;
	//ftStatus2 = FT_Open(1, &ftHandle2);
	//if (ftStatus2 != FT_OK)
	//{
	//	ts->Text = "Can't open FT2232H device %d!";
	//	return false;
	//}
	FT_PROGRAM_DATA ftData1, ftData2;

	char ManufacturerBuf[32];
	char ManufacturerIdBuf[16];
	char DescriptionBuf[64];
	char SerialNumberBuf[16];

	char ManufacturerBuf2[32];
	char ManufacturerIdBuf2[16];
	char DescriptionBuf2[64];
	char SerialNumberBuf2[16];
	char Desstr1[16] = "USB test1";
	char Desstr2[16] = "USB test2";

	ftData1.Signature1 = 0x00000000;
	ftData1.Signature2 = 0xffffffff;
	ftData1.Version = 0x00000001; // EEPROM structure with FT4232H extensions 
	ftData1.Manufacturer = ManufacturerBuf;
	ftData1.ManufacturerId = ManufacturerIdBuf;
	ftData1.Description = DescriptionBuf;
	ftData1.SerialNumber = SerialNumberBuf;

	ftData2.Signature1 = 0x00000000;
	ftData2.Signature2 = 0xffffffff;
	ftData2.Version = 0x00000001; // EEPROM structure with FT4232H extensions 
	ftData2.Manufacturer = ManufacturerBuf2;
	ftData2.ManufacturerId = ManufacturerIdBuf2;
	ftData2.Description = DescriptionBuf2;
	ftData2.SerialNumber = SerialNumberBuf2;

	ftStatus = FT_EraseEE(ftHandle);
	Sleep(100);
	ftStatus = FT_EE_Read(ftHandle, &ftData1);

	/*ftStatus = FT_EraseEE(ftHandle2);
	Sleep(100);
	ftStatus2 = FT_EE_Read(ftHandle2, &ftData2);*/

	strcpy(ftData1.Description, Desstr1);

	ftStatus = FT_EE_Program(ftHandle, &ftData1);
	Sleep(100);
	ftStatus = FT_EE_Read(ftHandle, &ftData1);

	ftStatus |= FT_GetQueueStatus(ftHandle, &dwNumInputBuffer);	 // Get the number of bytes in the FT2232H receive buffer

	ftStatus |= FT_ResetDevice(ftHandle); 	//Reset USB device
		//Purge USB receive buffer first by reading out all old data from FT2232H receive buffer
	ftStatus |= FT_GetQueueStatus(ftHandle, &dwNumInputBuffer);	 // Get the number of bytes in the FT2232H receive buffer
	if ((ftStatus == FT_OK) && (dwNumInputBuffer > 0))
		FT_Read(ftHandle, &InputBuffer, dwNumInputBuffer, &dwNumBytesRead);  	//Read out the data from FT2232H receive buffer
	ftStatus |= FT_SetUSBParameters(ftHandle, 65536, 65535);	//Set USB request transfer size
	ftStatus |= FT_SetChars(ftHandle, false, 0, false, 0);	 //Disable event and error characters
	ftStatus |= FT_SetTimeouts(ftHandle, 0, 5000);		//Sets the read and write timeouts in milliseconds for the FT2232H
	ftStatus |= FT_SetLatencyTimer(ftHandle, 16);		//Set the latency timer
	ftStatus |= FT_SetBitMode(ftHandle, 0x0, 0x00); 		//Reset controller
	ftStatus |= FT_SetBitMode(ftHandle, 0x0, 0x02);	 	//Enable MPSSE mode

	if (ftStatus != FT_OK)
	{
		ts->Text = "fail on initialize FT2232H device !";
	}
	Sleep(50);	// Wait for all the USB stuff to complete and work
	OutputBuffer[dwNumBytesToSend++] = 0xAA;		//Add BAD command Ў®0xAAЎЇ
	ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);	// Send off the BAD commands
	dwNumBytesToSend = 0;			//Clear output buffer
	do {
		ftStatus = FT_GetQueueStatus(ftHandle, &dwNumInputBuffer);	 // Get the number of bytes in the device input buffer
	} while ((dwNumInputBuffer == 0) && (ftStatus == FT_OK));   	//or Timeout

	bool bCommandEchod = false;
	ftStatus = FT_Read(ftHandle, &InputBuffer, dwNumInputBuffer, &dwNumBytesRead);  //Read out the data from input buffer
	for (dwCount = 0; dwCount < dwNumBytesRead - 1; dwCount++)	//Check if Bad command and echo command received
	{
		if ((InputBuffer[dwCount] == BYTE(0xFA)) && (InputBuffer[dwCount + 1] == BYTE(0xAA)))
		{
			bCommandEchod = true;
			break;
		}
	}
	if (bCommandEchod == false)
	{
		ts->Text = "fail to synchronize MPSSE with command '0xAA'";
	}

	//////////////////////////////////////////////////////////////////
	// Synchronize the MPSSE interface by sending bad command Ў®0xABЎЇ
	//////////////////////////////////////////////////////////////////
	//dwNumBytesToSend = 0;			//Clear output buffer
	OutputBuffer[dwNumBytesToSend++] = 0xAB;	//Send BAD command Ў®0xABЎЇ
	ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);	// Send off the BAD commands
	dwNumBytesToSend = 0;			//Clear output buffer
	do {
		ftStatus = FT_GetQueueStatus(ftHandle, &dwNumInputBuffer);	//Get the number of bytes in the device input buffer
	} while ((dwNumInputBuffer == 0) && (ftStatus == FT_OK));   //or Timeout
	bCommandEchod = false;
	ftStatus = FT_Read(ftHandle, &InputBuffer, dwNumInputBuffer, &dwNumBytesRead);  //Read out the data from input buffer
	for (dwCount = 0; dwCount < dwNumBytesRead - 1; dwCount++)	//Check if Bad command and echo command received
	{
		if ((InputBuffer[dwCount] == BYTE(0xFA)) && (InputBuffer[dwCount + 1] == BYTE(0xAB)))
		{
			bCommandEchod = true;
			break;
		}
	}
	if (bCommandEchod == false)
	{
		ts->Text = "fail to synchronize MPSSE with command '0xAB'";
		/*Error, canЎЇt receive echo command , fail to synchronize MPSSE interface;*/
	}

	ts->Text = "MPSSE synchronized with BAD command";

	////////////////////////////////////////////////////////////////////
	//Configure the MPSSE for I2C communication with 24LC02B
	//////////////////////////////////////////////////////////////////
	OutputBuffer[dwNumBytesToSend++] = 0x8A; 	//Ensure disable clock divide by 5 for 60Mhz master clock
	OutputBuffer[dwNumBytesToSend++] = 0x97;	 //Ensure turn off adaptive clocking
	OutputBuffer[dwNumBytesToSend++] = 0x8D; 	//Enable 3 phase data clock, used by I2C to allow data on both clock edges
	ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);	// Send off the commands
	dwNumBytesToSend = 0;			//Clear output buffer
	OutputBuffer[dwNumBytesToSend++] = 0x80; 	//Command to set directions of lower 8 pins and force value on bits set as output 
	OutputBuffer[dwNumBytesToSend++] = 0x03; 	//Set SDA, SCL high, WP disabled by SK, DO at bit Ў®1ЎЇ, GPIOL0 at bit Ў®0ЎЇ
	OutputBuffer[dwNumBytesToSend++] = 0x13;	//Set SK,DO,GPIOL0 pins as output with bit ЎЇ1ЎЇ, other pins as input with bit Ў®0ЎЇ
	// The SK clock frequency can be worked out by below algorithm with divide by 5 set as off
	// SK frequency  = 60MHz /((1 +  [(1 +0xValueH*256) OR 0xValueL])*2)
	OutputBuffer[dwNumBytesToSend++] = 0x86; 			//Command to set clock divisor
	OutputBuffer[dwNumBytesToSend++] = dwClockDivisor & 0xFF;	//Set 0xValueL of clock divisor
	OutputBuffer[dwNumBytesToSend++] = (dwClockDivisor >> 8) & 0xFF;	//Set 0xValueH of clock divisor
	ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);	// Send off the commands
	dwNumBytesToSend = 0;			//Clear output buffer
	Sleep(20);		//Delay for a while

	//Turn off loop back in case
	OutputBuffer[dwNumBytesToSend++] = 0x85;		//Command to turn off loop back of TDI/TDO connection
	ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);	// Send off the commands
	dwNumBytesToSend = 0;			//Clear output buffer
	Sleep(30);
	FT_Close(ftHandle);
	return true;
}

bool i2c_send_byte_ftdi(int Testn, int ProdNum, I2CParams ^ ParmsI2c, bool checked, bool synchrCheck, System::Windows::Forms::ToolStripStatusLabel ^ ts)
{
	bool i2c_send = true;
	array<unsigned char> ^DataArray;
	DataArray = crArray(Testn, ProdNum, i2c_send, checked, synchrCheck);//создание массива для конкретного теста
	array<unsigned char>^DataArray2 = gcnew array<unsigned char>(DataArray->Length + 1);
	setParamsForTest_IPZO2(Testn, ParmsI2c);
	setParamsForTest_IPZO3(Testn, ParmsI2c); //установка параметров в соотвествии с номером модуля и его тестом для Write
	setParamsForTest_IPZO4(Testn, ParmsI2c);
	setParamsForTest_IPZO5(Testn, ProdNum, ParmsI2c);

	DataArray2[0] = ParmsI2c->firstbyte;
	for (int i = 0; i < DataArray->Length; i++)
		DataArray2[i + 1] = DataArray[i];
	HighSpeedSetI2CStart();
	I2C_SendByteGetACK(ParmsI2c->SlaveAddr);
	for (int i = 0; i < DataArray2->Length; i++)
		I2C_SendByteGetACK(DataArray2[i]);
	HighSpeedSetI2CStop();

	if (ftStatus == FT_OK)
	{
		ts->Text = "Запись произведена успешно!";
	}
	else
	{
		ts->Text = "Ошибка записи";
	}
	return true;
}

String ^ i2c_read_ftdi(int testn, int ProdNum, double(*CABLE_KOEF)[2][3], double(*POWER_KOEF)[3], double(*POWER_CORRECT)[2][3], I2CParams ^ i2cp)
{
	array<unsigned char>^ SendData;
	SendData = crSarray();
	unsigned char DataLength;
	String^ Result;
	DataLength = SendData->Length;
	Vstr^ valStr; //указатель на структуру аргументов
	valStr = gcnew Vstr;
	valStr->CABLE_KOEF = CABLE_KOEF;
	valStr->POWER_KOEF = POWER_KOEF;
	valStr->POWER_CORRECT = POWER_CORRECT;

	setParamsForTest_IPZO2(testn, i2cp);
	setParamsForTest_IPZO3(testn, i2cp); //установка параметров в соотвествии с номером модуля и его тестом для Read
	setParamsForTest_IPZO4(testn, i2cp);
	setParamsForTest_IPZO5(testn, ProdNum, i2cp);

	HighSpeedSetI2CStart();
	I2C_SendByteGetACK((byte)(i2cp->SlaveAddr | 1));
	for (int i = 0; i < SendData->Length; i++)
	{
		if (i < (SendData->Length - 1))
			SendData[i] = I2C_ReadByteSendACK();
		else SendData[i] = I2C_ReadByteSendNACK();
	}
	HighSpeedSetI2CStop();

	Result = IPZO2_Test_Result(testn, SendData, valStr);
	if (Result)return Result;
	Result = IPZO3_Test_Result(testn, SendData, valStr);       //выводы результатов после обработки, типа стринг
	if (Result)return Result;
	Result = IPZO4_Test_Result(testn, SendData);       //выводы результатов после обработки, типа стринг
	if (Result)return Result;
	Result = IPZO5_Test_Result(testn, ProdNum, SendData, valStr);
	if (Result)return Result;
}
