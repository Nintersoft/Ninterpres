//---------------------------------------------------------------------------

#ifndef AtualizarH
#define AtualizarH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
//---------------------------------------------------------------------------
class TfrmAtualizar : public TForm
{
__published:	// IDE-managed Components



private:	// User declarations
public:		// User declarations
	__fastcall TfrmAtualizar(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAtualizar *frmAtualizar;
//---------------------------------------------------------------------------
#endif