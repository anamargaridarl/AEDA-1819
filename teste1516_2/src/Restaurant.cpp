/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Restaurant.h"
#include <iostream>

using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)) {
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {

	Dish *add =  new Dish(collection, type);

	for(unsigned int i = 0; i<n; i++)
	{
	getCleanDishStack(collection, type).push(add);
	}

}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish *d;

	d = dirty.front();
	dirty.pop();

	drying.push_back(d);

	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */
void Restaurant::clearTable(vector<Table>::size_type idx) {

	vector<Dish*>a;

	if(tables.empty())
		return;
	else if(idx > tables.size()-1 )
		return;
	else if(idx <= tables.size()-1)
	{
		a = tables.at(idx).clear();
	}

	for(size_t i = 0; i< a.size(); i++)
	{
		dirty.push(a.at(i));
	}

}

/**
 * Stores in the respective clean stack all drying dishes of a given collection and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {

	list<Dish*>::iterator it = drying.begin();
	list<Dish*>::iterator ite = drying.end();

	vector<Dish*>toclean;

	while(it != ite)
	{
		if((*it)->getCollection() == collection && (*it)->getType() == type)
		{
			toclean.push_back(*it);
			it = drying.erase(it);
		}
		it++;
	}

	for(size_t i= 0 ; i< toclean.size(); i++)
	{
		getCleanDishStack(collection, type).push(toclean.at(i));
	}

}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {
	cout << "a" << endl;
	if(tables.empty())
	{
		cout << "b" << endl;
		return;
	}
	else if(idx > tables.size()-1 )
	{
		cout << "c" << endl;
		return;
	}
	else if(idx <= tables.size()-1)
	{
		cout << "d" << endl;
		if(!tables.at(idx).empty())
		{
			cout << "e" << endl;
			throw(TableNotReadyException());
		}

		cout << "g" << endl;
		stack<Dish*> &dishes = getCleanDishStack(collection, Plate);

		cout << "f" << endl;
		if(dishes.size() < tables.at(idx).size())
		{
			throw(NotEnoughDishesException());
		}
		else
		{
			vector<Dish*>a;

			for(size_t i =0; i < tables.at(idx).size(); i++)
			{
				a.push_back(dishes.top());
				dishes.pop();
			}
			tables.at(idx).putOn(a);
		}
	}


}

/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped;

	// TODO

	return dry_grouped;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {

	// TODO

	return 0;
}

