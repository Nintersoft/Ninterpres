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
#include "Carregar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
const float RealTamFonte = 1.3125;
int tpEscolha = 1, Cam = 390, CorBordaTransp, CorFundoTransp, Vis = 0;
bool prim, salvo = false, confSalvo = false;
String TranspSelec, locSalvo;
TFileStream* ProjAtual;
TFileStream* ProjSecun;
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
	ShowMessage("Caso haja mais de um autor, você deverá separá-los \ncom vírgula de acordo com as normas ABNT.");

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
		frmPrincipal->Caption = "Apresentação sem título - Ninterpres";
		frmPrincipal->lblTituloForm->Text = "Apresentação sem título - Ninterpres";
		frmCodigo->mmCodigo->Lines->Strings[0] = "Apresentação sem título";
		edtApresTitulo->Text = "Apresentação sem título";

		if (Transp == 0){
			lblTitulo->Text = "Título da apresentação";
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
		SelecTransp->Selected = SelecTransp->Items->Item[Transp];
		SelecTransp->EndUpdate();

		frmCarregar->Show();
		frmPrincipal->Visible = false;
		prim = false;

	}

	int COR = listaCorApresenta->Color;
	vsTransp->Fill->Color = COR;
	int LOCLIN = LocDet("COR_TRANSP");
	frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "COR:"+IntToStr(COR);

	listaPrevTransp->ItemIndex = 3;

	LOCLIN = LocDet("TAM_FONTE");
	float TamConv = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
	lblTranspTexto->TextSettings->Font->Size = TamConv;

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
		ShowMessage("Os dados da capa são alterados e salvos automaticamente!");
	}
	else {
		ModificarDados(Transp);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btLimpDadosClick(TObject *Sender)
{
	int LimpConf = MessageBox (0, L"Você está certo disso?\nEsta ação não pode ser desfeita.\nVocê terá que reconfigurar tudo novamente!", L"Ninterpres - Aviso", MB_YESNO+MB_ICONQUESTION);
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

	Transp = 0;

	// Adquire a cor da borda da transparência

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
			lblTitulo->Text = "Título da apresentação";
		}
		else {
			lblTitulo->Text = "Título da transparência";
		}
	}
	if (Transp == 0) {
		if (edTranspTitulo->Text != "") {
			edtApresTitulo->Text = edTranspTitulo->Text;
		}
		else {
			edtApresTitulo->Text = "Apresentação sem título";
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
		ShowMessage("Você não pode mudar a disposição dos elementos da capa.\nCaso você deseje esta capacidade, por favor, contate nossa equipe\npara que possamos desenvolver esta característica.");
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
	if (edtApresTitulo->Text == "Apresentação sem título") {
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
			frmPrincipal->Caption = "Apresentação sem título - Ninterpres";
			frmPrincipal->lblTituloForm->Text = "Apresentação sem título - Ninterpres";
			frmCodigo->mmCodigo->Lines->Strings[0] = "Apresentação sem título";
			edtApresTitulo->Text = "Apresentação sem título";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::listaCorApresentaChange(TObject *Sender)
{
	if (listaCorApresenta->Color == listaCorTexto->Color) {
		ShowMessage("Você não pode escolher a mesma cor da fonte para o fundo da transparência.");
	}
	else {
		vsTransp->Fill->Color = listaCorApresenta->Color;
		int a = vsTransp->Fill->Color, LOCLIN = LocDet("COR_TRANSP");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "COR:" + IntToStr(a);
			if (cbBorda->IsChecked == true) {
				vsTransp->Stroke->Color = listaCorApresenta->Color;
			}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAjudaOnlineClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "http://www.nintersoft.ml/", NULL, NULL, SW_SHOW );
	ShowMessage("Por favor, aguarde enquanto nosso site é aberto!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cbBordaChange(TObject *Sender)
{
	if (cbBorda->IsChecked) {
		vsTransp->Stroke->Color = vsTransp->Fill->Color;
		int LOCLIN = LocDet("APL_BORDA");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "NSBD";
	}
	else {
		vsTransp->Stroke->Color = CorBordaTransp;
		int LOCLIN = LocDet("APL_BORDA");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "!NSBD";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cbTodosChange(TObject *Sender)
{
	if (cbTodos->IsChecked) {
		cbFonte->Enabled = true;
		int LOCLIN = LocDet("APL_TODOS");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "NSTT";
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
		int LOCLIN = LocDet("APL_TODOS");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "!NSTT";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cbFonteChange(TObject *Sender)
{
	if (cbFonte->IsChecked) {
		listaCorTexto->Enabled = true;
		lblListaCorTexto->Enabled = true;
		int LOCLIN = LocDet("APL_FONTE");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "NSFT";
		int cor = listaCorTexto->Color;
		IntToStr(cor);
		LOCLIN = LocDet("COR_FONTE");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "COR:" + IntToStr(cor);
	}
	else {
		listaCorTexto->Enabled = false;
		lblListaCorTexto->Enabled = false;
		int LOCLIN = LocDet("APL_FONTE");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "!NSFT";
		lblTitulo->TextSettings->FontColor = CorBordaTransp;
		lblTranspTexto->TextSettings->FontColor = CorBordaTransp;
		lblImgLeg->TextSettings->FontColor = CorBordaTransp;
		listaCorTexto->Color = CorBordaTransp;
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
		ShowMessage("Você não pode escolher a mesma cor da transparência para a cor da fonte!");
	}
	else {
		int cor = listaCorTexto->Color;
		lblTitulo->TextSettings->FontColor = listaCorTexto->Color;
		lblTranspTexto->TextSettings->FontColor = listaCorTexto->Color;
		lblImgLeg->TextSettings->FontColor = listaCorTexto->Color;
		int LOCLIN = LocDet("COR_FONTE");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "COR:" + IntToStr(cor);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btEmailClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "mailto:suporte@nintersoft.ml", NULL, NULL, SW_SHOW );
	ShowMessage("Por favor, aguarde enquanto o email oficial de suporte é aberto!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btDocWikiClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "http://docwiki.nintersoft.ml/ninterpres", NULL, NULL, SW_SHOW );
	ShowMessage("Por favor, aguarde enquanto nossa central de ajuda e conhecimento\nà respeito do Ninterpres é aberta!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btCentralSupClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "http://www.nintersoft.ml/suporte/", NULL, NULL, SW_SHOW );
	ShowMessage("Por favor, aguarde enquanto nossa central de suporte é aberta!");
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

			int pos = tam;
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
				SelecTransp->Selected = SelecTransp->Items->Item[Transp];
				CarregarTransp (Transp);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btMinimizarClick(TObject *Sender)
{
	frmPrincipal->WindowState = TWindowState::wsMinimized;
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
				throw Exception ("ERRO 000001: A capa não foi encontrada no código de compilação!\nVerifique este erro clicando na aba Visualizar e depois no botão 'Código'.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
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
						throw Exception ("ERRO 000003: O arquivo de imagem não foi salvo corretamente.\nVerifique este erro clicando na aba Visualizar e depois no botão 'Código'.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
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
							throw Exception ("ERRO 000003: O arquivo de imagem não foi salvo corretamente.\nVerifique este erro clicando na aba Visualizar e depois no botão 'Código'.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
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
			if (pos == 0 && frmCodigo->mmCodigo->Lines->Strings[0] != "Apresentação sem título") {
				frmPrincipal->lblTitulo->Text = frmCodigo->mmCodigo->Lines->Strings[0];
				frmPrincipal->edTranspTitulo->Text = frmCodigo->mmCodigo->Lines->Strings[0];
				pos++;
			}
			else if (pos == 0) {
				frmPrincipal->edtApresTitulo->Text = "Apresentação sem título";
				frmPrincipal->lblTitulo->Text =  "Digite o título da apresentação";
				pos++;
			}
			else if (pos == 1 && frmCodigo->mmCodigo->Lines->Strings[1] != "Nintersoft") {
				frmPrincipal->lblTranspTexto->Text = frmCodigo->mmCodigo->Lines->Strings[1];
				frmPrincipal->mmTranspCont->Text =  frmCodigo->mmCodigo->Lines->Strings[1];
				pos++;
			}
			else if (pos == 1) {
				frmPrincipal->lblTranspTexto->Text = "Nome do Autor, Nome do Segundo Autor, Nome do Terceiro Autor, Nome do Autor nºx.";
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
				throw Exception ("ERRO 000001: A transparência selecionada não foi encontrada no código de compilação!\nVerifique este erro clicando na aba Visualizar e depois no botão 'Código'.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
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
				throw Exception ("Erro na configuração do tipo de transparência!");
			}
			else if (pos == 1 && frmCodigo->mmCodigo->Lines->Strings[loc] != "*.*") {
				frmPrincipal->lblTitulo->Text = frmCodigo->mmCodigo->Lines->Strings[loc];
				frmPrincipal->edTranspTitulo->Text = frmCodigo->mmCodigo->Lines->Strings[loc];
				loc++;
				pos++;
			}
			else if (pos == 1 && frmCodigo->mmCodigo->Lines->Strings[loc] == "*.*") {
				frmPrincipal->lblTitulo->Text = "Digite o título da transparência";
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
						throw Exception ("ERRO 000003: O arquivo de imagem não foi salvo corretamente.\nVerifique este erro clicando na aba Visualizar e depois no botão 'Código'.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
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
							throw Exception ("ERRO 000003: O arquivo de imagem não foi salvo corretamente.\nVerifique este erro clicando na aba Visualizar e depois no botão 'Código'.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
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
				primVar = true;
				loc++;
				pos++;
			}
			else if (pos == 3 && frmCodigo->mmCodigo->Lines->Strings[loc] == "*.*") {
				frmPrincipal->lblImgLeg->Text = "";
				frmImgConf->edtImgLeg->Text = "";
				primVar = true;
				loc++;
				pos++;
			}
			else if (pos == 4 && frmCodigo->mmCodigo->Lines->Strings[loc] != "*.*") {

				if (primVar) {
					frmPrincipal->mmTranspCont->BeginUpdate();
					frmPrincipal->mmTranspCont->Lines->Clear();
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
				frmPrincipal->mmTranspCont->Repaint();
				frmPrincipal->mmTranspCont->GoToTextEnd();
				frmPrincipal->lblTranspTexto->Text = frmPrincipal->mmTranspCont->Text;
				pos++;

			}
			else if (pos == 4 && frmCodigo->mmCodigo->Lines->Strings[loc] == "*.*") {
				frmPrincipal->lblTranspTexto->Text = "Digite seu conteúdo de texto para esta transparência aqui.";
				frmPrincipal->mmTranspCont->Lines->Clear();
				loc++;
				pos++;
			}
		} while (frmCodigo->mmCodigo->Lines->Strings[loc] != "!(FDT)");

		frmPrincipal->mmTranspCont->ReadOnly = false;

	}

	frmPrincipal->lblTranspAtual->Text = IntToStr(frmPrincipal->SelecTransp->Selected->Index + 1);
	frmPrincipal->lblQtdTransp->Text = IntToStr(frmPrincipal->SelecTransp->Items->Count);

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
	frmConfig->abasConf->ActiveTab = frmConfig->abaDesenv;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::opMostrarNSTranspChange(TObject *Sender)
{
	if (opMostrarNSTransp->IsChecked) {
		int LOCLIN = LocDet("MSTR_TRANSP");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "NSFN";
	}
	else {
		int LOCLIN = LocDet("MSTR_TRANSP");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "!NSFN";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::opMostrarLogoNSChange(TObject *Sender)
{
	if (opMostrarLogoNS->IsChecked) {
		int LOCLIN = LocDet("MSTR_LOGO");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "NSLG";
	}
	else {
		int LOCLIN = LocDet("MSTR_LOGO");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "!NSLG";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::opMostrarDataAtualChange(TObject *Sender)
{
	if (opMostrarDataAtual->IsChecked) {
		int LOCLIN = LocDet("MSTR_DATA");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "NSDT";
	}
	else {
		int LOCLIN = LocDet("MSTR_DATA");
		frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "!NSDT";
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
		throw Exception ("Não foi possível alterar o tipo da transparência.\nPor favor, verifique se o código está seguindo as diretrizes determinadas em nossa DocWiki.");
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mmTranspContExit(TObject *Sender)
{
	if (mmTranspCont->Text != "") {
		lblTranspTexto->Text = mmTranspCont->Text;
	}
	else {
		lblTranspTexto->Text = "Digite seu conteúdo de texto para esta transparência aqui.";
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
		lblTranspTexto->Text = "Digite seu conteúdo de texto para esta transparência aqui.";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btExcluirTranspClick(TObject *Sender)
{
	if (Transp == 0){
		throw Exception("Você não pode excluir a capa. Caso esta função seja realmente necessária, por favor, contate a equipe de desenvolvimento.");
	}
	else{
		int LimpConf = MessageBox (0, L"Você está certo disso?\nEsta ação não pode ser desfeita.\nEsta transparência não poderá ser reposta!", L"Ninterpres - Aviso", MB_YESNO+MB_ICONQUESTION);
		if (LimpConf == 6) {
			ExcluirTransp(Transp);
		}
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
				throw Exception ("ERRO 000002: Não foi possível carregar o leiaute desta transparência!\nVerifique este erro clicando na aba Visualizar e depois no botão 'Código'.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
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
					while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
						loc++;
					}
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
					while (comentario(frmCodigo->mmCodigo->Lines->Strings[loc])){
						loc++;
					}
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

	CarregarTransp(Transp);

}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::mmTranspContClick(TObject *Sender)
{
	if (mmTranspCont->ReadOnly) {
		ShowMessage("Você está editando a capa.\nPara editar o nome dos autores vá até a aba 'Arquivo' e no campo 'Autor(es)', digite o nome do(s) autor(es) desejado(s).");
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
	int Exclui = MessageBox (0, L"Você realmente deseja remover a imagem?\nCaso você esteja editando a capa esta ação será automaticamente salva.", L"Aviso - Ninterpres", MB_YESNO+MB_ICONQUESTION);
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
	float ValorHorzM = 0.00585651 * LargTransp; //Porcentagem correspondente à 8 em 1366
	float ValorHorz = 0.00781250 * LargTransp;  //Porcentagem correspondente à 8 em 1024
	float ValorVert = 0.01041667 * AltTransp;   //Porcentagem correspondente à 8 em 768

	TfrmPrincipal::AjusteVisual();

	if (Vis == 0) {
		if (Transp == 0) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
			frmPrincipal->vsTransp->Fill->Color = cor;

			if (frmPrincipal->cbBorda->IsChecked) {
				vsTransp->Stroke->Color = cor;
			}
			else {
				vsTransp->Stroke->Color = CorBordaTransp;
			}

			frmPrincipal->lblTitulo->Position->Y = AltTransp/2;
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTitulo->Position->X = (3 * ValorHorzM);
			else frmPrincipal->lblTitulo->Position->X = (3 * ValorHorz);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTitulo->Width = (vsTransp->Width - (3 * ValorHorzM));
			else frmPrincipal->lblTitulo->Width = (vsTransp->Width - (3 * ValorHorz));
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x1;
			frmPrincipal->lblTitulo->Height = tamFonteTitulo;
			frmPrincipal->lblTitulo->Font->Size = tamFonteTitulo;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Width = LargTransp - (4 * ValorHorzM);
			else frmPrincipal->lblTranspTexto->Width = LargTransp - (4 * ValorHorz);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Position->X = ValorHorzM * 3;
			else frmPrincipal->lblTranspTexto->Position->X = ValorHorz * 3;
			frmPrincipal->lblTranspTexto->Position->Y = AltTransp/2 + ValorVert + frmPrincipal->lblTitulo->Height;
			frmPrincipal->lblTranspTexto->Height = tamFonteBasica * RealTamFonte * 2;
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x1;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x1;

			frmPrincipal->imgTransp->Position->X = 0;
			frmPrincipal->imgTransp->Position->Y = 0;
			frmPrincipal->imgTransp->Width = LargTransp;
			frmPrincipal->imgTransp->Height = AltTransp;
			frmPrincipal->imgTransp->WrapMode = TImageWrapMode::iwStretch;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Width = LargTransp - (ValorHorzM * 4);
			else frmPrincipal->lblImgLeg->Width = LargTransp - (ValorHorz * 4);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Position->X = ValorHorzM * 3;
			else frmPrincipal->lblImgLeg->Position->X = ValorHorz * 3;
			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x2;
			frmPrincipal->lblImgLeg->Position->Y = AltTransp - ValorVert * 3 - frmPrincipal->lblImgLeg->Height;
			frmPrincipal->lblImgLeg->Visible = true;

		}
		else if (estilo == 1) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: Há um problema no código de compilação.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informações sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTitulo->Position->Y = (ValorHorzM * 3);
			else frmPrincipal->lblTitulo->Position->Y = (ValorHorz * 3);
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->Width = vsTransp->Width;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblTitulo->Height = tamFonteTitulo;
			frmPrincipal->lblTitulo->Font->Size = tamFonteTitulo;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Width = LargTransp/2 - (ValorHorzM * 4);
			else frmPrincipal->imgTransp->Width = LargTransp/2 - (ValorHorz * 4);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Position->X = LargTransp / 2 + ValorHorzM;
			else frmPrincipal->imgTransp->Position->X = LargTransp / 2 + ValorHorz;
			frmPrincipal->imgTransp->Height = AltTransp - (ValorVert * 14) - frmPrincipal->lblImgLeg->Height - (ValorVert * 4);
			frmPrincipal->imgTransp->Position->Y = (ValorVert * 13) + (ValorVert/4);
			frmPrincipal->imgTransp->WrapMode = TImageWrapMode::iwFit;

			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x0;
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Width = LargTransp/2 - ValorHorzM * 4;
			else frmPrincipal->lblImgLeg->Width = LargTransp/2 - ValorHorz * 4;
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Position->X = LargTransp / 2 + ValorHorzM * 2;
			else frmPrincipal->lblImgLeg->Position->X = LargTransp / 2 + ValorHorz * 2;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + ValorVert;
			frmPrincipal->lblImgLeg->Visible = true;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Width = LargTransp/2 - (ValorHorzM * 4);
			else frmPrincipal->lblTranspTexto->Width = LargTransp/2 - (ValorHorz * 4);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Position->X = ValorHorzM * 3;
			else frmPrincipal->lblTranspTexto->Position->X = ValorHorz * 3;
			frmPrincipal->lblTranspTexto->Height = frmPrincipal->imgTransp->Height;
			frmPrincipal->lblTranspTexto->Position->Y = (ValorVert * 13) + (ValorVert/4);
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x2;

		}
		else if (estilo == 2) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: Há um problema no código de compilação.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informações sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = ValorVert * 3;
			frmPrincipal->lblTitulo->Width = vsTransp->Width;
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblTitulo->Height = tamFonteTitulo;
			frmPrincipal->lblTitulo->Font->Size = tamFonteTitulo;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Width = LargTransp/2 - ValorHorzM * 4;
			else frmPrincipal->imgTransp->Width = LargTransp/2 - ValorHorz * 4;
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Position->X = ValorHorzM * 3;
			else frmPrincipal->imgTransp->Position->X = ValorHorz * 3;
			frmPrincipal->imgTransp->Height = AltTransp - (ValorVert * 14) - frmPrincipal->lblImgLeg->Height - (ValorVert * 4);
			frmPrincipal->imgTransp->Position->Y = (ValorVert * 13) + (ValorVert/4);
			frmPrincipal->imgTransp->WrapMode = TImageWrapMode::iwFit;

			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x0;
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Width = LargTransp/2 - (ValorHorzM * 4);
			else frmPrincipal->lblImgLeg->Width = LargTransp/2 - (ValorHorz * 4);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Position->X = ValorHorz * 3;
			else frmPrincipal->lblImgLeg->Position->X = ValorHorz * 3;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + ValorVert;
			frmPrincipal->lblImgLeg->Visible = true;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Width = LargTransp/2 - (ValorHorzM * 4);
			else frmPrincipal->lblTranspTexto->Width = LargTransp/2 - (ValorHorz * 4);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Position->X = LargTransp / 2 + ValorHorzM;
			else frmPrincipal->lblTranspTexto->Position->X = LargTransp / 2 + ValorHorzM;\
			frmPrincipal->lblTranspTexto->Height = frmPrincipal->imgTransp->Height;
			frmPrincipal->lblTranspTexto->Position->Y = (ValorVert * 13) + (ValorVert/4);
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x1;

		}
		else if (estilo == 3) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: Há um problema no código de compilação.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informações sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = AltTransp - (ValorVert * 11);
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->Width = vsTransp->Width;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblTitulo->Height = tamFonteTitulo;
			frmPrincipal->lblTitulo->Font->Size = tamFonteTitulo;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Width = LargTransp/2 - (3 * ValorHorzM);
			else frmPrincipal->imgTransp->Width = LargTransp/2 - (3 * ValorHorz);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Position->X = LargTransp / 2 + ValorHorzM;
			else frmPrincipal->imgTransp->Position->X = LargTransp / 2 + ValorHorz;
			frmPrincipal->imgTransp->Height = AltTransp - (ValorVert * 14) - frmPrincipal->lblImgLeg->Height - 32;
			frmPrincipal->imgTransp->Position->Y = ValorVert * 3;
			frmPrincipal->imgTransp->WrapMode = TImageWrapMode::iwFit;

			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x0;
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Width = LargTransp/2 - (ValorHorzM * 4);
			else frmPrincipal->lblImgLeg->Width = LargTransp/2 - (ValorHorz * 4);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Position->X = LargTransp / 2 + ValorHorzM;
			else frmPrincipal->lblImgLeg->Position->X = LargTransp / 2 + ValorHorz;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + ValorVert;
			frmPrincipal->lblImgLeg->Visible = true;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Width = LargTransp/2 - (ValorHorzM * 4);
			else frmPrincipal->lblTranspTexto->Width = LargTransp/2 - (ValorHorz * 4);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Position->X = ValorHorzM * 3;
			else frmPrincipal->lblTranspTexto->Position->X = ValorHorz * 3;
			frmPrincipal->lblTranspTexto->Height = frmPrincipal->imgTransp->Height;
			frmPrincipal->lblTranspTexto->Position->Y = ValorVert * 3;
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x2;

		}
		else if (estilo == 4) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: Há um problema no código de compilação.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informações sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = AltTransp - (ValorVert * 11);
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->Width = vsTransp->Width;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblTitulo->Height = tamFonteTitulo;
			frmPrincipal->lblTitulo->Font->Size = tamFonteTitulo;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Width = LargTransp/2 - (4 * ValorHorzM);
			else frmPrincipal->imgTransp->Width = LargTransp/2 - (4 * ValorHorz);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Position->X = ValorHorzM * 3;
			else frmPrincipal->imgTransp->Position->X = ValorHorz * 3;
			frmPrincipal->imgTransp->Height = AltTransp - (ValorVert * 14) - frmPrincipal->lblImgLeg->Height - (ValorVert * 4);
			frmPrincipal->imgTransp->Position->Y = ValorVert * 3;
			frmPrincipal->imgTransp->WrapMode = TImageWrapMode::iwFit;

			frmPrincipal->lblImgLeg->TextSettings->HorzAlign = 0x0;
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Width = LargTransp/2 - (ValorHorzM * 4);
			else frmPrincipal->lblImgLeg->Width = LargTransp/2 - (ValorHorz * 4);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Position->X = ValorHorzM * 3;
			else frmPrincipal->lblImgLeg->Position->X = ValorHorz * 3;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + ValorVert;
			frmPrincipal->lblImgLeg->Visible = true;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Width = LargTransp/2 - (ValorHorzM * 4);
			else frmPrincipal->lblTranspTexto->Width = LargTransp/2 - (ValorHorz * 4);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Position->X = LargTransp / 2 + ValorHorzM;
			else frmPrincipal->lblTranspTexto->Position->X = LargTransp / 2 + ValorHorz;
			frmPrincipal->lblTranspTexto->Height = frmPrincipal->imgTransp->Height;
			frmPrincipal->lblTranspTexto->Position->Y = (ValorVert * 3);
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x1;

		}
		else if (estilo == 5) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: Há um problema no código de compilação.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informações sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = (ValorVert * 3);
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->Width = vsTransp->Width;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblTitulo->Height = tamFonteTitulo;
			frmPrincipal->lblTitulo->Font->Size = tamFonteTitulo;

			frmPrincipal->imgTransp->Width = 0;
			frmPrincipal->imgTransp->Position->X = 0;
			frmPrincipal->imgTransp->Height = 0;
			frmPrincipal->imgTransp->Position->Y = 0;

			frmPrincipal->lblImgLeg->Width = 0;
			frmPrincipal->lblImgLeg->Position->X = 0;
			frmPrincipal->lblImgLeg->Position->Y = 0;
			frmPrincipal->lblImgLeg->Visible = false;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Width = LargTransp - (ValorHorzM * 6);
			else frmPrincipal->lblTranspTexto->Width = LargTransp - (ValorHorz * 6);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblTranspTexto->Position->X = (ValorHorzM * 3);
			else frmPrincipal->lblTranspTexto->Position->X = (ValorHorz * 3);
			frmPrincipal->lblTranspTexto->Height = AltTransp - (ValorVert * 17);
			frmPrincipal->lblTranspTexto->Position->Y = (ValorVert * 13) + (ValorVert/4);
			frmPrincipal->lblTranspTexto->TextSettings->VertAlign = 0x0;
			frmPrincipal->lblTranspTexto->TextSettings->HorzAlign = 0x0;

		}
		else if (estilo == 6) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: Há um problema no código de compilação.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informações sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = ValorVert * 3;
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->Width = vsTransp->Width;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblTitulo->Height = tamFonteTitulo;
			frmPrincipal->lblTitulo->Font->Size = tamFonteTitulo;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Width = LargTransp - (ValorHorzM * 6);
			else frmPrincipal->imgTransp->Width = LargTransp - (ValorHorz * 6);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Position->X = ValorHorzM * 3;
			else frmPrincipal->imgTransp->Position->X = ValorHorz * 3;
			frmPrincipal->imgTransp->Height = AltTransp - (ValorVert * 14) - frmPrincipal->lblImgLeg->Height - (ValorVert * 4);
			frmPrincipal->imgTransp->Position->Y = (ValorVert * 13) + (ValorVert/4);
			frmPrincipal->imgTransp->WrapMode = TImageWrapMode::iwFit;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Width = LargTransp - (ValorHorzM * 6);
			else frmPrincipal->lblImgLeg->Width = LargTransp - (ValorHorz * 6);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Position->X = ValorHorzM * 3;
			else frmPrincipal->lblImgLeg->Position->X = ValorHorz * 3;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + ValorVert;
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

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				frmPrincipal->vsTransp->Fill->Color = cor;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = cor;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				frmPrincipal->vsTransp->Fill->Color = CorFundoTransp;
					if (frmPrincipal->cbBorda->IsChecked) {
						frmPrincipal->vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						frmPrincipal->vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: Há um problema no código de compilação.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informações sobre este erro visite nossa DocWiki.");
			}

			frmPrincipal->lblTitulo->Width = LargTransp;
			frmPrincipal->lblTitulo->Position->Y = AltTransp - (ValorVert * 11);
			frmPrincipal->lblTitulo->Position->X = 0;
			frmPrincipal->lblTitulo->Width = vsTransp->Width;
			frmPrincipal->lblTitulo->TextSettings->HorzAlign = 0x0;
			frmPrincipal->lblTitulo->Height = tamFonteTitulo;
			frmPrincipal->lblTitulo->Font->Size = tamFonteTitulo;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Width = LargTransp - (ValorHorzM * 6);
			else frmPrincipal->imgTransp->Width = LargTransp - (ValorHorz * 6);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->imgTransp->Position->X = ValorHorzM * 3;
			else frmPrincipal->imgTransp->Position->X = ValorHorz * 3;
			frmPrincipal->imgTransp->Height = AltTransp - (ValorVert * 14) - frmPrincipal->lblImgLeg->Height - (ValorVert * 4);
			frmPrincipal->imgTransp->Position->Y = (ValorVert * 3);
			frmPrincipal->imgTransp->WrapMode = TImageWrapMode::iwFit;

			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Width = LargTransp - (6 * ValorHorzM);
			else frmPrincipal->lblImgLeg->Width = LargTransp - (6 * ValorHorz);
			if (listaPrevTransp->Index == 0 | listaPrevTransp->Index == 1 ) frmPrincipal->lblImgLeg->Position->X = ValorHorzM * 3;
			else frmPrincipal->lblImgLeg->Position->X = ValorHorz * 3;
			frmPrincipal->lblImgLeg->Position->Y = frmPrincipal->imgTransp->Position->Y + frmPrincipal->imgTransp->Height + ValorVert;
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
	int LOCLIN = LocDet("TAM_FONTE");
	frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "TAM:"+FloatToStr(edtTamFonte->Value);
	AjusteVisual();
	lblTranspTexto->TextSettings->Font->Size = tamFonteBasica;
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
	int LOCLIN = LocDet("TAM_FONTE");
	frmCodigo->mmEstilo->Lines->Strings[LOCLIN] = "TAM:"+FloatToStr(edtTamFonte->Value);
	AjusteVisual();
	lblTranspTexto->TextSettings->Font->Size = tamFonteBasica;
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
	int SalvaFecha = MessageBox (0, L"Você encerrará a aplicação.\nOs dados não salvos da apresentação serão perdidos.\nDeseja salvar os dados da apresentação atual?", L"Aviso - Ninterpres", MB_YESNOCANCEL+MB_ICONQUESTION);
	if (SalvaFecha == 6) {
		if (salvo) {
			String arq = System::Ioutils::TPath::Combine(locSalvo, L"NSCA.nps");
			frmCodigo->mmCodigo->Lines->SaveToFile(arq);
			String arqb = System::Ioutils::TPath::Combine(locSalvo, L"NSST.stl");
			frmCodigo->mmEstilo->Lines->SaveToFile(arqb);
		}
		else {
			if (frmCodigo->mmCodigo->Lines->Strings[0] != "Apresentação sem título") {
				dsSalvarProj->FileName = frmCodigo->mmCodigo->Lines->Strings[0];
			}
			else {
				dsSalvarProj->FileName = "Apresentação sem título";
			}
			if (dsSalvarProj->Execute()) {
				PWSTR pszPath;
				if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
				{
					String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP");
					CoTaskMemFree(pszPath);

					String arq = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSCA.nps");
					frmCodigo->mmCodigo->Lines->SaveToFile(arq);
					String arqb = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSST.stl");
					frmCodigo->mmEstilo->Lines->SaveToFile(arqb);

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
		Application->Terminate();
	}
	else if (SalvaFecha == 2) {
		Action = TCloseAction::caNone;
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
		Application->Terminate();
	}

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
	int escSalva = MessageBox (0, L"Você gostaria de exportar a apresentação concluída?\nCaso não deseje, você irá salvá-la no modo de edição.\nPara maiores informações visite nossa docwiki.", L"Aviso - Ninterpres", MB_YESNO+MB_ICONQUESTION);
	if (escSalva == 6) {

		TZipFile* ArquivoPronto = new TZipFile();

		if (frmCodigo->mmCodigo->Lines->Strings[0] != "Apresentação sem título") {
			dsExportar->FileName = frmCodigo->mmCodigo->Lines->Strings[0];
		}
		else {
			dsExportar->FileName = "Apresentação sem título";
		}

		if (salvo) {
			String bin = System::Ioutils::TPath::Combine(locSalvo, L"BIN");
			TDirectory::Copy(L"BIN", bin);
			String arq = System::Ioutils::TPath::Combine(locSalvo, L"NSCA.nps");
			frmCodigo->mmCodigo->Lines->SaveToFile(arq);
			String arqb = System::Ioutils::TPath::Combine(locSalvo, L"NSST.stl");
			frmCodigo->mmEstilo->Lines->SaveToFile(arqb);
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
				throw Exception("Você cancelou a operação!\nCaso esta ação não tenha sido sua, por favor, considere os dados apresentados a seguir:\nERRO 000102: Não foi possível executar a operação de exportação.\nPara maiores informações sobre este erro visite nossa DocWiki.");
			}

		}
		else {
			if (frmCodigo->mmCodigo->Lines->Strings[0] != "Apresentação sem título") {
				dsExportar->FileName = frmCodigo->mmCodigo->Lines->Strings[0];
			}
			else {
				dsExportar->FileName = "Apresentação sem título";
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
					String arqb = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSST.stl");
					frmCodigo->mmEstilo->Lines->SaveToFile(arqb);
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
				throw Exception("Você cancelou a operação!\nCaso esta ação não tenha sido sua, por favor, considere os dados apresentados a seguir:\nERRO 000102: Não foi possível executar a operação de exportação.\nPara maiores informações sobre este erro visite nossa DocWiki.");
			}
		}
	}
	else {
		if (salvo) {
			String arq = System::Ioutils::TPath::Combine(locSalvo, L"NSCA.nps");
			delete ProjAtual;
			frmCodigo->mmCodigo->Lines->SaveToFile(arq);
			ProjAtual = new TFileStream(arq, TFileMode::fmOpen);
			String Estilo = System::Ioutils::TPath::Combine(locSalvo, "NSST.stl");
			delete ProjSecun;
			frmCodigo->mmEstilo->Lines->SaveToFile(Estilo);
			ProjSecun = new TFileStream(Estilo, TFileMode::fmOpen);
		}
		else {
			if (frmCodigo->mmCodigo->Lines->Strings[0] != "Apresentação sem título") {
				dsSalvarProj->FileName = frmCodigo->mmCodigo->Lines->Strings[0];
			}
			else {
				dsSalvarProj->FileName = "Apresentação sem título";
			}
			if (dsSalvarProj->Execute()) {
				PWSTR pszPath;
				if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
				{
					String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\TEMP");
					CoTaskMemFree(pszPath);

					String arq = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSCA.nps");
					frmCodigo->mmCodigo->Lines->SaveToFile(arq);
					String arqb = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSST.stl");
					frmCodigo->mmEstilo->Lines->SaveToFile(arqb);

					TDirectory::Move(NSNPTEMP, dsSalvarProj->FileName);

					salvo = true;
					locSalvo = dsSalvarProj->FileName;

				}
			}
			else {
				throw Exception("Você cancelou a operação!\nCaso esta ação não tenha sido sua, por favor, considere os dados apresentados a seguir:\nERRO 000100: Não foi possível executar a operação de salvamento de arquivo.\nPara maiores informações sobre este erro visite nossa DocWiki.");
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAbrirProjClick(TObject *Sender)
{
	int a;
	if (daAbrirProj->Execute()) {
		locSalvo = ExtractFilePath(daAbrirProj->FileName);
		if (salvo) {
			delete ProjAtual;
			delete ProjSecun;
			frmCodigo->mmCodigo->Lines->Clear();
			frmCodigo->mmCodigo->BeginUpdate();
			frmCodigo->mmCodigo->Lines->LoadFromFile(daAbrirProj->FileName);
			frmCodigo->mmCodigo->EndUpdate();
			ProjAtual = new TFileStream(daAbrirProj->FileName, TFileMode::fmOpen);
			String PreEstilo = System::Ioutils::TPath::Combine(locSalvo, "NSST"), Estilo = PreEstilo+".stl";

			if (TFile::Exists(Estilo)) {
				frmCodigo->mmEstilo->Lines->Clear();
				frmCodigo->mmEstilo->BeginUpdate();
				frmCodigo->mmEstilo->Lines->LoadFromFile(Estilo);
				frmCodigo->mmEstilo->EndUpdate();
				ProjSecun = new TFileStream(Estilo, TFileMode::fmOpen);
			}
			else {

				PWSTR pszPath;
				if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
				{
					String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres");
					CoTaskMemFree(pszPath);

					String arqa = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSST");
					Estilo = arqa+".stl";

					if (!TFile::Exists(arqa+".stl")) {
						throw Exception ("ERRO 000010: O modelo de estilos novo não pode ser encontrado.\nPara corrigir este problema, por favor, reinicie o programa.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
					}
				}

				frmCodigo->mmEstilo->Lines->Clear();
				frmCodigo->mmEstilo->BeginUpdate();
				frmCodigo->mmEstilo->Lines->LoadFromFile(Estilo);
				frmCodigo->mmEstilo->EndUpdate();
				ProjSecun = new TFileStream(Estilo, TFileMode::fmOpen);
				ShowMessage("Parece que não há folha de estilo para esta apresentação!\nEsta apresentação poderá ser lida incorretamente!\nBaixe uma versão mais antiga do Ninterpres para ler esta apresentação.\nOBS.: A última versão a suportar apresentações sem folha de estilo foi a 0.9.1.43-BETA\nPara maiores informações visite nossa docwiki.");

			}
		}
		else {
			frmCodigo->mmCodigo->Lines->Clear();
			frmCodigo->mmCodigo->BeginUpdate();
			frmCodigo->mmCodigo->Lines->LoadFromFile(daAbrirProj->FileName);
			frmCodigo->mmCodigo->EndUpdate();
			ProjAtual = new TFileStream(daAbrirProj->FileName, TFileMode::fmOpen);

			String PreEstilo = System::Ioutils::TPath::Combine(locSalvo, "NSST");
			String Estilo = PreEstilo+".stl";

			if (TFile::Exists(Estilo)) {
				frmCodigo->mmEstilo->Lines->Clear();
				frmCodigo->mmEstilo->BeginUpdate();
				frmCodigo->mmEstilo->Lines->LoadFromFile(Estilo);
				frmCodigo->mmEstilo->EndUpdate();
				ProjSecun = new TFileStream(Estilo, TFileMode::fmOpen);
			}
			else {

				PWSTR pszPath;
				if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
				{
					String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres");
					CoTaskMemFree(pszPath);

					String arqa = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSST");
					Estilo = arqa+".stl";

					if (!TFile::Exists(arqa+".stl")) {
						throw Exception ("ERRO 000010: O modelo de estilos novo não pode ser encontrado.\nPara corrigir este problema, por favor, reinicie o programa.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
					}
				}

				frmCodigo->mmEstilo->Lines->Clear();
				frmCodigo->mmEstilo->BeginUpdate();
				frmCodigo->mmEstilo->Lines->LoadFromFile(Estilo);
				frmCodigo->mmEstilo->EndUpdate();
				ProjSecun = new TFileStream(Estilo, TFileMode::fmOpen);
				ShowMessage("Parece que não há folha de estilo para esta apresentação!\nEsta apresentação poderá ser lida incorretamente!\nBaixe uma versão mais antiga do Ninterpres para ler esta apresentação.\nOBS.: A última versão a suportar apresentações sem folha de estilo foi a 0.9.1.43-BETA\nPara maiores informações visite nossa docwiki.");

			}

		}

		salvo = true;
		SelecTransp->BeginUpdate();
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

		SelecTransp->EndUpdate();

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
		int LOCLIN = LocDet("COR_TRANSP");
		vsTransp->Fill->Color = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
		listaCorApresenta->Color = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);

		LOCLIN = LocDet("APL_BORDA");
		if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSBD") {
			LOCLIN = LocDet("COR_TRANSP");
			vsTransp->Stroke->Color = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
			cbBorda->IsChecked = true;
		}
		else {
			vsTransp->Stroke->Color = CorBordaTransp;
			cbBorda->IsChecked = false;
		}

		LOCLIN = LocDet("APL_FONTE");
		int LOCLIN2 = LocDet("APL_TODOS"), LOCAUX = LocDet("COR_FONTE");

		if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN2] == "NSTT" && frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSFT") {
			lblTitulo->TextSettings->FontColor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCAUX]);
			lblTranspTexto->TextSettings->FontColor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCAUX]);
			lblImgLeg->TextSettings->FontColor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCAUX]);
			listaCorTexto->Color = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCAUX]);
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

		LOCLIN = LocDet("TAM_FONTE");
		float TamConv = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
		lblTranspTexto->TextSettings->Font->Size = TamConv;
		edtTamFonte->Text = FloatToStr(TamConv);
		baTamFonte->Value = TamConv;

		LOCLIN = LocDet("MSTR_TRANSP");
		if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSFN") {
			opMostrarNSTransp->IsChecked = true;
		}
		else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSFN") {
			opMostrarNSTransp->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000010: Falha nas configurações especiais (Última transparência).\nPara maiores informações sobre este erro visite nossa DocWiki.");
		}

		LOCLIN = LocDet("MSTR_LOGO");
		if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSLG") {
			opMostrarLogoNS->IsChecked = true;
		}
		else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSLG") {
			opMostrarLogoNS->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000011: Falha nas configurações especiais (Logo NS).\nPara maiores informações sobre este erro visite nossa DocWiki.");
		}

		LOCLIN = LocDet("MSTR_DATA");
		if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSDT") {
			opMostrarDataAtual->IsChecked = true;
		}
		else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSDT") {
			opMostrarDataAtual->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000012: Falha nas configurações especiais (Data).\nPara maiores informações sobre este erro visite nossa DocWiki.");
		}

		SelecTransp->Selected = SelecTransp->Items->Item[Transp];
		Transp = 0;
		CarregarTransp(Transp);
	}
	else {
		throw Exception ("Você cancelou a operação!\nCaso esta ação não tenha sido sua, por favor, considere os dados apresentados a seguir:\nERRO 000100: Falha na operação de abertura de arquivo.\nPara maiores informações sobre este erro visite nossa DocWiki.");
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btNovoProjClick(TObject *Sender)
{

	String arqa, arqb;

	PWSTR pszPath;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
	{
		String NSNPTEMP = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres");
		CoTaskMemFree(pszPath);

		arqb = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSNV");
		arqa = System::Ioutils::TPath::Combine(NSNPTEMP, L"NSST");

		if (!TFile::Exists(arqb+".nps")) {
			throw Exception ("ERRO 000009: O modelo de apresentação novo não pode ser encontrado.\nPara corrigir este problema, por favor, reinicie o programa.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
		}
		if (!TFile::Exists(arqa+".stl")) {
			throw Exception ("ERRO 000010: O modelo de estilos novo não pode ser encontrado.\nPara corrigir este problema, por favor, reinicie o programa.\nPara maiores informações à respeito deste erro, por favor visite nossa docwiki.");
		}
	}

	frmCodigo->mmCodigo->Lines->Clear();
	frmCodigo->mmCodigo->Lines->LoadFromFile(arqb+".nps");
	frmCodigo->mmEstilo->Lines->Clear();
	frmCodigo->mmEstilo->Lines->LoadFromFile(arqa+".stl");
	SelecTransp->BeginUpdate();
	SelecTransp->Items->Clear();
	SelecTransp->Items->Add()->Text = "CAPA";
	SelecTransp->EndUpdate();

		if (frmCodigo->mmCodigo->Lines->Strings[1] != "Nintersoft") {
			edtApresAutor->Text = frmCodigo->mmCodigo->Lines->Strings[1];
		}
		else {
			edtApresAutor->Text = "";
		}

		int LOCLIN = LocDet("COR_TRANSP");
		vsTransp->Fill->Color = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
		listaCorApresenta->Color = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);

		LOCLIN = LocDet("APL_BORDA");
		if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSBD") {
			vsTransp->Stroke->Color = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
			cbBorda->IsChecked = true;
		}
		else {
			vsTransp->Stroke->Color = CorBordaTransp;
			cbBorda->IsChecked = false;
		}

		LOCLIN = LocDet("APL_FONTE");
		int LOCLIN2 = LocDet("APL_TODOS");
		if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN2] == "NSTT" && frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSFT") {
			LOCLIN = LocDet("COR_FONTE");
			lblTitulo->TextSettings->FontColor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
			lblTranspTexto->TextSettings->FontColor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
			lblImgLeg->TextSettings->FontColor = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
			listaCorTexto->Color = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
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

		LOCLIN = LocDet("TAM_FONTE");
		float TamConv = AdquireTam(frmCodigo->mmEstilo->Lines->Strings[LOCLIN]);
		lblTranspTexto->TextSettings->Font->Size = TamConv;
		edtTamFonte->Text = FloatToStr(TamConv);
		baTamFonte->Value = TamConv;

		LOCLIN = LocDet("MSTR_TRANSP");
		if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSFN") {
			opMostrarNSTransp->IsChecked = true;
		}
		else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSFN") {
			opMostrarNSTransp->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000010: Falha nas configurações especiais (Última transparência).\nPara maiores informações sobre este erro visite nossa DocWiki.");
		}

		LOCLIN = LocDet("MSTR_LOGO");
		if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSLG") {
			opMostrarLogoNS->IsChecked = true;
		}
		else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSLG") {
			opMostrarLogoNS->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000011: Falha nas configurações especiais (Logo NS).\nPara maiores informações sobre este erro visite nossa DocWiki.");
		}

		LOCLIN = LocDet("MSTR_DATA");
		if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "NSDT") {
			opMostrarDataAtual->IsChecked = true;
		}
		else if (frmCodigo->mmEstilo->Lines->Strings[LOCLIN] == "!NSDT") {
			opMostrarDataAtual->IsChecked = false;
		}
		else {
			throw Exception ("ERRO 000012: Falha nas configurações especiais (Data).\nPara maiores informações sobre este erro visite nossa DocWiki.");
		}

	edTranspTitulo->Text = "";
	Transp = 0;
	CarregarTransp(Transp);
	salvo = false;

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::CorAbaVisualizarMouseEnter(TObject *Sender)
{
	brVisualizar->ShowScrollBars = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::CorAbaVisualizarMouseLeave(TObject *Sender)
{
	brVisualizar->ShowScrollBars = false;
}
//---------------------------------------------------------------------------
void TfrmPrincipal::ExcluirTransp(int LOC)
{

	SelecTransp->BeginUpdate();
	SelecTransp->Items->Delete(LOC);
	SelecTransp->EndUpdate();

	int pos = LOC + 1, tam = frmCodigo->mmCodigo->Lines->Count;

	for (int i = 0; i < tam; i++) {
		if (frmCodigo->mmCodigo->Lines->Strings[i] == "$TRANSP" + IntToStr(LOC)) {
			while (frmCodigo->mmCodigo->Lines->Strings[i] != "!(FDT)"){
				frmCodigo->mmCodigo->BeginUpdate();
				frmCodigo->mmCodigo->Lines->Delete(i);
				frmCodigo->mmCodigo->EndUpdate();
			}

			frmCodigo->mmCodigo->BeginUpdate();
			frmCodigo->mmCodigo->Lines->Delete(i);
			frmCodigo->mmCodigo->EndUpdate();
			break;
		}
	}

	tam = frmCodigo->mmCodigo->Lines->Count;

	for (int i = 0; i < tam; i++) {
		if (frmCodigo->mmCodigo->Lines->Strings[i] == "$TRANSP" + IntToStr(pos)){
			frmCodigo->mmCodigo->BeginUpdate();
			frmCodigo->mmCodigo->Lines->Strings[i] = "$TRANSP" + IntToStr(pos - 1);
			frmCodigo->mmCodigo->EndUpdate();
			pos++;
		}
	}

	for (int i = 0; i < SelecTransp->Items->Count; i++) {
		if (SelecTransp->Items->Item[i]->Index != 0) {
			SelecTransp->BeginUpdate();
			SelecTransp->Items->Item[i]->Text = "TRANSP" + IntToStr(SelecTransp->Items->Item[i]->Index);
			SelecTransp->EndUpdate();
		}
	}

	if (SelecTransp->Items->Count > LOC) {
		Transp = LOC;
	}
	else {
		Transp = LOC - 1;
	}

	SelecTransp->Selected = SelecTransp->Items->Item[Transp];
	CarregarTransp(Transp);
}
//---------------------------------------------------------------------------
void TfrmPrincipal::AjusteVisual() {
	if (listaPrevTransp->ItemIndex == 0) {

		int altmax = (int)brTransp->Height - 40;
		vsTransp->Height = altmax;

		int largmax = (int)((altmax/9)*16);
		vsTransp->Width = largmax;

		float altmaxconv = altmax;

		tamFonteBasica = ((altmaxconv/768) * edtTamFonte->Value);
		tamFonteTitulo = ((altmaxconv * 64) / 768);

		vsTransp->Position->X = (brTransp->Width - vsTransp->Width)/2;
		vsTransp->Position->Y = (brTransp->Height - vsTransp->Height)/2;

	}
	else if (listaPrevTransp->ItemIndex == 1) {

		float trPos[2], brTam[2], trTam[2];

		vsTransp->Width = 1366;
		vsTransp->Height = 768;

		tamFonteBasica = edtTamFonte->Value;
		tamFonteTitulo = 64;

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
	else if (listaPrevTransp->ItemIndex == 2) {

		int altmax = (int)brTransp->Height - 40;
		vsTransp->Height = altmax;

		int largmax = (int)((altmax/3)*4);
		vsTransp->Width = largmax;

		float altmaxconv = altmax;

		vsTransp->Position->X = (brTransp->Width - vsTransp->Width)/2;
		vsTransp->Position->Y = (brTransp->Height - vsTransp->Height)/2;

		tamFonteBasica = ((altmaxconv/768) * edtTamFonte->Value);
		tamFonteTitulo = ((altmaxconv * 64) / 768);


	}
	else {

		float trPos[2], brTam[2], trTam[2];

		vsTransp->Width = 1024;
		vsTransp->Height = 768;

		tamFonteBasica = edtTamFonte->Value;
		tamFonteTitulo = 64;

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
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::listaPrevTranspItemClick(TCustomListBox * const Sender,
		  TListBoxItem * const Item)
{
	CarregarTransp(SelecTransp->Selected->Index);
	CarregarTransp(SelecTransp->Selected->Index);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btExcluirTranspMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btExcluirTransp->Fill->Color = -40121;
	btExcluirTransp->Stroke->Color = -40121;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btExcluirTranspMouseLeave(TObject *Sender)
{
	btExcluirTransp->Fill->Color = -65536;
	btExcluirTransp->Stroke->Color = -65536;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btExcluirTranspMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btExcluirTransp->Fill->Color = -65536;
	btExcluirTransp->Stroke->Color = -65536;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btConfigMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btConfig->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btConfigMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btConfig->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btConfigMouseLeave(TObject *Sender)
{
	btConfig->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btVisualizarCodigoMouseLeave(TObject *Sender)
{
	btVisualizarCodigo->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btVisualizarCodigoMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btVisualizarCodigo->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btVisualizarCodigoMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btVisualizarCodigo->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btInformacoesMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btInformacoes->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btInformacoesMouseLeave(TObject *Sender)
{
	btInformacoes->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btInformacoesMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btInformacoes->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btInformacoesClick(TObject *Sender)
{
	frmConfig->Show();
	frmConfig->abasConf->ActiveTab = frmConfig->abaInfo;
}
//---------------------------------------------------------------------------

int TfrmPrincipal::LocDet(String Valor)
{

	int tamTot = frmCodigo->mmEstilo->Lines->Count - 1;
	bool inicio = true, encont = false;

	if (Valor == "TAM_FONTE" | Valor == "COR_FONTE" | Valor == "COR_TRANSP") {

		int comeco, fim, loc = 0;
		String Categoria, Tipo;

		if (Valor == "TAM_FONTE" | Valor == "COR_FONTE") Categoria = "$FNT";
		else if (Valor == "COR_TRANSP") Categoria = "$TRANSP";
		if (Valor == "COR_FONTE" | Valor == "COR_TRANSP") Tipo = "COR:";
		else if (Valor == "TAM_FONTE") Tipo = "TAM:";

		for (int i = 0; i < tamTot; i++) {
			if (inicio) {
				if (frmCodigo->mmEstilo->Lines->Strings[i] == Categoria) {
					comeco = i;
					inicio = false;
				}
			}
			else {
				if (frmCodigo->mmEstilo->Lines->Strings[i] == "!(FDD)") {
					fim = i;
					break;
				}
			}
		}

		for (int i = comeco; i < fim; i++) {

			String temp = "", dados = frmCodigo->mmEstilo->Lines->Strings[i];

			if (dados.Length() >= 5) {
				for (int k = 0; k < 4; k++) {
					if (temp + dados.c_str()[k] != NULL && temp + dados.c_str()[k] != ' ') {
						temp = temp + dados.c_str()[k];
					}
				}
				if (temp == Tipo) {
					loc = i;
					break;
				}
				else {
					temp = "";
				}
			}
		}

		if (loc == 0) {
			frmCodigo->mmEstilo->Lines->Insert(inicio + 1, "TAM:");
		}


		return loc;

	}

	else if (Valor == "MSTR_DATA" | Valor == "MSTR_TRANSP" | Valor == "MSTR_LOGO" | Valor == "APL_BORDA" | Valor == "APL_TODOS" | Valor == "APL_FONTE") {

		int comeco, fim, loc = 0;
		String Procura, Categoria;
		if (Valor == "MSTR_DATA") Procura = "NSDT";
		else if (Valor == "MSTR_TRANSP") Procura = "NSFN";
		else if (Valor == "MSTR_LOGO")   Procura = "NSLG";
		else if (Valor == "APL_BORDA")   Procura = "NSBD";
		else if (Valor == "APL_TODOS")   Procura = "NSTT";
		else if (Valor == "APL_FONTE")   Procura = "NSFT";
		if (Valor == "MSTR_DATA" | Valor == "MSTR_TRANSP" | Valor == "MSTR_LOGO") Categoria = "$OPO";
		else if (Valor == "APL_BORDA" | Valor == "APL_TODOS" | Valor == "APL_FONTE") Categoria = "$TRANSP";

		for (int i = 0; i < tamTot; i++) {
			if (inicio) {
				if (frmCodigo->mmEstilo->Lines->Strings[i] == Categoria) {
					comeco = i;
					inicio = false;
				}
			}
			else {
				if (frmCodigo->mmEstilo->Lines->Strings[i] == "!(FDD)") {
					fim = i;
					break;
				}
			}
		}

		for (int i = comeco; i < fim; i++) {

			String temp = "", dados = frmCodigo->mmEstilo->Lines->Strings[i];

			if (dados.Length() >= 4 && dados.Length() <= 5) {
				for (int k = 0; k < dados.Length(); k++) {
					if (temp + dados.c_str()[k] != NULL && temp + dados.c_str()[k] != " ") {
						temp = temp + dados.c_str()[k];
					}
				}
				if (temp == Procura | temp == "!"+Procura) {
					loc = i;
					break;
				}
				else {
					temp = "";
				}
			}
		}

		if (loc == 0) {
			if (Categoria == "$OPO") frmCodigo->mmEstilo->Lines->Insert(inicio + 1, Procura);
			else if (Categoria == "$TRANSP") frmCodigo->mmEstilo->Lines->Insert(inicio + 1, "!"+Procura);
		}


		return loc;

	}
	else {
		throw Exception (L"O valor declarado está incorreto!");
	}

}
//---------------------------------------------------------------------------
int TfrmPrincipal::AdquireTam(String Texto)
{

	bool inicio = true;
	String Tamanho = "";

	for (int i = 0; i < Texto.Length(); i++) {
		if (inicio){
			if (Texto.c_str()[i] == ':') {
				inicio = false;
			}
		}
		else {
			if (Texto.c_str()[i] != ' ') {
				Tamanho = Tamanho + Texto.c_str()[i];
			}
		}
	}

	int Convertido = (int)StrToFloat(Tamanho);

	return Convertido;

}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::tmCopiaSegTimer(TObject *Sender)
{
	if (salvo) {
		PWSTR pszPath;
		if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pszPath)))
		{
			String NSNPSV = System::Ioutils::TPath::Combine(pszPath, L"Nintersoft\\Ninterpres\\CPSEG\\");
			CoTaskMemFree(pszPath);

			String NSNPSVD = System::Ioutils::TPath::Combine(NSNPSV, frmCodigo->mmCodigo->Lines->Strings[0]);

			if (TDirectory::Exists(NSNPSVD)) TDirectory::Delete(NSNPSV, true);

			delete ProjAtual;
			delete ProjSecun;

			TDirectory::Copy(locSalvo, NSNPSVD);

			String arq = System::Ioutils::TPath::Combine(NSNPSVD, L"NSCA.nps");
			String Estilo = System::Ioutils::TPath::Combine(NSNPSVD, "NSST.stl");
			frmCodigo->mmCodigo->Lines->SaveToFile(arq);
			frmCodigo->mmEstilo->Lines->SaveToFile(Estilo);

			arq = System::Ioutils::TPath::Combine(locSalvo, L"NSCA.nps");
			Estilo = System::Ioutils::TPath::Combine(locSalvo, "NSST.stl");
			ProjSecun = new TFileStream(Estilo, TFileMode::fmOpen);
			ProjAtual = new TFileStream(arq, TFileMode::fmOpen);


		}
		else {
			throw Exception (L"ERRO 000020: Falha ao localizar o diretório Ninterpres.\nA cópia de segurança da apresentação não pôde ser salva.");
		}
	}
}
//---------------------------------------------------------------------------
