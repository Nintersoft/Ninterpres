//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Cript.h"
#include "CriptLib.h"
#include "Apresentador.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma comment (lib, "CriptLib.lib")

TfrmCript *frmCript;
//---------------------------------------------------------------------------
int tentativas = 5;
//---------------------------------------------------------------------------
__fastcall TfrmCript::TfrmCript(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCript::btCancelarClick(TObject *Sender)
{
	int escSalva = MessageBox (0, L"Esta ação fará com que a aplicação seja encerrada.\nVocê tem certeza que deseja continuar?", L"Aviso - Ninterpres", MB_YESNO+MB_ICONQUESTION);
	if (escSalva == 6) {
		Application->Terminate();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCript::FormClose(TObject *Sender, TCloseAction &Action)
{
	int escSalva = MessageBox (0, L"Esta ação fará com que a aplicação seja encerrada.\nVocê tem certeza que deseja continuar?", L"Aviso - Ninterpres", MB_YESNO+MB_ICONQUESTION);
	if (escSalva == 6) {
		Application->Terminate();
	}
	else {
		Action = TCloseAction::caNone;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCript::btConfClick(TObject *Sender)
{
	try {
		CriptLib::Decriptar::Subst(edtSenha->Text, frmApresentacao->mmCodigo);
		CriptLib::Decriptar::Subst(edtSenha->Text, frmApresentacao->mmEstilo);
		frmCript->Hide();
		frmApresentacao->LerApresentacao();
		frmApresentacao->Show();
	} catch (...) {
		tentativas--;
		if (tentativas > 0) {
			ShowMessage("Problema no processo de decriptação dos arquivos (Possivelmente senha incorreta).\nVocê ainda tem "+IntToStr(tentativas)+" tentativas.");
		}
		else {
			ShowMessage("Esgotaram-se as tentativas. A aplicação será encerrada.");
			Application->Terminate();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCript::edtSenhaKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
	if (Key == VK_RETURN) {
		frmCript->btConfClick(btConf);
	}
}
//---------------------------------------------------------------------------
