#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
	bool operator==(const No<N,A> &a);
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
	bool operator==(Aresta<N,A> &a);
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }



// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

template <class N, class A>
Grafo<N,A>::Grafo()
{
	vector< No<N,A> *> nos;
	this->nos =nos;
}

template <class N, class A>
Grafo<N,A>::~Grafo()
{
	/*for(size_t i =0; i < nos.size();i++)
	{
		delete[] nos.at(i);
	}
	*/

	typename vector< No<N,A> *>::iterator it;

	for (it =nos.begin();it != nos.end();it++)
	{
		delete *it;
	}


}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

template <class N, class A>
int Grafo<N,A>::numNos(void) const
{
	return nos.size();
}

template <class N, class A>
int Grafo<N,A>::numArestas(void) const
{
	int arestas =0;

	for(size_t i =0; i < nos.size();i++)
		{
			arestas = arestas + nos.at(i)->arestas.size();
		}

return arestas;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

//esta a dar erro
/*template <class N, class A>
bool No<N,A>::operator==(const No<N,A> &a)
{
	if(info == a.info)
		return true;
	else
		return false;
}
*/

template <class N, class A>
bool Aresta<N,A>::operator==(Aresta<N,A> &a)
{
	return (valor == a.valor() &&(destino == a.destino()));
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N &dados)
{
	No<N,A > *cmp = new No<N,A>(dados);
	//typename vector< No<N,A> *>::iterator it;

	for (size_t i = 0; i< nos.size();i++)
	{
		if(nos.at(i)->info == dados)
			throw(NoRepetido<N>(dados));
	}

	nos.push_back(cmp);

	return *this;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

template <class N>
class ArestaRepetida {
public:
	N infoI;
	N infoF;
	ArestaRepetida(N ini, N fim)
	{
		infoI = ini;
		infoF = fim;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ni)
{ out << "Aresta Repetida com no inicial: " << ni.infoI << "e no final" << ni.infoF; return out; }



template <class N, class A>
bool lookForAresta(const No<N,A> &a, const N &fim)
{
	for(size_t i = 0; i < a.arestas.size(); i++ )
	{
		if(a.arestas.at(i).destino->info == fim)
			return true;
		else
			return false;

	}
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val)
{
	int flagI =0;
	int flagF =0;
	int indI, indF;

	/* esta a dar erro operador ==
	No<N,A > *ini = new No<N,A>(inicio);
	No<N,A > *end = new No<N,A>(fim);*/

	//procurar se nos de inicio e fim de aresta existem

		for (size_t i = 0; i < nos.size();i++)
		{
			if(nos.at(i)->info == inicio)
			{
				 indI = i;
				 flagI++;
			}
			else if(nos.at(i)->info == fim)
			{
				indF = i;
				flagF++;
			}

		}

		if(flagI == 0)
			throw(NoInexistente<N>(inicio));
		else if(flagF == 0)
			throw(NoInexistente<N>(fim));
		else
		{
			if(lookForAresta(*(nos.at(indF)),fim))
				throw(ArestaRepetida<N>(inicio, fim));
			else
			{
				Aresta<N,A> a (nos.at(indF),val);
				nos.at(indI)->arestas.push_back(a);
			}
		}

	return *this;

}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
template <class N>
class ArestaInexistente {
public:
	N infoI;
	N infoF;
	ArestaInexistente(N ini, N fim)
	{
		infoI = ini;
		infoF = fim;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ni)
{ out << "Aresta Repetida com no inicial: " << ni.infoI << "e no final" << ni.infoF; return out; }


A & Grafo<N,A>::valorAresta(const N &inicio, const N &fim)
{
	for (size_t i = 0; i < nos.size();i++)
	{
		int flag = 0;

		if(nos.at(i)->info == inicio)
		{

		for (size_t n = 0; i < nos.at(i)->arestas.size(); n++)
		{
			if(nos.at(i)->arestas.at(n)->destino ==fim)
			{
				flag++;
				return this->nos.at(i)->arestas.at(n)->valor;
			}
		}

		}
	}

	throw(ArestaInixestente<N>(inicio,fim));


}


