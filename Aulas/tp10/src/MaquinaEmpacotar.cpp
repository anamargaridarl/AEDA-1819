/*
 * Empacotador.cpp
 */

#include "MaquinaEmpacotar.h"


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


/* a implementar pelos estudantes */

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {

	unsigned n =0 ;

	for(size_t i =0 ; i < objs.size(); i++)
	{

		if(objs.at(i).getPeso() <= capacidadeCaixas)
		{
			objetos.push(objs.at(i));
			objs.erase(objs.begin()+i);
			n++;
			i--;
		}
	}

	return n;
}

/* necessario melhorar implementaçao */
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {

	Caixa cx;
	vector<Caixa>pesq_caixas;
	size_t size = caixas.size();

	for(size_t i = 0; i< size ; i++)
	{
		if(caixas.top().getCargaLivre() < obj.getPeso())
		{
			pesq_caixas.push_back(caixas.top());
			caixas.pop();
		}
		else
		{
			cx = caixas.top();
			caixas.pop();

			for(auto i: pesq_caixas)
			{
				caixas.push(i);
			}
			return cx;
		}

	}

	for(auto i: pesq_caixas)
	{
		caixas.push(i);
	}

	Caixa a(capacidadeCaixas);
	return a;
}


unsigned MaquinaEmpacotar::empacotaObjetos() {

		Caixa cx;

		size_t size = objetos.size();

		for(size_t i = 0; i < size; i++ )
		{
		Objeto c = objetos.top();
		cx = procuraCaixa(c);
		cx.addObjeto(c);
		addCaixa(cx);
		objetos.pop();
		}

	return numCaixasUsadas();
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {

	string final = "";
	vector<Objeto>pesq_obj;

	size_t size = objetos.size();

	if(objectos.empty())
	{
		return "Nao ha objetos!\n";
	}

	for(size_t i = 0; i < size; i++ )
	{
	Objeto c = objetos.top();
	cout << c << "\n";
	pesq_obj.push_back(c);
	objetos.pop();
	}

	for(auto i: pesq_obj)
	{
		objetos.push(i);
	}


	return final;

}



Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	// TODO
	Caixa cx;
	return cx;
}



