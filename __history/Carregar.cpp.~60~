//---------------------------------------------------------------------------

#include <fmx.h>
#include <IOUtils.hpp>
#include <shlobj.h>
#pragma hdrstop

#include "Carregar.h"
#include "Principal.h"
#include "Codigo.h"
#include "Configuracoes.h"
#include "Sobre.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmCarregar *frmCarregar;
//---------------------------------------------------------------------------
int cont = 0;
//---------------------------------------------------------------------------
__fastcall TfrmCarregar::TfrmCarregar(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCarregar::tmConfigurarTimer(TObject *Sender)
{
	if (cont == 0) {

	lblEstado->Text = "Lendo arquivos...";

	PWSTR pszPath;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
	{
		String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP");
		NSNPLOC = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres");
		NSNPLOCATL = System::Ioutils::TPath::Combine(NSNPLOC, L"NSNPATL");

		if (!TDirectory::Exists(NSNPTEMP)) TDirectory::CreateDirectory(NSNPTEMP);
		if (!TDirectory::Exists(NSNPLOCATL)) TDirectory::CreateDirectory(NSNPLOCATL);

		String NSNA = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSTEMP.nps");
		String NSNS = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSSTEMP.stl");;

		if (TFile::Exists(NSNA)){
			TFile::Delete(NSNA);
		}

		if (TFile::Exists(NSNS)){
			TFile::Delete(NSNS);
		}

		NSNPCONF = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\Config");
		CoTaskMemFree(pszPath);

		if (!TDirectory::Exists(NSNPCONF)) {
			TDirectory::CreateDirectory(NSNPCONF);
		}

	}

		cont ++;

	}

	else if (cont == 1) {

		lblEstado->Text = "Gerando arquivo inicial...";

		String aprmod = System::Ioutils::TPath::Combine(NSNPLOC, L"NSNV");
		String aprstl = System::Ioutils::TPath::Combine(NSNPLOC, L"NSST");

		if (!TFile::Exists(aprmod + ".nps")) {
			frmCodigo->mmCodigo->Lines->SaveToFile(aprmod + ".nps");
		}

		if (!TFile::Exists(aprstl + ".stl")) {
			frmCodigo->mmEstilo->Lines->SaveToFile(aprstl + ".stl");
		}

		tmConfigurar->Interval = 3500;
		cont++;

	}

	else if (cont == 2) {

		lblEstado->Text = "Aplicando configurações do usuário...";

		String NSNPARQCONF = System::Ioutils::TPath::Combine(NSNPCONF, L"CONF");

		if (TFile::Exists(NSNPARQCONF+".conf")) {

			frmConfig->mmConfig->Lines->LoadFromFile(NSNPARQCONF+".conf");

			if (frmConfig->mmConfig->Lines->Count < 15) {
				ShowMessage("ERRO 001000: Arquivo de configuração corrompido excluído.\nConfigurações padrões serão utilizadas.\nOperação de carregamento de configurações cancelada.");
				falha:
				TFile::Delete(NSNPARQCONF+".conf");
			}
			else {
				try {
					TfrmCarregar::AplicarConfig();
				} catch (...) {
					cont++;
					ShowMessage("ERRO 001001: Erro durante a aplicação das configurações.\nAs configurações serão restauradas à seus padrões.");
					goto falha;
				}
			}

		}

		tmConfigurar->Interval = 2500;
		cont++;

	}

	else {

		lblEstado->Text = "Carregando...";

		Application->MainForm->Show();
		tmConfigurar->Enabled = false;
		frmCarregar->Close();

	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCarregar::btFecharClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------
void TfrmCarregar::AplicarConfig()
{

	//---------------------------- Editor -----------------------------------

	if (frmConfig->mmConfig->Lines->Strings[0] == "NSEDT") {
		frmConfig->cbAtivarEditor->IsChecked = true;
		frmCodigo->mmCodigo->ReadOnly = false;
		frmCodigo->mmEstilo->ReadOnly = false;
	}
	else if (frmConfig->mmConfig->Lines->Strings[0] == "!NSEDT") {
		frmConfig->cbAtivarEditor->IsChecked = false;
		frmCodigo->mmCodigo->ReadOnly = true;
		frmCodigo->mmEstilo->ReadOnly = false;
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplicação das configurações.\nAs configurações serão restauradas à seus padrões.");
	}

	//---------------------------- Nome ------------------------------------

	frmConfig->edtNomeLicen->Text = frmConfig->mmConfig->Lines->Strings[13];
	frmSobre->lblLicencProg->Text = frmConfig->mmConfig->Lines->Strings[13];

	//-------------------- Salvamento Automático ---------------------------

	if (frmConfig->mmConfig->Lines->Strings[8] == "NSSVSA") {
		frmConfig->cbSalvarAuto->IsChecked = true;
		frmPrincipal->tmCopiaSeg->Enabled = true;
	}
	else if (frmConfig->mmConfig->Lines->Strings[8] == "!NSSVSA"){
		frmConfig->cbSalvarAuto->IsChecked = false;
		frmPrincipal->tmCopiaSeg->Enabled = false;
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplicação das configurações.\nAs configurações serão restauradas à seus padrões.");
	}

	if (StrToInt(frmConfig->mmConfig->Lines->Strings[10]) >= 0 && StrToInt(frmConfig->mmConfig->Lines->Strings[10]) <= 4 ) {
		frmConfig->lsSelecInter->ItemIndex = StrToInt(frmConfig->mmConfig->Lines->Strings[10]);
		frmPrincipal->tmCopiaSeg->Interval = (StrToInt(frmConfig->lsSelecInter->Selected->Text)*60000);
	}
	else if (StrToInt(frmConfig->mmConfig->Lines->Strings[10]) == 5) {
		int intervalo = StrToInt(frmConfig->mmConfig->Lines->Strings[11]);
		if (intervalo <= 5) {
			frmConfig->lsSelecInter->ItemIndex = StrToInt(frmConfig->mmConfig->Lines->Strings[10]);
			frmConfig->edtTempSeg->Value = 5;
			frmPrincipal->tmCopiaSeg->Interval = 300000;
		}
		else {
			frmConfig->lsSelecInter->ItemIndex = StrToInt(frmConfig->mmConfig->Lines->Strings[10]);
			frmConfig->edtTempSeg->Value = intervalo;
			frmPrincipal->tmCopiaSeg->Interval = intervalo*60000;
		}
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplicação das configurações.\nAs configurações serão restauradas à seus padrões.");
	}

	//--------------------------- Idioma -----------------------------------

	int Idioma = StrToInt(frmConfig->mmConfig->Lines->Strings[14]);
	frmConfig->cbSelecIdioma->ItemIndex = Idioma;

	if (Idioma == 0) {
		frmPrincipal->Idioma->Lang = "pt";
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplicação das configurações.\nAs configurações serão restauradas à seus padrões.");
	}

	//--------------------------- Marcação ---------------------------------

	frmConfig->env = true;
	frmConfig->cbDefPad->IsChecked = true;

}
//---------------------------------------------------------------------------
