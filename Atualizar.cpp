//---------------------------------------------------------------------------

#include <fmx.h>
#include <System.IOUtils.hpp>
#pragma hdrstop

#include "Atualizar.h"
#include "Sobre.h"
#include "Carregar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.Windows.fmx", _PLAT_MSWINDOWS)

TfrmAtualizar *frmAtualizar;
//---------------------------------------------------------------------------
__fastcall TfrmAtualizar::TfrmAtualizar(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


