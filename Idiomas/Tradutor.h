//---------------------------------------------------------------------------

#ifndef TradutorH
#define TradutorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TfrmTradutor : public TForm
{
__published:	// IDE-managed Components
	TMemo *mmTraducao;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmTradutor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmTradutor *frmTradutor;
//---------------------------------------------------------------------------
#endif
