//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "ImgConf.h"
#include "Principal.h"
#include "Codigo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmImgConf *frmImgConf;
//---------------------------------------------------------------------------
	int Transp;
//---------------------------------------------------------------------------
__fastcall TfrmImgConf::TfrmImgConf(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmImgConf::btSalvarClick(TObject *Sender)
{
	SalvarDepend();
}
//---------------------------------------------------------------------------
void TfrmImgConf::CarregarDadosVar (int transp)
{
	Transp = transp;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImgConf::edtImgLegKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
	if (Key == VK_RETURN) {
		SalvarDepend();
	}
}
//---------------------------------------------------------------------------
void TfrmImgConf::SalvarDepend ()
{
	if (edtImgLeg->Text.IsEmpty()) {
		frmPrincipal->lblImgLeg->Text = "";
		frmPrincipal->lblImgLeg->Visible = false;
		frmImgConf->Close();
	}
	else {
		frmPrincipal->lblImgLeg->Text = edtImgLeg->Text;
		frmPrincipal->lblImgLeg->Visible = true;
		if (Transp == 0) {
			int loc, pos = 0, tam = frmCodigo->mmCodigo->Lines->Count;
			for (int i = 0; i < tam; i++) {
				if (frmCodigo->mmCodigo->Lines->Strings[i] == "$CAPA") {
					loc = i + 1;
					i = tam;
				}
			}
			do {
				while (frmPrincipal->comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
					loc++;
				}
				if (pos == 0) {
					loc++;
					pos++;
				}
				else if (pos == 1) {
					frmCodigo->mmCodigo->Lines->Strings[loc] = edtImgLeg->Text;
					pos++;
					loc++;
				}
				else {
					loc++;
				}
			} while (frmCodigo->mmCodigo->Lines->Strings[loc] != "!(FDT)");
		}
		else frmPrincipal->lblImgLeg->Text = edtImgLeg->Text;
		frmImgConf->Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmImgConf::FormShow(TObject *Sender)
{
	edtImgLeg->GoToTextEnd();
}
//---------------------------------------------------------------------------

void __fastcall TfrmImgConf::btSalvarMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, float X, float Y)
{
	btSalvar->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmImgConf::btSalvarMouseLeave(TObject *Sender)
{
	btSalvar->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmImgConf::btSalvarMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btSalvar->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

