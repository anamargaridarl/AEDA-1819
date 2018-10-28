/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name)
{
	for(size_t i =0; i< postmen.size(); i++)
	{
		if(postmen.at(i).getName() == name)
		{
			Postman a = postmen.at(i);
			postmen.erase(postmen.begin()+i);
			return a.getMail();
		}
	}

	return vector<Mail *>();

}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance)
{
	vector<Mail *> a;
	balance = 0;

	for(size_t i =0; i<mailToSend.size(); i++)
	{
		balance += mailToSend.at(i)->getPrice();
		string zipcode = mailToSend.at(i)->getZipCode();
		if(zipcode > firstZipCode && zipcode < lastZipCode)
			addMailToDeliver(mailToSend.at(i));
		else
			a.push_back(mailToSend.at(i));
	}

	mailToSend.clear();

	return a;
}

Postman PostOffice::addMailToPostman(Mail *m, string name)
{
	for(size_t i =0; i<postmen.size(); i++)
	{
		if(postmen.at(i).getName() == name)
		{
			postmen.at(i).addMail(m);
			return postmen.at(i);
		}
	}

	throw(NoPostmanException(name));
}
