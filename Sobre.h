//---------------------------------------------------------------------------

#ifndef SobreH
#define SobreH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <IdCookieManager.hpp>
//---------------------------------------------------------------------------
class TfrmSobre : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblProg;
	TLabel *lblNomeProg;
	TLabel *lblVersao;
	TLabel *lblVersaoProg;
	TLabel *lblDesenvolvedor;
	TLabel *lblDesenvolvedorProg;
	TRoundRect *btAtualizar;
	TRoundRect *btFacebook;
	TRectangle *btSite;
	TLabel *lblLicenc;
	TLabel *lblLicencProg;
	TLabel *lblAtualizar;
	TLabel *Label2;
	TLabel *Label3;
	TImage *imgLogo;
	TAniIndicator *Indicador;
	TIdHTTP *gerWebArq;
	TLabel *lblEstado;
	TIdSSLIOHandlerSocketOpenSSL *gerSegSSL;
	TMemo *mmDados;
	TTimer *Controle;
	TIdCookieManager *gerWebAt;
	TLabel *lblExt;
	TLabel *lblExtNome;
	void __fastcall btAtualizarClick(TObject *Sender);
	void __fastcall btSiteClick(TObject *Sender);
	void __fastcall btFacebookClick(TObject *Sender);
	void __fastcall btAtualizarMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall btSiteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall btFacebookMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall btAtualizarMouseLeave(TObject *Sender);
	void __fastcall btAtualizarMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall btSiteMouseLeave(TObject *Sender);
	void __fastcall btSiteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall btFacebookMouseLeave(TObject *Sender);
	void __fastcall btFacebookMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ControleTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall gerWebArqWork(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCount);

private:	// User declarations
public:		// User declarations
	int verat;
	bool Atualizado ();
	void AdquirirNomes();
	void Principal ();
	__fastcall TfrmSobre(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSobre *frmSobre;
//---------------------------------------------------------------------------
#endif
