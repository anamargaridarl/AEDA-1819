#include "zoo.h"
#include <vector>

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

	string final = " ";

	for(size_t i = 0 ; i< animais.size();i++)
	{
	final = final + animais.at(i)->getInformacao() + " ";
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
