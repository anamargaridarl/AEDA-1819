/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>
#include <string>
#include "Car.h"


class Garage {
	std::vector<Car *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Car *> getVehicles() const;
	void setVehicles(std::vector<Car *> vehicles);
	int getCapacity() const;
	bool addVehicle(Car *vehicle);
	Car* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

class NoSuchBrandException {
public:
	NoSuchBrandException(std::string brand)
{
		this->brand=brand;
}
	std::string brand;
	std::string getBrand()
	{return brand;}
};


Garage::Garage(int size) : capacity(size) {
}

Garage::~Garage() {
	typename std::vector<Car *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}


std::vector<Car *> Garage::getVehicles() const {
	return vehicles;
}


void Garage::setVehicles(std::vector<Car*> vehicles) {
	this->vehicles = vehicles;
}


int Garage::getCapacity() const {
	return capacity;
}

bool Garage::addVehicle(Car *vehicle)
{
	if(vehicles.size() < capacity)
	{
		for(size_t i =0; i <vehicles.size(); i++)
		{
			if(vehicles.at(i) == vehicle)
				return false;
		}
	}

	vehicles.push_back(vehicle);
	return true;

}


void Garage::sortVehicles()
{
	for(size_t i =0; i< vehicles.size(); i++)
	{
		for(size_t n =1; n< vehicles.size(); n++)
			{
				if(vehicles.at(i)->getBrand() > vehicles.at(n)->getBrand())
				{
					Car * a = vehicles.at(n);
					vehicles.at(n) = vehicles.at(i);
					vehicles.at(i) = vehicles.at(n);
				}
				else if(vehicles.at(i)->getBrand() == vehicles.at(n)->getBrand())
				{
					if(vehicles.at(i)->getPrice() < vehicles.at(n)->getPrice())
					{
						Car * a = vehicles.at(n);
						vehicles.at(n) = vehicles.at(i);
						vehicles.at(i) = vehicles.at(n);
					}

				}
			}
	}
}


Car * Garage::removeVehicle(std::string brand, std::string model)
{
	for(size_t i =0; i<vehicles.size(); i++)
	{
		if((vehicles.at(i)->getBrand() == brand) && (vehicles.at(i)->getModel() == model))
		{
			Car * a = vehicles.at(i);
			vehicles.erase(vehicles.begin()+i);
			return a;
		}
	}

	throw(NoSuchVehicleException());

}


float Garage::avgPrice(std::string brand) const
{
	float result = 0;
	float n =0 ;

	for(size_t i =0; i<vehicles.size(); i++)
	{
		if(vehicles.at(i)->getBrand() == brand)
		{
			result += vehicles.at(i)->getPrice();
			n++;
		}
	}

	if(result ==0)
	{
		throw(NoSuchBrandException(brand));
	}
	else
		return result/n;
}




#endif /* SRC_GARAGE_H_ */
