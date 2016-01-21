//---------------------------------------------------------------------------

#ifndef CriptH
#define CriptH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TfrmCript : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblMensagem;
	TButton *btCancelar;
	TStyleBook *Estilo;
	TButton *btConf;
	TLabel *lblSenha;
	TEdit *edtSenha;
	void __fastcall btCancelarClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btConfClick(TObject *Sender);
	void __fastcall edtSenhaKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCript(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCript *frmCript;
//---------------------------------------------------------------------------
#endif
