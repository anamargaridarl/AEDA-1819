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

//função virtual-> permite aplicar o mesmo objetivo final mas a classes diferentes
//função é inicializada para cada classe de acordo com os atributos de cada uma,
//podendo ser usadas as funções das classes anteriores

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

bool Veiculo::operator < (const Veiculo & v) const
{
	if(ano != v.ano)
	{
		if(ano < v.ano)
			return true;
		else return false;
	}
	else
	{
		if(mes < v.mes)
				return true;
		else return false;
	}

}

float Motorizado::calcImposto() const {

	if (((combustivel == "gasolina") && (cilindrada <= 1000))
			|| ((combustivel != "gasolina") && (cilindrada <= 1500)))
	{
		if (ano > 1995)
			return 14.56;
		else
			return 8.10;
	}
	else if (((combustivel == "gasolina") && (cilindrada <= 1300))
			|| ((combustivel != "gasolina") && (cilindrada <= 2000)))
	{
		if (ano > 1995)
			return 29.06;
		else
			return 14.56;
	}
	else if (((combustivel == "gasolina") && (cilindrada <= 1750))
			|| ((combustivel != "gasolina") && (cilindrada <= 3000)))
	{
		if (ano > 1995)
			return 45.15;
		else
			return 22.65;
	}
	else if (((combustivel == "gasolina") && (cilindrada > 1750)
			&& (cilindrada <= 2600)) || (combustivel != "gasolina"))
	{
		if (ano > 1995)
			return 113.98;
		else
			return 54.89;
	}
	else if ((combustivel == "gasolina") && (cilindrada <= 3500))
	{
		if (ano > 1995)
			return 181.17;
		else
			return 87.13;
	}
	else if (combustivel == "gasolina")
	{
		if (ano > 1995)
			return 320.89;
		else
			return 148.37;
	}
}

//confirmar com professora
float Bicicleta::calcImposto() const {
	return 0;
}



