#include "zoo.h"
#include <vector>
#include <iostream>

using namespace std;

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

Zoo::Zoo(){
	vector<Animal *> a;
	vector<Veterinario *>b;
	a= animais;
	b = veterinarios;
}

void Zoo::adicionaAnimal(Animal *a1){
	animais.push_back(a1);
}

string Zoo::getInformacao() const{

	string final;

	for(size_t i = 0 ; i< animais.size();i++)
	{
	final = final + animais.at(i)->getInformacao() + "\n";
	}

	return final;
}

bool Zoo::animalJovem(string nomeA)
{

	int flag = 1;

	for(size_t i = 0 ; i< animais.size();i++)
		{
		if(animais.at(i)->getNome() == nomeA)
		{
			if(animais.at(i)->eJovem() == true)
				flag  = 0;
		}
		}

	if (flag == 0)
		return true;
	else
		return false;
}

void Zoo::alocaVeterinarios(istream &isV)
{

string nome,cod;

	while (getline(isV, nome, '\n'))
	{
		getline(isV, cod, '\n');
		nome.erase(nome.end()-1);
		Veterinario *v1 = new Veterinario(nome,stoi(cod));
		veterinarios.push_back(v1);
	}


	size_t n=0;

	for(size_t i = 0; i< animais.size();i++)
	{
		animais.at(i)->setVet(veterinarios.at(n));
		n++;
		if(n >= veterinarios.size())
		{
			n =0;
		}
	}

}

bool Zoo::removeVeterinario (string nomeV)
{
	int flag = 1; //flag para saber se encontrou veterinario

	for(size_t i = 0; i< veterinarios.size();i++) //procura veterinario
	{
		if(veterinarios.at(i)->getNome()== nomeV) //procura nome
		{
			flag = 0;
			for(size_t n=0; n < animais.size();n++) //procura animais
			{
				if(animais.at(i)->getVet()->getNome() == nomeV) //procura nome do ve no animal
				{
					animais.at(i)->setVet(veterinarios.at(i+1)); //modifica vet
				}
			}

			veterinarios.erase(veterinarios.begin()+i);
		}
	}

	if(flag == 0)
		return true;
	else
		return false;

}

bool Zoo::operator < (Zoo& zoo2) const
{
	int id1,id2;
	id1=id2 =0;

	for(size_t i=0; i<animais.size();i++)
	{
		id1 = id1 + animais.at(i)->getIdade();
	}

	for(size_t i=0; i< zoo2.animais.size();i++)
	{
			id2 = id2 + zoo2.animais.at(i)->getIdade();
	}

	if(id1 < id2)
		return true;
	else
		return false;
}
