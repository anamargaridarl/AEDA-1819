/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
using namespace std;
#include <iostream>
#include <list>

unsigned Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;
  int n=1;
  unsigned pos = frase.find(' ');
  while ( pos != string::npos ) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}


Jogo::Jogo()
{
	// a alterar
}

Jogo::Jogo(list<Crianca>& lc2)
{
	// a alterar
}

void Jogo::insereCrianca(const Crianca &c1)
{
	this->criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return criancas;
}


string Jogo::escreve() const
{
	string final;

	list<Crianca>::const_iterator it = criancas.begin();
	list<Crianca>::const_iterator ite = criancas.end();

	while(it != ite)
	{
		final = final + it->escreve() + "\n";
		it++;
	}

	return final;
}


Crianca& Jogo::perdeJogo(string frase)
{
	int npal = numPalavras(frase) - 1;
	list<Crianca>::iterator it = criancas.begin();
	list<Crianca>::iterator ite = criancas.end();
	while (criancas.size() > 1) {
		int nc = criancas.size();
		int p = npal % nc;
		for (int i = 1; i <= p; i++) {
			it++;
			if (it == ite)
				it = criancas.begin();
		}
		cout << "sai: " << it->escreve() << endl;
		it = criancas.erase(it);
		if (it == ite)
			it = criancas.begin();
	}
	return *it;

}


list<Crianca>& Jogo::inverte()
{
	criancas.reverse();
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	list<Crianca> removed;
	list<Crianca>::iterator it = criancas.begin();
	list<Crianca>::iterator ite = criancas.end();

	while(it != ite)
	{
		if(it->getIdade() > id)
		{
			removed.push_back(*it);
			it = criancas.erase(it);
		}
		else
			it++;
	}


	return removed;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	this->criancas=l1;
}


bool Jogo::operator==(Jogo& j2)
{

}


list<Crianca> Jogo::baralha() const
{
	// a alterar
	list<Crianca> res;
	return res;
}
