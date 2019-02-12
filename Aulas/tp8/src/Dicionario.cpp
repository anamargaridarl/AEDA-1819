#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;


BST<PalavraSignificado> Dicionario::getPalavras() const
{ return palavras; }



bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const
{
	if(palavra < ps1.getPalavra())
	{
		return true;
	}
	else
		return false;

}

ostream & operator<<(ostream & o, const PalavraSignificado & d)
{
	o<< d.getPalavra() << endl;
	o<< d.getSignificado() << endl;

	return o;
}
void Dicionario::lerDicionario(ifstream &fich)
{
	string palavra;
	string significado;

	while(getline(fich,palavra))
	{
		palavra = palavra.substr(0,palavra.find('\r'));
		cout << palavra << endl;

		getline(fich,significado);
		significado = significado.substr(0,significado.find('\r'));
		cout << significado << endl;

		palavras.insert(PalavraSignificado(palavra, significado));

	}

	return;
}


string Dicionario::consulta(string palavra) const
{
	BSTItrIn<PalavraSignificado> it(palavras);

	string send;

	string PalavraAntes = "";
	string SignificadoAntes = "";
	string PalavraApos = "";
	string SignificadoApos  = "";


	while(! it.isAtEnd())
	{
		if(it.retrieve().getPalavra() > palavra)
		{
			PalavraApos = it.retrieve().getPalavra();
			SignificadoApos = it.retrieve().getSignificado();
			throw(PalavraNaoExiste(PalavraAntes,SignificadoAntes,PalavraApos,SignificadoApos));
		}
		if(it.retrieve().getPalavra() == palavra)
		{
			send = it.retrieve().getSignificado();
			return send;
		}
		else
		{
		PalavraAntes = it.retrieve().getPalavra();
		SignificadoAntes = it.retrieve().getSignificado();
		it.advance();
		}
	}

	throw(PalavraNaoExiste(PalavraAntes,SignificadoAntes,PalavraApos,SignificadoApos));

}


bool Dicionario::corrige(string palavra, string significado)
{
	BSTItrIn<PalavraSignificado> it(palavras);

	while(! it.isAtEnd())
	{
		if(it.retrieve().getPalavra() == palavra)
		{
			palavras.remove(it.retrieve());
			palavras.insert(PalavraSignificado(palavra, significado));
			return true;
		}
		else
		{
		it.advance();
		}
	}

	palavras.insert(PalavraSignificado(palavra, significado));
	return false;
}


void Dicionario::imprime() const
{
	getPalavras().printTree();
     return;
}
