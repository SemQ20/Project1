#pragma once
#include "namespaces.h"

ref struct Vstr { //��������� ���������� ������������ �������
	String^ PValue; // ����� ����� �������� ������ ����� String ����� ����� ����� ����������� ����-��
	String^ DValue; // ������� ����� �������� ������ ����� String ����� ����� ����� ����������� ����-��
	int OKnum; // ����� ������ ��1 ��� ��2
	int Fnum; // ������� (f2,f3,f4)
	int CableNum; // ����� ������ ��� ����������� ����-�� �� ��������
	double power;
	double(*CABLE_KOEF)[2][3]; //������ �������� ��� �������
	double(*POWER_KOEF)[3]; //������ ���-�� ��� ��������
	double(*POWER_CORRECT)[2][3];
};

void setStrParams(int Test, Vstr ^valStr, String^ integer, String^ tenth);

double PowerCorrection(Vstr ^valStr);

String^ PowerCorrect(Vstr ^valStr);
