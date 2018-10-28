/*
 * Agencia.cpp
 */

#include "Agencia.h"


//Conta
Conta::Conta(int nConta, float sd, int nTrans): numConta(nConta), saldo(sd), numTransacoes(nTrans), titular2(NULL)
{ }

int Conta::getNumConta() const
{ return numConta; }

float Conta::getSaldo() const
{ return saldo; }

int Conta::getNumTransacoes() const
{ return numTransacoes; }


void Conta::setTitular2(Cliente *cli2)
{ titular2=cli2; }

Cliente *Conta::getTitular2() const
{ return titular2; }

void Conta::deposito(float valor)
{
	saldo = saldo + valor;
	numTransacoes++;
}

//normal
Normal::Normal(int nConta, float sd, int nTrans): Conta(nConta, sd, nTrans)
{}

bool Normal::levantamento(float valor){

	if(valor <= saldo)
	{
	saldo = saldo -valor;
	numTransacoes++;
	return true;
	}
	else
		return false;

}

float Normal::fim()
{
	saldo = saldo - 1.5;
	return saldo;
}


//deoperacao
DeOperacao::DeOperacao(int nConta, float tx, float sd, int nTrans): Conta(nConta, sd, nTrans), taxa(tx)
{}

bool DeOperacao::levantamento(float valor){

	if(valor <= saldo)
	{
	saldo = saldo -valor - taxa;
	numTransacoes++;
	return true;
	}
	else return false;
}

float DeOperacao::fim()
{
	return saldo;
}

//Cliente
Cliente::Cliente (string nm): nome(nm)
{}

string Cliente::getNome() const
{ return nome; }

vector<Conta *> Cliente::getContas() const
{ return contas; }

void Cliente::adicionaConta(Conta *c1)
{ contas.push_back(c1); }

float Cliente::getSaldoTotal()
{
	float sum;
	for(size_t i =0; i< contas.size(); i++)
	{
		sum += contas.at(i)->getSaldo();
	}
	return sum;
}

//Agencia
Agencia::Agencia(string desig): designacao(desig)
{}

string Agencia::getDesignacao() const
{ return designacao; }

vector<Cliente *> Agencia::getClientes() const
{ return clientes; }

vector<Gerente> Agencia::getGerentes() const
{ return gerentes; }

void Agencia::adicionaCliente(Cliente *cli1)
{ clientes.push_back(cli1); }

Conta * Agencia::levantamento(string nomeCli, float valor)
{
	for(size_t i = 0; i < clientes.size();i++)
	{
		if(clientes.at(i)->getNome() == nomeCli)
		{
			 vector<Conta *> contas = clientes.at(i)->getContas();

			 for(size_t n = 0; n < contas.size(); n++)
			 {
				 if(valor < contas.at(n)->getSaldo())
				 {
					 contas.at(n)->levantamento(valor);
					 return contas.at(n);
				 }
			 }
		}
	}

	Conta *a= new Conta(-1,0,0);
	return a;
}

float Agencia::fimMes() const
{
	float sum;

	for(size_t i =0; i <clientes.size(); i++)
	{
		for(size_t n =0 ; n < clientes.at(i)->getContas().size(); n++)
		{
			sum += clientes.at(i)->getContas().at(n)->fim();
		}
	}
}

vector<Conta*> Agencia::removeCliente(string nomeCli)
{
	vector<Conta*> remContas;
	vector<Conta*> t2contas;

	for(size_t i = 0; i < clientes.size(); i++)
	{
		if(clientes.at(i)->getNome() == nomeCli)
		{
			vector<Conta *> contas = clientes.at(i)->getContas();

			for(size_t n =0 ; n < contas.size(); n++)
			{
				if(contas.at(n)->getTitular2() == NULL)
				{
					remContas.push_back(contas.at(n));
				}
				else
				{
					t2contas.push_back(contas.at(n));
				}
			}
			clientes.erase(clientes.begin()+i);
		}
	}

	for(size_t i = 0; i < clientes.size(); i++)
	{
		for(size_t n = 0; n < t2contas.size(); n++)
		{
			if(t2contas.at(n)->getTitular2()==clientes.at(i))
			{
				t2contas.at(n)->setTitular2(NULL);
				clientes.at(i)->adicionaConta(t2contas.at(n));
			}
		}
	}

	return remContas;


}


/*[3 valores] Implemente na classe Agencia o operador <. Uma agência é menor que outra se o saldo
médio por cliente é menor. Nota: O saldo médio por cliente é igual ao quociente entre a soma dos
saldos de todas as contas da agência e o número de clientes.*/
bool Agencia::operator<(const Agencia &a)
{
	float sumE, sumD;

		for(size_t i =0; i < clientes.size(); i++)
		{
			sumE += clientes.at(i)->getSaldoTotal();
		}
		sumE = sumE / (float)clientes.size();

		for(size_t i =0; i < a.clientes.size(); i++)
		{
		sumD += a.clientes.at(i)->getSaldoTotal();
		}
		sumD = sumD / (float)clientes.size();

		return (sumE < sumD);

}

float Agencia::operator()(string nameCli)
{
	for(size_t i = 0; i < clientes.size(); i++)
	{
		if(clientes.at(i)->getNome() == nameCli)
		{
			return clientes.at(i)->getSaldoTotal();
		}
	}

	return -1;
}

int nextID =0;

void Agencia::setGerenteID (int IDinicio)
{
	nextID = IDinicio;
}

void Agencia::adicionaGerente(string nomeGer)
{
	Gerente g(nomeGer);
	this->gerentes.push_back(g);
}
//Gerente
int Gerente::getID() const
{ return ID; }

string Gerente::getNome() const
{ return nome; }

Gerente::Gerente(string nm)
{
	nome = nm;
	ID = nextID;
}


