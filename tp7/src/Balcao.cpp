#include <queue>
#include <cstdlib>
#include "Balcao.h"
#include <ctime>
#include "exceptions.h"

using namespace std;


Cliente::Cliente() {
	 //srand(time(NULL));
	 int i = rand() % 5 +1;

	 this->numPresentes = i;
}


int Cliente::getNumPresentes() const {
	return numPresentes;
}


Balcao::Balcao(int te): tempo_embrulho(te) {
	this->tempo_atual = 0;
	this->prox_saida =0;
	this->clientes_atendidos = 0;
	 //srand(time(NULL));
	 int i = rand() % 20 +1;

	 this->prox_chegada=i;
}      

void Balcao::chegada()
{
	int flag = 0;

	if(clientes.empty())
		flag = 1;

	Cliente a;
	clientes.push(a);


	int i = rand() % 20 +1;
	this->prox_chegada=i;

	if(flag == 1)
	{
	this->prox_saida = tempo_atual + a.getNumPresentes()*tempo_embrulho;
	}

	cout << "tempo= "<< tempo_atual << endl;
	cout << "chegou novo cliente com "<< a.getNumPresentes() << " presentes" << endl;

}   


void Balcao::saida()
{
	getProxCliente();

	clientes.pop();

	this->prox_saida= tempo_atual + clientes.front().getNumPresentes()*tempo_embrulho;

	cout<< "cenas"<< endl;
}

void Balcao:: proximoEvento()
{
	if(!clientes.empty())
	{
	if(prox_chegada <= prox_saida)
	{
		this->tempo_atual = prox_chegada;
		chegada();
	}
	else
	{
		saida();
		this->tempo_atual = prox_saida;
	}
	}
	else
	{
		this->tempo_atual = prox_chegada;
		chegada();
	}
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }

int Balcao::getClientesEspera() const
{
	return (int)clientes.size();
}
ostream & operator << (ostream & out, const Balcao & b1)
{
	 out << "numero de clientes atendidos: "<< b1.getClientesAtendidos() << "numero clientes em espera: "<<  b1.getClientesEspera() << endl;
     return out;
}


int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return prox_saida;
}


int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}


Cliente & Balcao::getProxCliente() {

	if(clientes.empty())
		throw(FilaVazia());
	else
	{
		return clientes.front();
	}

}

      
