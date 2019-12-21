#include "ConvertResI2C.h"

String ^ ConvertI2CHbyte(array<unsigned char>^ Data, int Testn)
{
	double units, units4;
	String^ units1;
	String^ units2;
	String^ units3;

	switch (Testn)
	{
	case(700):
		units = Convert::ToDouble((Data[6] / 16));
		units4 = Convert::ToDouble(Data[6] % 0x10);
		units1 = Convert::ToString(units);
		units2 = Convert::ToString(units4);
		units3 = units1 + units2;
		return units3;
		break;
	case(701):
	case(702):
	case(703):
	case(704):
	case(705):
	case(706):
		units = Convert::ToInt16((Data[2]));
		units3 += Convert::ToString(units);
		units4 = 0;
		units = Convert::ToInt16((Data[3] / 10)); //выделяю первый полубайт
		units4 = Convert::ToInt16(Data[3] % 0x10);//выделяю второй полубайт
		units1 = Convert::ToString(units);
		units2 = Convert::ToString(units4);
		units3 += units1 + units2;
		return units3;
		break;
	case 707:
	case 708:
		units = Convert::ToDouble((Data[2])); //второй полубайт, байта[2], по протоколу тысячи кода АЦП
		units3 += Convert::ToString(units);
		units = 0;
		units4 = 0;
		units = Convert::ToDouble((Data[3] / 10));//сотни кода АЦП
		units4 = Convert::ToDouble(Data[3] % 0x10);//десятки кода АЦП
		units1 = Convert::ToString(units);
		units2 = Convert::ToString(units4);
		units3 += units1 + units2;
		units = 0;
		units4 = 0;
		//units = Convert::ToDouble((Data[3] / 10));
		//units1 = Convert::ToString(units);
		//units3 += units1;
		return units3;
		break;
	case(510):
	case(511):
	case(512):
		units = Convert::ToDouble((Data[1] >> 4));
		units4 = Convert::ToDouble(Data[1] % 0x10);
		units1 = Convert::ToString(units);
		units2 = Convert::ToString(units4);
		units3 = units1 + units2;
		units = 0;
		units4 = 0;
		units = Convert::ToDouble((Data[2] >> 4));
		units4 = Convert::ToDouble(Data[2] % 0x10);
		units1 = Convert::ToString(units);
		units2 = Convert::ToString(units4);
		units3 += units1 + units2;
		return units3;
		break;
	default:
		break;
	}
}

String ^ ConvertI2CLbyte(array<unsigned char>^ Data, int Testn)
{
	double tens, tens4;
	String^ tens1;
	String^ tens2;
	String^ tens3;
	switch (Testn)
	{
	case 20:
		tens = Convert::ToDouble((Data[4] / 16));
		tens4 = Convert::ToDouble(Data[4] % 0x10);
		tens1 = Convert::ToString(tens);
		tens2 = Convert::ToString(tens4);
		tens3 = tens1 + tens2;
		return tens3;
		break;
	case(700):
		tens = Convert::ToDouble((Data[7] / 16));
		tens4 = Convert::ToDouble(Data[7] % 0x10);
		tens1 = Convert::ToString(tens);
		tens2 = Convert::ToString(tens4);
		tens3 = tens1 + tens2;
		return tens3;
		break;
	case(701):
	case(702):
	case(703):
	case(704):
	case(705):
	case(706):
		tens4 = Convert::ToDouble(Data[4] / 10);
		tens2 = Convert::ToString(tens4);
		tens3 = tens2;
		return tens3;
		break;
	case(510):
	case(511):
	case(512):
		tens = Convert::ToDouble((Data[3] >> 4));
		tens4 = Convert::ToDouble(Data[3] % 0x10);
		tens1 = Convert::ToString(tens);
		tens2 = Convert::ToString(tens4);
		tens3 = tens1 + tens2;
		return tens3;
		break;
	default:
		break;
	}
}

