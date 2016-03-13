//---------------------------------------------------------------------------

#ifndef ImgConfH
#define ImgConfH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Controls.Presentation.hpp>
//---------------------------------------------------------------------------
class TfrmImgConf : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblImgLeg;
	TEdit *edtImgLeg;
	TRoundRect *btSalvar;
	TLabel *lblBtSalvar;
	void __fastcall btSalvarClick(TObject *Sender);
	void __fastcall edtImgLegKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btSalvarMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall btSalvarMouseLeave(TObject *Sender);
	void __fastcall btSalvarMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmImgConf(TComponent* Owner);
	void CarregarDadosVar (int);
	void SalvarDepend ();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmImgConf *frmImgConf;
//---------------------------------------------------------------------------
#endif
