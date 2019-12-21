#include "arrays.h"
#include "namespaces.h"

byte b[1];
bool secondSending;

byte LongToDigits(uint Value, byte Offset, byte DigitNum, byte * Digits)
{
	int DigitIndex;	//	индекс цифры (полубайта), начинается от 0
	unsigned int CurValue = Value;
	byte CurDigit;
	if ((Offset + DigitNum) > 10) return 0;
	for (DigitIndex = Offset + DigitNum - 1; DigitIndex >= Offset; DigitIndex--, CurValue /= 10)
	{
		CurDigit = (byte)(CurValue % 10);
		if ((DigitIndex % 2) != 0)
		{	//	не делится на 2 -> младший (правый) полубайт (цифра)
			Digits[DigitIndex >> 1] = (byte)((Digits[DigitIndex >> 1] & 0xF0) + CurDigit);
		}
		else
		{			//	делится на 2 -> старший (левый) полубайт (цифра)
			Digits[DigitIndex >> 1] = (byte)((Digits[DigitIndex >> 1] & 0x0F) + CurDigit * 16);
		}
	}
	return (byte)(Offset + DigitNum);
}

void setIPZO3Params(byte Arm, byte Freq, byte PrelimAtt, byte OutOK, byte OutPBL, byte TypeOut, byte Modulator, IPZO3PARAMS ^ Params)
{
	Params->valueArm = Arm;
	Params->valueFrequency = Freq;
	Params->valuePrelimAtt = PrelimAtt;
	Params->valueOutOK = OutOK;
	Params->valueOutPBL = OutPBL;
	Params->typeOut = TypeOut;
	Params->valueModulator = Modulator;
}

array<byte>^ dArray(IPZO3PARAMS ^ Params)
{
	array<byte>^ DataArray = gcnew array<byte>(8);
	DataArray[0] = (byte)(((byte)Params->valueArm) << 4);  //уровень АРМ: 1 - +10 дБм, 0 - -10дБм, частота
	DataArray[0] |= (byte)Params->valueFrequency; // частота
	DataArray[1] = (byte)Params->valuePrelimAtt; // код предварит. аттенюатора
	DataArray[2] = (byte)Params->valueOutOK; // код выходного аттенюатора ОК
	DataArray[3] = (byte)Params->valueOutPBL; // код выходного аттенюатора ОК
	DataArray[4] = (byte)(((byte)Params->typeOut) << 4); // номер выхода
	DataArray[4] |= (byte)Params->valueModulator; // код модулятора
	return DataArray;
}

array<byte>^ crSarray()
{
	array<byte>^ DataArray = gcnew array<byte>(14);
	DataArray[0] = 0x00;
	DataArray[1] = 0x00;
	DataArray[2] = 0x00;
	DataArray[3] = 0x00;
	DataArray[4] = 0x00;
	DataArray[5] = 0x00;
	DataArray[6] = 0x00;
	DataArray[7] = 0x00;
	DataArray[8] = 0x00;
	DataArray[9] = 0x00;
	DataArray[10] = 0x00;
	DataArray[11] = 0x00;
	DataArray[12] = 0x00;
	DataArray[13] = 0x00;
	return DataArray;
}

