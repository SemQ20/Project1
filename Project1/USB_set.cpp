#include "USB_set.h"
#include "arrays.h"

void USB_Set(SerialPort ^ sp, String ^ comport)
{
	if (sp->IsOpen)
	{
		sp->Close();
	}
	sp->PortName = comport;
	sp->BaudRate = 115200;
	sp->DataBits = 8;
	sp->Parity = Parity::None;
	sp->StopBits = StopBits::One;
	sp->Open();
}

void SetCRC(array<unsigned char>^ data)
{
	for (unsigned char i = 1; i < 11; data[12] = (unsigned char)(data[12] ^ data[i++]));
	if ((data[12] >> 4) > 9) data[12] -= 0xA0;
	if ((data[12] & 0x0F) > 9) data[12] -= 0x0A;
}

unsigned char GetMask(unsigned char index)
{
	switch (index)
	{
	case 7: return 128;
	case 6: return 64;
	case 5: return 32;
	case 4: return 16;
	case 3: return 8;
	case 2: return 4;
	case 1: return 2;
	case 0: return 1;
	}
	return 0;
}

void ByteReversing(array<unsigned char>^ barray)
{
	unsigned char b2 = 0;
	for (int i = 0; i < barray->Length; i++)
	{
		b2 = 0;
		b2 |= (unsigned char)((barray[i] & GetMask(7)) >> 7);
		b2 |= (unsigned char)((barray[i] & GetMask(6)) >> 5);
		b2 |= (unsigned char)((barray[i] & GetMask(5)) >> 3);
		b2 |= (unsigned char)((barray[i] & GetMask(4)) >> 1);
		b2 |= (unsigned char)((barray[i] & GetMask(3)) << 1);
		b2 |= (unsigned char)((barray[i] & GetMask(2)) << 3);
		b2 |= (unsigned char)((barray[i] & GetMask(1)) << 5);
		b2 |= (unsigned char)((barray[i] & GetMask(0)) << 7);
		barray[i] = b2;
	}
}

