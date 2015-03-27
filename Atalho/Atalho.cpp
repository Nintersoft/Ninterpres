#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

int main(){
	try {
		cout<<"Abrindo programa de apresentacao"<<endl<<"Por favor, aguarde";
		Sleep(2000);
		ShellExecuteA( NULL, "open", "BIN\\Ninterpres-a.exe", NULL, NULL, SW_SHOW );
		Sleep(2000);
	} catch (...) {
		cout<<endl<<endl<<"Erro na abertura do programa. certifique-se de que o executável encontra-se em BIN";
		getch();
	}

	return 0;
}
