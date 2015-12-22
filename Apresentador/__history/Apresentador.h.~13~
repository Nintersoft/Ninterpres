//---------------------------------------------------------------------------

#ifndef ApresentadorH
#define ApresentadorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Memo.hpp>
//---------------------------------------------------------------------------
class TfrmApresentacao : public TForm
{
__published:	// IDE-managed Components
	TRectangle *vsTransp;
	TScrollBox *brTransp;
	TLabel *lblTitulo;
	TText *lblTranspTexto;
	TLabel *lblImgLeg;
	TImage *imgTransp;
	TImage *imgLogoNS;
	TMemo *mmCodigo;
	TMemo *mmTranspCont;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmApresentacao(TComponent* Owner);
	void CarregarTransp (int);
	bool comentario (String);
	void RearranjoTransp (int);
	void Padronizar ();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmApresentacao *frmApresentacao;
//---------------------------------------------------------------------------
#endif