String ^ ConvertBitFromCom(array<unsigned char>^ Data, int testnum)
{
#define TAB1 "         "
#define TAB "\n"+"\n"+"\n"+TAB1+"��������� ���:"+"\n"+TAB1
	String^ Result;
	String^ units;
	String^ units1;
	String^ units2;
	String^ units3;
	String^ units4;
	String^ units5;
	switch (testnum)
	{
	case 1: //��������,�����������
		if (Convert::ToDouble(Data[2] & 0x0F) == 0)//������ ���� �������� ������� ���������� �����
		{
			units3 += Convert::ToString(Convert::ToDouble(Data[3] >> 4));//������
			units3 += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));//�����
			units3 += Convert::ToString(Convert::ToDouble(Data[4] >> 4));
			units3 += Convert::ToString(Convert::ToDouble(Data[4] & 0x0F));
			Result = TAB + "��������: " + units3 + " ��";

		}
		else if (Convert::ToDouble(Data[2] & 0x0F) == 0 && (Convert::ToDouble(Data[3] >> 4)))//������ ���� �������� ������� ���������� �����
		{
			units3 += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));//�����
			units3 += Convert::ToString(Convert::ToDouble(Data[4] >> 4));
			units3 += Convert::ToString(Convert::ToDouble(Data[4] & 0x0F));
			Result = TAB + "��������: " + units3 + " ��";

		}
		else//������ ���� �������� ������� ���������� �������� �����
		{
			units3 += Convert::ToString(Convert::ToDouble(Data[2] & 0x0F));//������� �����
			units3 += Convert::ToString(Convert::ToDouble(Data[3] >> 4));//������
			units3 += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));//�����
			units3 += Convert::ToString(Convert::ToDouble(Data[4] >> 4));
			units3 += Convert::ToString(Convert::ToDouble(Data[4] & 0x0F));
			Result = TAB + "��������: " + units3 + " ��";
		}
		return Result;
		break;
	case 2://����������������,����� ���������
		if (Convert::ToDouble(Data[2] & 0x0F) == 0)
		{
			units3 += Convert::ToString(Convert::ToDouble(Data[3] >> 4));//�������
			units3 += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));//�������
			Result = TAB + "����������������: " + units3 + " ��/��" + "\n" + TAB1;
		}
		else
		{
			units3 += Convert::ToString(Convert::ToDouble(Data[2] & 0x0F));//�����
			units3 += Convert::ToString(Convert::ToDouble(Data[3] >> 4));//�������
			units3 += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));//�������
			Result = TAB + "����������������: " + units3 + " ��/��" + "\n" + TAB1;
		}
		units += Convert::ToString(Convert::ToDouble(Data[4] & 0x0F));//���.���
		units += Convert::ToString(Convert::ToDouble(Data[5] >> 4));//������
		units += Convert::ToString(Convert::ToDouble(Data[5] & 0x0F));//�����
		units += Convert::ToString(Convert::ToDouble(Data[6] >> 4));//�������
		Result += "����� ���������: " + units;
		return Result;
		break;
	case 3://��������� ���������
		units3 += Convert::ToString(Convert::ToDouble(Data[2] & 0x0F));
		units3 += Convert::ToString(Convert::ToDouble(Data[3] >> 4));
		units3 += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));
		Result += TAB + "��������� ���������" + "\n" + TAB1 + "���������: " + units3 + " �" + "\n" + TAB1;
		units += Convert::ToString(Convert::ToDouble(Data[4] & 0x0F));
		units += Convert::ToString(Convert::ToDouble(Data[5] >> 4));
		units += ",";
		units += Convert::ToString(Convert::ToDouble(Data[5] & 0x0F));
		Result += "������������ ��������: " + units + " ���" + "\n" + TAB1;
		units1 += "0,";
		units1 += Convert::ToString(Convert::ToDouble(Data[6] >> 4));
		units1 += Convert::ToString(Convert::ToDouble(Data[6] & 0x0F));
		Result += "����� ��������: " + units1 + " ���" + "\n" + TAB1;
		units2 += Convert::ToString(Convert::ToDouble(Data[7] >> 4));
		units2 += Convert::ToString(Convert::ToDouble(Data[7] & 0x0F));
		units2 += Convert::ToString(Convert::ToDouble(Data[8] >> 4));
		Result += "���-�� ���������: " + units2 + "\n" + TAB1;
		units4 += Convert::ToString(Convert::ToDouble(Data[9] >> 4));
		units4 += Convert::ToString(Convert::ToDouble(Data[9] & 0x0F));
		Result += "���� �����: " + units4 + " %";
		return Result;
		break;
	case 4://������� ��������
		units3 += Convert::ToString(Convert::ToDouble(Data[2] & 0x0F));
		units3 += Convert::ToString(Convert::ToDouble(Data[3] >> 4));
		units3 += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));
		units3 += ",";
		units3 += Convert::ToString(Convert::ToDouble(Data[4] >> 4));
		Result += TAB + "������� ��������" + "\n" + TAB1 + "2-��: " + units3 + " ���" + "\n" + TAB1;
		units += Convert::ToString(Convert::ToDouble(Data[4] & 0x0F));
		units += Convert::ToString(Convert::ToDouble(Data[5] >> 4));
		units += Convert::ToString(Convert::ToDouble(Data[5] & 0x0F));
		units += ",";
		units += Convert::ToString(Convert::ToDouble(Data[6] >> 4));
		Result += "3-��: " + units + " ���" + "\n" + TAB1;
		units1 += Convert::ToString(Convert::ToDouble(Data[6] & 0x0F));
		units1 += Convert::ToString(Convert::ToDouble(Data[7] >> 4));
		units1 += Convert::ToString(Convert::ToDouble(Data[7] & 0x0F));
		units1 += ",";
		units1 += Convert::ToString(Convert::ToDouble(Data[8] >> 4));
		Result += "4-��: " + units1 + " ���" + "\n" + TAB1;
		units2 += Convert::ToString(Convert::ToDouble(Data[8] & 0x0F));
		units2 += Convert::ToString(Convert::ToDouble(Data[9] >> 4));
		units2 += Convert::ToString(Convert::ToDouble(Data[9] & 0x0F));
		units2 += ",";
		units2 += Convert::ToString(Convert::ToDouble(Data[10] >> 4));
		Result += "5-��: " + units2 + " ���" + "\n" + TAB1;
		units4 += Convert::ToString(Convert::ToDouble(Data[10] & 0x0F));
		units4 += Convert::ToString(Convert::ToDouble(Data[11] >> 4));
		units4 += ",";
		units4 += Convert::ToString(Convert::ToDouble(Data[11] & 0x0F));
		Result += "6-��: " + units4 + " ���";
		return Result;
		break;
	case 5:
		units3 += Convert::ToString(Convert::ToDouble(Data[2] & 0x0F));
		units3 += Convert::ToString(Convert::ToDouble(Data[3] >> 4));
		units3 += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));
		units3 += ",";
		units3 += Convert::ToString(Convert::ToDouble(Data[4] >> 4));
		Result += TAB + "������� ��������" + "\n" + TAB1 + "1f2: " + units3 + " ���" + "\n" + TAB1;
		units += Convert::ToString(Convert::ToDouble(Data[4] & 0x0F));
		units += Convert::ToString(Convert::ToDouble(Data[5] >> 4));
		units += Convert::ToString(Convert::ToDouble(Data[5] & 0x0F));
		units += ",";
		units += Convert::ToString(Convert::ToDouble(Data[6] >> 4));
		Result += "1f3: " + units + " ���" + "\n" + TAB1;
		units1 += Convert::ToString(Convert::ToDouble(Data[6] & 0x0F));
		units1 += Convert::ToString(Convert::ToDouble(Data[7] >> 4));
		units1 += Convert::ToString(Convert::ToDouble(Data[7] & 0x0F));
		units1 += ",";
		units1 += Convert::ToString(Convert::ToDouble(Data[8] >> 4));
		Result += "2f2: " + units1 + " ���" + "\n" + TAB1;
		units2 += Convert::ToString(Convert::ToDouble(Data[8] & 0x0F));
		units2 += Convert::ToString(Convert::ToDouble(Data[9] >> 4));
		units2 += Convert::ToString(Convert::ToDouble(Data[9] & 0x0F));
		units2 += ",";
		units2 += Convert::ToString(Convert::ToDouble(Data[10] >> 4));
		Result += "2f3: " + units2 + " ���" + "\n" + TAB1;
		units4 += Convert::ToString(Convert::ToDouble(Data[10] & 0x0F));
		units4 += Convert::ToString(Convert::ToDouble(Data[11] >> 4));
		units4 += ",";
		units4 += Convert::ToString(Convert::ToDouble(Data[11] & 0x0F));
		Result += "3f3: " + units4 + " ���";
		return Result;
		break;
	case 6:
		units3 += Convert::ToString(Convert::ToDouble(Data[2] & 0x0F));//������� �����
		units3 += Convert::ToString(Convert::ToDouble(Data[3] >> 4));//������
		units3 += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));//�����
		units3 += Convert::ToString(Convert::ToDouble(Data[4] >> 4));
		units3 += Convert::ToString(Convert::ToDouble(Data[4] & 0x0F));
		Result = TAB + "������� �������: " + units3 + " ���";
		return Result;
		break;
	case 7:
		units3 += Convert::ToString(Convert::ToDouble(Data[2] & 0x0F));
		units3 += Convert::ToString(Convert::ToDouble(Data[3] >> 4));
		Result += TAB + "����� �����: " + "\n" + TAB1 + "����. 1-�� ���: " + units3 + " ���" + "\n" + TAB1;
		units += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));
		units += Convert::ToString(Convert::ToDouble(Data[4] >> 4));
		Result += "����. 2-�� ���: " + units + " ���" + "\n" + TAB1;
		units1 += Convert::ToString(Convert::ToDouble(Data[4] & 0x0F));
		units1 += Convert::ToString(Convert::ToDouble(Data[5] >> 4));
		Result += "����. ���������: " + units1 + " ���" + "\n" + TAB1;
		units2 += Convert::ToString(Convert::ToDouble(Data[5] & 0x0F));
		units2 += Convert::ToString(Convert::ToDouble(Data[6] >> 4));
		Result += "����. ���. ��������: " + units2 + " ���" + "\n" + TAB1;
		units4 += Convert::ToString(Convert::ToDouble(Data[6] & 0x0F));
		units4 += Convert::ToString(Convert::ToDouble(Data[7] >> 4));
		Result += "���-�� ��������: " + units4 + " ��." + "\n" + TAB1;
		units5 += Convert::ToString(Convert::ToDouble(Data[7] & 0x0F));
		units5 += Convert::ToString(Convert::ToDouble(Data[8] >> 4));
		Result += "����� ���. ��: " + units5 + " ��.";
		return Result;
		break;
	case 8:
		units += Convert::ToString(Convert::ToDouble(Data[2] & 0x0F));
		units += Convert::ToString(Convert::ToDouble(Data[3] >> 4));
		Result += TAB + "������� ���: " + "\n" + TAB1 + "����� �������: " + units + "\n" + TAB1;
		units1 += Convert::ToString(Convert::ToDouble(Data[3] & 0x0F));
		units1 += Convert::ToString(Convert::ToDouble(Data[4] >> 4));
		Result += "����� �����: " + units1;
		return Result;
		break;
	default:
		break;
	}
	return Result;
}

