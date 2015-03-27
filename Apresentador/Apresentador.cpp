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
int Transp = 0, CorBordaTransp, num = 1, Transps, Vis = 0, CorFundoTransp;
bool TranspData, TranspProp, CorBordaDif;
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
		mmCodigo->Lines->LoadFromFile("..\\NSCA.nps");
	}
	else {
		throw Exception ("ERRO 000020: O arquivo de apresenta��o n�o p�de ser lido.\nPor favor, certifique-se de que ele se encontra na pasta principal.\nPara maiores informa��es, visite nossa DocWiki.");
	}

	int i = 0, tam = mmCodigo->Lines->Count;

	do{
		if (mmCodigo->Lines->Strings[i] == "$TRANSP"+IntToStr(num)) {
			num++;
		}
		i++;
	}while (i < tam);

	lblTranspTexto->TextSettings->Font->Size = StrToFloat(mmCodigo->Lines->Strings[7]);

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

	if (Vis == 0) {
		if (Transp == 0) {

			int cor = StrToInt(mmCodigo->Lines->Strings[2]);
			vsTransp->Fill->Color = cor;

			if (CorBordaDif) {
				vsTransp->Stroke->Color = cor;
			}
			else {
				vsTransp->Stroke->Color = CorBordaTransp;
			}

			lblTitulo->Position->Y = AltTransp/2;
			lblTitulo->Position->X = 24;
			lblTitulo->TextSettings->HorzAlign = 0x1;

			lblTranspTexto->Width = LargTransp - 32;
			lblTranspTexto->Position->X = 24;
			lblTranspTexto->Position->Y = AltTransp/2 + 8 + lblTitulo->Height;
			lblTranspTexto->Height = 42;
			lblTranspTexto->TextSettings->VertAlign = 0x1;
			lblTranspTexto->TextSettings->HorzAlign = 0x1;

			imgTransp->Position->X = 0;
			imgTransp->Position->Y = 0;
			imgTransp->Width = LargTransp;
			imgTransp->Height = AltTransp;

			lblImgLeg->Width = LargTransp - 32;
			lblImgLeg->Position->X = 24;
			lblImgLeg->TextSettings->HorzAlign = 0x2;
			lblImgLeg->Position->Y = AltTransp - 24 - lblImgLeg->Height;
			lblImgLeg->Visible = true;

		}
		else if (estilo == 1) {

			int cor = StrToInt(mmCodigo->Lines->Strings[2]);

			if (mmCodigo->Lines->Strings[4] == "==") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmCodigo->Lines->Strings[4] == "!="){
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
			lblTitulo->Position->Y = 24;
			lblTitulo->Position->X = 0;
			lblTitulo->TextSettings->HorzAlign = 0x0;

			imgTransp->Width = LargTransp/2 - 32;
			imgTransp->Position->X = LargTransp / 2 + 8;
			imgTransp->Height = AltTransp - 112 - lblImgLeg->Height - 32;
			imgTransp->Position->Y = 106;

			lblImgLeg->TextSettings->HorzAlign = 0x0;
			lblImgLeg->Width = LargTransp/2 - 32;
			lblImgLeg->Position->X = LargTransp / 2 + 16;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + 8;
			lblImgLeg->Visible = true;

			lblTranspTexto->Width = LargTransp/2 - 32;
			lblTranspTexto->Position->X = 24;
			lblTranspTexto->Height = imgTransp->Height;
			lblTranspTexto->Position->Y = 106;
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x2;

		}
		else if (estilo == 2) {

			int cor = StrToInt(mmCodigo->Lines->Strings[2]);

			if (mmCodigo->Lines->Strings[4] == "==") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmCodigo->Lines->Strings[4] == "!="){
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
			lblTitulo->Position->Y = 24;
			lblTitulo->Position->X = 0;
			lblTitulo->TextSettings->HorzAlign = 0x0;

			imgTransp->Width = LargTransp/2 - 32;
			imgTransp->Position->X = 24;
			imgTransp->Height = AltTransp - 112 - lblImgLeg->Height - 32;
			imgTransp->Position->Y = 106;

			lblImgLeg->TextSettings->HorzAlign = 0x0;
			lblImgLeg->Width = LargTransp/2 - 32;
			lblImgLeg->Position->X = 24;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + 8;
			lblImgLeg->Visible = true;

			lblTranspTexto->Width = LargTransp/2 - 32;
			lblTranspTexto->Position->X = LargTransp / 2 + 8;
			lblTranspTexto->Height = imgTransp->Height;
			lblTranspTexto->Position->Y = 106;
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x1;

		}
		else if (estilo == 3) {

			int cor = StrToInt(mmCodigo->Lines->Strings[2]);

			if (mmCodigo->Lines->Strings[4] == "==") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmCodigo->Lines->Strings[4] == "!="){
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
			lblTitulo->Position->Y = AltTransp - 88;
			lblTitulo->Position->X = 0;
			lblTitulo->TextSettings->HorzAlign = 0x0;

			imgTransp->Width = LargTransp/2 - 32;
			imgTransp->Position->X = LargTransp / 2 + 8;
			imgTransp->Height = AltTransp - 112 - lblImgLeg->Height - 32;
			imgTransp->Position->Y = 24;

			lblImgLeg->TextSettings->HorzAlign = 0x0;
			lblImgLeg->Width = LargTransp/2 - 32;
			lblImgLeg->Position->X = LargTransp / 2 + 8;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + 8;
			lblImgLeg->Visible = true;

			lblTranspTexto->Width = LargTransp/2 - 32;
			lblTranspTexto->Position->X = 24;
			lblTranspTexto->Height = imgTransp->Height;
			lblTranspTexto->Position->Y = 24;
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x2;

		}
		else if (estilo == 4) {

			int cor = StrToInt(mmCodigo->Lines->Strings[2]);

			if (mmCodigo->Lines->Strings[4] == "==") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmCodigo->Lines->Strings[4] == "!="){
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
			lblTitulo->Position->Y = AltTransp - 88;
			lblTitulo->Position->X = 0;
			lblTitulo->TextSettings->HorzAlign = 0x0;

			imgTransp->Width = LargTransp/2 - 32;
			imgTransp->Position->X = 24;
			imgTransp->Height = AltTransp - 112 - lblImgLeg->Height - 32;
			imgTransp->Position->Y = 24;

			lblImgLeg->TextSettings->HorzAlign = 0x0;
			lblImgLeg->Width = LargTransp/2 - 32;
			lblImgLeg->Position->X = 24;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + 8;
			lblImgLeg->Visible = true;

			lblTranspTexto->Width = LargTransp/2 - 32;
			lblTranspTexto->Position->X = LargTransp / 2 + 8;
			lblTranspTexto->Height = imgTransp->Height;
			lblTranspTexto->Position->Y = 24;
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x1;

		}
		else if (estilo == 5) {

			int cor = StrToInt(mmCodigo->Lines->Strings[2]);

			if (mmCodigo->Lines->Strings[4] == "==") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmCodigo->Lines->Strings[4] == "!="){
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
			lblTitulo->Position->Y = 24;
			lblTitulo->Position->X = 0;
			lblTitulo->TextSettings->HorzAlign = 0x0;

			imgTransp->Width = 0;
			imgTransp->Position->X = 0;
			imgTransp->Height = 0;
			imgTransp->Position->Y = 0;

			lblImgLeg->Width = 0;
			lblImgLeg->Position->X = 0;
			lblImgLeg->Position->Y = 0;
			lblImgLeg->Visible = false;

			lblTranspTexto->Width = LargTransp - 48;
			lblTranspTexto->Position->X = 24;
			lblTranspTexto->Height = AltTransp - 136;
			lblTranspTexto->Position->Y = 106;
			lblTranspTexto->TextSettings->VertAlign = 0x0;
			lblTranspTexto->TextSettings->HorzAlign = 0x0;

		}
		else if (estilo == 6) {

			int cor = StrToInt(mmCodigo->Lines->Strings[2]);

			if (mmCodigo->Lines->Strings[4] == "==") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmCodigo->Lines->Strings[4] == "!="){
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
			lblTitulo->Position->Y = 24;
			lblTitulo->Position->X = 0;
			lblTitulo->TextSettings->HorzAlign = 0x0;

			imgTransp->Width = LargTransp - 48;
			imgTransp->Position->X = 24;
			imgTransp->Height = AltTransp - 112 - lblImgLeg->Height - 32;
			imgTransp->Position->Y = 106;

			lblImgLeg->Width = LargTransp - 48;
			lblImgLeg->Position->X = 24;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + 8;
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

			int cor = StrToInt(mmCodigo->Lines->Strings[2]);

			if (mmCodigo->Lines->Strings[4] == "==") {
				vsTransp->Fill->Color = cor;
					if (CorBordaDif) {
						vsTransp->Stroke->Color = cor;
					}
					else {
						vsTransp->Stroke->Color = CorBordaTransp;
					}
			}
			else if (mmCodigo->Lines->Strings[4] == "!="){
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
			lblTitulo->Position->Y = AltTransp - 88;
			lblTitulo->Position->X = 0;
			lblTitulo->TextSettings->HorzAlign = 0x0;

			imgTransp->Width = LargTransp - 48;
			imgTransp->Position->X = 24;
			imgTransp->Height = AltTransp - 112 - lblImgLeg->Height - 32;
			imgTransp->Position->Y = 24;

			lblImgLeg->Width = LargTransp - 48;
			lblImgLeg->Position->X = 24;
			lblImgLeg->Position->Y = imgTransp->Position->Y + imgTransp->Height + 8;
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
	int cor = StrToInt(mmCodigo->Lines->Strings[2]), tamk = mmCodigo->Lines->Count;
	vsTransp->Fill->Color = cor;
	if (mmCodigo->Lines->Strings[3] == "==") {
		vsTransp->Stroke->Color = cor;
		CorBordaDif = true;
	}
	else {
		vsTransp->Stroke->Color = CorBordaTransp;
		CorBordaDif = false;
	}

	if (mmCodigo->Lines->Strings[tamk-1] == "NSFN") {
		TranspProp = true;
	}
	else if (mmCodigo->Lines->Strings[tamk-1] == "!NSFN") {
		TranspProp = false;
	}
	else {
		throw Exception ("ERRO 000010: Falha nas configura��es especiais (�ltima transpar�ncia).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
	}

	if (mmCodigo->Lines->Strings[tamk-2] == "NSPR") {
		imgLogoNS->Visible = true;
	}
	else if (mmCodigo->Lines->Strings[tamk-2] == "!NSPR") {
		imgLogoNS->Visible = false;
	}
	else {
		throw Exception ("ERRO 000011: Falha nas configura��es especiais (Logo NS).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
	}

	if (mmCodigo->Lines->Strings[tamk-3] == "NSDT") {
		TranspData = true;
	}
	else if (mmCodigo->Lines->Strings[tamk-3] == "!NSDT") {
		TranspData = false;
	}
	else {
		throw Exception ("ERRO 000012: Falha nas configura��es especiais (Data).\nPara maiores informa��es sobre este erro visite nossa DocWiki.");
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

