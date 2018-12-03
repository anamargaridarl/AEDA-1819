#include "Aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Aposta::contem(unsigned num) const
{
	if( numeros.find(num) != numeros.end())
	return true;
	else
		return false;
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
	int flag = 0;
	vector<unsigned>repetidos;
	unsigned i = 0;

	for(unsigned nelem = 0; (i < n) & (nelem < valores.size() ) ; nelem++)
	{
		for(size_t p = 0; p < repetidos.size();p++)
		{
			if(repetidos.at(p) == valores.at(nelem))
			flag = 1;
		}

		if(flag != 1)
		{
		numeros.insert(valores.at(nelem));
		repetidos.push_back(valores.at(nelem));
		i++;
		}
		else
		{
		flag = 0;
		}

	}
}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
	unsigned certos = 0;

	for(auto i: sorteio)
	{
		if (numeros.find(i) != numeros.end())
		{
			certos++;
		}

	}

	return certos;
}




