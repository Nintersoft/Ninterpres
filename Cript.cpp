//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Cript.h"
#include "Principal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmCript *frmCript;
//---------------------------------------------------------------------------
__fastcall TfrmCript::TfrmCript(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCript::Button1Click(TObject *Sender)
{
	frmCript->Hide();
	frmPrincipal->SalvaCript();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCript::btCancelarClick(TObject *Sender)
{
	frmCript->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCript::FormShow(TObject *Sender)
{
	frmCript->Invalidate();
}
//---------------------------------------------------------------------------

