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
	bool operator==(No<N,A> &a);
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

template <class N, class A>
bool No<N,A>::operator==(No<N,A> &a)
{
	return (info == a.info() && arestas == a.arestas());
}

template <class N, class A>
bool Aresta<N,A>::operator==(Aresta<N,A> &a)
{
	return (valor == a.valor() && destino == a.destino());
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N &dados)
{
	No<N,A > *cmp = new No<N,A>(dados);
	typename vector< No<N,A> *>::iterator it;

	for (it =nos.begin();it != nos.end();it++)
	{
		if(*it == cmp)
			throw NoRepetido<N>(dados);
	}

	nos.push_back(cmp);

	return *this;
}

/*
template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val)
{
	int flag =0;
	typename vector< No<N,A> *>::iterator it;

		for (it =nos.begin();it != nos.end();it++)
		{
			if(*it == inicio)
				flag++;

		}

		if(flag == 1)
			throw NoInexistente<N>();


}
*/


