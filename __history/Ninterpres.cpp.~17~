//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Sobre.cpp", frmSobre);
USEFORM("Principal.cpp", frmPrincipal);
USEFORM("Min.cpp", frmMin);
USEFORM("Codigo.cpp", frmCodigo);
USEFORM("Carregar.cpp", frmCarregar);
USEFORM("ImgConf.cpp", frmImgConf);
USEFORM("Configuracoes.cpp", frmConfig);
USEFORM("Idiomas\Tradutor.cpp", frmTradutor);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TfrmPrincipal), &frmPrincipal);
		Application->CreateForm(__classid(TfrmCarregar), &frmCarregar);
		Application->CreateForm(__classid(TfrmCodigo), &frmCodigo);
		Application->CreateForm(__classid(TfrmConfig), &frmConfig);
		Application->CreateForm(__classid(TfrmImgConf), &frmImgConf);
		Application->CreateForm(__classid(TfrmSobre), &frmSobre);
		Application->CreateForm(__classid(TfrmMin), &frmMin);
		Application->CreateForm(__classid(TfrmTradutor), &frmTradutor);
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
