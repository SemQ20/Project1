#pragma once
#include "namespaces.h"

ref struct I2CParams
{
	unsigned char SlaveAddr;
	unsigned char firstbyte;
};


//������� ��������� ����� ����� ����������� ��������� �� I2C � ����������� � ����������, ���������� �������� ���� String ��� ������ �� �����
String^ ConvertI2CHbyte(array<unsigned char>^ Data, int Testn);

//������� ��������� ������� ����� ����������� ��������� �� I2C � ����������� � ����������, ���������� �������� ���� String ��� ������ �� �����
String^ ConvertI2CLbyte(array<unsigned char>^ Data, int Testn);

String^ ConvResI2CFromIPZO5(int TestNum, array<unsigned char>^ SendData);

String^ ConvResI2CFromIPZO3(int TestNum, array<unsigned char>^ SendData);

