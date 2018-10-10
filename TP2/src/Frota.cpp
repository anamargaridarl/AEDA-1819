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
			//veiculos é um vetor de apontadores para uma classe.
			//Para chamar as funçoes das classes apontadas é necessario (*)veiculos.at(i).getAno(), equivalente a:
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
	cout <<" Veiculo nº" << i << endl;
	f.veiculos.at(i)->info();
	cout << endl;
}

return o;
}

vector<Veiculo *> Frota::operator () (int anoM) const
{
	vector<Veiculo *> AnoIgual;

	for(size_t i = 0; i< veiculos.size(); i++)
	{
		if( veiculos.at(i)->getAno() == anoM)
			AnoIgual.push_back(veiculos.at(i));
	}

	return AnoIgual;
}

float Frota::totalImposto() const
{
	float total = 0;

	for(size_t i = 0; i < veiculos.size(); i++)
	{
		total = total + veiculos.at(i)->calcImposto();
	}

	return total;
}
