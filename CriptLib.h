#ifndef CriptLibH
#define CriptLibH

#ifdef CRIPTNSDLL_EXPORTS
#define CRIPTLIB_API __declspec(dllexport)
#else
#define CRIPTLIB_API __declspec(dllimport)
#endif

#ifdef __cplusplus

#include <fmx.h>
#include <FMX.Dialogs.hpp>
#include <System.Classes.hpp>
#include <string.h>
#include <FMX.Memo.hpp>

extern "C" {
#endif

	CRIPTLIB_API void Cript_BasicoM(String Original, String Chave, TMemo* Memo);
	CRIPTLIB_API void Cript_BasicoL(String Original, String Chave, TStringList* Lista);
	CRIPTLIB_API void Cript_BasicoS(String Original, String Chave, String Linha);
	CRIPTLIB_API void Decript_BasicoM(String Chave, TMemo* Memo);
	CRIPTLIB_API void Decript_BasicoL(String Chave, TStringList* Lista);
	CRIPTLIB_API void Decript_BasicoS(String Original, String Chave, String Linha);
	CRIPTLIB_API String VerProg();

#ifdef __cplusplus
}

namespace CriptLib
{
	class Encriptar
	{
	public:
		static void Subst(String Original, String Chave, TMemo* Memo) { Cript_BasicoM(Original, Chave, Memo); }
		static void Subst(String Original, String Chave, TStringList* Lista) { Cript_BasicoL(Original, Chave, Lista); }
		static void Subst(String Original, String Chave, String Linha) { Cript_BasicoS(Original, Chave, Linha); }
	};

	class Decriptar
	{
	public:
		static void Subst(String Chave, TMemo* Memo) { Decript_BasicoM(Chave, Memo); }
		static void Subst(String Chave, TStringList* Lista) { Decript_BasicoL(Chave, Lista); }
		static void Subst(String Original, String Chave, String Linha) { Decript_BasicoS(Original, Chave, Linha); }
	};

	class Info
	{
	public:
		static String Ver() { return VerProg(); }
	};

}
#endif

#endif

