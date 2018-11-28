/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"
#include <iostream>
using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article *p = new Article(client, barCode);
	p->setPresent(present);
	p->setDeliverHome(deliverHome);

	return p;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

	list< std::stack<Article*> >::iterator it = bags.begin();
	list< std::stack<Article*> >::iterator ite = bags.end();

	while(it!= ite)
	{
		if(it->size() != BAG_SIZE)
		{
			it->push(article);
			return;
		}
		it++;
	}

	stack<Article*>newstack;
	newstack.push(article);
	bags.push_back(newstack);

}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

	vector<Article*> presents;
	vector<Article*> articles;



	list< std::stack<Article*> >::iterator it = bags.begin();
	list< std::stack<Article*> >::iterator ite = bags.end();

		while(it!= ite)
		{
			unsigned size = it->size();

			for(size_t i =0; i < size; i++)
			{
			if(it->top()->getPresent())
			{
				presents.push_back(it->top());
				it->pop();
			}
			else
			{
				articles.push_back(it->top());
				it->pop();
			}
			}

			for (size_t i = articles.size(); i > 0; i--)
			{
				it->push(articles.at(i -1));
			}
			articles.clear();
			it++;
		}

	return presents;

}