array<byte>^ crArray(int Test, int ProdNum, bool i2c_status, bool checked, bool synchrCheck) 
{

	array<byte>^ DataArray = gcnew array<byte>(11);
	{
		/*ТЕСТЫ ИПЗО5, МАССИВЫ if else использовался для уменьшения case'ов*/
#pragma region
		if (ProdNum == 51)
		{

			if (Test >= 32 && Test <= 40)
			{
				std::vector<byte> v = { 0xB0,0x00,(byte)(0x00 + (Test - 31)),0x00,0x10,0x50 };
				fillArrays(DataArray, v);
			}
			if (Test >= 41 && Test <= 43)
			{
				std::vector<byte> v = { 0xB0,0x00,(byte)(0x10 + (Test - 41)),0x00,0x10,0x50 };
				fillArrays(DataArray, v);
			}
		}
		if (Test >= 91 && Test <= 100)
		{
			if (!secondSending)
			{

				std::vector<byte> v = { 0x00,0x00,0x00,0x00,(byte)(0x10 + (Test - 91)),0x00,0x00,0x00,0x00,0x00 };
				fillArrays(DataArray, v);
			}
			else
			{
				std::vector<byte> v = { 0xA0,(byte)(0x00 + (Test - 91)),0x00,0x00,0x10,0x50 };
				fillArrays(DataArray, v);
			}
		}
		if (Test >= 114 && Test <= 122)
		{
			std::vector<byte> v = { 0xB0,0x21,(byte)(Test - 113),0x00,0x10,0x50 };
			fillArrays(DataArray, v);
		}
		if (Test >= 133 && Test <= 142)
		{
			std::vector<byte> v = { 0xA0,0x21,(byte)(0x00 + (Test - 133)),0x00,0x10,0x50 };
			fillArrays(DataArray, v);
		}
		if (Test >= 144 && Test <= 153)
		{
			std::vector<byte> v = { 0xA0,0x21,(byte)(0x00 + (Test - 144)),0x00,0x10,0x50 };
			fillArrays(DataArray, v);
		}
		if (Test >= 225 && Test <= 254)
		{
			LongToDigits(Test - 218, 0, 2, b);
			std::vector<byte> v = { 0x10,b[0],(byte)(synchrCheck ? 0xC0 : 0x00),0x00,0x00,0x99,0x90,0x01 };
			fillArrays(DataArray, v);
		}
		if (Test >= 257 && Test <= 286)
		{
			LongToDigits(Test - 250, 0, 2, b);
			std::vector<byte> v = { 0x00,b[0] };
			fillArrays(DataArray, v);
		}
		if (Test >= 440 && Test <= 466)
		{
			LongToDigits(Test - 430, 0, 2, b);
			std::vector<byte> v = { 0x30,b[0],(byte)(synchrCheck ? 0xC0 : 0x00),0x00,0x00,0x99,0x90,0x01 };
			fillArrays(DataArray, v);
		}
#pragma endregion

		/*ТЕСТЫ ИПЗО5, МАССИВЫ ПРОДОЛЖЕНИЕ*/
#pragma region
		switch (Test)
		{

		case 11:
		{
			std::vector<byte> v = { 0xAA,0x00,0x00,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 24:
		{
			std::vector<byte> v = { 0xB0,0x00,0x00,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 51:
		case 52:
		{
			std::vector<byte> v = { 0xB0,0x00,(byte)(Test == 51 ? 0x20 : 0x28),0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 53:
		{
			std::vector<byte> v = { 0xB0,0x00,0x30,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 64:
		{
			std::vector<byte> v = { 0xB0,0x00,0x08,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 74:
		{
			std::vector<byte> v = { 0xB0,0x00,0x10,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 84:
		{
			std::vector<byte> v = { 0xB0,0x00,0x38,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 81:
		case 82:
		{
			std::vector<byte> v = { 0xA0,0x00,0x00,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 86:
		{
			std::vector<byte> v = { 0xB0,0x00,0x01,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 88:
		case 89:
		{
			std::vector<byte> v = { (byte)(Test == 88 ? 0xA0 : 0xE0),(byte)(Test == 88 ? 0x21 : 0x22),0x00,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 90:
		{
			std::vector<byte> v = { 0xB0,0x23,0x00,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 101:
		case 102:
		case 103:
		case 104:
		{
			if (!secondSending)
			{

				std::vector<byte> v = { 0x00,0x00,0x00,0x00,(byte)(0x10 + (Test - 91)),0x00,0x00,0x00,0x00,0x00 };
				fillArrays(DataArray, v);
			}
			else
			{
				std::vector<byte> v = { 0xA0,(byte)(0x10 + (Test - 101)),0x00,0x00,0x10,0x50 };
				fillArrays(DataArray, v);
			}
			return DataArray;
			break;
		}
		case 105:
		case 106:
		{
			if (!secondSending)
			{
				std::vector<byte> v = { 0x00,0x00,0x00,0x00,(byte)(0x10 + (Test - 91)) };
				fillArrays(DataArray, v);
			}
			else
			{
				std::vector<byte> v = { 0xA0,(byte)(0x10 + (Test - 101)),0x00,0x00,0x10,0x50 };
				fillArrays(DataArray, v);
			}
			return DataArray;
			break;
		}
		case 107:
		case 108:
		case 109:
		case 110:
		{
			std::vector<byte> v = { 0xA0,(byte)(0x20 + (Test - 103)),0x24,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 111:
		case 112:
		case 113:
		{
			std::vector<byte> v = { 0xA0,(byte)(0x30 + (Test - 103)),0x24,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 123:
		{
			std::vector<byte> v = { 0xB0,0x21,0x10,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 124:
		case 125:
		case 126:
		case 127:
		case 128:
		case 129:
		case 130:
		{
			std::vector<byte> v = { 0xA0,0x21,(byte)(Test - 123),0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 131:
		{
			std::vector<byte> v = { 0xAD,0x00,0x00,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 132:
		{
			std::vector<byte> v = { 0xBD,0x21,0x00,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 143:
		{
			std::vector<byte> v = { 0xA0,0x21,0x09,0x20,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 154:
		{
			std::vector<byte> v = { 0xA0,0x21,0x09,0x20,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 188:
		case 189:
		{
			std::vector<byte> v = { (byte)(Test == 188 ? 0xA0 : 0xE0),(byte)(Test == 188 ? 0x31 : 0x32),0x00,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 190:
		{
			std::vector<byte> v = { 0xB0,0x33,0x00,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 255:
		case 256:
		{
			LongToDigits(Test - 164, 0, 2, b);
			std::vector<byte> v = { 0x10,b[0],(byte)(synchrCheck ? 0xC0 : 0x00),0x00,0x00,0x99,0x90,0x01 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 287:
		case 288:
		{
			LongToDigits(Test - 196, 0, 2, b);
			std::vector<byte> v = { 0x00,b[0] };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 403:
		{
			std::vector<byte> v = { 0x20,0x10,0x00,0x00,0x00,0x10,0x01,0x00,0x03 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 404:
		{
			std::vector<byte> v = { 0x80,0x10,(byte)(synchrCheck ? 0xC0 : 0x00),0x00,0x00,0x99,0x90 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 405:
		{
			std::vector<byte> v = { 0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 406:
		case 408:
		{
			std::vector<byte> v = { (byte)(Test == 406 ? 0x01 : 0x02),0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 407:
		{
			std::vector<byte> v = { 0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 409:
		case 410:
		{
			std::vector<byte> v = { (byte)(Test == 409 ? 0x13 : 0x03),0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 411:
		case 412:
		{
			std::vector<byte> v = { (byte)(Test == 411 ? 0x04 : 0x08),0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 413:
		{
			std::vector<byte> v = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 415:
		{
			std::vector<byte> v = { 0x02,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 416:
		{
			std::vector<byte> v = { 0x02,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 417:
		{
			std::vector<byte> v = { 0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 418:
		{
			if (!secondSending)
			{
				std::vector<byte> v = { 0xA0,0x21,0x00,0x00,0x10,0x50 };
				fillArrays(DataArray, v);
			}
			else
			{
				std::vector<byte> v = { 0x00,0x01,0x10,0x35,0x00,0x00,0x00,0x00,0x00,0x00 };
				fillArrays(DataArray, v);
			}
			return DataArray;
			break;
		}
		case 424:
		case 425:
		{
			std::vector<byte> v = { (byte)(Test == 424 ? 0xA0 : 0xE0),0x00,0x00,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 426:
		case 432:
		{
			std::vector<byte> v = { 0xA0,0x00,0x01,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 428:
		case 429:
		case 430:
		{
			std::vector<byte> v = { 0xB0,0x00,0x01,(byte)(0x00 + (Test - 424)),0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 431:
		{
			std::vector<byte> v = { 0xB0,0x00,0x03,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 427:
		{
			std::vector<byte> v = { 0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 434:
		case 436:
		case 438:
		{
			std::vector<byte> v = { 0xB0,0x21,0x01,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 435:
		case 437:
		case 439:
		{
			std::vector<byte> v = { 0xB0,0x21,0x09,0x00,0x10,0x50 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}

		case 467:
		case 468:
		{
			LongToDigits(Test - 376, 0, 2, b);
			std::vector<byte> v = { 0x30,b[0],(byte)(synchrCheck ? 0xC0 : 0x00),0x00,0x00,0x99,0x90,0x01 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 505:
		case 506:
		{
			std::vector<byte> v = { 0x80,(byte)((Test == 505) ? 0x91 : 0x92),(byte)(synchrCheck ? 0xC0 : 0x00),0x00,0x00,0x99,0x90 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 709:
		{
			std::vector<byte> v = { 0 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 711:
		{
			std::vector<byte> v = { 2 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 716:
		{
			std::vector<byte> v = { 0x10,0x32,(byte)(synchrCheck ? 0xC0 : 0x00),0x00,0x00,0x99,0x90,0x01 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
#pragma endregion

		/*ТЕСТЫ ИПЗО2, МАССИВЫ*/
#pragma region
		case (40):
		case (41):
		{
			std::vector<byte> v = { 0x15,0x95,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 700:
		case 707:
		case 708:
		case 710:
		{
			std::vector<byte> v = { 1 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 701:
		case 702:
		case 703:
		case 704:
		case 705:
		case 706:
		{
			std::vector<byte> v = { 0x30 | 1 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
#pragma endregion

		/*ТЕСТЫ ИПЗО4, МАССИВЫ*/
#pragma region
		case 510:
		case 511:
		case 512:
		{
			std::vector<byte> v = { 0x00,0x00,0x00,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
#pragma endregion

		/*ТЕСТЫ ИПЗО3, МАССИВЫ*/
#pragma region
		case 608:
		case 609:
		{
			std::vector<byte> v = { (byte)((1 << 4) | (Test - 606)),0x04,0x00,0x04,0x00,(byte)(checked ? 0x10 : 0x00) };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 610:
		case 611:
		case 612:
		case 613:
		case 614:
		case 615:
		case 616:
		case 617:
		case 618:
		{
			std::vector<byte> v = { (1 << 4) | 0x02,(byte)(Test - 608),0x00,(byte)(Test - 608),0x00,(byte)(checked ? 0x10 : 0x00) };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 619:
		case 629:
		{
			std::vector<byte> v = { (byte)((1 << 4) | (Test == 619 ? 0x02 : 0x03)),0x03,65,0x03,65,(byte)(checked ? 0x10 : 0x00) };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 620:
		case 621:
		case 622:
		case 623:
		case 624:
		case 625:
		case 626:
		case 627:
		case 628:
		{
			std::vector<byte> v = { (1 << 4) | 0x3,(byte)(Test - 618),0,(byte)(Test - 618),0,(byte)(checked ? 0x10 : 0x00) };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 630:
		case 631:
		case 632:
		case 633:
		case 634:
		case 635:
		case 636:
		case 637:
		case 638:
		{
			std::vector<byte> v = { (1 << 4) | 0x4,(byte)(Test - 628),0,(byte)(Test - 628),0,(byte)(checked ? 0x10 : 0x00) };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 639:
		{
			std::vector<byte> v = { (0 << 4) | 0x4,0x03,65,0x03,65,(byte)(checked ? 0x10 : 0x00) };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 640:
		{
			std::vector<byte> v = { (1 << 4) | 0x2,0x03,0x95,0x03,0x95,0,0x10,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 641:
		{
			std::vector<byte> v = { (1 << 4) | 0x2,0x4,0x00,0x4,0x00,0,0x10,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 642:
		{
			std::vector<byte> v = { (1 << 4) | 0x2,0x4,0x05,0x4,0x05,0,0x10,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 643:
		{
			std::vector<byte> v = { (1 << 4) | 0x3,0x03,0x95,0x03,0x95,0,0x10,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 644:
		{
			std::vector<byte> v = { (1 << 4) | 0x3,0x4,0x00,0x4,0x00,0,0x10,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 645:
		{
			std::vector<byte> v = { (1 << 4) | 0x3,0x4,0x05,0x4,0x05,0,0x10,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 646:
		{
			std::vector<byte> v = { (1 << 4) | 0x4,0x03,0x95,0x03,0x95,0,0x10,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 647:
		{
			std::vector<byte> v = { (1 << 4) | 0x4,0x4,0x00,0x4,0x00,0,0x10,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 648:
		{
			std::vector<byte> v = { (1 << 4) | 0x4,0x4,0x05,0x4,0x05,0,0x10,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 649:
		case 650:
		case 651:
		{
			std::vector<byte> v = { (byte)((1 << 4) | (Test - 647)),0x4,0x00,0x4,0x00,0,0x10,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 652:
		{
			std::vector<byte> v = { 0x27,0x4,0x00,0x5,0x00,(byte)(2 << 4) };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 653:
		case 654:
		{
			std::vector<byte> v = { (byte)((1 << 4) | (Test - 652)),0x4,0x00,0x4,0x00,(byte)(checked ? 0x10 : 0x00) };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 655:
		case 656:
		case 657:
		{
			std::vector<byte> v = { (byte)(1 << 4) | 0x04,0x4,0x00,0x4,0x00,(byte)(checked ? 0x10 : 0x00) };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
		case 658:
		case 659:
		case 660:
		case 661:
		case 662:
		{
			std::vector<byte> v = { (byte)((Test - 657) << 4),0x01,0x00,0x00 };
			fillArrays(DataArray, v);
			return DataArray;
			break;
		}
#pragma endregion
		default:
			break;
		}
		return DataArray;
	}
}


