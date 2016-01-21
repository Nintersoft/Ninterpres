//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Apresentador.cpp", frmApresentacao);
USEFORM("Cript.cpp", frmCript);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TfrmApresentacao), &frmApresentacao);
		Application->CreateForm(__classid(TfrmCript), &frmCript);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
