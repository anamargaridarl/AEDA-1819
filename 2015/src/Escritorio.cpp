#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }

Documento Documento::operator+(const Documento &doc)
{
	float pretoPer = (pPreto*numPaginas +  doc.getPercentagemPreto()*doc.getNumPaginas())/(numPaginas + doc.getNumPaginas());
	float amareloPer = (pAmarelo*numPaginas +  doc.getPercentagemAmarelo()*doc.getNumPaginas())/(numPaginas + doc.getNumPaginas());

	return Documento(numPaginas + doc.getNumPaginas(), pretoPer, amareloPer);
}


//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }


//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }

bool ImpressoraPB::imprime(Documento doc1)
{
	if(doc1.getNumPaginas() <= numPagImprimir)
	{
		numPagImprimir= numPagImprimir - doc1.getNumPaginas();
		docsImpressos.push_back(doc1);
		return true;
	}
	else
		return false;
}


//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo)
		return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1)
{

	float p= doc1.getNumPaginas()*doc1.getPercentagemPreto();
	float b= doc1.getNumPaginas()*doc1.getPercentagemAmarelo();

	if((p <= numPagImprimirPreto) && (b <= numPagImprimirAmarelo))
	{
		numPagImprimirPreto = numPagImprimirPreto -p;
		numPagImprimirAmarelo =numPagImprimirAmarelo -b;
		docsImpressos.push_back(doc1);
		return true;
	}
	else
		return false;

}


//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

int Escritorio::numImpressorasSemResponsavel() const
{
	int number =0;
	int flag =0;

	for(size_t i =0; i< impressoras.size(); i++)
	{
		string codigo = impressoras.at(i)->getCodigo();

		for(size_t n =0; n< funcionarios.size(); n++)
		{
			vector<Impressora *> imp = funcionarios.at(n).getImpressoras();

			for(size_t j = 0; j< imp.size(); j++)
			{
				if(imp.at(j)->getCodigo() == codigo)
					flag ++;
			}

		}

		if(flag ==0)
			number++;
		else
			flag =0;
	}

	return number;
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1)
{
	vector<Impressora *> rem;

	for(size_t i =0; i< impressoras.size(); i++)
	{
		cout <<"Imp: " << impressoras.at(i)->getAno()<< endl;

		if(impressoras.at(i)->getAno() < ano1)
		{
			cout << impressoras.at(i)->getAno()<< endl;
			rem.push_back(impressoras.at(i));
			impressoras.erase(impressoras.begin()+i);
			i--;
		}
	}

	cout << "end" << endl;
	return rem;
}

Impressora * Escritorio::imprimeDoc(Documento doc1) const
{
	for(size_t i =0; i< impressoras.size(); i++)
	{
		if(impressoras.at(i)->imprime(doc1) == true)
			return impressoras.at(i);
	}

	return new Impressora("inexistente",0);
}

bool ImpressoraPB::getLevels()
{
	if(getNumPaginasImprimir() < 30)
		return true;
	else
		return false;
}

bool ImpressoraCores::getLevels()
{
	if(getNumPaginasImprimir() < 20)
		return true;
	else
		return false;
}

vector<Impressora *> Escritorio::tonerBaixo() const
{
	vector<Impressora *> low;

	for(size_t i =0; i< impressoras.size(); i++)
		{
			if(impressoras.at(i)->getLevels() == true)
				low.push_back(impressoras.at(i));
		}

	return low;
}

string Escritorio::operator()(string codImpr)
{
	for(size_t i =0 ; i < funcionarios.size(); i++)
	{
		 vector<Impressora *> imp;
		 imp = funcionarios.at(i).getImpressoras();
		 for(size_t j =0 ; j < imp.size(); j++)
		 {
			 if(imp.at(j)->getCodigo() == codImpr)
				 return funcionarios.at(i).getCodigo();
		 }

	}
	string empty = "nulo";
	return 	empty;

}
