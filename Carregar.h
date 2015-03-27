//---------------------------------------------------------------------------

#ifndef CarregarH
#define CarregarH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TfrmCarregar : public TForm
{
__published:	// IDE-managed Components
	TImage *btFechar;
	TImage *btMinimizar;
	TLabel *Label1;
	TAniIndicator *AniIndicator1;
	TTimer *tmConfigurar;
	void __fastcall tmConfigurarTimer(TObject *Sender);
	void __fastcall btFecharClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCarregar(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCarregar *frmCarregar;
//---------------------------------------------------------------------------
#endif
