//---------------------------------------------------------------------------

#include <fmx.h>
#include <IOUtils.hpp>
#include <shlobj.h>
#pragma hdrstop

#include "Configuracoes.h"
#include "Codigo.h"
#include "Principal.h"
#include "Sobre.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmConfig *frmConfig;
//---------------------------------------------------------------------------
bool TempConf[5];
//---------------------------------------------------------------------------
__fastcall TfrmConfig::TfrmConfig(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::btAjudaCorClick(TObject *Sender)
{
	ShowMessage("Fique atento com a cor escolhida!\nDependendo da cor, sua experiência visual poderá não ser como o esperado!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btAjudaAppDataClick(TObject *Sender)
{
	ShowMessage("Usar pasta %APPDATA%\\Nintersoft\\Ninterpres\\TEMP para pré-carregar os arquivos da apresentação caso ainda não tenha sido salva.\nCaso você desmarque esta opção, será mostrada uma caixa para salvar sua apresentação ao iniciar o programa.");
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btAjudaCopiaClick(TObject *Sender)
{
	ShowMessage("Salva uma cópia de segurança de sua apresentação automaticamente.");
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btAjudaEditorClick(TObject *Sender)
{
		ShowMessage("Ativa a edição do código da apresentação.\nRecomendamos que visite nossa DocWiki antes de realizar quaisquer alterações no código.");
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btCancelarClick(TObject *Sender)
{
	frmConfig->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btSalvarClick(TObject *Sender)
{
	SalvarConfig();
	AplicarImpConfig();

	if (cbDefPad->IsChecked) {

		PWSTR pszPath;
		if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
		{
			String NSNPCONF = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\Config");
			String NSNPARQCONF = System::Ioutils::TPath::Combine(NSNPCONF, L"CONF");
			CoTaskMemFree(pszPath);

			frmConfig->mmConfig->Lines->SaveToFile(NSNPARQCONF+".conf");

		}
		else {
			throw Exception ("ERRO 001002: Não foi possível salvar suas configurações personalizadas para a próxima inicialização.");
		}
	}

	frmConfig->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::FormCreate(TObject *Sender)
{
	for (int i = 0; i < 5; i++) {
		TempConf[i] = false;
	}

	env = false;

}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btAjudaEstiloClick(TObject *Sender)
{
	ShowMessage("Escolha o estilo da borda da aplicação.");
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btAjudaAtualizarClick(TObject *Sender)
{
	ShowMessage("Libera a aplicação da atualização diretamente pelo código.\nAtenção: Ative esta funcionalidade apenas se você possuir conhecimentos avançados no Ninterpres");
}
//---------------------------------------------------------------------------

void TfrmConfig::Restaurar()
{
	frmConfig->cbAtivarEditor->IsChecked = false;
	frmConfig->cbAtualizarCod->IsChecked = false;
	frmConfig->cxTamFonte->Value = 16;
	frmConfig->cbMostrarTransp->IsChecked = true;
	frmConfig->cbMostrarLogo->IsChecked = true;
	frmConfig->cbMostrarData->IsChecked = false;
	frmConfig->csEstilo->ItemIndex = 1;
	frmConfig->listaCorTema->ItemIndex = 30;
	frmConfig->cbSalvarAuto->IsChecked = false;
	frmConfig->btApresTemp->IsChecked = false;
	frmConfig->lsSelecInter->ItemIndex = 2;
	frmConfig->edtTempSeg->Value = 5;
	frmConfig->cbSalvarTemp->IsChecked = true;
	frmConfig->edtNomeLicen->Text = "Equipe de desenvolvimento Nintersoft";
	frmConfig->cbSelecIdioma->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btRestaurarClick(TObject *Sender)
{
	int Conf = MessageBox (0, L"Você está certo disso?\nEsta ação restaurará todas as configurações às configurações de instalação!", L"Ninterpres - Aviso", MB_YESNO+MB_ICONQUESTION);
	if (Conf == 6) {
		Restaurar();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmConfig::cbDefPadChange(TObject *Sender)
{
	if (!env) {
		if (!cbDefPad->IsChecked) {
			ShowMessage("Atenção!\nSuas configurações não serão salvas para futuras execuções deste programa.");
		}
		else {
			ShowMessage("Atenção!\nEsta é apenas uma versão BETA do Ninterpres.\nApós a próxima atualização suas configurções personalizadas serão perdidas.");
		}
	}
	else {
    	env = false;
	}
}
//---------------------------------------------------------------------------

void TfrmConfig::SalvarConfig()
{
	frmConfig->mmConfig->BeginUpdate();
	frmConfig->mmConfig->Lines->Clear();

	if (frmConfig->cbAtivarEditor->IsChecked) {
		frmConfig->mmConfig->Lines->Add("NSEDT");
	}
	else {
		frmConfig->mmConfig->Lines->Add("!NSEDT");
	}

	if (frmConfig->cbAtualizarCod->IsChecked) {
		frmConfig->mmConfig->Lines->Add("NSATC");
	}
	else {
		frmConfig->mmConfig->Lines->Add("!NSATC");
	}

	frmConfig->mmConfig->Lines->Add(FloatToStr(cxTamFonte->Value));

	if (cbMostrarTransp->IsChecked) {
		frmConfig->mmConfig->Lines->Add("NSMSTR");
	}
	else {
		frmConfig->mmConfig->Lines->Add("!NSMSTR");
	}

	if (cbMostrarLogo->IsChecked) {
		frmConfig->mmConfig->Lines->Add("NSMSLG");
	}
	else {
		frmConfig->mmConfig->Lines->Add("!NSMSLG");
	}

	if (cbMostrarData->IsChecked) {
		frmConfig->mmConfig->Lines->Add("NSMSDT");
	}
	else {
		frmConfig->mmConfig->Lines->Add("!NSMSDT");
	}

	frmConfig->mmConfig->Lines->Add(IntToStr(csEstilo->ItemIndex));

	frmConfig->mmConfig->Lines->Add(IntToStr(listaCorTema->ItemIndex));

	if (cbSalvarAuto->IsChecked) {
		frmConfig->mmConfig->Lines->Add("NSSVSA");
	}
	else {
		frmConfig->mmConfig->Lines->Add("!NSSVSA");
	}

	if (btApresTemp->IsChecked) {
		frmConfig->mmConfig->Lines->Add("NSSVAT");
	}
	else {
		frmConfig->mmConfig->Lines->Add("!NSSVAT");
	}

	int Intervalo = lsSelecInter->ItemIndex;
	if (Intervalo >= 0) frmConfig->mmConfig->Lines->Add(IntToStr(Intervalo));
	else {
		Intervalo++;
		frmConfig->mmConfig->Lines->Add(IntToStr(Intervalo));
	}

	int TempSeg = edtTempSeg->Value;
	frmConfig->mmConfig->Lines->Add(IntToStr(TempSeg));

	if (cbSalvarTemp->IsChecked) {
		frmConfig->mmConfig->Lines->Add("NSSVAD");
	}
	else {
		frmConfig->mmConfig->Lines->Add("!NSSVAD");
	}

	frmConfig->mmConfig->Lines->Add(edtNomeLicen->Text);

	frmConfig->mmConfig->Lines->Add(IntToStr(cbSelecIdioma->ItemIndex));

	frmConfig->mmConfig->EndUpdate();
}
//---------------------------------------------------------------------------

void TfrmConfig::AplicarImpConfig()
{
	if (mmConfig->Lines->Strings[0] == "NSEDT") {
		frmCodigo->mmCodigo->ReadOnly = false;
		frmCodigo->mmEstilo->ReadOnly = false;
	}
	else {
		frmCodigo->mmCodigo->ReadOnly = true;
		frmCodigo->mmEstilo->ReadOnly = true;
	}

	frmSobre->lblLicencProg->Text = frmConfig->mmConfig->Lines->Strings[1];

}
//---------------------------------------------------------------------------
