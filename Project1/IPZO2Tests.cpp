#include "ConvertResI2C.h"
#include "PowerCorrect.h"
#include "IPZO2Tests.h"


String ^ IPZO2_Test_Result(int TestNum, array<unsigned char>^ SendData, Vstr ^ valStr)
{
#define TAB1 "         "
#define TAB "\n"+"\n"+"\n"+TAB1+"ПАРАМЕТРЫ ПРД:"+"\n"+TAB1
	String^ integer;
	String^ tenth;
	String^ Result;
	String^ Correct;
	String^ InNum;
	String^ OKNum;
	switch (TestNum)
	{
	case 40:
	case 41:
		Result += TAB + "Технологический режим - настройка платы измерения несущей." + (TestNum == 40 ? InNum = "Вход РЧ" : InNum = "Вход F") + "\n" + TAB1;
		return Result;
		delete[]SendData;
		break;
	case 700:
		integer = ConvertI2CHbyte(SendData, TestNum);
		tenth = ConvertI2CLbyte(SendData, TestNum);
		Result += TAB + "Температура ИПЗО2" + "\n" + TAB1 + integer + "," + tenth + " C";
		return Result;
		delete[]SendData;
		break;
	case 701:
	case 702:
	case 703:
	case 704:
	case 705:
	case 706:
		integer = ConvertI2CHbyte(SendData, TestNum);
		tenth = ConvertI2CLbyte(SendData, TestNum);
		setStrParams(TestNum, valStr, integer, tenth);
		Correct = PowerCorrect(valStr);
		Result += TAB + "Мощность по" + (TestNum == 701 || TestNum == 702 || TestNum == 703 ? OKNum = "OK1" : OKNum = "OK2") + "\n" + TAB1 + Correct;
		return Result;
		delete[]SendData;
		break;
	case 707:
	case 708:
		integer = ConvertI2CHbyte(SendData, TestNum);
		tenth = ConvertI2CLbyte(SendData, TestNum);
		Result += TAB + "Код АЦП" + (TestNum == 707 ? OKNum = "OK1" : OKNum = "OK2") + "\n" + TAB1 + integer + "," + tenth;
		return Result;
		delete[]SendData;
		break;
	case 709:
		Result += TAB + "СВЧ-переключатель в режим ВСК" + "\n" + TAB1;
		return Result;
		delete[]SendData;
		break;
	case 710:
		Result += TAB + "СВЧ-переключатель в режим измерения мощности или несущей" + "\n" + TAB1;
		return Result;
		delete[]SendData;
		break;
	case 711:
		Result += TAB + "СВЧ-переключатель в режим измерения чувствительности" + "\n" + TAB1;
		return Result;
		delete[]SendData;
		break;
	default:break;
	}
}

bool setParamsForTest_IPZO2(int Testnum, I2CParams ^ i2cp)
{
	bool measure;
	switch (Testnum)
	{
	case 40:
	case 41:
		measure = false;
		i2cp->firstbyte = (Testnum == 40 ? 0x00 : 0x10);
		i2cp->SlaveAddr = 0x82;
		return measure;
		break;
	case 700:
		measure = true;
		i2cp->firstbyte = 0x12; //temperature
		i2cp->SlaveAddr = 0x42;
		return measure;
		break;
	case 701:  //power
	case 702:
	case 703:
	case 704:
	case 705:
	case 706:
		i2cp->firstbyte = ((((Testnum == 701 || Testnum == 702 || Testnum == 703) ? 1 : 2) << 4) | ((Testnum == 701 || Testnum == 702 || Testnum == 703) ? Testnum - 699 : Testnum - 702)); // ok1/ok2,f2,f3,f4
		measure = true;
		i2cp->SlaveAddr = 0x42;
		return measure;
		break;
	case 707:  //power
	case 708:
		i2cp->firstbyte = ((Testnum - 706) << 4) | 0; // ok1,измерение непрерывной мощности, код ацп
		measure = true;
		i2cp->SlaveAddr = 0x42;
		return measure;
		break;
	case 709:  //power
	case 710:
	case 711:
		i2cp->firstbyte = 0; // СВЧ-переключатель в режим ВСК
		measure = false;
		i2cp->SlaveAddr = 0x42;
		return measure;
		break;
	}
}
