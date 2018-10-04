#include "Veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc,int m, int a)
{
	marca = mc;
	mes = m;
	ano = a;
}

Motorizado::Motorizado(string mc, int m, int a,string c,int cil): Veiculo(mc,m,a) ,combustivel(c),cilindrada(cil){

}

Automovel::Automovel(string mc,int m, int a, string c, int cil):  Motorizado(mc,m, a,c,cil){

}

Camiao::Camiao(string mc,int m, int a, string c, int cil,int cm): Motorizado(mc,m,a,c,cil), carga_maxima(cm){
}

Bicicleta::Bicicleta(string mc,int m, int a, string t): Veiculo(mc,m,a), tipo(t){

}

string Motorizado::getCombustivel() const{
	return combustivel;
}

string Veiculo::getMarca() const{
	return marca;
}

int Veiculo::getAno() const
{
	return ano;
}

int Veiculo::info() const
{
	cout << "Marca " << marca << endl;
	cout << "Ano "<< ano << endl;
	cout << "Mes " << mes << endl;

	return 3;
}

int Motorizado::info() const
{
	Veiculo::info();
	cout << "Combustivel " << combustivel << endl;
	cout << "Cilindrada " << cilindrada << endl;

	return 5;
}

int Automovel::info() const {
	Motorizado::info();
	return 5;
}

int Camiao::info() const {
	Motorizado::info();
	cout << "Carga maxima "<< carga_maxima << endl;
	return 6;
}

int Bicicleta::info() const{
	Veiculo::info();
	cout << "Tipo " << tipo << endl;
	return 4;
}


