#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>
#include<algorithm>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

bool InfoCartao::operator == (const InfoCartao &ic1) const
{
	if(ic1.nome == nome)
		return true;
	else
		return false;
}

// a alterar
int ParqueEstacionamento::posicaoCliente(const string & nome) const {

	InfoCartao a;
	a.nome = nome;

	return sequentialSearch(clientes,a);
}


int ParqueEstacionamento::getFrequencia(const string &nome) const
{
	int i;

	i = posicaoCliente(nome);

	if(i == -1)
	{
		throw(ClienteNaoExistente(nome));
	}
	else
		return clientes.at(i).frequencia;
}

bool InfoCartao::operator < (const InfoCartao &ic1) const
{
	if(ic1.frequencia < frequencia)
		return true;
	else if(ic1.frequencia == frequencia)
	{
		return ic1.nome > nome;
	}
	else
		return false;
}

void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
	insertionSort(clientes);
}

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
	vector<string> result;

	ordenaClientesPorFrequencia();

	for(size_t i =0; i< clientes.size(); i++)
	{
		if((clientes.at(i).frequencia >= n1 )&& (clientes.at(i).frequencia <= n2))
		{
			result.push_back(clientes.at(i).nome);
		}
	}

	return result;

}

bool myfunction (InfoCartao i,InfoCartao j)
{
	return i.nome < j.nome;
}

void ParqueEstacionamento::ordenaClientesPorNome()
{
	sort(clientes.begin(),clientes.end(),myfunction);
}

InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
	if(p <clientes.size())
	{
		return clientes.at(p);
	}
	else
		throw(PosicaoNaoExistente(p));
}

ostream & operator << (ostream &os, const ParqueEstacionamento &pe)
{
	for(size_t i =0 ; i < pe.clientes.size();i++)
	{
		os << pe.getClienteAtPos(i).nome << " ";
		if(pe.getClienteAtPos(i).presente){
			os << "Presente" << " ";
		}
		else{
			os << "Ausente" << " ";
		}
			os << pe.getClienteAtPos(i).frequencia << " ";
	}
	return os;
}
