
#include "animal.h"

using namespace std;

int Animal::maisJovem = 200;

string Animal::getNome() const {
	return nome;
}

int Animal::getIdade() const {
	return idade;
}

Animal::Animal(string nome,int idade){
	this->nome=nome;
	this->idade=idade;

	if(this->idade < maisJovem)
		maisJovem = this->idade;
}

Voador::Voador(int vmax, int amax){
	velocidade_max =vmax;
	altura_max = amax;
}

Cao::Cao(string nome, int idade, string raca): Animal(nome,idade) {
this->raca = raca;
}

Morcego::Morcego(string nome, int idade, int vmax, int amax):Animal(nome,idade) , Voador(vmax,amax){

}


bool Cao::eJovem()const{
	if(idade < 5)
		return true;
	else
		return false;

}

bool Morcego::eJovem()const{
	if(idade < 4)
		return true;
	else
		return false;

}

string Animal::getInformacao() const
{
	string final;
	final = nome + ", " + to_string(idade) + ", ";
	if(vet != NULL)
	{
		final = final + this->vet->getNome() + ", " + to_string(this->vet->getCod()) + ", ";
	}

	return final;

}

string Cao::getInformacao() const
{
	string final;
	final = Animal::getInformacao();
	final = final + this->raca;
	return final;
}

string Voador::getInformacao() const
{
	string final;
	final = to_string(this->velocidade_max) + ", "+ to_string(this->altura_max);
	return final;
}

string Morcego::getInformacao() const
{
	string final;
	final = Animal::getInformacao() + Voador::getInformacao();
	return final;
}

void Animal::setVet(Veterinario *v1)
{
	vet =v1;
}

Veterinario* Animal::getVet()
{
	return vet;
}


