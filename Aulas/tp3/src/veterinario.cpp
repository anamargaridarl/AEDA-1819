
#include "veterinario.h"
#include <string>

using namespace std;

string Veterinario::getNome() const {
	return nome;
}

int Veterinario::getCod() const{
	return codOrdem;
}

Veterinario::Veterinario(string nome, int cod){
	this->nome=nome;
	codOrdem = cod;
}


