//---------------------------------------------------------------------------

#include <fmx.h>
#include <FMX.Platform.Win.hpp>
#include <IOUtils.hpp>
#pragma hdrstop

#include "Sobre.h"
#include "Carregar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.Windows.fmx", _PLAT_MSWINDOWS)
String novo, arq;
int temp = 0;
TfrmSobre *frmSobre;
//---------------------------------------------------------------------------
__fastcall TfrmSobre::TfrmSobre(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::btAtualizarClick(TObject *Sender)
{
	frmSobre->BeginUpdate();
	btAtualizar->Visible = false;
	btSite->Visible = false;
	btFacebook->Visible = false;
	lblEstado->Text = "Verificando atualiza��es...";
	lblEstado->Visible = true;
	Indicador->Visible = true;
	Application->ProcessMessages();
	frmSobre->EndUpdate();
	Sleep(1000);
	Controle->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::btSiteClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "http://www.nintersoft.com/", NULL, NULL, SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::btFacebookClick(TObject *Sender)
{
	ShellExecuteA( NULL, "open", "http://www.facebook.com/Nintersoft", NULL, NULL, SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::btAtualizarMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btAtualizar->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSobre::btSiteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y)
{
	btSite->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSobre::btFacebookMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btFacebook->Fill->Color = -12525360;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSobre::btAtualizarMouseLeave(TObject *Sender)
{
	btAtualizar->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSobre::btAtualizarMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btAtualizar->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSobre::btSiteMouseLeave(TObject *Sender)
{
	btSite->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSobre::btSiteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y)
{
	btSite->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSobre::btFacebookMouseLeave(TObject *Sender)
{
	btFacebook->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSobre::btFacebookMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, float X, float Y)
{
	btFacebook->Fill->Color = -16777011;
}
//---------------------------------------------------------------------------
void TfrmSobre::Principal()
{
	try {
		String LOC = System::Ioutils::TPath::Combine(frmCarregar->NSNPLOCATL, L"NSATL.txt");
		TFileStream* arquivo = new TFileStream(LOC, fmCreate);
		Application->ProcessMessages();
		gerWebArq->Get(L"https://docs.google.com/uc?id=0BxyKD6Pyuhy4ajJPMFVlajZXQkE&export=download", arquivo);
		delete arquivo;
		mmDados->BeginUpdate();
		mmDados->Lines->LoadFromFile(LOC);
		mmDados->EndUpdate();
		TFile::Delete(LOC);
	} catch (...) {
		lblEstado->Text = L"Erro";
		frmSobre->BeginUpdate();
		btAtualizar->Visible = true;
		btSite->Visible = true;
		btFacebook->Visible = true;
		frmSobre->Updating();
		frmSobre->UpdateActions();
		Application->ProcessMessages();
		frmSobre->EndUpdate();
		lblEstado->Visible = false;
		Indicador->Visible = false;
		novo = "Adquirindo ";
		throw Exception (L"Voc� est� conectado � internet?\nHouve um erro de conex�o com o servidor");
	}
	if (Atualizado()) {
		lblEstado->Text = L"J� est� atualizado!";
		novo = "Adquirindo ";
		ShowMessage(L"Seu Ninterpres j� encontra-se atualizado!");
	}
	else {
		AdquirirNomes();
		lblEstado->Text = novo;
		Sleep(5000);
		try {
			String LOC = System::Ioutils::TPath::Combine(frmCarregar->NSNPLOCATL, L"INPS.exe");
			TFileStream* arquivo = new TFileStream(LOC, fmCreate);
			Application->ProcessMessages();
			gerWebArq->Get(arq, arquivo);
			gerWebArq->Free();
			delete arquivo;
			ShowMessage(L"Aten��o: A aplica��o ser� encerrada e o instalador ser� iniciado.");
			ShellExecuteW( NULL, L"open", LOC.c_str(), NULL, NULL, SW_SHOW );
			Application->Terminate();
		} catch (...) {
			frmSobre->BeginUpdate();
			btAtualizar->Visible = true;
			btSite->Visible = true;
			btFacebook->Visible = true;
			frmSobre->Updating();
			frmSobre->UpdateActions();
			Application->ProcessMessages();
			frmSobre->EndUpdate();
			lblEstado->Visible = false;
			Indicador->Visible = false;
			lblEstado->Text = L"Erro";
			throw Exception (L"Voc� est� certo de que est� conectado � internet?\nAlgum erro ocorreu enquanto baixavamos as atualiza��es..");
		}
	}

	frmSobre->BeginUpdate();
	btAtualizar->Visible = true;
	btSite->Visible = true;
	btFacebook->Visible = true;
	frmSobre->Updating();
	frmSobre->UpdateActions();
	frmSobre->EndUpdate();
	Application->ProcessMessages();
	lblEstado->Visible = false;
	Indicador->Visible = false;
}
//---------------------------------------------------------------------------
void TfrmSobre::AdquirirNomes()
{
	String linha = mmDados->Lines->Strings[0];
	int num = 0;
	for (int i = 0; i < linha.Length(); i++) {
		if (num < 1) {
			if (linha.c_str()[i] == '=') {
				num ++;
			}
			else {
				novo = novo + linha.c_str()[i];
			}
		}
		else if (num >= 1 && num < 4) {
			if (linha.c_str()[i] == '=') {
				num++;
				if (num < 4) {
					arq = arq + linha.c_str()[i];
				}
			}
			else {
				arq = arq + linha.c_str()[i];
			}
		}
	}
}
//---------------------------------------------------------------------------
bool TfrmSobre::Atualizado()
{
	String ver, linha = mmDados->Lines->Strings[0];
	int num = 0;
	for (int i = 0; i < linha.Length(); i++) {
		if (num < 4) {
			if (linha.c_str()[i] == '=') {
				num ++;
			}
		}
		else {
			ver = ver + linha.c_str()[i];
		}
	}
	if (StrToInt(ver) <= verat)	return true;
	else return false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::FormCreate(TObject *Sender)
{
	HWND hWnd = Fmx::Platform::Win::FormToHWND(frmSobre);
	if (hWnd != NULL)
	{
		LONG Style = GetWindowLong(hWnd, GWL_EXSTYLE);
		SetWindowLong(hWnd, GWL_EXSTYLE, Style | WS_EX_APPWINDOW);
	}
	verat = 4;
	novo = "Adquirindo ";
	arq = "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmSobre::ControleTimer(TObject *Sender)
{
	if (temp < 1) temp++;
	else {
		temp = 0;
		Controle->Enabled = false;
		Principal();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSobre::FormShow(TObject *Sender)
{
	HWND hWnd = Fmx::Platform::Win::FormToHWND(frmSobre);
	if (hWnd != NULL)
	{
		LONG Style = GetWindowLong(hWnd, GWL_EXSTYLE);
		SetWindowLong(hWnd, GWL_EXSTYLE, Style | WS_EX_APPWINDOW);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::gerWebArqWork(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCount)
{
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------


