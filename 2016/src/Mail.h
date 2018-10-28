/*
 * Mail.h
 */

#ifndef SRC_MAIL_H_
#define SRC_MAIL_H_

#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class Mail {
	string sender;
	string receiver;
	string zipCode;
public:
	Mail(string send, string rec, string zcode);
	virtual ~Mail();
	string getZipCode() const;
	virtual unsigned int getPrice() const = 0;
};


class RegularMail: public Mail {
	unsigned int weight;
public:
	RegularMail(string send, string rec, string code, unsigned int w);
	unsigned int getPrice() const;
};


class GreenMail: public Mail {
	string type;  // "envelope", "bag", "box"
public:
	GreenMail(string send, string rec, string code, string t);
	unsigned int getPrice() const;
};

template<class T>
unsigned int numberDifferent(const vector<T>&v1)
{
	unsigned int dif= v1.size();
	vector<unsigned int>repetidos;

	for(size_t i = 0; i < v1.size(); i++)
	{
		for(size_t n = 0; n < v1.size(); n++)
		{
			if(find(repetidos.begin(),repetidos.end(),i) == repetidos.end())
			{
				if(i != n)
				{
					if(v1.at(i)==v1.at(n))
					{
					dif--;
					repetidos.push_back(n);
					}
				}
			}
		}
	}

	return dif;
}

#endif /* SRC_MAIL_H_ */
