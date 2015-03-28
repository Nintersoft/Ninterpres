//---------------------------------------------------------------------------

#include <fmx.h>
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
	ShowMessage("Fique atento com a cor escolhida!\nDependendo da cor, sua experi�ncia visual poder� n�o ser como o esperado!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btAjudaAppDataClick(TObject *Sender)
{
	ShowMessage("Usar pasta %APPDATA%\\Nintersoft\\Ninterpres\\TEMP para pr�-carregar os arquivos da apresenta��o caso ainda n�o tenha sido salva.\nCaso voc� desmarque esta op��o, ser� mostrada uma caixa para salvar sua apresenta��o ao iniciar o programa.");
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btAjudaCopiaClick(TObject *Sender)
{
	ShowMessage("Salva uma c�pia de seguran�a de sua apresenta��o automaticamente.");
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btAjudaEditorClick(TObject *Sender)
{
		ShowMessage("Ativa a edi��o do c�digo da apresenta��o.\nRecomendamos que visite nossa DocWiki antes de realizar quaisquer altera��es no c�digo.");
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btCancelarClick(TObject *Sender)
{
	frmConfig->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmConfig::btSalvarClick(TObject *Sender)
{
	mmConfig->Lines->Clear();
		if (TempConf[0]) {
			mmConfig->Lines->Add("NSEDT");
			frmCodigo->mmCodigo->ReadOnly = false;
		}
		else {
			mmConfig->Lines->Add("!NSEDT");
			frmCodigo->mmCodigo->ReadOnly = true;
		}
		frmSobre->lblLicencProg->Text = edtNomeLicen->Text;
	frmConfig->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::cbAtivarEditorChange(TObject *Sender)
{
	if (cbAtivarEditor->IsChecked) {
		TempConf[0] = true;
	}
	else {
		TempConf[0] = false;
	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmConfig::FormCreate(TObject *Sender)
{
	for (int i = 0; i < 5; i++) {
		TempConf[i] = false;
	}
}
//---------------------------------------------------------------------------
