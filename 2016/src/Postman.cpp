/*
 * Postman.cpp
 */
#include "Postman.h"

int idC = 1;

Postman::Postman(): id(0) {}

Postman::Postman(string name)
{
	this->id=idC;
	idC++;
	name =name;
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator<(const Postman &a)
{
	vector<string>apost;
	vector<string>post;

	for(size_t i =0; i< myMail.size(); i++)
	{
		post.push_back(myMail.at(i)->getZipCode());
	}
	for(size_t i =0; i< a.myMail.size(); i++)
	{
		apost.push_back(a.myMail.at(i)->getZipCode());
	}

	return numberDifferent(post) < numberDifferent(apost);
}



