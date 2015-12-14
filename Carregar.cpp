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

		cont++;

	}

	else if (cont == 2) {

		lblEstado->Text = "Aplicando configura��es do usu�rio...";

		bool Existe = false;

		String NSNPARQCONF = System::Ioutils::TPath::Combine(NSNPCONF, L"CONF");

		if (TFile::Exists(NSNPARQCONF+".conf")) {

			Existe = true;
			frmConfig->mmConfig->Lines->LoadFromFile(NSNPARQCONF+".conf");

			if (frmConfig->mmConfig->Lines->Count < 15) {
				ShowMessage("ERRO 001000: Arquivo de configura��o corrompido exclu�do.\nConfigura��es padr�es ser�o utilizadas.\nOpera��o de carregamento de configura��es cancelada.");
				falha:
				TFile::Delete(NSNPARQCONF+".conf");
			}
			else {
				try {
					TfrmCarregar::AplicarConfig();
				} catch (...) {
					ShowMessage("ERRO 001001: Erro durante a aplica��o das configura��es.\nAs configura��es ser�o restauradas � seus padr�es.");
					goto falha;
				}
			}

		}

		cont++;
		if (Existe) ReconfiguraCont(5000);
		else ReconfiguraCont(1000);

	}
	else if (cont == 3) {
		lblEstado->Text = "Ajustando a interface...";
		frmPrincipal->AjusteVisual();
		cont++;
		ReconfiguraCont(1500);
	}

	else {

		lblEstado->Text = "Carregando...";

		cont++;
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
		throw Exception ("ERRO 001001: Erro durante a aplica��o das configura��es.\nAs configura��es ser�o restauradas � seus padr�es.");
	}

	if (frmConfig->mmConfig->Lines->Strings[1] == "NSATC") {
		frmConfig->cbAtualizarCod->IsChecked = true;
		frmCodigo->btAlterar->Enabled = true;
	}
	else if (frmConfig->mmConfig->Lines->Strings[1] == "!NSATC") {
		frmConfig->cbAtualizarCod->IsChecked = false;
		frmCodigo->btAlterar->Enabled = false;
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplica��o das configura��es.\nAs configura��es ser�o restauradas � seus padr�es.");
	}

	//-------------------- Tamanho da fonte b�sica -------------------------

	long double tamFonteBasica = StrToFloat(frmConfig->mmConfig->Lines->Strings[2]);
	frmConfig->cxTamFonte->Value = tamFonteBasica;
	frmPrincipal->lblTranspTexto->TextSettings->Font->Size = tamFonteBasica;
	frmPrincipal->tamFonteBasica = tamFonteBasica;
	frmPrincipal->edtTamFonte->Value = tamFonteBasica;
	frmPrincipal->baTamFonte->Value = tamFonteBasica;
	int LOCLIN = frmPrincipal->LocDet("TAM_FONTE");
	frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "TAM:"+FloatToStr(tamFonteBasica);

	//---------------------- Marca��es opcionais ---------------------------

	if (frmConfig->mmConfig->Lines->Strings[3] == "NSMSTR") {
		LOCLIN = frmPrincipal->LocDet("MSTR_TRANSP");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "NSFN";
		frmConfig->cbMostrarTransp->IsChecked = true;
		frmPrincipal->opMostrarNSTransp->IsChecked = true;
	}
	else if (frmConfig->mmConfig->Lines->Strings[3] == "!NSMSTR") {
		LOCLIN = frmPrincipal->LocDet("MSTR_TRANSP");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "!NSFN";
		frmConfig->cbMostrarTransp->IsChecked = false;
		frmPrincipal->opMostrarNSTransp->IsChecked = false;
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplica��o das configura��es.\nAs configura��es ser�o restauradas � seus padr�es.");
	}

	if (frmConfig->mmConfig->Lines->Strings[4] == "NSMSLG") {
		LOCLIN = frmPrincipal->LocDet("MSTR_LOGO");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "NSLG";
		frmConfig->cbMostrarLogo->IsChecked = true;
		frmPrincipal->opMostrarLogoNS->IsChecked = true;
	}
	else if (frmConfig->mmConfig->Lines->Strings[4] == "!NSMSLG") {
		LOCLIN = frmPrincipal->LocDet("MSTR_LOGO");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "!NSLG";
		frmConfig->cbMostrarLogo->IsChecked = false;
		frmPrincipal->opMostrarLogoNS->IsChecked = false;
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplica��o das configura��es.\nAs configura��es ser�o restauradas � seus padr�es.");
	}

	if (frmConfig->mmConfig->Lines->Strings[5] == "NSMSDT") {
		LOCLIN = frmPrincipal->LocDet("MSTR_DATA");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "NSDT";
		frmConfig->cbMostrarData->IsChecked = true;
		frmPrincipal->opMostrarDataAtual->IsChecked = true;
	}
	else if (frmConfig->mmConfig->Lines->Strings[5] == "!NSMSDT") {
		LOCLIN = frmPrincipal->LocDet("MSTR_DATA");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "!NSDT";
		frmConfig->cbMostrarData->IsChecked = false;
		frmPrincipal->opMostrarDataAtual->IsChecked = false;
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplica��o das configura��es.\nAs configura��es ser�o restauradas � seus padr�es.");
	}

	//--------------------- Aplica��o de estilos ---------------------------

	int pos = StrToInt(frmConfig->mmConfig->Lines->Strings[6]);
	if (pos == 0) {
		frmConfig->csEstilo->ItemIndex = pos;
		frmPrincipal->BorderStyle = TFmxFormBorderStyle::Sizeable;
		frmPrincipal->WindowState = TWindowState::wsMaximized;
		frmPrincipal->lblTituloForm->Visible = false;
		frmPrincipal->btMinimizar->Visible = false;
		frmPrincipal->btMaximizar->Visible = false;
		frmPrincipal->btFechar->Visible = false;
		frmPrincipal->btFecharEf->Visible = false;
	}
	else if (pos == 2) {
		frmConfig->csEstilo->ItemIndex = pos;
		frmPrincipal->BorderStyle = TFmxFormBorderStyle::Sizeable;
		frmPrincipal->WindowState = TWindowState::wsMaximized;
		frmPrincipal->lblTituloForm->Visible = false;
		frmPrincipal->btMinimizar->Visible = false;
		frmPrincipal->btMaximizar->Visible = false;
		frmPrincipal->btFechar->Visible = false;
		frmPrincipal->btFecharEf->Visible = false;
	}
	else if (pos == 3) {

		int cor = StrToInt(frmConfig->mmConfig->Lines->Strings[7]);

		frmConfig->csEstilo->ItemIndex = pos;
		frmConfig->listaCorTema->BeginUpdate();
		frmConfig->listaCorTema->Color = cor;
		frmConfig->listaCorTema->EndUpdate();

		frmPrincipal->corAbaAjuda->BeginUpdate();
		frmPrincipal->corAbaAjuda->Fill->Color = cor;
		frmPrincipal->corAbaAjuda->Stroke->Color = cor;
		frmPrincipal->corAbaAjuda->EndUpdate();
		frmPrincipal->corAbaAjuda->Repaint();
		frmPrincipal->CorAbaVisualizar->BeginUpdate();
		frmPrincipal->CorAbaVisualizar->Fill->Color = cor;
		frmPrincipal->CorAbaVisualizar->Stroke->Color = cor;
		frmPrincipal->CorAbaVisualizar->EndUpdate();
		frmPrincipal->CorAbaVisualizar->Repaint();
		frmPrincipal->CorAbaEditar->BeginUpdate();
		frmPrincipal->CorAbaEditar->Fill->Color = cor;
		frmPrincipal->CorAbaEditar->Stroke->Color = cor;
		frmPrincipal->CorAbaEditar->EndUpdate();
		frmPrincipal->CorAbaEditar->Repaint();
		frmPrincipal->FundoAbaSelec->BeginUpdate();
		frmPrincipal->FundoAbaSelec->Fill->Color = cor;
		frmPrincipal->FundoAbaSelec->Stroke->Color = cor;
		frmPrincipal->FundoAbaSelec->EndUpdate();
		frmPrincipal->FundoAbaSelec->Repaint();
		frmConfig->listaCorTema->Enabled = true;
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplica��o das configura��es.\nAs configura��es ser�o restauradas � seus padr�es.");
	}

	//-------------------- Salvamento Autom�tico ---------------------------

	if (frmConfig->mmConfig->Lines->Strings[8] == "NSSVSA") {
		frmConfig->cbSalvarAuto->IsChecked = true;
		frmPrincipal->tmCopiaSeg->Enabled = true;

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
			throw Exception ("ERRO 001001: Erro durante a aplica��o das configura��es.\nAs configura��es ser�o restauradas � seus padr�es.");
		}

	}
	else if (frmConfig->mmConfig->Lines->Strings[8] == "!NSSVSA"){
		frmConfig->cbSalvarAuto->IsChecked = false;
		frmPrincipal->tmCopiaSeg->Enabled = false;
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplica��o das configura��es.\nAs configura��es ser�o restauradas � seus padr�es.");
	}

	//---------------------------- Nome ------------------------------------

	frmConfig->edtNomeLicen->Text = frmConfig->mmConfig->Lines->Strings[13];
	frmSobre->lblLicencProg->Text = frmConfig->edtNomeLicen->Text;

	//--------------------------- Idioma -----------------------------------

	int Idioma = StrToInt(frmConfig->mmConfig->Lines->Strings[14]);
	frmConfig->cbSelecIdioma->ItemIndex = Idioma;

	if (Idioma == 0) {
		frmPrincipal->Idioma->Lang = "pt";
	}
	else {
		throw Exception ("ERRO 001001: Erro durante a aplica��o das configura��es.\nAs configura��es ser�o restauradas � seus padr�es.");
	}

	//--------------------------- Marca��o ---------------------------------

	frmConfig->env = true;
	frmConfig->cbDefPad->IsChecked = true;

}
//---------------------------------------------------------------------------
void TfrmCarregar::ReconfiguraCont (int Tempo)
{
	frmCarregar->tmConfigurar->Enabled = false;
	frmCarregar->tmConfigurar->Interval = Tempo;
	frmCarregar->tmConfigurar->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCarregar::FormShow(TObject *Sender)
{
	tmConfigurar->Enabled = true;
}
//---------------------------------------------------------------------------

