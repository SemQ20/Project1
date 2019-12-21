#include "arrays.h"
#include "ConvertResI2C.h"
#include "PowerCorrect.h"
#include "IPZO5Tests.h"

String ^ IPZO5_Test_Result(int Testnum, int ProdNum, array<unsigned char>^ SendData, Vstr ^ valStr)
{
#pragma region
#define TAB1 "         "
#define TAB "\n"+"\n"+"\n"+TAB1+"��������� ���:"+"\n"+TAB1
	String^ Result;
	String^ ConvRes;
	if (Testnum == 11)
	{
		Result = TAB + "�������� �������";
	}
	else if (Testnum >= 225 && Testnum <= 254)
	{
		ConvRes = ConvResI2CFromIPZO5(Testnum, SendData);
		Result = TAB + "��������� ��������� ����������� ���������� �� ����� �������� �������" + Convert::ToString(Testnum - 218) + " (����" + Convert::ToString(Testnum - 222) + ")" + "\n" + TAB1 + ConvRes;
	}
	else if (Testnum == 255 || Testnum == 256)
	{
		ConvRes = ConvResI2CFromIPZO5(Testnum, SendData);
		Result = TAB + "��������� ��������� ����������� ���������� �� ����� �������� �������" + Convert::ToString(Testnum - 164) + "\n" + TAB1 + ConvRes;
	}
	else if (Testnum >= 257 && Testnum <= 286)
	{
		ConvRes = ConvResI2CFromIPZO5(Testnum, SendData);
		Result = TAB + "��������� ���� ��� �� ����� �������� �������" + Convert::ToString(Testnum - 250) + "  (���� " + Convert::ToString(Testnum - 254) + ")" + "\n" + TAB1 + ConvRes;
	}
	else if (Testnum == 287 || Testnum == 288)
	{
		ConvRes = ConvResI2CFromIPZO5(Testnum, SendData);
		Result = TAB + "��������� ���� ��� �� ����� �������� ������� " + Convert::ToString(Testnum - 196) + "\n" + TAB1 + ConvRes;
	}
	else if (Testnum >= 440 && Testnum <= 466)
	{
		ConvRes = ConvResI2CFromIPZO5(Testnum, SendData);
		Result = TAB + "��������� ���������� �������� �� ����� �������� ������� " + Convert::ToString(Testnum - 430) + "  (���� " + Convert::ToString(Testnum - 434) + ")" + "\n" + TAB1 + ConvRes;
	}
	else if (Testnum == 716)
	{
		ConvRes = ConvResI2CFromIPZO5(Testnum, SendData);
		Result = TAB + "��������� ��������� ����������� ���������� �� ����� �������� �������" + Convert::ToString(Testnum - 674) + "\n" + TAB1 + ConvRes;
	}
	else if (Testnum == 403)
	{
		ConvRes = ConvResI2CFromIPZO5(Testnum, SendData);
		Result = TAB + "��������� ��������� ����������� ���������� �� ����� �������� �������" + Convert::ToString(Testnum - 674) + "\n" + TAB1 + ConvRes;
	}
	else if (Testnum == 404 || Testnum == 505 || Testnum == 506)
	{
		ConvRes = ConvResI2CFromIPZO5(Testnum, SendData);
		Result = TAB + "��������� ��������" + "\n" + TAB1 + ConvRes;
	}
	else if (Testnum >= 406 && Testnum <= 413 || Testnum >= 415 && Testnum <= 417)
	{
		switch (Testnum)
		{
		case 405:
		case 406:
			Result = TAB + "�������� ��1";
			return Result;
			break;
		case 407:
		case 408:
			Result = TAB + "�������� ��2";
			return Result;
			break;
		case 409:
		case 410:
			Result = TAB + "�������� ��3";
			return Result;
			break;
		case 411:
			Result = TAB + "�������� ������";
			return Result;
			break;
		case 412:
			Result = TAB + "�������� ��� �";
			return Result;
			break;
		case 413:
			Result = TAB + "�������� ��� �";
			return Result;
			break;
		case 415:
			Result = TAB + "�������� ������ ���";
			return Result;
			break;
		case 416:
		case 417:
			Result = TAB + "�������� ���� ��";
			return Result;
			break;
		default:
			break;
		}
	}
	else if (Testnum >= 88 && Testnum <= 90 || Testnum >= 188 && Testnum <= 190)
	{
		Result = TAB + "�������� �� 1 ������";
	}
	else if (Testnum == 418 || Testnum >= 91 && Testnum <= 106)
	{
		if (!secondSending)
		{
			switch (Testnum)
			{
			case 418:
				Result = TAB + "�������� �� 1 ������";
				return Result;
				break;
			case 91:
			case 92:
			case 93:
			case 94:
			case 95:
			case 96:
			case 97:
			case 98:
			case 99:
			case 100:
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
				Result = TAB + "���� ��, ���" + Convert::ToString(Testnum - 91);
				return Result;
				break;

			default:
				break;
			}
		}
		else
		{
			switch (Testnum)
			{
			case 418:
				Result = TAB + "�������� ���� ���";
				return Result;
				break;
			case 91:
			case 92:
			case 93:
			case 94:
			case 95:
			case 96:
			case 97:
			case 98:
			case 99:
			case 100:
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
				Result = TAB + "�������� �� 2 ������";
				return Result;
				break;
			default:
				break;
			}
		}
	}
	else if (Testnum >= 107 && Testnum <= 113)
	{
		Result = TAB + "�������� �� 3 ������";
	}
	else if (Testnum >= 114 && Testnum <= 130 || Testnum >= 434 && Testnum <= 439)
	{
		Result = TAB + "�������� �� 3 ������";
	}
	else if (Testnum == 131 || Testnum == 132)
	{
		switch (Testnum)
		{
		case 131:
		case 132:
			Result = TAB + "�������� " + Convert::ToString(Testnum - 130) + " �����";
			return Result;
			break;
		default:
			break;
		}
	}
	else if (Testnum >= 133 && Testnum <= 143)
	{
		Result = TAB + "�������� �� 6 ������";
	}
	else if (Testnum >= 144 && Testnum <= 154)
	{
		Result = TAB + "�������� �� 9 ������";
	}
	else if (Testnum == 24 || Testnum >= 424 && Testnum <= 425)
	{
		Result = TAB + "�������� �� 1 ������";
	}
	else if (Testnum == 86 || Testnum == 426 || Testnum == 432)
	{
		Result = TAB + "�������� �� 2 ������";
	}
	if (ProdNum)
	{
		if (Testnum >= 32 && Testnum <= 43)
		{
			Result = TAB + "�������� �� 3 ������";
		}
	}

	else if (Testnum >= 51 && Testnum <= 53 || Testnum == 64 || Testnum == 74 || Testnum == 84)
	{
		Result = TAB + "�������� �� 4K ������";
	}
	else if (Testnum == 81 || Testnum == 82)
	{
		Result = TAB + "�������� �� 4 ������";
	}
	else if (Testnum >= 428 && Testnum <= 431)
	{
		Result = TAB + "�������� �� 2K ������";
	}
	else if (Testnum == 427)
	{
		if (SendData[0] == 0xDE)
		{
			Result = TAB + "�������� ����������� ����5" + "\n" + TAB1 + "�������� ����5";
		}
		else
		{
			Result = TAB + "�������� ����������� ����5" + "\n" + TAB1 + "���������� ����5";
		}
	}
	return Result;
}

