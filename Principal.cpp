//---------------------------------------------------------------------------

#include <fmx.h>
#include <IOUtils.hpp>
#include <System.Zip.hpp>
#include <shlobj.h>
#pragma hdrstop

#include "Principal.h"
#include "Codigo.h"
#include "Configuracoes.h"
#include "ImgConf.h"
#include "Sobre.h"
#include "Min.h"
#include "Carregar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
int tpEscolha = 1, Cam = 390, Transp = 0, CorBordaTransp, CorFundoTransp, Vis = 0;
bool prim, salvo = false, confSalvo = false;
String TranspSelec, locSalvo;
//---------------------------------------------------------------------------
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btTranspTipoMouseEnter(TObject *Sender)
{
	btTranspTipo->ShowScrollBars = true;
	lblTranspTipo->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btTranspTipoMouseLeave(TObject *Sender)
{
	btTranspTipo->ShowScrollBars = false;
	lblTranspTipo->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tpTipo2Click(TObject *Sender)
{
	spTipoSelec->Position->X = tpTipo2->Position->X - 8;
	tpEscolha = 2;
	btCriarTransp->Enabled = true;
	btModTransp->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tpTipo1Click(TObject *Sender)
{
	spTipoSelec->Position->X = tpTipo1->Position->X - 8;
	tpEscolha = 1;
	btCriarTransp->Enabled = true;
	btModTransp->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tpTipo3Click(TObject *Sender)
{
	spTipoSelec->Position->X = tpTipo3->Position->X - 8;
	tpEscolha = 3;
	btCriarTransp->Enabled = true;
	btModTransp->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tpTipo4Click(TObject *Sender)
{
	spTipoSelec->Position->X = tpTipo4->Position->X - 8;
	tpEscolha = 4;
	btCriarTransp->Enabled = true;
	btModTransp->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tpTipo5Click(TObject *Sender)
{
	spTipoSelec->Position->X = tpTipo5->Position->X - 8;
	tpEscolha = 5;
	btCriarTransp->Enabled = true;
	btModTransp->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tpTipo6Click(TObject *Sender)
{
	spTipoSelec->Position->X = tpTipo6->Position->X - 8;
	tpEscolha = 6;
	btCriarTransp->Enabled = true;
	btModTransp->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tpTipo7Click(TObject *Sender)
{
	spTipoSelec->Position->X = tpTipo7->Position->X - 8;
	tpEscolha = 7;
	btCriarTransp->Enabled = true;
	btModTransp->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSelecImagemClick(TObject *Sender)
{
	if (daImagem->Execute()) {

		edCamTranspImg->Text = daImagem->FileName;

		PWSTR pszPath;
		if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
		{
			String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP\\IMG");
			CoTaskMemFree(pszPath);

			if (!TDirectory::Exists(NSNPTEMP)) {
				TDirectory::CreateDirectory(NSNPTEMP);
			}

			String ext = Extensao(edCamTranspImg->Text);
			String arqt, arq;

			if (Transp == 0) {
				arq = System::Ioutils::TPath::Combine(NSNPTEMP, L"CAPA");
			}
			else {
				arqt = "TRANSP" + IntToStr(Transp);
				arq = System::Ioutils::TPath::Combine(NSNPTEMP, arqt);
			}

			TFile::Copy(edCamTranspImg->Text , arq+ext, true);

			if (Transp == 0) {
				int loc, tam = frmCodigo->mmCodigo->Lines->Count;
				for (int i = 0; i < tam; i++) {
					if (frmCodigo->mmCodigo->Lines->Strings[i] == "$CAPA") {
						loc = i + 1;
						i = tam;
					}
				}
				while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
					loc++;
				}
					frmCodigo->mmCodigo->Lines->Strings[loc] = "..\\IMG\\CAPA" + ext;
			}

			edCamTranspImg->Text =  arq+ext;

	}


		imgTransp->Bitmap->LoadFromFile(edCamTranspImg->Text);
		imgTransp->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAjudaAutorClick(TObject *Sender)
{
	ShowMessage("Caso haja mais de um autor, voc� dever� separ�-los \ncom v�rgula de acordo com as normas ABNT.");

}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::edtApresTituloExit(TObject *Sender)
{
	if (edtApresTitulo->Text != "") {
		frmPrincipal->Caption = edtApresTitulo->Text + " - Ninterpres";
		frmPrincipal->lblTituloForm->Text = edtApresTitulo->Text + " - Ninterpres";
		frmCodigo->mmCodigo->Lines->Strings[0] = edtApresTitulo->Text;
	}
	else {
		frmPrincipal->Caption = "Apresenta��o sem t�tulo - Ninterpres";
		frmPrincipal->lblTituloForm->Text = "Apresenta��o sem t�tulo - Ninterpres";
		frmCodigo->mmCodigo->Lines->Strings[0] = "Apresenta��o sem t�tulo";
		edtApresTitulo->Text = "Apresenta��o sem t�tulo";

		if (Transp == 0){
			lblTitulo->Text = "T�tulo da apresenta��o";
			edTranspTitulo->Text = "";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::lblTranspTipoMouseEnter(TObject *Sender)
{
	btTranspTipo->ShowScrollBars = true;
	lblTranspTipo->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::lblTranspTipoMouseLeave(TObject *Sender)
{
	btTranspTipo->ShowScrollBars = false;
	lblTranspTipo->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSelecVisualizarClick(TObject *Sender)
{
	Abas->ActiveTab = frmPrincipal->AbaVisualizar;
	FundoAbaSelec->Visible = true;
	FundoAbaSelec->Position->X = btSelecVisualizar->Position->X;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSelecEditarClick(TObject *Sender)
{
	Abas->ActiveTab = frmPrincipal->AbaEditar;
	FundoAbaSelec->Visible = true;
	FundoAbaSelec->Position->X = btSelecEditar->Position->X;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSelecAjudaClick(TObject *Sender)
{
	Abas->ActiveTab = frmPrincipal->AbaAjuda;
	FundoAbaSelec->Visible = true;
	FundoAbaSelec->Position->X = btSelecAjuda->Position->X;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSelecArquivoClick(TObject *Sender)
{
	Abas->ActiveTab = frmPrincipal->AbaArquivo;
	FundoAbaSelec->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::FormShow(TObject *Sender)
{

	CorFundoTransp = frmPrincipal->vsTransp->Fill->Color;

	TSize Tamanho = Screen->Size();
	frmPrincipal->Width = Tamanho.Width;
	frmPrincipal->Height = Tamanho.Height - 40;

	btMaximizar->Enabled = false;

	Transp = 0;

	if (prim) {

		SelecTransp->BeginUpdate();
		SelecTransp->Items->Add()->Text = "CAPA";
		SelecTransp->EndUpdate();

		frmCarregar->Show();
		frmPrincipal->Visible = false;
		prim = false;

	}

	int COR = listaCorApresenta->Color;
	vsTransp->Fill->Color = COR;
	frmCodigo->mmCodigo->Lines->Strings[2] = IntToStr(COR);

	lblTranspTexto->TextSettings->Font->Size = StrToFloat(frmCodigo->mmCodigo->Lines->Strings[7]);

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btFecharClick(TObject *Sender)
{
	frmPrincipal->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSalvarDadosClick(TObject *Sender)
{
	if (Transp == 0) {
		ShowMessage("Os dados da capa s�o alterados e salvos automaticamente!");
	}
	else {
		ModificarDados(Transp);
		CarregarTransp(Transp);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btLimpDadosClick(TObject *Sender)
{
	int LimpConf = MessageBox (0, L"Voc� est� certo disso?\nEsta a��o n�o pode ser desfeita.\nVoc� ter� que reconfigurar tudo novamente!", L"Ninterpres - Aviso", MB_YESNO+MB_ICONQUESTION);
	if (LimpConf == 6) {
		edTranspTitulo->Text = "";
		edCamTranspImg->Text = "";
		mmTranspCont->Lines->Clear();
		imgTransp->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::brTranspResize(TObject *Sender)
{
	float trPos[2], brTam[2], trTam[2];
	brTam[0] = frmPrincipal->brTransp->Width;
	brTam[1] = frmPrincipal->brTransp->Height;
	trTam[0] = frmPrincipal->vsTransp->Width;
	trTam[1] = frmPrincipal->vsTransp->Height;

	if (brTam[0] >= trTam[0]) {
		trPos[0] = (brTam[0] - trTam[0])/2;
		frmPrincipal->vsTransp->Position->X = trPos[0];
	}
	else {
		frmPrincipal->vsTransp->Position->X = 20;
	}

	if (brTam[1] >= trTam[1]) {
		trPos[1] = (brTam[1] - trTam[1])/2;
		frmPrincipal->vsTransp->Position->Y = trPos[1];
	}
	else {
		frmPrincipal->vsTransp->Position->Y = 20;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::FormCreate(TObject *Sender)
{

	float trPos[2], brTam[2], trTam[2];
	brTam[0] = frmPrincipal->brTransp->Width;
	brTam[1] = frmPrincipal->brTransp->Height;
	trTam[0] = frmPrincipal->vsTransp->Width;
	trTam[1] = frmPrincipal->vsTransp->Height;

	if (brTam[0] >= trTam[0]) {
		trPos[0] = (brTam[0] - trTam[0])/2;
		frmPrincipal->vsTransp->Position->X = trPos[0];
	}
	else {
		frmPrincipal->vsTransp->Position->X = 20;
	}

	if (brTam[1] >= trTam[1]) {
		trPos[1] = (brTam[1] - trTam[1])/2;
		frmPrincipal->vsTransp->Position->Y = trPos[1];
	}
	else {
		frmPrincipal->vsTransp->Position->Y = 20;
	}

	prim = true;

	// Adquire a cor da borda da transpar�ncia

	CorBordaTransp = vsTransp->Stroke->Color;

}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::CorAbaEditarMouseLeave(TObject *Sender)
{
	brEditar->ShowScrollBars = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::CorAbaEditarMouseEnter(TObject *Sender)
{
	brEditar->ShowScrollBars = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btVisualizarCodigoClick(TObject *Sender)
{
	frmCodigo->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::edtApresAutorTyping(TObject *Sender)
{
	if (Transp == 0) {
		if (edtApresTitulo->Text != "") {
			mmTranspCont->Text = edtApresAutor->Text;
			lblTranspTexto->Text = edtApresAutor->Text;
			frmCodigo->mmCodigo->Lines->Strings[1] = edtApresAutor->Text;
		}
		else {
			frmCodigo->mmCodigo->Lines->Strings[1] = "Nintersoft";
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::edTranspTituloTyping(TObject *Sender)
{
	if (edTranspTitulo->Text != "") {
		lblTitulo->Text = edTranspTitulo->Text;
	}
	else {
		if (Transp == 0) {
			lblTitulo->Text = "T�tulo da apresenta��o";
		}
		else {
			lblTitulo->Text = "T�tulo da transpar�ncia";
		}
	}
	if (Transp == 0) {
		if (edTranspTitulo->Text != "") {
			edtApresTitulo->Text = edTranspTitulo->Text;
		}
		else {
			edtApresTitulo->Text = "Apresenta��o sem t�tulo";
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btOpImgTranspClick(TObject *Sender)
{
	if (lblImgLeg->Text == "(Legenda da imagem)" | lblImgLeg->Text == "") {
		frmImgConf->CarregarDadosVar(Transp);
		frmImgConf->Show();
	}
	else {
		frmImgConf->edtImgLeg->Text = lblImgLeg->Text;
		frmImgConf->CarregarDadosVar(Transp);
		frmImgConf->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btModTranspClick(TObject *Sender)
{
	if (Transp == 0) {
		ShowMessage("Voc� n�o pode mudar a disposi��o dos elementos da capa.\nCaso voc� deseje esta capacidade, por favor, contate nossa equipe\npara que possamos desenvolver esta caracter�stica.");
	}
	else {
		MudarTransp(Transp, tpEscolha);
		CarregarTransp(Transp);
	}
		btModTransp->Enabled = false;
		btCriarTransp->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btCriarTranspClick(TObject *Sender)
{
		btModTransp->Enabled = false;
		btCriarTransp->Enabled = false;
		CriarTransp();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::edtApresTituloTyping(TObject *Sender)
{
	if (Transp == 0) {
		if (edtApresTitulo->Text != "") {
			edTranspTitulo->Text = edtApresTitulo->Text;
			lblTitulo->Text = edtApresTitulo->Text;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::edtApresTituloClick(TObject *Sender)
{
	if (edtApresTitulo->Text == "Apresenta��o sem t�tulo") {
		edtApresTitulo->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::edTranspTituloExit(TObject *Sender)
{
	if (Transp == 0) {
		if (edTranspTitulo->Text != "") {
			frmCodigo->mmCodigo->Lines->Strings[0] = edtApresTitulo->Text;
			frmPrincipal->Caption = edtApresTitulo->Text + " - Ninterpres";
			frmPrincipal->lblTituloForm->Text = edtApresTitulo->Text + " - Ninterpres";
		}
		else {
			frmPrincipal->Caption = "Apresenta��o sem t�tulo - Ninterpres";
			frmPrincipal->lblTituloForm->Text = "Apresenta��o sem t�tulo - Ninterpres";
			frmCodigo->mmCodigo->Lines->Strings[0] = "Apresenta��o sem t�tulo";
			edtApresTitulo->Text = "Apresenta��o sem t�tulo";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::listaCorApresentaChange(TObject *Sender)
{
	if (listaCorApresenta->Color == listaCorTexto->Color) {
		ShowMessage("Vo�� n�o pode escolher a mesma cor da fonte para o fundo da transpar�ncia.");
	}
	else {
		vsTransp->Fill->Color = listaCorApresenta->Color;
		int a = vsTransp->Fill->Color;
		frmCodigo->mmCodigo->Lines->Strings[2] = IntToStr(a);
			if (cbBorda->IsChecked == true) {
				vsTransp->Stroke->Color = listaCorApresenta->Color;
			}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAjudaOnlineClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "http://www.nintersoft.ml/", NULL, NULL, SW_SHOW );
	ShowMessage("Por favor, aguarde enquanto nosso site � aberto!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cbBordaChange(TObject *Sender)
{
	if (cbBorda->IsChecked) {
		vsTransp->Stroke->Color = vsTransp->Fill->Color;
		frmCodigo->mmCodigo->Lines->Strings[3] = "==";
	}
	else {
		vsTransp->Stroke->Color = CorBordaTransp;
		frmCodigo->mmCodigo->Lines->Strings[3] = "!=";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cbTodosChange(TObject *Sender)
{
	if (cbTodos->IsChecked) {
		cbFonte->Enabled = true;
		frmCodigo->mmCodigo->Lines->Strings[4] = "==";
	}
	else {
		cbFonte->IsChecked = false;
		cbFonte->Enabled = false;
		listaCorTexto->Enabled = false;
		lblListaCorTexto->Enabled = false;
		lblTitulo->TextSettings->FontColor = CorBordaTransp;
		lblTranspTexto->TextSettings->FontColor = CorBordaTransp;
		lblImgLeg->TextSettings->FontColor = CorBordaTransp;
		listaCorTexto->Color = CorBordaTransp;
		frmCodigo->mmCodigo->Lines->Strings[4] = "!=";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cbFonteChange(TObject *Sender)
{
	if (cbFonte->IsChecked) {
		listaCorTexto->Enabled = true;
		lblListaCorTexto->Enabled = true;
		frmCodigo->mmCodigo->Lines->Strings[5] = "==";
		int cor = listaCorTexto->Color;
		IntToStr(cor);
		frmCodigo->mmCodigo->Lines->Strings[6] = IntToStr(cor);
	}
	else {
		listaCorTexto->Enabled = false;
		lblListaCorTexto->Enabled = false;
		lblTitulo->TextSettings->FontColor = CorBordaTransp;
		lblTranspTexto->TextSettings->FontColor = CorBordaTransp;
		lblImgLeg->TextSettings->FontColor = CorBordaTransp;
		listaCorTexto->Color = CorBordaTransp;
		frmCodigo->mmCodigo->Lines->Strings[5] = "!=";
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::btSobreClick(TObject *Sender)
{
	frmSobre->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::listaCorTextoChange(TObject *Sender)
{
	if (listaCorTexto->Color == listaCorApresenta->Color) {
		ShowMessage("Voc� n�o pode escolher a mesma cor da transpar�ncia para a cor da fonte!");
	}
	else {
		int cor = listaCorTexto->Color;
		lblTitulo->TextSettings->FontColor = listaCorTexto->Color;
		lblTranspTexto->TextSettings->FontColor = listaCorTexto->Color;
		lblImgLeg->TextSettings->FontColor = listaCorTexto->Color;
		frmCodigo->mmCodigo->Lines->Strings[6] = IntToStr(cor);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btEmailClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "mailto:suporte@nintersoft.ml", NULL, NULL, SW_SHOW );
	ShowMessage("Por favor, aguarde enquanto o email oficial de suporte � aberto!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btDocWikiClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "http://docwiki.nintersoft.ml/ninterpres", NULL, NULL, SW_SHOW );
	ShowMessage("Por favor, aguarde enquanto nossa central de ajuda e conhecimento\n� respeito do Ninterpres � aberta!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btCentralSupClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "http://www.nintersoft.ml/suporte/", NULL, NULL, SW_SHOW );
	ShowMessage("Por favor, aguarde enquanto nossa central de suporte � aberta!");
}
//---------------------------------------------------------------------------
void TfrmPrincipal::CriarTransp (){
int num = 1, tam = frmCodigo->mmCodigo->Lines->Count;
bool res = true;
	do {
		for ( int i = 0; i < tam; i++) {
			if (frmCodigo->mmCodigo->Lines->Strings[i] == "$TRANSP" + IntToStr(num)) {
				res = false;
				num++;
				i = tam;
			}
			if (i == tam-1 && frmCodigo->mmCodigo->Lines->Strings[i] != "$TRANSP" + IntToStr(num)) {
				res = true;
				i = tam;
			}
		}
	} while (res == false);

			int pos = tam - 4;
				frmPrincipal->SelecTransp->Items->Add()->Text = "TRANSP" + IntToStr(num);
				frmCodigo->mmCodigo->Lines->Insert(pos, "!(FDT)");
				frmCodigo->mmCodigo->Lines->Insert(pos, "*.*");
				frmCodigo->mmCodigo->Lines->Insert(pos, "*.*");
				frmCodigo->mmCodigo->Lines->Insert(pos, "*.*");
				frmCodigo->mmCodigo->Lines->Insert(pos, "*.*");
				frmCodigo->mmCodigo->Lines->Insert(pos, IntToStr(tpEscolha));
				frmCodigo->mmCodigo->Lines->Insert(pos, "$TRANSP" + IntToStr(num));
				Transp = num;
				frmPrincipal->mmTranspCont->ReadOnly = false;
				CarregarTransp (Transp);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btMinimizarClick(TObject *Sender)
{
	frmPrincipal->WindowState = frmMin->WindowState;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::edtApresAutorExit(TObject *Sender)
{
	if (Transp == 0) {
		mmTranspCont->Text = edtApresAutor->Text;
		lblTranspTexto->Text = edtApresAutor->Text;
	}

	frmCodigo->mmCodigo->Lines->Strings[1] = edtApresAutor->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::SelecTranspItemClick(const TObject *Sender, const TListViewItem *AItem)
{
	if (SelecTransp->Selected->Text == "CAPA") {
		Transp = 0;
		CarregarTransp(Transp);
		mmTranspCont->ReadOnly = true;
	}
	else {
		Transp = SelecTransp->Selected->Index;
		CarregarTransp(Transp);
		mmTranspCont->ReadOnly = false;
	}
	btModTransp->Enabled = false;
	btCriarTransp->Enabled = false;
}
//---------------------------------------------------------------------------
void TfrmPrincipal::CarregarTransp (int indice)
{
	int loc, pos = 0,tam = frmCodigo->mmCodigo->Lines->Count;

	if (indice == 0) {
		for (int i = 0; i < tam; i++) {
			if (frmCodigo->mmCodigo->Lines->Strings[i] == "$CAPA") {
				loc = i + 1;
				i = tam;
			}
			if (i == tam - 2 && frmCodigo->mmCodigo->Lines->Strings[i] != "$CAPA") {
				throw Exception ("ERRO 000001: A capa n�o foi encontrada no c�digo de compila��o!\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
			}
		}
		do{
			RearranjoTransp(indice);
			while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
			loc++;
			}
			if (pos == 0 && frmCodigo->mmCodigo->Lines->Strings[loc] != "*.*") {
				if (salvo) {
					String arqz = System::Ioutils::TPath::Combine(locSalvo, L"IMG");

					String arqt, arq, ext;
					bool extver = false;

					for (int i = frmCodigo->mmCodigo->Lines->Strings[loc].Length() - 5; i < frmCodigo->mmCodigo->Lines->Strings[loc].Length(); i++) {
						if (frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i] == '.') {
							extver = true;
							ext = ext + frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i];
						}
						else if (extver) {
							ext = ext + frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i];
						}
					}

					arq = System::Ioutils::TPath::Combine(arqz, L"CAPA");

					if (TFile::Exists(arq+ext)) {
						frmPrincipal->imgTransp->Bitmap->LoadFromFile(arq+ext);
						frmPrincipal->edCamTranspImg->Text = arq+ext;
					}
					else {
						throw Exception ("ERRO 000003: O arquivo de imagem n�o foi salvo corretamente.\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
					}

				}
				else {
					PWSTR pszPath;
					if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
					{
						String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP\\IMG");
						CoTaskMemFree(pszPath);

						String arqt, arq, ext;
						bool extver = false;

						for (int i = frmCodigo->mmCodigo->Lines->Strings[loc].Length() - 5; i < frmCodigo->mmCodigo->Lines->Strings[loc].Length(); i++) {
							if (frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i] == '.') {
								extver = true;
								ext = ext + frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i];
							}
							else if (extver) {
								ext = ext + frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i];
							}
						}

						arq = System::Ioutils::TPath::Combine(NSNPTEMP, L"CAPA");

						if (TFile::Exists(arq+ext)) {
							frmPrincipal->imgTransp->Bitmap->LoadFromFile(arq+ext);
							frmPrincipal->edCamTranspImg->Text = arq+ext;
						}
						else {
							throw Exception ("ERRO 000003: O arquivo de imagem n�o foi salvo corretamente.\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
						}
					}
				}
				frmPrincipal->imgTransp->Visible = true;
				loc++;
				pos++;
			}
			else if (pos == 0 && frmCodigo->mmCodigo->Lines->Strings[loc] == "*.*") {
				loc++;
				pos++;
				frmPrincipal->imgTransp->Visible = false;
				frmPrincipal->edCamTranspImg->Text = "";
			}
			else if (pos == 1 && frmCodigo->mmCodigo->Lines->Strings[loc] != "*.*") {
				frmPrincipal->lblImgLeg->Text = frmCodigo->mmCodigo->Lines->Strings[loc];
				frmImgConf->edtImgLeg->Text =  frmCodigo->mmCodigo->Lines->Strings[loc];
				loc++;
				pos++;
			}
			else if (pos == 1 && frmCodigo->mmCodigo->Lines->Strings[loc] == "*.*") {
				frmPrincipal->lblImgLeg->Text = "";
				frmImgConf->edtImgLeg->Text = "";
				loc++;
				pos++;
			}
		} while (frmCodigo->mmCodigo->Lines->Strings[loc] != "!(FDT)");

		int pos = 0;

		do {
			if (pos == 0 && frmCodigo->mmCodigo->Lines->Strings[0] != "Apresenta��o sem t�tulo") {
				frmPrincipal->lblTitulo->Text = frmCodigo->mmCodigo->Lines->Strings[0];
				frmPrincipal->edTranspTitulo->Text = frmCodigo->mmCodigo->Lines->Strings[0];
				pos++;
			}
			else if (pos == 0) {
				frmPrincipal->edtApresTitulo->Text = "Apresenta��o sem t�tulo";
				frmPrincipal->lblTitulo->Text =  "Digite o t�tulo da apresenta��o";
				pos++;
			}
			else if (pos == 1 && frmCodigo->mmCodigo->Lines->Strings[1] != "Nintersoft") {
				frmPrincipal->lblTranspTexto->Text = frmCodigo->mmCodigo->Lines->Strings[1];
				frmPrincipal->mmTranspCont->Text =  frmCodigo->mmCodigo->Lines->Strings[1];
				pos++;
			}
			else if (pos == 1) {
				frmPrincipal->lblTranspTexto->Text = "Nome do Autor, Nome do Segundo Autor, Nome do Terceiro Autor, Nome do Autor n�x.";
				frmPrincipal->mmTranspCont->Lines->Clear();
				pos++;
			}
		} while (pos < 2);



		frmPrincipal->mmTranspCont->ReadOnly = true;

	}
	else {

		bool primVar = true;

		for (int i = 0; i < tam; i++) {
			if (frmCodigo->mmCodigo->Lines->Strings[i] == "$TRANSP" + IntToStr (indice)) {
				loc = i + 1;
				i = tam;
			}
			if (i == tam - 2 && frmCodigo->mmCodigo->Lines->Strings[i] != "$TRANSP" + IntToStr (indice)) {
				throw Exception ("ERRO 000001: A transpar�ncia selecionada n�o foi encontrada no c�digo de compila��o!\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
			}
		}
		do{
			while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
			loc++;
			}
			if (pos == 0 && StrToInt(frmCodigo->mmCodigo->Lines->Strings[loc]) > 0 && StrToInt(frmCodigo->mmCodigo->Lines->Strings[loc]) < 8 ) {
				RearranjoTransp(StrToInt(frmCodigo->mmCodigo->Lines->Strings[loc]));
				loc++;
				pos++;
			}
			else if (pos == 0) {
				throw Exception ("Erro na configura��o do tipo de transpar�ncia!");
			}
			else if (pos == 1 && frmCodigo->mmCodigo->Lines->Strings[loc] != "*.*") {
				frmPrincipal->lblTitulo->Text = frmCodigo->mmCodigo->Lines->Strings[loc];
				frmPrincipal->edTranspTitulo->Text = frmCodigo->mmCodigo->Lines->Strings[loc];
				loc++;
				pos++;
			}
			else if (pos == 1 && frmCodigo->mmCodigo->Lines->Strings[loc] == "*.*") {
				frmPrincipal->lblTitulo->Text = "Digite o t�tulo da transpar�ncia";
				frmPrincipal->edTranspTitulo->Text = "";
				loc++;
				pos++;
			}
			else if (pos == 2 && frmCodigo->mmCodigo->Lines->Strings[loc] != "*.*") {
				if (salvo) {
					String arqz = System::Ioutils::TPath::Combine(locSalvo, L"IMG");

					String arqt, arq, ext;
					bool extver = false;

					for (int i = frmCodigo->mmCodigo->Lines->Strings[loc].Length() - 5; i < frmCodigo->mmCodigo->Lines->Strings[loc].Length(); i++) {
						if (frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i] == '.') {
							extver = true;
							ext = ext + frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i];
						}
						else if (extver) {
							ext = ext + frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i];
						}
					}

					arqt = "TRANSP" + IntToStr(indice);

					arq = System::Ioutils::TPath::Combine(arqz, arqt);

					if (TFile::Exists(arq+ext)) {
						frmPrincipal->imgTransp->Bitmap->LoadFromFile(arq+ext);
						frmPrincipal->edCamTranspImg->Text = arq+ext;
					}
					else {
						frmPrincipal->edCamTranspImg->Text = "ERRO 000003";
						throw Exception ("ERRO 000003: O arquivo de imagem n�o foi salvo corretamente.\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
					}

					frmPrincipal->imgTransp->Visible = true;
				}
				else {
					PWSTR pszPath;
					if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
					{
						String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP\\IMG");
						CoTaskMemFree(pszPath);

						String arqt, arq, ext;
						bool extver = false;

						for (int i = frmCodigo->mmCodigo->Lines->Strings[loc].Length() - 5; i < frmCodigo->mmCodigo->Lines->Strings[loc].Length(); i++) {
							if (frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i] == '.') {
								extver = true;
								ext = ext + frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i];
							}
							else if (extver) {
								ext = ext + frmCodigo->mmCodigo->Lines->Strings[loc].c_str()[i];
							}
						}

						arqt = "TRANSP" + IntToStr(indice);

						arq = System::Ioutils::TPath::Combine(NSNPTEMP, arqt);

						if (TFile::Exists(arq+ext)) {
							frmPrincipal->imgTransp->Bitmap->LoadFromFile(arq+ext);
							frmPrincipal->edCamTranspImg->Text = arq+ext;
						}
						else {
							frmPrincipal->edCamTranspImg->Text = "ERRO 000003";
							throw Exception ("ERRO 000003: O arquivo de imagem n�o foi salvo corretamente.\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
						}

					}
				}
				frmPrincipal->imgTransp->Visible = true;
				loc++;
				pos++;
			}
			else if (pos == 2 && frmCodigo->mmCodigo->Lines->Strings[loc] == "*.*") {
				frmPrincipal->imgTransp->Visible = false;
				frmPrincipal->edCamTranspImg->Text = "";
				loc++;
				pos++;
			}
			else if (pos == 3 && frmCodigo->mmCodigo->Lines->Strings[loc] != "*.*") {
				frmPrincipal->lblImgLeg->Text = frmCodigo->mmCodigo->Lines->Strings[loc];
				frmImgConf->edtImgLeg->Text = frmCodigo->mmCodigo->Lines->Strings[loc];
				loc++;
				pos++;
			}
			else if (pos == 3 && frmCodigo->mmCodigo->Lines->Strings[loc] == "*.*") {
				frmPrincipal->lblImgLeg->Text = "";
				frmImgConf->edtImgLeg->Text = "";
				loc++;
				pos++;
			}
			else if (pos == 4 && frmCodigo->mmCodigo->Lines->Strings[loc] != "*.*") {

				if (primVar) {
					frmPrincipal->mmTranspCont->Lines->Clear();
					frmPrincipal->mmTranspCont->BeginUpdate();
					primVar = false;
				}

				do {

					while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
					loc++;
					}

					frmPrincipal->mmTranspCont->Lines->Add(frmCodigo->mmCodigo->Lines->Strings[loc]);
					loc++;

					while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
					loc++;
					}

				}while (frmCodigo->mmCodigo->Lines->Strings[loc] != "!(FDT)");

				frmPrincipal->mmTranspCont->EndUpdate();
				frmPrincipal->lblTranspTexto->Text = frmPrincipal->mmTranspCont->Text;
				pos++;

			}
			else if (pos == 4 && frmCodigo->mmCodigo->Lines->Strings[loc] == "*.*") {
				frmPrincipal->lblTranspTexto->Text = "Digite seu conte�do de texto para esta transpar�ncia aqui.";
				frmPrincipal->mmTranspCont->Lines->Clear();
				loc++;
				pos++;
			}
		} while (frmCodigo->mmCodigo->Lines->Strings[loc] != "!(FDT)");

		frmPrincipal->mmTranspCont->ReadOnly = false;

	}
}
//---------------------------------------------------------------------------
bool TfrmPrincipal::comentario (String linha){

	bool eh;
		if (linha.c_str()[0] == '/' && linha.c_str()[1] == '/') {
			eh = true;
		}
		else {
			eh = false;
		}
	return eh;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btConfigClick(TObject *Sender)
{
	frmConfig->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::opMostrarNSTranspChange(TObject *Sender)
{
	if (opMostrarNSTransp->IsChecked) {
		int pos = frmCodigo->mmCodigo->Lines->Count - 1;
		frmCodigo->mmCodigo->Lines->Strings[pos] = "NSFN";
	}
	else {
		int pos = frmCodigo->mmCodigo->Lines->Count - 1;
		frmCodigo->mmCodigo->Lines->Strings[pos] = "!NSFN";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::opMostrarLogoNSChange(TObject *Sender)
{
	if (opMostrarLogoNS->IsChecked) {
		int pos = frmCodigo->mmCodigo->Lines->Count - 2;
		frmCodigo->mmCodigo->Lines->Strings[pos] = "NSPR";
	}
	else {
		int pos = frmCodigo->mmCodigo->Lines->Count - 2;
		frmCodigo->mmCodigo->Lines->Strings[pos] = "!NSPR";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::opMostrarDataAtualChange(TObject *Sender)
{
	if (opMostrarDataAtual->IsChecked) {
		int pos = frmCodigo->mmCodigo->Lines->Count - 3;
		frmCodigo->mmCodigo->Lines->Strings[pos] = "NSDT";
	}
	else {
		int pos = frmCodigo->mmCodigo->Lines->Count - 3;
		frmCodigo->mmCodigo->Lines->Strings[pos] = "!NSDT";
	}
}
//---------------------------------------------------------------------------
void TfrmPrincipal::MudarTransp (int numero, int tipo)
{
	String num = IntToStr(numero);
	int loc, tam = frmCodigo->mmCodigo->Lines->Count;

	for (int i = 0; i < tam; i++) {
		if (frmCodigo->mmCodigo->Lines->Strings[i] == "$TRANSP" + num) {
			loc = i +1;
			i = tam;
		}
	}
	while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
		loc++;
	}
	try {
		StrToInt(frmCodigo->mmCodigo->Lines->Strings[loc]);
		frmCodigo->mmCodigo->Lines->Strings[loc] = IntToStr(tipo);
	}
	catch (...) {
		throw Exception ("N�o foi poss�vel alterar o tipo da transpar�ncia.\nPor favor, verifique se o c�digo est� seguindo as diretrizes determinadas em nossa DocWiki.");
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mmTranspContExit(TObject *Sender)
{
	if (mmTranspCont->Text != "") {
		lblTranspTexto->Text = mmTranspCont->Text;
	}
	else {
		lblTranspTexto->Text = "Digite seu conte�do de texto para esta transpar�ncia aqui.";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::mmTranspContKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
	if (mmTranspCont->Text != "") {
		try {
			lblTranspTexto->Text = mmTranspCont->Text;
		} catch (...) {
		}
	}
	else {
		lblTranspTexto->Text = "Digite seu conte�do de texto para esta transpar�ncia aqui.";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btExcluirTranspClick(TObject *Sender)
{
	int LimpConf = MessageBox (0, L"Voc� est� certo disso?\nEsta a��o n�o pode ser desfeita.\nEsta transpar�ncia n�o poder� ser reposta!", L"Ninterpres - Aviso", MB_YESNO+MB_ICONQUESTION);
	if (LimpConf == 6) {
		SelecTransp->Items->Delete(SelecTransp->Selected->Index);
	}
}
//---------------------------------------------------------------------------

void TfrmPrincipal::ModificarDados (int transp)
{

	int loc, pos = 0,tam = frmCodigo->mmCodigo->Lines->Count;

	for (int i = 0; i < tam; i++) {
		if (frmCodigo->mmCodigo->Lines->Strings[i] == "$TRANSP" + IntToStr(transp)) {
			loc = i + 1;
			i = tam;
		}
	}

	do {

		while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
			loc++;
		}
		if (pos == 0) {
			try {
				RearranjoTransp(StrToInt(frmCodigo->mmCodigo->Lines->Strings[loc]));
			} catch (...) {
				throw Exception ("ERRO 000002: N�o foi poss�vel carregar o leiaute desta transpar�ncia!\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
			}
			pos++;
			loc++;
		}
		else if (pos == 1) {
			if (frmPrincipal->edTranspTitulo->Text == "") {
				frmCodigo->mmCodigo->BeginUpdate();
				frmCodigo->mmCodigo->Lines->Strings[loc] = "*.*";
				frmCodigo->mmCodigo->EndUpdate();
			}
			else {
				frmCodigo->mmCodigo->BeginUpdate();
				frmCodigo->mmCodigo->Lines->Strings[loc] = frmPrincipal->edTranspTitulo->Text;
				frmCodigo->mmCodigo->EndUpdate();
			}
			pos++;
			loc++;
		}
		else if (pos == 2) {
			if (frmPrincipal->edCamTranspImg->Text == "") {
				frmCodigo->mmCodigo->BeginUpdate();
				frmCodigo->mmCodigo->Lines->Strings[loc] = "*.*";
				frmCodigo->mmCodigo->EndUpdate();
			}
			else {
				frmCodigo->mmCodigo->BeginUpdate();
				frmCodigo->mmCodigo->Lines->Strings[loc] = "..\\IMG\\TRANSP"+IntToStr(transp)+Extensao(frmPrincipal->edCamTranspImg->Text);
				frmCodigo->mmCodigo->EndUpdate();
			}
			pos++;
			loc++;
		}
		else if (pos == 3) {
			if (frmPrincipal->lblImgLeg->Text == "" | frmPrincipal->lblImgLeg->Text == "(Legenda da imagem)") {
				frmCodigo->mmCodigo->BeginUpdate();
				frmCodigo->mmCodigo->Lines->Strings[loc] = "*.*";
				frmCodigo->mmCodigo->EndUpdate();
			}
			else {
				frmCodigo->mmCodigo->BeginUpdate();
				frmCodigo->mmCodigo->Lines->Strings[loc] = frmImgConf->edtImgLeg->Text;
				frmCodigo->mmCodigo->EndUpdate();
			}
			pos++;
			loc++;
		}
		else if (pos == 4) {
			if (frmPrincipal->mmTranspCont->Text == "") {
				frmCodigo->mmCodigo->BeginUpdate();
				while (frmCodigo->mmCodigo->Lines->Strings[loc] != "!(FDT)") {
					while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
						loc++;
					}
					frmCodigo->mmCodigo->Lines->Delete(loc);
				}
				frmCodigo->mmCodigo->Lines->Insert(loc, "*.*");
				frmCodigo->mmCodigo->EndUpdate();
			}
			else {
				frmCodigo->mmCodigo->BeginUpdate();
				while (frmCodigo->mmCodigo->Lines->Strings[loc] != "!(FDT)") {
					while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
						loc++;
					}
					frmCodigo->mmCodigo->Lines->Delete(loc);
				}
				frmCodigo->mmCodigo->EndUpdate();

				int tam2 = frmPrincipal->mmTranspCont->Lines->Count - 1;

				frmCodigo->mmCodigo->BeginUpdate();
				for (int i = tam2 ; i >= 0; i--) {
					frmCodigo->mmCodigo->Lines->Insert(loc, frmPrincipal->mmTranspCont->Lines->Strings[i]);
				}
				frmCodigo->mmCodigo->EndUpdate();

			}
			pos++;
		}
		else if (pos == 5) {
			while (frmCodigo->mmCodigo->Lines->Strings[loc] != "!(FDT)"){
				loc++;
			}
		}

	} while (frmCodigo->mmCodigo->Lines->Strings[loc] != "!(FDT)");

}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mmTranspContClick(TObject *Sender)
{
	if (mmTranspCont->ReadOnly) {
		ShowMessage("Voc� est� editando a capa.\nPara editar o nome dos autores v� at� a aba 'Arquivo' e no campo 'Autor(es)', digite o nome do(s) autor(es) desejado(s).");
	}
}
//---------------------------------------------------------------------------
	String TfrmPrincipal::Extensao(String DArquivo){
	String ext;
	bool extver = false;

		for (int i = 0; i < DArquivo.Length(); i++) {
			if (DArquivo.c_str()[i] == '.') {
				extver = true;
				ext = ext + DArquivo.c_str()[i];
			}
			else if (extver) {
				ext = ext + DArquivo.c_str()[i];
			}
		}

	return ext;
	}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btExcluidadosClick(TObject *Sender)
{
	int Exclui = MessageBox (0, L"Voc� realmente deseja remover a imagem?\nCaso voc� esteja editando a capa esta a��o ser� automaticamente salva.", L"Aviso - Ninterpres", MB_YESNO+MB_ICONQUESTION);
	if (Exclui == 6) {
		frmPrincipal->imgTransp->Visible = false;
		if (Transp == 0) {
			int loc, tam = frmCodigo->mmCodigo->Lines->Count;
			for (int i = 0; i < tam; i++) {
				if (frmCodigo->mmCodigo->Lines->Strings[i] == "$CAPA"){
					loc = i + 1;
					i = tam;
				}
			}

			while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
				loc++;
			}

			frmCodigo->mmCodigo->Lines->Strings[loc] = "*.*";

			if (TFile::Exists(edCamTranspImg->Text)) {
					TFile::Delete(edCamTranspImg->Text);
			}

			edCamTranspImg->Text = "";

		}
		else {
			frmPrincipal->edCamTranspImg->Text = "";
		}
	}
}
//---------------------------------------------------------------------------
void TfrmPrincipal::RearranjoTransp (int estilo){

	float AltTransp = frmPrincipal->vsTransp->Height, LargTransp = frmPrincipal->vsTransp->Width;

	if (Vis == 0) {
		if (Transp == 0) {

			int cor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);
			frmPrincipal->vsTransp->Fill->Color = cor;

			if (frmPrincipal->cbBorda->IsChecked) {
				vsTransp->Stroke->Color = cor;
			}
			else {
				vsTransp->Stroke->Color = CorBordaTransp;
			}

			frmPrincipal->lblTitulo->Position->Y = AltTransp/2;
			frmPrincipal->lblTitulo->Position->X = 24;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x1;

			frmPrincipal->lblTranspTexto->Width = LargTransp - 32;
			frmPrincipal->lblTranspTexto->Position->X = 24;
			frmPrincipal->lblTranspTexto->Position->Y = AltTransp/2 + 8 + frmPrincipal->lblTitulo->Height;
			frmPrincipal->lblTranspTexto->Height = 42;
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x1;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x1;

			frmPrincipal->imgTransp->Position->X = 0;
			frmPrincipal->imgTransp->Position->Y = 0;
			frmPrincipal->imgTransp->Width = LargTransp;
			frmPrincipal->imgTransp->Height = AltTransp;

			frmPrincipal->lblImgLeg->Width = LargTransp - 32;
			frmPrincipal->lblImgLeg->Position->X = 24;
			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x2;
			frmPrincipal->lblImgLeg->Position->Y = AltTransp - 24 - frmPrincipal->lblImgLeg->Height;
			frmPrincipal->lblImgLeg->Visible = true;

		}
		else if (estilo == 1) {

			int cor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);

			if (frmCodigo->mmCodigo->Lines->Strings[4] == "==") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmCodigo->Lines->Strings[4] == "!="){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = 24;
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;

			frmPrincipal->imgTransp->Width = LargTransp/2 - 32;
			frmPrincipal->imgTransp->Position->X = LargTransp / 2 + 8;
			frmPrincipal->imgTransp->Height = AltTransp - 112 - frmPrincipal->lblImgLeg->Height - 32;
			frmPrincipal->imgTransp->Position->Y = 106;

			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblImgLeg->Width = LargTransp/2 - 32;
			frmPrincipal->lblImgLeg->Position->X = LargTransp / 2 + 16;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + 8;
			frmPrincipal->lblImgLeg->Visible = true;

			frmPrincipal->lblTranspTexto->Width = LargTransp/2 - 32;
			frmPrincipal->lblTranspTexto->Position->X = 24;
			frmPrincipal->lblTranspTexto->Height = frmPrincipal->imgTransp->Height;
			frmPrincipal->lblTranspTexto->Position->Y = 106;
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x2;

		}
		else if (estilo == 2) {

			int cor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);

			if (frmCodigo->mmCodigo->Lines->Strings[4] == "==") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmCodigo->Lines->Strings[4] == "!="){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = 24;
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;

			frmPrincipal->imgTransp->Width = LargTransp/2 - 32;
			frmPrincipal->imgTransp->Position->X = 24;
			frmPrincipal->imgTransp->Height = AltTransp - 112 - frmPrincipal->lblImgLeg->Height - 32;
			frmPrincipal->imgTransp->Position->Y = 106;

			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblImgLeg->Width = LargTransp/2 - 32;
			frmPrincipal->lblImgLeg->Position->X = 24;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + 8;
			frmPrincipal->lblImgLeg->Visible = true;

			frmPrincipal->lblTranspTexto->Width = LargTransp/2 - 32;
			frmPrincipal->lblTranspTexto->Position->X = LargTransp / 2 + 8;
			frmPrincipal->lblTranspTexto->Height = frmPrincipal->imgTransp->Height;
			frmPrincipal->lblTranspTexto->Position->Y = 106;
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x1;

		}
		else if (estilo == 3) {

			int cor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);

			if (frmCodigo->mmCodigo->Lines->Strings[4] == "==") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmCodigo->Lines->Strings[4] == "!="){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = AltTransp - 88;
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;

			frmPrincipal->imgTransp->Width = LargTransp/2 - 32;
			frmPrincipal->imgTransp->Position->X = LargTransp / 2 + 8;
			frmPrincipal->imgTransp->Height = AltTransp - 112 - frmPrincipal->lblImgLeg->Height - 32;
			frmPrincipal->imgTransp->Position->Y = 24;

			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblImgLeg->Width = LargTransp/2 - 32;
			frmPrincipal->lblImgLeg->Position->X = LargTransp / 2 + 8;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + 8;
			frmPrincipal->lblImgLeg->Visible = true;

			frmPrincipal->lblTranspTexto->Width = LargTransp/2 - 32;
			frmPrincipal->lblTranspTexto->Position->X = 24;
			frmPrincipal->lblTranspTexto->Height = frmPrincipal->imgTransp->Height;
			frmPrincipal->lblTranspTexto->Position->Y = 24;
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x2;

		}
		else if (estilo == 4) {

			int cor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);

			if (frmCodigo->mmCodigo->Lines->Strings[4] == "==") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmCodigo->Lines->Strings[4] == "!="){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = AltTransp - 88;
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;

			frmPrincipal->imgTransp->Width = LargTransp/2 - 32;
			frmPrincipal->imgTransp->Position->X = 24;
			frmPrincipal->imgTransp->Height = AltTransp - 112 - frmPrincipal->lblImgLeg->Height - 32;
			frmPrincipal->imgTransp->Position->Y = 24;

			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblImgLeg->Width = LargTransp/2 - 32;
			frmPrincipal->lblImgLeg->Position->X = 24;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + 8;
			frmPrincipal->lblImgLeg->Visible = true;

			frmPrincipal->lblTranspTexto->Width = LargTransp/2 - 32;
			frmPrincipal->lblTranspTexto->Position->X = LargTransp / 2 + 8;
			frmPrincipal->lblTranspTexto->Height = frmPrincipal->imgTransp->Height;
			frmPrincipal->lblTranspTexto->Position->Y = 24;
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x1;

		}
		else if (estilo == 5) {

			int cor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);

			if (frmCodigo->mmCodigo->Lines->Strings[4] == "==") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmCodigo->Lines->Strings[4] == "!="){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = 24;
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;

			frmPrincipal->imgTransp->Width = 0;
			frmPrincipal->imgTransp->Position->X = 0;
			frmPrincipal->imgTransp->Height = 0;
			frmPrincipal->imgTransp->Position->Y = 0;

			frmPrincipal->lblImgLeg->Width = 0;
			frmPrincipal->lblImgLeg->Position->X = 0;
			frmPrincipal->lblImgLeg->Position->Y = 0;
			frmPrincipal->lblImgLeg->Visible = false;

			frmPrincipal->lblTranspTexto->Width = LargTransp - 48;
			frmPrincipal->lblTranspTexto->Position->X = 24;
			frmPrincipal->lblTranspTexto->Height = AltTransp - 136;
			frmPrincipal->lblTranspTexto->Position->Y = 106;
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x0;

		}
		else if (estilo == 6) {

			int cor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);

			if (frmCodigo->mmCodigo->Lines->Strings[4] == "==") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmCodigo->Lines->Strings[4] == "!="){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = 24;
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;

			frmPrincipal->imgTransp->Width = LargTransp - 48;
			frmPrincipal->imgTransp->Position->X = 24;
			frmPrincipal->imgTransp->Height = AltTransp - 112 - frmPrincipal->lblImgLeg->Height - 32;
			frmPrincipal->imgTransp->Position->Y = 106;

			frmPrincipal->lblImgLeg->Width = LargTransp - 48;
			frmPrincipal->lblImgLeg->Position->X = 24;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + 8;
			frmPrincipal->lblImgLeg->Visible = true;
			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x0;

			frmPrincipal->lblTranspTexto->Width = 0;
			frmPrincipal->lblTranspTexto->Position->X = 0;
			frmPrincipal->lblTranspTexto->Height = 0;
			frmPrincipal->lblTranspTexto->Position->Y = 0;
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x0;

		}
		else if (estilo == 7) {

			int cor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);

			if (frmCodigo->mmCodigo->Lines->Strings[4] == "==") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmCodigo->Lines->Strings[4] == "!="){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = AltTransp - 88;
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;

			frmPrincipal->imgTransp->Width = LargTransp - 48;
			frmPrincipal->imgTransp->Position->X = 24;
			frmPrincipal->imgTransp->Height = AltTransp - 112 - frmPrincipal->lblImgLeg->Height - 32;
			frmPrincipal->imgTransp->Position->Y = 24;

			frmPrincipal->lblImgLeg->Width = LargTransp - 48;
			frmPrincipal->lblImgLeg->Position->X = 24;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + 8;
			frmPrincipal->lblImgLeg->Visible = true;
			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x0;

			frmPrincipal->lblTranspTexto->Width = 0;
			frmPrincipal->lblTranspTexto->Position->X = 0;
			frmPrincipal->lblTranspTexto->Height = 0;
			frmPrincipal->lblTranspTexto->Position->Y = 0;
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x0;

		}

	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btMaximizarClick(TObject *Sender)
{
	TSize Tamanho = Screen->Size();
	frmPrincipal->Width = Tamanho.Width;
	frmPrincipal->Height = Tamanho.Height - 40;
	btMaximizar->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::FormResize(TObject *Sender)
{
	TSize Tamanho = Screen->Size();
	if (frmPrincipal->Width != Tamanho.Width | frmPrincipal->Height != Tamanho.Height - 40) {
		btMaximizar->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::baTamFonteTracking(TObject *Sender)
{
	edtTamFonte->Value = baTamFonte->Value;
	frmCodigo->mmCodigo->Lines->Strings[7] = FloatToStr(edtTamFonte->Value);
	lblTranspTexto->TextSettings->Font->Size = StrToFloat(frmCodigo->mmCodigo->Lines->Strings[7]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::CorAbaArquivoMouseEnter(TObject *Sender)
{
	brArquivo->ShowScrollBars = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::CorAbaArquivoMouseLeave(TObject *Sender)
{
	brArquivo->ShowScrollBars = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::edtTamFonteChange(TObject *Sender)
{
	baTamFonte->Value = edtTamFonte->Value;
	frmCodigo->mmCodigo->Lines->Strings[7] = FloatToStr(edtTamFonte->Value);
	lblTranspTexto->TextSettings->Font->Size = StrToFloat(frmCodigo->mmCodigo->Lines->Strings[7]);
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::btSalvarDadosMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btSalvarDados->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSalvarDadosMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btSalvarDados->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btModTranspMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btModTransp->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btModTranspMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btModTransp->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btCriarTranspMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btCriarTransp->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btCriarTranspMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btCriarTransp->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btLimpDadosMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btLimpDados->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btLimpDadosMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btLimpDados->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::FormClose(TObject *Sender, TCloseAction &Action)
{
	pergunta:
	int SalvaFecha = MessageBox (0, L"Voc� encerrar� a aplica��o.\nOs dados n�o salvos da apresenta��o ser�o perdidos.\nDeseja salvar os dados da apresenta��o atual?", L"Aviso - Ninterpres", MB_YESNO+MB_ICONQUESTION);
	if (SalvaFecha == 6) {
		if (salvo) {
			String arq = System::Ioutils::TPath::Combine(locSalvo, L"NSCA.nps");
			frmCodigo->mmCodigo->Lines->SaveToFile(arq);
		}
		else {
			if (frmCodigo->mmCodigo->Lines->Strings[0] != "Apresenta��o sem t�tulo") {
				dsSalvarProj->FileName = frmCodigo->mmCodigo->Lines->Strings[0];
			}
			else {
				dsSalvarProj->FileName = "Apresenta��o sem t�tulo";
			}
			if (dsSalvarProj->Execute()) {
				PWSTR pszPath;
				if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
				{
					String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP");
					CoTaskMemFree(pszPath);

					String arq = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSCA.nps");
					frmCodigo->mmCodigo->Lines->SaveToFile(arq);

					TDirectory::Move(NSNPTEMP, dsSalvarProj->FileName);

					if (TDirectory::Exists(NSNPTEMP)) {
						TDirectory::Delete(NSNPTEMP, true);
					}

				}
			}
			else {
				goto pergunta;
			}
		}
	}
	else {
		PWSTR pszPath;
		if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
		{
			String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP");
			CoTaskMemFree(pszPath);

			if (TDirectory::Exists(NSNPTEMP)) {
				TDirectory::Delete(NSNPTEMP, true);
			}
		}
	}

	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btCriarTranspMouseLeave(TObject *Sender)
{
	btCriarTransp->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btModTranspMouseLeave(TObject *Sender)
{
	btModTransp->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSalvarDadosMouseLeave(TObject *Sender)
{
	btSalvarDados->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btLimpDadosMouseLeave(TObject *Sender)
{
	btLimpDados->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAjudaOnlineMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btAjudaOnline->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAjudaOnlineMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btAjudaOnline->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAjudaOnlineMouseLeave(TObject *Sender)
{
	btAjudaOnline->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btCentralSupMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btCentralSup->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btCentralSupMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btCentralSup->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btCentralSupMouseLeave(TObject *Sender)
{
	btCentralSup->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btEmailMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btEmail->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btEmailMouseLeave(TObject *Sender)
{
	btEmail->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btEmailMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btEmail->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btDocWikiMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btDocWiki->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btDocWikiMouseLeave(TObject *Sender)
{
	btDocWiki->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btDocWikiMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btDocWiki->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSobreMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btSobre->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSobreMouseLeave(TObject *Sender)
{
	btSobre->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSobreMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btSobre->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSalvarProjMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	spClique->Position->X = btSalvarProj->Position->X;
	spClique->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSalvarProjMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	spClique->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSalvarProjMouseLeave(TObject *Sender)
{
	spClique->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAbrirProjMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	spClique->Position->X = btAbrirProj->Position->X;
	spClique->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAbrirProjMouseLeave(TObject *Sender)
{
	spClique->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAbrirProjMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	spClique->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btNovoProjMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	spClique->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btNovoProjMouseLeave(TObject *Sender)
{
	spClique->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btNovoProjMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	spClique->Position->X = btNovoProj->Position->X;
	spClique->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSalvarProjClick(TObject *Sender)
{
	int escSalva = MessageBox (0, L"Voc� gostaria de exportar a apresenta��o conclu�da?\nCaso n�o deseje, voc� ir� salv�-la no modo de edi��o.\nPara maiores informa��es visite nossa docwiki.", L"Aviso - Ninterpres", MB_YESNO+MB_ICONQUESTION);
	if (escSalva == 6) {

		TZipFile* ArquivoPronto = new TZipFile();

		if (frmCodigo->mmCodigo->Lines->Strings[0] != "Apresenta��o sem t�tulo") {
			dsExportar->FileName = frmCodigo->mmCodigo->Lines->Strings[0];
		}
		else {
			dsExportar->FileName = "Apresenta��o sem t�tulo";
		}

		if (salvo) {
			String bin = System::Ioutils::TPath::Combine(locSalvo, L"BIN");
			TDirectory::Copy(L"BIN", bin);
			String arq = System::Ioutils::TPath::Combine(locSalvo, L"NSCA.nps");
			frmCodigo->mmCodigo->Lines->SaveToFile(arq);
//			String atalho = System::Ioutils::TPath::Combine(locSalvo, L"Ninterpres-a.exe");
//			TFile::Copy(L"Atalho.exe", atalho);

			if (dsExportar->Execute()) {
					ArquivoPronto->ZipDirectoryContents(dsExportar->FileName,locSalvo);
					ArquivoPronto->Free();
					if (TDirectory::Exists(bin)) {
						TDirectory::Delete(bin, true);
					}
  /*					if (TFile::Exists(atalho)) {
						TFile::Delete(atalho);
					} */
			}
			else {
				if (TDirectory::Exists(bin)) {
					TDirectory::Delete(bin, true);
				}
				throw Exception("Voc� cancelou a opera��o!\nCaso esta a��o n�o tenha sido sua, por favor, considere os dados apresentados a seguir:\nERRO 000102: N�o foi poss�vel executar a opera��o de exporta��o.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

		}
		else {
			if (frmCodigo->mmCodigo->Lines->Strings[0] != "Apresenta��o sem t�tulo") {
				dsExportar->FileName = frmCodigo->mmCodigo->Lines->Strings[0];
			}
			else {
				dsExportar->FileName = "Apresenta��o sem t�tulo";
			}
			if (dsExportar->Execute()) {
				PWSTR pszPath;
				if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
				{
					String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP");
					CoTaskMemFree(pszPath);

					String bin = System::Ioutils::TPath::Combine(NSNPTEMP, L"BIN");
					TDirectory::Copy(L"BIN", bin);
					String arq = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSCA.nps");
					frmCodigo->mmCodigo->Lines->SaveToFile(arq);
//					String atalho = System::Ioutils::TPath::Combine(NSNPTEMP, L"Ninterpres-a.exe");
//					TFile::Copy(L"Atalho.exe", atalho);

					ArquivoPronto->ZipDirectoryContents(dsExportar->FileName,NSNPTEMP);
					ArquivoPronto->Free();

					TFile::Delete(arq);
					TDirectory::Delete(bin, true);
//					TFile::Delete(atalho);
				}
			}
			else {
				throw Exception("Voc� cancelou a opera��o!\nCaso esta a��o n�o tenha sido sua, por favor, considere os dados apresentados a seguir:\nERRO 000102: N�o foi poss�vel executar a opera��o de exporta��o.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}
		}
	}
	else {
		if (salvo) {
			String arq = System::Ioutils::TPath::Combine(locSalvo, L"NSCA.nps");
			frmCodigo->mmCodigo->Lines->SaveToFile(arq);
		}
		else {
			if (frmCodigo->mmCodigo->Lines->Strings[0] != "Apresenta��o sem t�tulo") {
				dsSalvarProj->FileName = frmCodigo->mmCodigo->Lines->Strings[0];
			}
			else {
				dsSalvarProj->FileName = "Apresenta��o sem t�tulo";
			}
			if (dsSalvarProj->Execute()) {
				PWSTR pszPath;
				if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
				{
					String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP");
					CoTaskMemFree(pszPath);

					String arq = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSCA.nps");
					frmCodigo->mmCodigo->Lines->SaveToFile(arq);

					TDirectory::Move(NSNPTEMP, dsSalvarProj->FileName);

					salvo = true;
					locSalvo = dsSalvarProj->FileName;

				}
			}
			else {
				throw Exception("Voc� cancelou a opera��o!\nCaso esta a��o n�o tenha sido sua, por favor, considere os dados apresentados a seguir:\nERRO 000100: N�o foi poss�vel executar a opera��o de salvamento de arquivo.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAbrirProjClick(TObject *Sender)
{
	if (daAbrirProj->Execute()) {
		locSalvo = ExtractFilePath(daAbrirProj->FileName);
		frmCodigo->mmCodigo->Lines->Clear();
		frmCodigo->mmCodigo->BeginUpdate();
		frmCodigo->mmCodigo->Lines->LoadFromFile(daAbrirProj->FileName);
		frmCodigo->mmCodigo->EndUpdate();
		salvo = true;
		SelecTransp->Items->Clear();
		SelecTransp->Items->Add()->Text = "CAPA";

		int i = 0, num = 1, tam = frmCodigo->mmCodigo->Lines->Count;

		do{
			if (frmCodigo->mmCodigo->Lines->Strings[i] == "$TRANSP"+IntToStr(num)) {
				SelecTransp->Items->Add()->Text = "TRANSP"+IntToStr(num);
				num++;
			}
			i++;
		}while (i < tam);

		Transp = 0;
		edtApresTitulo->Text = frmCodigo->mmCodigo->Lines->Strings[0];
		edTranspTitulo->Text = frmCodigo->mmCodigo->Lines->Strings[0];
		frmPrincipal->Caption = frmCodigo->mmCodigo->Lines->Strings[0];
		lblTituloForm->Text = frmCodigo->mmCodigo->Lines->Strings[0];
		if (frmCodigo->mmCodigo->Lines->Strings[1] != "Nintersoft") {
			edtApresAutor->Text = frmCodigo->mmCodigo->Lines->Strings[1];
		}
		else {
			edtApresAutor->Text = "";
		}
		vsTransp->Fill->Color = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);
		listaCorApresenta->Color = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);
		if (frmCodigo->mmCodigo->Lines->Strings[3] == "==") {
			vsTransp->Stroke->Color = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);
			cbBorda->IsChecked = true;
		}
		else {
			vsTransp->Stroke->Color = CorBordaTransp;
			cbBorda->IsChecked = false;
		}
		if (frmCodigo->mmCodigo->Lines->Strings[4] == "==" && frmCodigo->mmCodigo->Lines->Strings[5] == "==") {
			lblTitulo->TextSettings->FontColor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[6]);
			lblTranspTexto->TextSettings->FontColor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[6]);
			lblImgLeg->TextSettings->FontColor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[6]);
			listaCorTexto->Color = StrToInt(frmCodigo->mmCodigo->Lines->Strings[6]);
			cbTodos->IsChecked = true;
			cbFonte->IsChecked = true;
		}
		else {
			lblTitulo->TextSettings->FontColor = CorBordaTransp;
			lblTranspTexto->TextSettings->FontColor = CorBordaTransp;
			lblImgLeg->TextSettings->FontColor = CorBordaTransp;
			listaCorTexto->Color = CorBordaTransp;
			cbTodos->IsChecked = false;
			cbFonte->IsChecked = false;
		}
		lblTranspTexto->TextSettings->Font->Size = StrToFloat(frmCodigo->mmCodigo->Lines->Strings[7]);
		edtTamFonte->Text = frmCodigo->mmCodigo->Lines->Strings[7];
		baTamFonte->Value = StrToFloat(frmCodigo->mmCodigo->Lines->Strings[7]);

		int tamk = frmCodigo->mmCodigo->Lines->Count;

		if (frmCodigo->mmCodigo->Lines->Strings[tamk-1] == "NSFN") {
			opMostrarNSTransp->IsChecked = true;
		}
		else if (frmCodigo->mmCodigo->Lines->Strings[tamk-1] == "!NSFN") {
			opMostrarNSTransp->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000010: Falha nas configura��es especiais (�ltima transpar�ncia).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
		}

		if (frmCodigo->mmCodigo->Lines->Strings[tamk-2] == "NSPR") {
			opMostrarLogoNS->IsChecked = true;
		}
		else if (frmCodigo->mmCodigo->Lines->Strings[tamk-2] == "!NSPR") {
			opMostrarLogoNS->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000011: Falha nas configura��es especiais (Logo NS).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
		}

		if (frmCodigo->mmCodigo->Lines->Strings[tamk-3] == "NSDT") {
			opMostrarDataAtual->IsChecked = true;
		}
		else if (frmCodigo->mmCodigo->Lines->Strings[tamk-3] == "!NSDT") {
			opMostrarDataAtual->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000012: Falha nas configura��es especiais (Data).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
		}

		CarregarTransp(Transp);
	}
	else {
		throw Exception ("Voc� cancelou a opera��o!\nCaso esta a��o n�o tenha sido sua, por favor, considere os dados apresentados a seguir:\nERRO 000100: Falha na opera��o de abertura de arquivo.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btNovoProjClick(TObject *Sender)
{

	String arqb;

	PWSTR pszPath;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
	{
		String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres");
		CoTaskMemFree(pszPath);

		arqb = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSNV");

		if (!TFile::Exists(arqb+".nps")) {
			throw Exception ("ERRO 000009: O modelo de apresenta��o novo n�o pode ser encontrado.\nPara corrigir este problema, por favor, reinicie o programa.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
		}
	}

	frmCodigo->mmCodigo->Lines->Clear();
	frmCodigo->mmCodigo->Lines->LoadFromFile(arqb+".nps");
	SelecTransp->Items->Clear();
	SelecTransp->Items->Add()->Text = "CAPA";
		if (frmCodigo->mmCodigo->Lines->Strings[1] != "Nintersoft") {
			edtApresAutor->Text = frmCodigo->mmCodigo->Lines->Strings[1];
		}
		else {
			edtApresAutor->Text = "";
		}
		vsTransp->Fill->Color = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);
		listaCorApresenta->Color = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);
		if (frmCodigo->mmCodigo->Lines->Strings[3] == "==") {
			vsTransp->Stroke->Color = StrToInt(frmCodigo->mmCodigo->Lines->Strings[2]);
			cbBorda->IsChecked = true;
		}
		else {
			vsTransp->Stroke->Color = CorBordaTransp;
			cbBorda->IsChecked = false;
		}
		if (frmCodigo->mmCodigo->Lines->Strings[4] == "==" && frmCodigo->mmCodigo->Lines->Strings[5] == "==") {
			lblTitulo->TextSettings->FontColor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[6]);
			lblTranspTexto->TextSettings->FontColor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[6]);
			lblImgLeg->TextSettings->FontColor = StrToInt(frmCodigo->mmCodigo->Lines->Strings[6]);
			listaCorTexto->Color = StrToInt(frmCodigo->mmCodigo->Lines->Strings[6]);
			cbTodos->IsChecked = true;
			cbFonte->IsChecked = true;
		}
		else {
			lblTitulo->TextSettings->FontColor = CorBordaTransp;
			lblTranspTexto->TextSettings->FontColor = CorBordaTransp;
			lblImgLeg->TextSettings->FontColor = CorBordaTransp;
			listaCorTexto->Color = CorBordaTransp;
			cbTodos->IsChecked = false;
			cbFonte->IsChecked = false;
		}
		lblTranspTexto->TextSettings->Font->Size = StrToFloat(frmCodigo->mmCodigo->Lines->Strings[7]);
		edtTamFonte->Text = frmCodigo->mmCodigo->Lines->Strings[7];
		baTamFonte->Value = StrToFloat(frmCodigo->mmCodigo->Lines->Strings[7]);

		int tamk = frmCodigo->mmCodigo->Lines->Count;

		if (frmCodigo->mmCodigo->Lines->Strings[tamk-1] == "NSFN") {
			opMostrarNSTransp->IsChecked = true;
		}
		else if (frmCodigo->mmCodigo->Lines->Strings[tamk-1] == "!NSFN") {
			opMostrarNSTransp->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000010: Falha nas configura��es especiais (�ltima transpar�ncia).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
		}

		if (frmCodigo->mmCodigo->Lines->Strings[tamk-2] == "NSPR") {
			opMostrarLogoNS->IsChecked = true;
		}
		else if (frmCodigo->mmCodigo->Lines->Strings[tamk-2] == "!NSPR") {
			opMostrarLogoNS->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000011: Falha nas configura��es especiais (Logo NS).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
		}

		if (frmCodigo->mmCodigo->Lines->Strings[tamk-3] == "NSDT") {
			opMostrarDataAtual->IsChecked = true;
		}
		else if (frmCodigo->mmCodigo->Lines->Strings[tamk-3] == "!NSDT") {
			opMostrarDataAtual->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000012: Falha nas configura��es especiais (Data).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
		}
	edTranspTitulo->Text = "";
	Transp = 0;
	CarregarTransp(Transp);
	salvo = false;

}
//---------------------------------------------------------------------------

