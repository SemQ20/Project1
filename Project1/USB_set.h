#ifndef USB_SET_H
#define USB_SET_H

#include "namespaces.h"

//������ ��������� ��� COM ����� � ��������� ���
void USB_Set(SerialPort^sp, String^ comport);

//�������� ����������� ����� ��� ����
void SetCRC(array<unsigned char>^ data);

//��������������� ������� ��� ������� ������
unsigned char GetMask(unsigned char index);

//������� ��� ������� ������
void ByteReversing(array<unsigned char>^ barray);

String^ ConvertBitFromCom(array<unsigned char>^ Data, int testnum);

String^ PrintResultFromCom(array<unsigned char>^ aray, int testNum);

void Data_Send(SerialPort^sp, String^ prodNum, String^Testnum);

String^ DataRecieave(SerialPort^ sp, String^ Testn);

#endif // !USB_SET_H