bool setParamsForTest_IPZO5(int Testn, int ProdNum, I2CParams ^ i2cp)
{
	if (ProdNum == 0)
	{
		if (Testn >= 225 && Testn <= 288 || Testn >= 440 && Testn <= 468 || Testn == 716 || Testn == 403 || Testn == 404 || Testn == 505 || Testn == 506)
		{
			i2cp->firstbyte = 0x10;
			i2cp->SlaveAddr = 0xA2;
		}
		else if (Testn >= 405 && Testn <= 413 || Testn >= 415 && Testn <= 418)
		{
			i2cp->firstbyte = 0x20;
			i2cp->SlaveAddr = 0xA2;
			if (Testn == 418)
			{
				if (!secondSending)
				{
					i2cp->firstbyte = 0x01;
					i2cp->SlaveAddr = 0xA2;
				}
				else
				{
					i2cp->firstbyte = 0x20;
					i2cp->SlaveAddr = 0xA2;
				}
			}
		}
		else if (Testn >= 434 && Testn <= 439)
		{
			i2cp->firstbyte = 0x05;
			i2cp->SlaveAddr = 0xA6;
		}
		else if (Testn >= 428 && Testn <= 431)
		{
			i2cp->firstbyte = 0x32;
			i2cp->SlaveAddr = 0xA2;
		}
		else if (Testn == 424 || Testn == 425)
		{
			i2cp->firstbyte = 0x31;
			i2cp->SlaveAddr = 0xA6;
		}
		else if (Testn == 426 || Testn == 432)
		{
			i2cp->firstbyte = 0x32;
			i2cp->SlaveAddr = 0xA6;
		}
		else if (Testn == 427)
		{
			i2cp->firstbyte = 0xDE;
			i2cp->SlaveAddr = 0xA6;
		}
	}


	if (ProdNum == 1)
	{
		if (Testn >= 88 && Testn <= 90 || Testn >= 188 && Testn <= 190 || Testn == 132)
		{
			i2cp->firstbyte = 0x01;
			i2cp->SlaveAddr = 0xA6;
		}
		else if (Testn >= 91 && Testn <= 106)
		{
			if (!secondSending)
			{
				i2cp->firstbyte = 0x20;
				i2cp->SlaveAddr = 0xA2;
			}
			else
			{
				i2cp->firstbyte = 0x02;
				i2cp->SlaveAddr = 0xA6;
			}
		}
		else if (Testn >= 107 && Testn <= 113)
		{
			i2cp->firstbyte = 0x03;
			i2cp->SlaveAddr = 0xA6;
		}
		else if (Testn >= 114 && Testn <= 130)
		{
			i2cp->firstbyte = 0x05;
			i2cp->SlaveAddr = 0xA6;
		}
		else if (Testn == 131)
		{
			i2cp->firstbyte = 0x02;
			i2cp->SlaveAddr = 0xA6;
		}
		else if (Testn >= 11 || Testn >= 133 && Testn <= 144)
		{
			i2cp->firstbyte = 0x06;
			i2cp->SlaveAddr = 0xA6;
		}
		else if (Testn >= 144 && Testn <= 154)
		{
			i2cp->firstbyte = 0x04;
			i2cp->SlaveAddr = 0xA6;
		}
	}


	if (ProdNum == 51)
	{
		switch (Testn)
		{
		case 24:
			i2cp->firstbyte = 0x31;
			i2cp->SlaveAddr = 0xA6;
			break;
		case 86:
			i2cp->firstbyte = 0x32;
			i2cp->SlaveAddr = 0xA6;
			break;
		default:
			break;
		}
		if (Testn >= 32 && Testn <= 43)
		{
			i2cp->firstbyte = 0x33;
			i2cp->SlaveAddr = 0xA6;
		}
		else if (Testn >= 51 && Testn <= 53 || Testn == 64 || Testn == 74 || Testn == 84)
		{
			i2cp->firstbyte = 0x35;
			i2cp->SlaveAddr = 0xA6;
		}
	}

	if (ProdNum == 14)
	{
		switch (Testn)
		{
		case 81:
			i2cp->firstbyte = 0x36;
			i2cp->SlaveAddr = 0xA6;
			break;
		case 82:
			i2cp->firstbyte = 0x34;
			i2cp->SlaveAddr = 0xA6;
			break;
		default:
			break;
		}
	}
	return true;
}
