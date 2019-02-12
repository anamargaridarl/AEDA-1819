#include "Jogador.h"
#include <iostream>

void Jogador::adicionaAposta(const Aposta & ap)
{
	apostas.insert(ap);
}

unsigned Jogador::apostasNoNumero(unsigned num) const
{
	unsigned count = 0;

	for(auto i: apostas)
	{
		if(i.contem(num))
			count++;
	}

	return count;
}


tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;

	for(auto i: apostas)
	{
	 if (i.calculaCertos(sorteio) > 3)
	 {
		 money.insert(i);
	 }
	}

	return money;
}
