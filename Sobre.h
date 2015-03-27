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
	void __fastcall btAtualizarClick(TObject *Sender);
	void __fastcall btSiteClick(TObject *Sender);
	void __fastcall btFacebookClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSobre(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSobre *frmSobre;
//---------------------------------------------------------------------------
#endif
