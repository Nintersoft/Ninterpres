//---------------------------------------------------------------------------

#include <fmx.h>
// #include <FMX.Platform.Win.hpp>
#include <IOUtils.hpp>
#include <shlobj.h>
#pragma hdrstop

#include "Carregar.h"
#include "Principal.h"
#include "Min.h"
#include "Codigo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmCarregar *frmCarregar;
//---------------------------------------------------------------------------
int cont = 0;
String NSNPLOC;
//---------------------------------------------------------------------------
__fastcall TfrmCarregar::TfrmCarregar(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCarregar::tmConfigurarTimer(TObject *Sender)
{
	if (cont == 0) {
	PWSTR pszPath;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
	{
		String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP");
		NSNPLOC = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres");

		if (!TDirectory::Exists(NSNPTEMP)) {
			TDirectory::CreateDirectory(NSNPTEMP);
		}

		String NSNA = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSTEMP.nps");
		if (TFile::Exists(NSNA)){
			TFile::Delete(NSNA);
		}

		String NSNPCONF = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\Config");
		CoTaskMemFree(pszPath);

		if (!TDirectory::Exists(NSNPCONF)) {
			TDirectory::CreateDirectory(NSNPCONF);
		}

	}
	 cont ++;
	}
	else if (cont == 1) {

		String arq = System::Ioutils::TPath::Combine(NSNPLOC, L"NSNV");

		if (!TFile::Exists(arq+".nps")) {
			frmCodigo->mmCodigo->Lines->SaveToFile(arq+".nps");
		}
		cont++;
	}
	else {
		Application->MainForm->Show();
		frmCarregar->DestroyComponents();
		frmCarregar->Destroying();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCarregar::btFecharClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCarregar::FormCreate(TObject *Sender)
{
/*	HWND hWnd = FormToHWND(frmCarregar);
	if (hWnd != NULL)
	{
		LONG Style = GetWindowLong(hWnd, GWL_EXSTYLE);
		SetWindowLong(hWnd, GWL_EXSTYLE, Style | WS_EX_APPWINDOW);
	}
*/
}
//---------------------------------------------------------------------------
