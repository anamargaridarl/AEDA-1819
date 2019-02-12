#include "Jogo.h"

BinaryTree<Circulo> & Jogo::getJogo() {
	return jogo;
}


ostream &operator << (ostream &os, Circulo &c1)
{
	// a alterar
	return os;
}

BinaryTree<Circulo> criajogo(int p, int n,vector<int> &pontos, vector<bool> &estados)
{
	Circulo A(pontos.at(p), estados.at(p));

	if(n == 0)
		return BinaryTree<Circulo>(A);


	BinaryTree<Circulo> left = criajogo(2*p+1,n-1,pontos,estados);
	BinaryTree<Circulo> right = criajogo(2*p+2,n-1,pontos,estados);

	return BinaryTree<Circulo>(A,left,right);

}

Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
	this->jogo = criajogo(0, niv,pontos, estados);
}


string Jogo::escreveJogo()
{
	string final, estd;
	BTItrLevel<Circulo> it(jogo);
	final = "";

	while(!it.isAtEnd())
	{
		bool estado = it.retrieve().getEstado();

		if(estado == 1)
			estd = "true";
		else
			estd =  "false";

		final = final + to_string(it.retrieve().getPontuacao())+ "-" + estd + "-" + to_string(it.retrieve().getNVisitas()) + "\n";

		it.advance();
	}


	return final;
}


int Jogo::jogada()
{
	BTItrLevel<Circulo> it(jogo);

	int pos = 1;
	int pontos;
	bool estado;

	while(!it.isAtEnd())
	{
	   estado = it.retrieve().getEstado();

		if(pos == it.retrieve().getPontuacao())
		{
			if(estado == 1)
			{
				pos = pos * 2 +1;
			}
			else
				pos = pos * 2;

			it.retrieve().trocaEstado();
			it.retrieve().incNVisitas();
			pontos = it.retrieve().getPontuacao();
		}

		it.advance();

	}

	return pontos;
}



int Jogo::maisVisitado()
{
	BTItrLevel<Circulo> it(jogo);
	int MNVisitas = 0;

	it.advance();

	while(!it.isAtEnd())
	{
		Circulo &a = it.retrieve();

		if(a.getNVisitas() > MNVisitas)
		{
			MNVisitas = a.getNVisitas();
		}

		it.advance();
	}

	return MNVisitas;
}




