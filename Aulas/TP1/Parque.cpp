#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot,unsigned int nMaxCli): lotacao(lot),numMaximoClientes(nMaxCli)
{
	vagas=lot;
}


unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const
{
	return numMaximoClientes;
}


int ParqueEstacionamento::posicaoCliente(const string & nome) const
{
	for(size_t i =0 ; i<clientes.size(); i++)
	{

		if(clientes.at(i).nome==nome)
		{
			return i;
		}
	}

	return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
	if(clientes.size()< 5)
		{
		InfoCartao a;
		a.nome=nome;
		clientes.push_back(a);
		return true;
		}
	else
		return false;

}


bool ParqueEstacionamento::entrar(const string & nome)
{
	if(vagas!=0)
	{
	int i = posicaoCliente(nome);

		if(i!= -1&&clientes.at(i).presente==false)
		{
			clientes.at(i).presente=true;
			vagas--;
			return true;
		}
		else
			return false;
	}
	else
		return false;

}

bool ParqueEstacionamento::retiraCliente(const string & nome)
{
		int i = posicaoCliente(nome);

			if(i!= -1 &&clientes.at(i).presente==false)
			{
				clientes.erase(clientes.begin()+i);
				return true;
			}
			else
				return false;


}

bool ParqueEstacionamento::sair(const string & nome)
{
	int i = posicaoCliente(nome);

			if(i!= -1 &&clientes.at(i).presente==true)
			{
				clientes.at(i).presente=false;
				vagas++;
				return true;
			}
			else
				return false;

}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const
{
	unsigned int size= clientes.size();
	return size;
}
