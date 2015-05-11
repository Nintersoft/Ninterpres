//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("ImgConf.cpp", frmImgConf);
USEFORM("Sobre.cpp", frmSobre);
USEFORM("Principal.cpp", frmPrincipal);
USEFORM("Carregar.cpp", frmCarregar);
USEFORM("Codigo.cpp", frmCodigo);
USEFORM("Idiomas\Tradutor.cpp", frmTradutor);
USEFORM("Configuracoes.cpp", frmConfig);
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
