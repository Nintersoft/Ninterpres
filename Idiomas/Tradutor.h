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
#include <FMX.Menus.hpp>
#include <FMX.Grid.hpp>
#include <FMX.TabControl.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class TfrmTradutor : public TForm
{
__published:	// IDE-managed Components
	TMemo *mmTraducao;
	TMenuBar *barraCatalogo;
	TTabControl *abasTraducao;
	TTabItem *abaTradPrinc;
	TTabItem *abaTradConfig;
	TTabItem *abaTradSobre;
	TTabItem *abaTradRest;
	TStringGrid *StringGrid1;
	TStringColumn *clOriginal;
	TStringColumn *clTraducao;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmTradutor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmTradutor *frmTradutor;
//---------------------------------------------------------------------------
#endif
