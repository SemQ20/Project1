#pragma once
/*��������� ������ ����5 � �������������� ����� ������ ����������� �� �����*/
String^ IPZO5_Test_Result(int Testnum, int ProdNum, array<unsigned char>^ SendData, Vstr^ valStr);

bool setParamsForTest_IPZO5(int Testn, int ProdNum, I2CParams^ i2cp);

