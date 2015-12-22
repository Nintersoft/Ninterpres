//---------------------------------------------------------------------------

#include <fmx.h>
#include <IOUtils.hpp>
#pragma hdrstop

#include "Apresentador.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmApresentacao *frmApresentacao;
//---------------------------------------------------------------------------
const float RealTamFonte = 1.3125;

int Transp = 0, CorBordaTransp, num = 1, Transps, Vis = 0, CorFundoTransp, Visualiza = 3;
bool TranspData, TranspProp, CorBordaDif;
TFileStream* ProjAtual;
TFileStream* ProjSecun;
//---------------------------------------------------------------------------
__fastcall TfrmApresentacao::TfrmApresentacao(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmApresentacao::FormShow(TObject *Sender)
{

	CorBordaTransp = vsTransp->Stroke->Color;
	CorFundoTransp = vsTransp->Fill->Color;

	if (vsTransp->Height < brTransp->Height) {
		float dif = brTransp->Height - vsTransp->Height;
		vsTransp->Position->Y = dif/2;
	}
	else if (vsTransp->Height == brTransp->Height) {
		vsTransp->Position->Y = 0;
	}
	if (brTransp->Width > vsTransp->Width) {
		float dif = brTransp->Width - vsTransp->Width;
		vsTransp->Position->X = dif/2;
	}
	else if (vsTransp->Width == brTransp->Width) {
		vsTransp->Position->X = 0;
	}

	if (TFile::Exists("..\\NSCA.nps")) {
		mmCodigo->BeginUpdate();
		mmCodigo->Lines->LoadFromFile("..\\NSCA.nps");
		mmCodigo->EndUpdate();
		ProjAtual = new TFileStream("..\\NSCA.nps", TFileMode::fmOpen);
	}
/*	else if (TFile::Exists("NSCA.nps")) {
		mmCodigo->Lines->LoadFromFile("NSCA.nps");
		ProjAtual = new TFileStream("NSCA.nps", TFileMode::fmOpen);
	}*/
	else {
		throw Exception ("ERRO 000020: O arquivo de apresenta��o n�o p�de ser lido.\nPor favor, certifique-se de que ele se encontra na pasta principal.\nPara maiores informa��es, visite nossa DocWiki.");
	}

	if (TFile::Exists("..\\NSST.stl")) {
		mmEstilo->BeginUpdate();
		mmEstilo->Lines->LoadFromFile("..\\NSST.stl");
		mmEstilo->EndUpdate();
		ProjSecun = new TFileStream("..\\NSST.stl", TFileMode::fmOpen);
	}
/*	else if (TFile::Exists("NSST.stl")) {
		mmCodigo->Lines->LoadFromFile("NSST.stl");
		ProjSecun = new TFileStream("NSST.stl", TFileMode::fmOpen);
	}*/
	else {
		throw Exception ("ERRO 000021: O arquivo de estilos n�o p�de ser lido.\nPor favor, certifique-se de que ele se encontra na pasta principal.\nPara maiores informa��es, visite nossa DocWiki.");
	}

	int i = 0, tam = mmCodigo->Lines->Count;

	do{
		if (mmCodigo->Lines->Strings[i] == "$TRANSP"+IntToStr(num)) {
			num++;
		}
		i++;
	}while (i < tam);

	int LOCLIN = LocDet("TAM_FONTE");
	float TamConv = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);
	lblTranspTexto->TextSettings->Font->Size = TamConv;
	tamFonteBasica = TamConv;

	Transps = num - 1;

	CarregarTransp(Transp);
	Padronizar();

}
//---------------------------------------------------------------------------
void __fastcall TfrmApresentacao::FormResize(TObject *Sender)
{
	if (vsTransp->Height < brTransp->Height) {
		float dif = brTransp->Height - vsTransp->Height;
		vsTransp->Position->Y = dif/2;
	}
	else if (vsTransp->Height == brTransp->Height) {
		vsTransp->Position->Y = 0;
	}
	if (brTransp->Width > vsTransp->Width) {
		float dif = brTransp->Width - vsTransp->Width;
		vsTransp->Position->X = dif/2;
	}
	else if (vsTransp->Width == brTransp->Width) {
		vsTransp->Position->X = 0;
	}
}
//---------------------------------------------------------------------------
void TfrmApresentacao::CarregarTransp (int indice)
{

	int loc, pos = 0,tam = mmCodigo->Lines->Count;

	if (indice == 0) {
		for (int i = 0; i < tam; i++) {
			if (mmCodigo->Lines->Strings[i] == "$CAPA") {
				loc = i + 1;
				i = tam;
			}
			if (i == tam - 2 && mmCodigo->Lines->Strings[i] != "$CAPA") {
				throw Exception ("ERRO 000001: A capa n�o foi encontrada no c�digo de compila��o!\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
			}
		}
		do{
			RearranjoTransp(indice);
			while (comentario(mmCodigo->Lines->Strings[loc])){
			loc++;
			}
			if (pos == 0 && mmCodigo->Lines->Strings[loc] != "*.*") {
				try {
					imgTransp->Bitmap->LoadFromFile(mmCodigo->Lines->Strings[loc]);
				} catch (...) {
					throw Exception ("ERRO 000003: O arquivo de imagem n�o foi salvo corretamente.\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
				}
				imgTransp->Visible = true;
				loc++;
				pos++;
			}
			else if (pos == 0 && mmCodigo->Lines->Strings[loc] == "*.*") {
				loc++;
				pos++;
				imgTransp->Visible = false;
			}
			else if (pos == 1 && mmCodigo->Lines->Strings[loc] != "*.*") {
				lblImgLeg->Text = mmCodigo->Lines->Strings[loc];
				loc++;
				pos++;
			}
			else if (pos == 1 && mmCodigo->Lines->Strings[loc] == "*.*") {
				lblImgLeg->Text = "";
				loc++;
				pos++;
			}
		} while (mmCodigo->Lines->Strings[loc] != "!(FDT)");

		int pos = 0;

		do {
			if (pos == 0 && mmCodigo->Lines->Strings[0] != "Apresenta��o sem t�tulo") {
				lblTitulo->Text = mmCodigo->Lines->Strings[0];
				pos++;
			}
			else if (pos == 0) {
				lblTitulo->Text =  "";
				pos++;
			}
			else if (pos == 1 && mmCodigo->Lines->Strings[1] != "Nintersoft") {
				lblTranspTexto->Text = mmCodigo->Lines->Strings[1];
				pos++;
			}
			else if (pos == 1) {
				lblTranspTexto->Text = "";
				pos++;
			}
		} while (pos < 2);

	}
	else {

		bool primVar = true;

		for (int i = 0; i < tam; i++) {
			if (mmCodigo->Lines->Strings[i] == "$TRANSP" + IntToStr (indice)) {
				loc = i + 1;
				i = tam;
			}
			if (i == tam - 2 && mmCodigo->Lines->Strings[i] != "$TRANSP" + IntToStr (indice)) {
				throw Exception ("ERRO 000001: A transpar�ncia selecionada n�o foi encontrada no c�digo de compila��o!\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
			}
		}
		do{
			while (comentario(mmCodigo->Lines->Strings[loc])){
			loc++;
			}
			if (pos == 0 && StrToInt(mmCodigo->Lines->Strings[loc]) > 0 && StrToInt(mmCodigo->Lines->Strings[loc]) < 8 ) {
				RearranjoTransp(StrToInt(mmCodigo->Lines->Strings[loc]));
				loc++;
				pos++;
			}
			else if (pos == 0) {
				throw Exception ("Erro na configura��o do tipo de transpar�ncia!");
			}
			else if (pos == 1 && mmCodigo->Lines->Strings[loc] != "*.*") {
				lblTitulo->Text = mmCodigo->Lines->Strings[loc];
				loc++;
				pos++;
			}
			else if (pos == 1 && mmCodigo->Lines->Strings[loc] == "*.*") {
				lblTitulo->Text = "";
				loc++;
				pos++;
			}
			else if (pos == 2 && mmCodigo->Lines->Strings[loc] != "*.*") {
				try {
					imgTransp->Bitmap->LoadFromFile(mmCodigo->Lines->Strings[loc]);
				} catch (...) {
					throw Exception ("ERRO 000003: O arquivo de imagem n�o foi salvo corretamente.\nVerifique este erro clicando na aba Visualizar e depois no bot�o 'C�digo'.\nPara maiores informa��es � respeito deste erro, por favor visite nossa docwiki.");
				}
				imgTransp->Visible = true;
				loc++;
				pos++;
			}
			else if (pos == 2 && mmCodigo->Lines->Strings[loc] == "*.*") {
				imgTransp->Visible = false;
				loc++;
				pos++;
			}
			else if (pos == 3 && mmCodigo->Lines->Strings[loc] != "*.*") {
				lblImgLeg->Text = mmCodigo->Lines->Strings[loc];
				loc++;
				pos++;
			}
			else if (pos == 3 && mmCodigo->Lines->Strings[loc] == "*.*") {
				lblImgLeg->Text = "";
				loc++;
				pos++;
			}
			else if (pos == 4 && mmCodigo->Lines->Strings[loc] != "*.*") {

				if (primVar) {
					mmTranspCont->Lines->Clear();
					mmTranspCont->BeginUpdate();
					primVar = false;
				}

				do {

					while (comentario(mmCodigo->Lines->Strings[loc])){
					loc++;
					}

					mmTranspCont->Lines->Add(mmCodigo->Lines->Strings[loc]);
					loc++;

					while (comentario(mmCodigo->Lines->Strings[loc])){
					loc++;
					}

				}while (mmCodigo->Lines->Strings[loc] != "!(FDT)");

				mmTranspCont->EndUpdate();
				lblTranspTexto->Text = mmTranspCont->Text;
				pos++;

			}
			else if (pos == 4 && mmCodigo->Lines->Strings[loc] == "*.*") {
				lblTranspTexto->Text = "";
				mmTranspCont->Lines->Clear();
				loc++;
				pos++;
			}
		} while (mmCodigo->Lines->Strings[loc] != "!(FDT)");
	}

}
//---------------------------------------------------------------------------
bool TfrmApresentacao::comentario (String linha)
{
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
void TfrmApresentacao::RearranjoTransp (int estilo){

	float AltTransp = vsTransp->Height, LargTransp = vsTransp->Width;
	float ValorHorzM = 0.00585651 * LargTransp; //Porcentagem correspondente � 8 em 1366
	float ValorHorz = 0.00781250 * LargTransp;  //Porcentagem correspondente � 8 em 1024
	float ValorVert = 0.01041667 * AltTransp;   //Porcentagem correspondente � 8 em 768

	AjusteVisual();

	if (Vis == 0) {
		if (Transp == 0) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);
			vsTransp->Fill->Color = cor;

			if (CorBordaDif) {
				vsTransp->Stroke->Color = cor;
			}
			else {
				vsTransp->Stroke->Color = CorBordaTransp;
			}

			lblTitulo->Position->Y = AltTransp/2;
			if (Visualiza == 0 | Visualiza == 1 ) lblTitulo->Position->X = (3 * ValorHorzM);
			else lblTitulo->Position->X = (3 * ValorHorz);
			if (Visualiza == 0 | Visualiza == 1 ) lblTitulo->Width = (vsTransp->Width - (3 * ValorHorzM));
			else lblTitulo->Width = (vsTransp->Width - (3 * ValorHorz));
			lblTitulo->TextSettings->HorzAlign = 0x1;
			lblTitulo->Height = tamFonteTitulo;
			lblTitulo->Font->Size = tamFonteTitulo;

			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Width = LargTransp - (4 * ValorHorzM);
			else lblTranspTexto->Width = LargTransp - (4 * ValorHorz);
			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Position->X = ValorHorzM * 3;
			else lblTranspTexto->Position->X = ValorHorz * 3;
			lblTranspTexto->Position->Y = AltTransp/2 + ValorVert + lblTitulo->Height;
			lblTranspTexto->Height = tamFonteBasica * RealTamFonte * 2;
			lblTranspTexto->TextSettings->VertAlign = 0x1;
			lblTranspTexto->TextSettings->HorzAlign = 0x1;

			imgTransp->Position->X = 0;
			imgTransp->Position->Y = 0;
			imgTransp->Width = LargTransp;
			imgTransp->Height = AltTransp;
			imgTransp->WrapMode = TImageWrapMode::iwStretch;

			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Width = LargTransp - (ValorHorzM * 4);
			else lblImgLeg->Width = LargTransp - (ValorHorz * 4);
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Position->X = ValorHorzM * 3;
			else lblImgLeg->Position->X = ValorHorz * 3;
			lblImgLeg->TextSettings->HorzAlign = 0x2;
			lblImgLeg->Position->Y = AltTransp - ValorVert * 3 - lblImgLeg->Height;
			lblImgLeg->Visible = true;

		}
		else if (estilo == 1) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				vsTransp->Fill->Color = CorFundoTransp;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			lblTitulo->Width = LargTransp;
			if (Visualiza == 0 | Visualiza == 1 ) lblTitulo->Position->Y = (ValorHorzM * 3);
			else lblTitulo->Position->Y = (ValorHorz * 3);
			lblTitulo->Position->X = 0;
			lblTitulo->Width = vsTransp->Width;
			lblTitulo->TextSettings->HorzAlign = 0x0;
			lblTitulo->Height = tamFonteTitulo;
			lblTitulo->Font->Size = tamFonteTitulo;

			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Width = LargTransp/2 - (ValorHorzM * 4);
			else imgTransp->Width = LargTransp/2 - (ValorHorz * 4);
			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Position->X = LargTransp / 2 + ValorHorzM;
			else imgTransp->Position->X = LargTransp / 2 + ValorHorz;
			imgTransp->Height = AltTransp - (ValorVert * 14) - lblImgLeg->Height - (ValorVert * 4);
			imgTransp->Position->Y = (ValorVert * 13) + (ValorVert/4);
			imgTransp->WrapMode = TImageWrapMode::iwFit;

			lblImgLeg->TextSettings->HorzAlign = 0x0;
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Width = LargTransp/2 - ValorHorzM * 4;
			else lblImgLeg->Width = LargTransp/2 - ValorHorz * 4;
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Position->X = LargTransp / 2 + ValorHorzM * 2;
			else lblImgLeg->Position->X = LargTransp / 2 + ValorHorz * 2;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + ValorVert;
			lblImgLeg->Visible = true;

			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Width = LargTransp/2 - (ValorHorzM * 4);
			else lblTranspTexto->Width = LargTransp/2 - (ValorHorz * 4);
			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Position->X = ValorHorzM * 3;
			else lblTranspTexto->Position->X = ValorHorz * 3;
			lblTranspTexto->Height = imgTransp->Height;
			lblTranspTexto->Position->Y = (ValorVert * 13) + (ValorVert/4);
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x2;

		}
		else if (estilo == 2) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				vsTransp->Fill->Color = CorFundoTransp;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			lblTitulo->Width = LargTransp;
			lblTitulo->Position->Y = ValorVert * 3;
			lblTitulo->Width = vsTransp->Width;
			lblTitulo->Position->X = 0;
			lblTitulo->TextSettings->HorzAlign = 0x0;
			lblTitulo->Height = tamFonteTitulo;
			lblTitulo->Font->Size = tamFonteTitulo;

			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Width = LargTransp/2 - ValorHorzM * 4;
			else imgTransp->Width = LargTransp/2 - ValorHorz * 4;
			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Position->X = ValorHorzM * 3;
			else imgTransp->Position->X = ValorHorz * 3;
			imgTransp->Height = AltTransp - (ValorVert * 14) - lblImgLeg->Height - (ValorVert * 4);
			imgTransp->Position->Y = (ValorVert * 13) + (ValorVert/4);
			imgTransp->WrapMode = TImageWrapMode::iwFit;

			lblImgLeg->TextSettings->HorzAlign = 0x0;
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Width = LargTransp/2 - (ValorHorzM * 4);
			else lblImgLeg->Width = LargTransp/2 - (ValorHorz * 4);
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Position->X = ValorHorz * 3;
			else lblImgLeg->Position->X = ValorHorz * 3;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + ValorVert;
			lblImgLeg->Visible = true;

			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Width = LargTransp/2 - (ValorHorzM * 4);
			else lblTranspTexto->Width = LargTransp/2 - (ValorHorz * 4);
			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Position->X = LargTransp / 2 + ValorHorzM;
			else lblTranspTexto->Position->X = LargTransp / 2 + ValorHorzM;\
			lblTranspTexto->Height = imgTransp->Height;
			lblTranspTexto->Position->Y = (ValorVert * 13) + (ValorVert/4);
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x1;

		}
		else if (estilo == 3) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				vsTransp->Fill->Color = CorFundoTransp;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			lblTitulo->Width = LargTransp;
			lblTitulo->Position->Y = AltTransp - (ValorVert * 11);
			lblTitulo->Position->X = 0;
			lblTitulo->Width = vsTransp->Width;
			lblTitulo->TextSettings->HorzAlign = 0x0;
			lblTitulo->Height = tamFonteTitulo;
			lblTitulo->Font->Size = tamFonteTitulo;

			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Width = LargTransp/2 - (3 * ValorHorzM);
			else imgTransp->Width = LargTransp/2 - (3 * ValorHorz);
			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Position->X = LargTransp / 2 + ValorHorzM;
			else imgTransp->Position->X = LargTransp / 2 + ValorHorz;
			imgTransp->Height = AltTransp - (ValorVert * 14) - lblImgLeg->Height - 32;
			imgTransp->Position->Y = ValorVert * 3;
			imgTransp->WrapMode = TImageWrapMode::iwFit;

			lblImgLeg->TextSettings->HorzAlign = 0x0;
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Width = LargTransp/2 - (ValorHorzM * 4);
			else lblImgLeg->Width = LargTransp/2 - (ValorHorz * 4);
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Position->X = LargTransp / 2 + ValorHorzM;
			else lblImgLeg->Position->X = LargTransp / 2 + ValorHorz;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + ValorVert;
			lblImgLeg->Visible = true;

			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Width = LargTransp/2 - (ValorHorzM * 4);
			else lblTranspTexto->Width = LargTransp/2 - (ValorHorz * 4);
			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Position->X = ValorHorzM * 3;
			else lblTranspTexto->Position->X = ValorHorz * 3;
			lblTranspTexto->Height = imgTransp->Height;
			lblTranspTexto->Position->Y = ValorVert * 3;
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x2;

		}
		else if (estilo == 4) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				vsTransp->Fill->Color = CorFundoTransp;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			lblTitulo->Width = LargTransp;
			lblTitulo->Position->Y = AltTransp - (ValorVert * 11);
			lblTitulo->Position->X = 0;
			lblTitulo->Width = vsTransp->Width;
			lblTitulo->TextSettings->HorzAlign = 0x0;
			lblTitulo->Height = tamFonteTitulo;
			lblTitulo->Font->Size = tamFonteTitulo;

			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Width = LargTransp/2 - (4 * ValorHorzM);
			else imgTransp->Width = LargTransp/2 - (4 * ValorHorz);
			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Position->X = ValorHorzM * 3;
			else imgTransp->Position->X = ValorHorz * 3;
			imgTransp->Height = AltTransp - (ValorVert * 14) - lblImgLeg->Height - (ValorVert * 4);
			imgTransp->Position->Y = ValorVert * 3;
			imgTransp->WrapMode = TImageWrapMode::iwFit;

			lblImgLeg->TextSettings->HorzAlign = 0x0;
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Width = LargTransp/2 - (ValorHorzM * 4);
			else lblImgLeg->Width = LargTransp/2 - (ValorHorz * 4);
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Position->X = ValorHorzM * 3;
			else lblImgLeg->Position->X = ValorHorz * 3;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + ValorVert;
			lblImgLeg->Visible = true;

			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Width = LargTransp/2 - (ValorHorzM * 4);
			else lblTranspTexto->Width = LargTransp/2 - (ValorHorz * 4);
			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Position->X = LargTransp / 2 + ValorHorzM;
			else lblTranspTexto->Position->X = LargTransp / 2 + ValorHorz;
			lblTranspTexto->Height = imgTransp->Height;
			lblTranspTexto->Position->Y = (ValorVert * 3);
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x1;

		}
		else if (estilo == 5) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				vsTransp->Fill->Color = CorFundoTransp;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			lblTitulo->Width = LargTransp;
			lblTitulo->Position->Y = (ValorVert * 3);
			lblTitulo->Position->X = 0;
			lblTitulo->Width = vsTransp->Width;
			lblTitulo->TextSettings->HorzAlign = 0x0;
			lblTitulo->Height = tamFonteTitulo;
			lblTitulo->Font->Size = tamFonteTitulo;

			imgTransp->Width = 0;
			imgTransp->Position->X = 0;
			imgTransp->Height = 0;
			imgTransp->Position->Y = 0;

			lblImgLeg->Width = 0;
			lblImgLeg->Position->X = 0;
			lblImgLeg->Position->Y = 0;
			lblImgLeg->Visible = false;

			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Width = LargTransp - (ValorHorzM * 6);
			else lblTranspTexto->Width = LargTransp - (ValorHorz * 6);
			if (Visualiza == 0 | Visualiza == 1 ) lblTranspTexto->Position->X = (ValorHorzM * 3);
			else lblTranspTexto->Position->X = (ValorHorz * 3);
			lblTranspTexto->Height = AltTransp - (ValorVert * 17);
			lblTranspTexto->Position->Y = (ValorVert * 13) + (ValorVert/4);
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x0;

		}
		else if (estilo == 6) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				vsTransp->Fill->Color = CorFundoTransp;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			lblTitulo->Width = LargTransp;
			lblTitulo->Position->Y = ValorVert * 3;
			lblTitulo->Position->X = 0;
			lblTitulo->Width = vsTransp->Width;
			lblTitulo->TextSettings->HorzAlign = 0x0;
			lblTitulo->Height = tamFonteTitulo;
			lblTitulo->Font->Size = tamFonteTitulo;

			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Width = LargTransp - (ValorHorzM * 6);
			else imgTransp->Width = LargTransp - (ValorHorz * 6);
			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Position->X = ValorHorzM * 3;
			else imgTransp->Position->X = ValorHorz * 3;
			imgTransp->Height = AltTransp - (ValorVert * 14) - lblImgLeg->Height - (ValorVert * 4);
			imgTransp->Position->Y = (ValorVert * 13) + (ValorVert/4);
			imgTransp->WrapMode = TImageWrapMode::iwFit;

			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Width = LargTransp - (ValorHorzM * 6);
			else lblImgLeg->Width = LargTransp - (ValorHorz * 6);
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Position->X = ValorHorzM * 3;
			else lblImgLeg->Position->X = ValorHorz * 3;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + ValorVert;
			lblImgLeg->Visible = true;
			lblImgLeg->TextSettings->HorzAlign = 0x0;

			lblTranspTexto->Width = 0;
			lblTranspTexto->Position->X = 0;
			lblTranspTexto->Height = 0;
			lblTranspTexto->Position->Y = 0;
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x0;

		}
		else if (estilo == 7) {

			int LOCLIN = LocDet("COR_TRANSP");
			int cor = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);

			LOCLIN = LocDet("APL_TODOS");
			if (mmEstilo->Lines->Strings[LOCLIN] == "NSTT") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmEstilo->Lines->Strings[LOCLIN] == "!NSTT"){
				vsTransp->Fill->Color = CorFundoTransp;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = CorFundoTransp;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else {
				throw Exception ("ERRO 00009: H� um problema no c�digo de compila��o.\nPor favor, verifique a linha 5 do arquivo .nps.\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
			}

			lblTitulo->Width = LargTransp;
			lblTitulo->Position->Y = AltTransp - (ValorVert * 11);
			lblTitulo->Position->X = 0;
			lblTitulo->Width = vsTransp->Width;
			lblTitulo->TextSettings->HorzAlign = 0x0;
			lblTitulo->Height = tamFonteTitulo;
			lblTitulo->Font->Size = tamFonteTitulo;

			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Width = LargTransp - (ValorHorzM * 6);
			else imgTransp->Width = LargTransp - (ValorHorz * 6);
			if (Visualiza == 0 | Visualiza == 1 ) imgTransp->Position->X = ValorHorzM * 3;
			else imgTransp->Position->X = ValorHorz * 3;
			imgTransp->Height = AltTransp - (ValorVert * 14) - lblImgLeg->Height - (ValorVert * 4);
			imgTransp->Position->Y = (ValorVert * 3);
			imgTransp->WrapMode = TImageWrapMode::iwFit;

			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Width = LargTransp - (6 * ValorHorzM);
			else lblImgLeg->Width = LargTransp - (6 * ValorHorz);
			if (Visualiza == 0 | Visualiza == 1 ) lblImgLeg->Position->X = ValorHorzM * 3;
			else lblImgLeg->Position->X = ValorHorz * 3;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + ValorVert;
			lblImgLeg->Visible = true;
			lblImgLeg->TextSettings->HorzAlign = 0x0;

			lblTranspTexto->Width = 0;
			lblTranspTexto->Position->X = 0;
			lblTranspTexto->Height = 0;
			lblTranspTexto->Position->Y = 0;
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x0;

		}

	}
}
//---------------------------------------------------------------------------
void TfrmApresentacao::Padronizar()
{

	int LOCLIN = LocDet("COR_TRANSP");
	vsTransp->Fill->Color = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);

	LOCLIN = LocDet("APL_BORDA");
	if (mmEstilo->Lines->Strings[LOCLIN] == "NSBD") {
		LOCLIN = LocDet("COR_TRANSP");
		vsTransp->Stroke->Color = AdquireTam(mmEstilo->Lines->Strings[LOCLIN]);
		CorBordaDif = true;
	}
	else {
		vsTransp->Stroke->Color = CorBordaTransp;
		CorBordaDif = false;
	}

	LOCLIN = LocDet("APL_FONTE");
	int LOCLIN2 = LocDet("APL_TODOS"), LOCAUX = LocDet("COR_FONTE");

	if (mmEstilo->Lines->Strings[LOCLIN2] == "NSTT" && mmEstilo->Lines->Strings[LOCLIN] == "NSFT") {
		lblTitulo->TextSettings->FontColor = AdquireTam(mmEstilo->Lines->Strings[LOCAUX]);
		lblTranspTexto->TextSettings->FontColor = AdquireTam(mmEstilo->Lines->Strings[LOCAUX]);
		lblImgLeg->TextSettings->FontColor = AdquireTam(mmEstilo->Lines->Strings[LOCAUX]);
		CorBordaDif = true;
	}
	else {
		lblTitulo->TextSettings->FontColor = CorBordaTransp;
		lblTranspTexto->TextSettings->FontColor = CorBordaTransp;
		lblImgLeg->TextSettings->FontColor = CorBordaTransp;
		CorBordaDif = false;
	}

	LOCLIN = LocDet("MSTR_TRANSP");
	if (mmEstilo->Lines->Strings[LOCLIN] == "NSFN") {
		TranspProp = true;
	}
	else if (mmEstilo->Lines->Strings[LOCLIN] == "!NSFN") {
		TranspProp = false;
	}
	else {
		throw Exception (L"ERRO 000010: Falha nas configura��es especiais (�ltima transpar�ncia).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
	}

	LOCLIN = LocDet("MSTR_LOGO");
	if (mmEstilo->Lines->Strings[LOCLIN] == "NSLG") {
		imgLogoNS->Visible = true;
	}
	else if (mmEstilo->Lines->Strings[LOCLIN] == "!NSLG") {
		imgLogoNS->Visible = false;
	}
	else {
		throw Exception (L"ERRO 000011: Falha nas configura��es especiais (Logo NS).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
	}

	LOCLIN = LocDet("MSTR_DATA");
	if (mmEstilo->Lines->Strings[LOCLIN] == "NSDT") {
		TranspData = true;
	}
	else if (mmEstilo->Lines->Strings[LOCLIN] == "!NSDT") {
		TranspData = false;
	}
	else {
		throw Exception (L"ERRO 000012: Falha nas configura��es especiais (Data).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
	}

	frmApresentacao->Caption = mmCodigo->Lines->Strings[0] + " - Ninterpres";

}
//---------------------------------------------------------------------------
void __fastcall TfrmApresentacao::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
	if ((Key == VK_RIGHT | Key == VK_NEXT) && Transp < Transps) {
		Transp++;
		CarregarTransp(Transp);
	}
	else if ((Key == VK_RIGHT | Key == VK_NEXT) && Transp == Transps) {
		Transp = 0;
		CarregarTransp(Transp);
	}
	else if ((Key == VK_LEFT | Key == VK_PRIOR) && Transp >= 1) {
		Transp--;
		CarregarTransp(Transp);
	}
	else if (Key == VK_HOME) {
		Transp = 0;
		CarregarTransp(Transp);
	}
	else if (Key == VK_END) {
		Transp = Transps;
		CarregarTransp(Transp);
	}
	else if (Key == VK_ESCAPE) {
		Application->Terminate();
	}
}
//---------------------------------------------------------------------------
int TfrmApresentacao::LocDet(String Valor)
{

	int tamTot = mmEstilo->Lines->Count - 1;
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
				if (mmEstilo->Lines->Strings[i] == Categoria) {
					comeco = i;
					inicio = false;
				}
			}
			else {
				if (mmEstilo->Lines->Strings[i] == "!(FDD)") {
					fim = i;
					break;
				}
			}
		}

		for (int i = comeco; i < fim; i++) {

			String temp = "", dados = mmEstilo->Lines->Strings[i];

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
			mmEstilo->Lines->Insert(inicio + 1, "TAM:");
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
				if (mmEstilo->Lines->Strings[i] == Categoria) {
					comeco = i;
					inicio = false;
				}
			}
			else {
				if (mmEstilo->Lines->Strings[i] == "!(FDD)") {
					fim = i;
					break;
				}
			}
		}

		for (int i = comeco; i < fim; i++) {

			String temp = "", dados = mmEstilo->Lines->Strings[i];

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
			if (Categoria == "$OPO") mmEstilo->Lines->Insert(inicio + 1, Procura);
			else if (Categoria == "$TRANSP") mmEstilo->Lines->Insert(inicio + 1, "!"+Procura);
		}


		return loc;

	}
	else {
		throw Exception (L"O valor declarado est� incorreto!");
	}

}
//---------------------------------------------------------------------------
int TfrmApresentacao::AdquireTam(String Texto)
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
void __fastcall TfrmApresentacao::FormClose(TObject *Sender, TCloseAction &Action)

