//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Sobre.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmSobre *frmSobre;
//---------------------------------------------------------------------------
__fastcall TfrmSobre::TfrmSobre(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::btAtualizarClick(TObject *Sender)
{
	ShowMessage("Estamos abrindo nossa central de atualiza��es.\nPor favor, aguarde.");
	ShellExecuteA( NULL, "open", "http://www.nintersoft.ml/central-de-projetos/windows/", NULL, NULL, SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::btSiteClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "http://www.nintersoft.ml/", NULL, NULL, SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::btFacebookClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "http://www.facebook.com/Nintersoft", NULL, NULL, SW_SHOW );
}
//---------------------------------------------------------------------------