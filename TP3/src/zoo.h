
#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>
#include <string>


class Zoo {
	vector<Animal *> animais;
	vector<Veterinario *> veterinarios;
public:
	Zoo();
	int numAnimais() const;
	int numVeterinarios() const;
	void adicionaAnimal(Animal *a1);
	string getInformacao() const;
	bool animalJovem(string nomeA);
	//completar
};


#endif /* ZOO_H_ */
