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
	TMemo *mmEstilo;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmApresentacao(TComponent* Owner);
	void CarregarTransp (int);
	bool comentario (String);
	void RearranjoTransp (int);
	void Padronizar ();
	void AjusteVisual();
	int LocDet(String Valor);
	int AdquireTam (String Texto);

	long double tamFonteBasica, tamFonteTitulo;

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmApresentacao *frmApresentacao;
//---------------------------------------------------------------------------
#endif
