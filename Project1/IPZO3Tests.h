#pragma once
/*��������� ������ ����3 � �������������� ����� ������ ����������� �� �����*/
#include "arrays.h"

/*������� ��� ��������� ���������� ������������, ��� � �.� ��� ���������� ����3*/
String^ setIPZO3ParamsToI2c(I2CParams^ i2cp);

String^ IPZO3_Test_Result(int TestNum, array<unsigned char>^ SendData, Vstr^ valStr);

bool setParamsForTest_IPZO3(int Testn, I2CParams^ i2cp);