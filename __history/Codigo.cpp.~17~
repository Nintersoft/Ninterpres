//---------------------------------------------------------------------------

#include <fmx.h>
#include <FMX.Platform.Win.hpp>
#pragma hdrstop

#include "Codigo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmCodigo *frmCodigo;
//---------------------------------------------------------------------------
__fastcall TfrmCodigo::TfrmCodigo(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmCodigo::FormCreate(TObject *Sender)
{
	HWND hWnd = FormToHWND(frmCodigo);
	if (hWnd != NULL)
	{
		LONG Style = GetWindowLong(hWnd, GWL_EXSTYLE);
		SetWindowLong(hWnd, GWL_EXSTYLE, Style | WS_EX_APPWINDOW);
	}
}
//---------------------------------------------------------------------------

