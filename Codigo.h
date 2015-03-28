//---------------------------------------------------------------------------

#ifndef CodigoH
#define CodigoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmCodigo : public TForm
{
__published:	// IDE-managed Components
	TMemo *mmCodigo;
	TRectangle *bmPrincipal;
	TSpeedButton *btAlterar;
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCodigo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCodigo *frmCodigo;
//---------------------------------------------------------------------------
#endif