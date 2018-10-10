
#include "veterinario.h"
#include <string>

using namespace std;

string Veterinario::getNome() const {
	return nome;
}

Veterinario::Veterinario(string nome, int cod){
	this->nome=nome;
	codOrdem = cod;
}

string Veterinario::getInformacao() const
{
 string final = nome +  " " + to_string(codOrdem);
 return final;
}
