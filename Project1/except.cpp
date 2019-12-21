#include "except.h"


bool Except::exCapture(String ^ str, int numberr, System::Windows::Forms::ToolStripStatusLabel ^ ts)
{
	String^ err;
	try
	{
		if (str == nullptr||str=="COM1")
		{
			switch (numberr)
			{
			case 0:
				throw err = "Неверный номер порта";
				break;
			case 1:
				throw err = "Неверный тип файла или файл не был выбран";
				break;
			default:
				break;
			}
		}
	}
	catch (String^)
	{
		ts->Text = err;
		return false;
	}
	return true;
}
