#include "ConvertResI2C.h"
#include "PowerCorrect.h"
#include "IPZO3Tests.h"

String ^ setIPZO3ParamsToI2c(I2CParams ^ i2cp)
{
	i2cp->firstbyte = 0x00;//	������ ����� ���������
	unsigned char arrayLength;
	String^ Return_str = " ";
	String^ str;
	IPZO3PARAMS^ Params; //��������� �� ��������� ���������� � ��������� ��� ���� ������
	Params = gcnew IPZO3PARAMS;
	array<unsigned char> ^DataArray; //�������� ������� � ����������� ��� ����3
	DataArray = dArray(Params);
	arrayLength = DataArray->Length;
	i2cp->SlaveAddr = 0x62;
	if (PICkitS::I2CM::Write((unsigned char)i2cp->SlaveAddr, (unsigned char)i2cp->firstbyte, (unsigned char)arrayLength, DataArray, Return_str))
	{
		str = "������ ����������� �������!";
	}
	else
	{
		str = "������ ������";
		PICkitS::Device::Reset_Control_Block();       //clear any errors in PKSA
	}
	delete[]DataArray;
	return str;
}

String ^ IPZO3_Test_Result(int TestNum, array<unsigned char>^ SendData, Vstr ^ valStr)
{
#define TAB1 "         "
#define TAB "\n"+"\n"+"\n"+TAB1+"��������� ���:"+"\n"+TAB1
	String^ ConvRes;
	String^ Result;
	switch (TestNum)
	{
	case 608:
	case 609:
		Result += TAB + "�������� ������ �������� ������� �� F" + Convert::ToString(TestNum - 606) + "-40dB/W";
		delete[]SendData;
		return Result;
	case 610:
	case 611:
	case 612:
	case 613:
	case 614:
	case 615:
	case 616:
	case 617:
	case 618:
		Result += TAB + "�������� ������ �������� ������� �� F2 -" + Convert::ToString(TestNum - 608) + "0dB/W";
		delete[]SendData;
		return Result;
	case 619:
	case 629:
		Result += TAB + "�������� ������ ���������� ������� �� ������� F" + Convert::ToString(TestNum == 619 ? 2 : 3) + "-36,5dB/W, ������ �����";
		delete[]SendData;
		return Result;
	case 620:
	case 621:
	case 622:
	case 623:
	case 624:
	case 625:
	case 626:
	case 627:
	case 628:
		Result += TAB + "�������� ������ �������� ������� �� F2 -" + Convert::ToString(TestNum - 618) + "0dB/W";
		delete[]SendData;
		return Result;
	case 630:
	case 631:
	case 632:
	case 633:
	case 634:
	case 635:
	case 636:
	case 637:
	case 638:
		Result += TAB + "�������� ������ �������� ������� �� F2 -" + Convert::ToString(TestNum - 628) + "0dB/W";
		delete[]SendData;
		return Result;
	case 639:
		Result += TAB + "�������� ������ ���������� ������� �� ������� F4 - 36, 5dB / W, ������ �����";
		delete[]SendData;
		return Result;
	case 640:
		Result += TAB + "�������� ������������ ��������� ������ �� ������� F2 -39,5dB/W";
		delete[]SendData;
		return Result;
	case 641:
		Result += TAB + "�������� ������������ ��������� ������ �� ������� F2 -40dB/W";
		delete[]SendData;
		return Result;
	case 642:
		Result += TAB + "�������� ������������ ��������� ������ �� ������� F2 -40,5dB/W";
		delete[]SendData;
		return Result;
	case 643:
		Result += TAB + "�������� ������������ ��������� ������ �� ������� F3 -39,5dB/W";
		delete[]SendData;
		return Result;
	case 644:
		Result += TAB + "�������� ������������ ��������� ������ �� ������� F3 -40dB/W";
		delete[]SendData;
		return Result;
	case 645:
		Result += TAB + "�������� ������������ ��������� ������ �� ������� F2 -40,5dB/W";
		delete[]SendData;
		return Result;
	case 646:
		Result += TAB + "�������� ������������ ��������� ������ �� ������� F4 -39,5dB/W";
		delete[]SendData;
		return Result;
	case 647:
		Result += TAB + "�������� ������������ ��������� ������ �� ������� F4 -40dB/W";
		delete[]SendData;
		return Result;
	case 648:
		Result += TAB + "�������� ������������ ��������� ������ �� ������� F4 -40,5dB/W";
		delete[]SendData;
		return Result;
	case 649:
	case 650:
	case 651:
		Result += TAB + "�������� ���������� ����������� ��������� ������� F" + Convert::ToString(TestNum - 647) + "-40dB/W";
		delete[]SendData;
		return Result;
	case 652:
		Result += TAB + "�������� ������������ ��� �������� � �������� ������� 10 ��";
		delete[]SendData;
		return Result;
	case 653:
		Result += TAB + "�������� ������������ ��� �������� �� ������� �������� ������� �� ������� F2";
		delete[]SendData;
		return Result;
	case 654:
		Result += TAB + "�������� ������������ ��� �������� �� ������� �������� ������� �� ������� F3";
		delete[]SendData;
		return Result;
	case 655:
	case 656:
	case 657:
		Result += TAB + "�������� ������������ ��� �������� �� ������� �������� ������� �� ������� F4";
		delete[]SendData;
		return Result;
	case 658:
	case 659:
	case 660:
	case 661:
	case 662:
		ConvRes = ConvResI2CFromIPZO3(TestNum, SendData);
		Result += TAB + "�������� �������� ������������� c� ����� " + Convert::ToString(TestNum - 657) + "\n" + TAB1 + "����� ��������� " + ConvRes;
		delete[]SendData;
		return Result;
	default:
		break;
	}
}

bool setParamsForTest_IPZO3(int Testn, I2CParams ^ i2cp)
{
	bool measure;
	if (Testn >= 608 && Testn <= 650 || Testn == 651 || Testn >= 653 && Testn <= 657)
	{
		measure = false;
		i2cp->firstbyte = 0x01;
		i2cp->SlaveAddr = 0x62;
	}
	else if (Testn == 652)
	{
		i2cp->firstbyte = 0x07;
		i2cp->SlaveAddr = 0x62;
	}
	else if (Testn >= 658 && Testn <= 662)
	{
		i2cp->firstbyte = 0x06;
		i2cp->SlaveAddr = 0x62;
	}
	return measure;
}
