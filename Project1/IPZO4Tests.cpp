#include "ConvertResI2C.h"
#include "PowerCorrect.h"
#include "IPZO4Tests.h"

String ^ IPZO4_Test_Result(int TestNum, array<unsigned char>^ SendData)
{
#define TAB1 "         "
#define TAB "\n"+"\n"+"\n"+TAB1+"ПАРАМЕТРЫ ПРД:"+"\n"+TAB1
	String^ integer;
	String^ tenth;
	String^ Result;
	switch (TestNum)
	{
	case(510):
		integer = ConvertI2CHbyte(SendData, TestNum);
		tenth = ConvertI2CLbyte(SendData, TestNum);
		Result = TAB + "Несущая частота, F2" + "\n" + TAB1 + integer + "," + tenth + " Мгц";
		return Result;
		delete[]SendData;
		break;
	case(511):
		integer = ConvertI2CHbyte(SendData, TestNum);
		tenth = ConvertI2CLbyte(SendData, TestNum);
		Result = TAB + "Несущая частота, F3" + "\n" + TAB1 + integer + "," + tenth + " Мгц";
		return Result;
		delete[]SendData;
		break;
	case(512):
		integer = ConvertI2CHbyte(SendData, TestNum);
		tenth = ConvertI2CLbyte(SendData, TestNum);
		Result = TAB + "Несущая частота, F4" + "\n" + TAB1 + integer + "," + tenth + " Мгц";
		return Result;
		delete[]SendData;
		break;
	default:break;
	}
}

bool setParamsForTest_IPZO4(int Testnum, I2CParams ^ i2cp)
{
	bool measure;
	switch (Testnum)
	{
	case(510):
	case(511):
	case(512):
		measure = true;
		i2cp->firstbyte = (Testnum - 508); // несущая f2
		i2cp->SlaveAddr = 0x82;
		return measure;
		break;
	default:break;
	}
}