String ^ ConvResI2CFromIPZO5(int TestNum, array<unsigned char>^ SendData)
{
#define TAB11 "         "
	String^ Result;
	if (TestNum >= 225 && TestNum <= 254 || TestNum == 255 || TestNum == 256 || TestNum >= 257 && TestNum <= 288 || TestNum == 287 || TestNum == 288 || TestNum == 716)
	{
		Result += Convert::ToString(Convert::ToInt16((SendData[1] >> 4)));//десятки
		Result += Convert::ToString(Convert::ToInt16((SendData[1] & 0xF0)));//единицы
		Result += ",";
		Result += Convert::ToString(Convert::ToInt16((SendData[2] >> 4)));//десятые
		Result += Convert::ToString(Convert::ToInt16((SendData[2] & 0xF0)));//сотые
	}
	else if (TestNum >= 440 && TestNum <= 468)
	{
		Result += "Амплитуда импульса: ";
		Result += Convert::ToString(Convert::ToInt16((SendData[1] >> 4)));//десятки
		Result += Convert::ToString(SendData[1] & 0xF0);//единицы
		Result += ",";
		Result += Convert::ToString(Convert::ToInt16((SendData[2] >> 4)));//десятые
		Result += Convert::ToString(Convert::ToInt16((SendData[2] & 0xF0)));//сотые
		Result += " В" + "\n";
		Result += TAB11 + "Длительность импульса: ";
		if (Convert::ToInt16(SendData[3] & 0xF0) == 0)
		{
			Result += Convert::ToString(Convert::ToInt16((SendData[4] >> 4)));//десятки
			Result += Convert::ToString(Convert::ToInt16((SendData[4] & 0xF0)));//единицы
			Result += ",";
			Result += Convert::ToString(Convert::ToInt16((SendData[5] >> 4)));//десятые
			Result += Convert::ToString(Convert::ToInt16((SendData[5] & 0xF0)));//сотые
			Result += " мкс" + "\n";
		}
		else
		{
			Result += Convert::ToString(Convert::ToInt16((SendData[3] & 0xF0)));//сотые
			Result += Convert::ToString(Convert::ToInt16((SendData[4] >> 4)));//десятки
			Result += Convert::ToString(Convert::ToInt16((SendData[4] & 0xF0)));//единицы
			Result += ",";
			Result += Convert::ToString(Convert::ToInt16((SendData[5] >> 4)));//десятые
			Result += Convert::ToString(Convert::ToInt16((SendData[5] & 0xF0)));//сотые
			Result += " мкс" + "\n";
		}
		Result += TAB11 + "Длительность фронта: ";
		Result += Convert::ToString(Convert::ToInt16((SendData[6] >> 4)));//десятки
		Result += Convert::ToString(Convert::ToInt16((SendData[6] & 0xF0)));//единицы
		Result += ",";
		Result += Convert::ToString(Convert::ToInt16((SendData[7] >> 4)));//десятые
		Result += Convert::ToString(Convert::ToInt16((SendData[7] & 0xF0)));//сотые
		Result += " мкс" + "\n";
	}
	else if (TestNum == 403)
	{
		Result += "Число импульсов: ";
		Result += Convert::ToString(Convert::ToInt16((SendData[1] & 0xF0)));//тысячи
		Result += Convert::ToString(SendData[2] >> 4);//сотни
		Result += Convert::ToString(Convert::ToInt16((SendData[2] & 0xF0)));//десятки
		Result += Convert::ToString(Convert::ToInt16((SendData[3] >> 4)));//единицы
		Result += ",";
		Result += Convert::ToString(Convert::ToInt16((SendData[3] & 0xF0)));//десятые
	}
	else if (TestNum == 404 || TestNum == 505 || TestNum == 506)
	{
		Result += "Длительность импульса 1: ";
		Result += Convert::ToString(Convert::ToInt16((SendData[1] & 0xF0)));
		Result += Convert::ToString(Convert::ToInt16((SendData[2] >> 4)));
		Result += Convert::ToString(Convert::ToInt16((SendData[2] & 0xF0)));
		Result += ",";
		Result += Convert::ToString(Convert::ToInt16((SendData[3] >> 4)));
		Result += Convert::ToString(Convert::ToInt16((SendData[3] & 0xF0)));
		Result += " мкс" + "\n";
		Result += TAB11 + "Длительность импульса 2: ";
		Result += Convert::ToString(Convert::ToInt16((SendData[4] & 0xF0)));
		Result += Convert::ToString(Convert::ToInt16((SendData[5] >> 4)));
		Result += Convert::ToString(Convert::ToInt16((SendData[5] & 0xF0)));
		Result += ",";
		Result += Convert::ToString(Convert::ToInt16((SendData[6] >> 4)));
		Result += Convert::ToString(Convert::ToInt16((SendData[6] & 0xF0)));
		Result += " мкс" + "\n";
		Result += TAB11 + "Позиция 2-го импульса: ";
		Result += Convert::ToString(Convert::ToInt16((SendData[7] & 0xF0)));
		Result += Convert::ToString(Convert::ToInt16((SendData[8] >> 4)));
		Result += Convert::ToString(Convert::ToInt16((SendData[8] & 0xF0)));
		Result += ",";
		Result += Convert::ToString(Convert::ToInt16((SendData[9] >> 4)));
		Result += Convert::ToString(Convert::ToInt16((SendData[9] & 0xF0)));
		Result += " мкс" + "\n";
	}
	return Result;
}

String ^ ConvResI2CFromIPZO3(int TestNum, array<unsigned char>^ SendData)
{
	String^ Result;
	switch (TestNum)
	{
	case 658:
	case 659:
	case 660:
	case 661:
	case 662:
	{
		Result += Convert::ToString(Convert::ToInt16((SendData[1] & 0xF0)));//тысячи
		Result += Convert::ToString(SendData[2] >> 4);//сотни
		Result += Convert::ToString(Convert::ToInt16((SendData[2] & 0xF0)));//десятки
		Result += Convert::ToString(Convert::ToInt16((SendData[3] >> 4)));//единицы
		Result += ",";
		Result += Convert::ToString(Convert::ToInt16((SendData[3] & 0xF0)));//десятые
	}
	default:
		break;
	}
	return Result;
}
