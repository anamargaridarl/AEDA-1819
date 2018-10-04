#include "Frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1){
	veiculos.push_back(v1);
}

int Frota::numVeiculos() const{
	return (int) veiculos.size();
}

int Frota::menorAno() const{

	int menor = 3000;

	for(size_t i =0; i< veiculos.size(); i++)
	{
		if(veiculos.at(i)->getAno() < menor)
		{
			menor = veiculos.at(i)->getAno();
		}
	}

	if(menor == 3000)
		return 0;
	else
		return menor;

}

ostream & operator<<(ostream & o, const Frota & f){

for(size_t i =0; i< f.veiculos.size();i++)
{
	cout <<" Veiculo n" << i << endl;
	f.veiculos.at(i)->info();
	cout << endl;
}

return o;
}

