//---------------------------------------------------------------------------

#ifndef ConfiguracoesH
#define ConfiguracoesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Colors.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
//---------------------------------------------------------------------------
class TfrmConfig : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblCorTema;
	TLabel *lblNome;
	TCornerButton *btSalvar;
	TCornerButton *btCancelar;
	TColorListBox *listaCorTema;
	TEdit *edtNomeLicen;
	TGroupBox *Caixa1;
	TCheckBox *CheckBox1;
	TGroupBox *Caixa2;
	TCornerButton *btRestaurar;
	TMemo *mmConfig;
	TSpeedButton *btAjudaCor;
	TCheckBox *cbAtivarEditor;
	TCheckBox *cbSalvarAuto;
	TCheckBox *cbSalvarTemp;
	TSpeedButton *btAjudaEditor;
	TSpeedButton *btAjudaCopia;
	TSpeedButton *btAjudaAppData;
	TLabel *lblIntervalo;
	TCheckBox *btApresTemp;
	TListBox *lsSelecInter;
	void __fastcall btAjudaCorClick(TObject *Sender);
	void __fastcall btAjudaAppDataClick(TObject *Sender);
	void __fastcall btAjudaCopiaClick(TObject *Sender);
	void __fastcall btAjudaEditorClick(TObject *Sender);
	void __fastcall btCancelarClick(TObject *Sender);
	void __fastcall btSalvarClick(TObject *Sender);
	void __fastcall cbAtivarEditorChange(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmConfig(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfig *frmConfig;
//---------------------------------------------------------------------------
#endif