String ^ PrintResultFromCom(array<unsigned char>^ aray, int testNum)
{
	String^ Result;
	Result = ConvertBitFromCom(aray, Convert::ToInt16(aray[2] >> 4));
	return Result;
}

void Data_Send(SerialPort ^ sp, String ^ prodNum, String ^ Testnum)
{
	array<unsigned char>^ DataArray;
	DataArray = crSarray();
	DataArray[0] = 0xAA; // ������ ������ ������
	DataArray[1] = 0x08;// ��� ������ - 0, ���������� ���������� - 2
	DataArray[2] = Convert::ToChar(Convert::ToInt32(prodNum)); // ����� �������
	DataArray[3] = (unsigned char)Math::Truncate((double)((Convert::ToInt32(Testnum, 16) / 0x100)));
	DataArray[4] = (unsigned char)((double)((Convert::ToInt32(Testnum, 16) % 100)));
	SetCRC(DataArray);
	DataArray[13] = 0xBB;
	ByteReversing(DataArray);
	sp->Write(DataArray, 0, DataArray->Length);
}

String ^ DataRecieave(SerialPort ^ sp, String ^ Testn)
{
	String^ Result;
	array<unsigned char>^ DataArray1;
	DataArray1 = crSarray();
	sp->Read(DataArray1, 0, DataArray1->Length);
	ByteReversing(DataArray1);
	int test = Convert::ToInt32(Testn);
	Result = PrintResultFromCom(DataArray1, test);
	return Result;
}