{
	delete ProjAtual;
	delete ProjSecun;
}
//---------------------------------------------------------------------------
void TfrmApresentacao::AjusteVisual() {
	if (Visualiza == 0) {

		int altmax = (int)brTransp->Height - 40;
		vsTransp->Height = altmax;

		int largmax = (int)((altmax/9)*16);
		vsTransp->Width = largmax;

		float altmaxconv = altmax;

		tamFonteBasica = ((altmaxconv/768) * tamFonteBasica);
		tamFonteTitulo = ((altmaxconv * 64) / 768);

		vsTransp->Position->X = (brTransp->Width - vsTransp->Width)/2;
		vsTransp->Position->Y = (brTransp->Height - vsTransp->Height)/2;

	}
	else if (Visualiza == 1) {

		float trPos[2], brTam[2], trTam[2];

		vsTransp->Width = 1366;
		vsTransp->Height = 768;

		tamFonteTitulo = 64;

		brTam[0] = brTransp->Width;
		brTam[1] = brTransp->Height;
		trTam[0] = vsTransp->Width;
		trTam[1] = vsTransp->Height;

		if (brTam[0] >= trTam[0]) {
			trPos[0] = (brTam[0] - trTam[0])/2;
			vsTransp->Position->X = trPos[0];
		}
		else {
			vsTransp->Position->X = 20;
		}

		if (brTam[1] >= trTam[1]) {
			trPos[1] = (brTam[1] - trTam[1])/2;
			vsTransp->Position->Y = trPos[1];
		}
		else {
			vsTransp->Position->Y = 20;
		}

	}
	else if (Visualiza == 2) {

		int altmax = (int)brTransp->Height - 40;
		vsTransp->Height = altmax;

		int largmax = (int)((altmax/3)*4);
		vsTransp->Width = largmax;

		float altmaxconv = altmax;

		vsTransp->Position->X = (brTransp->Width - vsTransp->Width)/2;
		vsTransp->Position->Y = (brTransp->Height - vsTransp->Height)/2;

		tamFonteBasica = ((altmaxconv/768) * tamFonteBasica);
		tamFonteTitulo = ((altmaxconv * 64) / 768);


	}
	else {

		float trPos[2], brTam[2], trTam[2];

		vsTransp->Width = 1024;
		vsTransp->Height = 768;

		tamFonteTitulo = 64;

		brTam[0] = brTransp->Width;
		brTam[1] = brTransp->Height;
		trTam[0] = vsTransp->Width;
		trTam[1] = vsTransp->Height;

		if (brTam[0] >= trTam[0]) {
			trPos[0] = (brTam[0] - trTam[0])/2;
			vsTransp->Position->X = trPos[0];
		}
		else {
			vsTransp->Position->X = 20;
		}

		if (brTam[1] >= trTam[1]) {
			trPos[1] = (brTam[1] - trTam[1])/2;
			vsTransp->Position->Y = trPos[1];
		}
		else {
			vsTransp->Position->Y = 20;
		}

	}
}
//---------------------------------------------------------------------------
