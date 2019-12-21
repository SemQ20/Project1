#include "PowerCorrect.h"

void setStrParams(int Test, Vstr ^ valStr, String ^ integer, String ^ tenth)
{
	switch (Test)
	{
	case 701:
		valStr->OKnum = 1;
		valStr->Fnum = 2;
		valStr->CableNum = 4;
		valStr->PValue = integer;
		valStr->DValue = tenth;
		break;
	case 702:
		valStr->OKnum = 1;
		valStr->Fnum = 3;
		valStr->CableNum = 4;
		valStr->PValue = integer;
		valStr->DValue = tenth;
		break;
	case 703:
		valStr->OKnum = 1;
		valStr->Fnum = 4;
		valStr->CableNum = 1;
		valStr->PValue = integer;
		valStr->DValue = tenth;
		break;
	case 704:
		valStr->OKnum = 2;
		valStr->Fnum = 2;
		valStr->CableNum = 4;
		valStr->PValue = integer;
		valStr->DValue = tenth;
		break;
	case 705:
		valStr->OKnum = 2;
		valStr->Fnum = 3;
		valStr->CableNum = 4;
		valStr->PValue = integer;
		valStr->DValue = tenth;
		break;
	case 706:
		valStr->OKnum = 2;
		valStr->Fnum = 4;
		valStr->CableNum = 1;
		valStr->PValue = integer;
		valStr->DValue = tenth;
		break;
	default:break;
	}
}

double PowerCorrection(Vstr ^ valStr)
{
	valStr->power *= 0.1f;
	if (valStr->power < 50)
		return valStr->POWER_CORRECT[0][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 500)
		return valStr->POWER_CORRECT[1][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 1000)
		return valStr->POWER_CORRECT[2][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 2000)
		return valStr->POWER_CORRECT[3][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 5000)
		return valStr->POWER_CORRECT[4][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 8000)
		return valStr->POWER_CORRECT[5][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 11000)
		return valStr->POWER_CORRECT[6][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 13000)
		return valStr->POWER_CORRECT[7][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 15000)
		return valStr->POWER_CORRECT[8][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 16000)
		return valStr->POWER_CORRECT[9][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 17000)
		return valStr->POWER_CORRECT[10][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 18000)
		return valStr->POWER_CORRECT[11][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 19000)
		return valStr->POWER_CORRECT[12][valStr->OKnum - 1][valStr->Fnum - 2];
	else if (valStr->power < 20000)
		return valStr->POWER_CORRECT[13][valStr->OKnum - 1][valStr->Fnum - 2];
	else if ((valStr->power < 22000) || (valStr->power >= 22000))
		return valStr->POWER_CORRECT[14][valStr->OKnum - 1][valStr->Fnum - 2];
	return 1.0f;
}

String ^ PowerCorrect(Vstr ^ valStr)
{
	double Power;
	int PowerInt;
	String^ PowerStr;
	String^ Result;
	Power = (Convert::ToDouble(valStr->PValue));
	Power = Power * (valStr->CABLE_KOEF[valStr->CableNum][valStr->OKnum - 1][valStr->Fnum - 2]) * (valStr->POWER_KOEF[valStr->OKnum - 1][valStr->Fnum - 2]);
	Power = Power * PowerCorrection(valStr);
	PowerInt = Convert::ToInt16(Power);
	PowerStr = Convert::ToString(PowerInt);

	if (PowerInt <= 0)
	{
		return Result = valStr->PValue + "," + valStr->DValue + " Âò";
	}
	else
	{
		return Result = PowerStr + "," + valStr->DValue + " Âò";
	}
}
