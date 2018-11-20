/*
 * Hospital.cpp
 */

#include "Hospital.h"
#include "Doctor.h"
//
#include <algorithm>
#include <iostream>


Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
	unsigned nb = 0;
	list<Doctor>::const_iterator it = doctors.begin();
	list<Doctor>::const_iterator ite = doctors.end();

	while(it != ite)
	{
		if(it->getMedicalSpecialty() == medicalSpecialty)
		{
			nb = nb + it-> getPatients().size();
		}
		it++;
	}

	return nb;
}

bool compare(Doctor &it, Doctor &it2) {

	if ((it.getPatients().size()) > (it2.getPatients().size()))
	{
		return false;
	}
	else if ((it.getPatients().size()) == (it2.getPatients().size()))
	{
		if (it.getMedicalSpecialty() > it2.getMedicalSpecialty())
		{
			return false;
		}
		else if ((it.getMedicalSpecialty() == it2.getMedicalSpecialty()))
		{
			if ((it.getCode() > it2.getCode()))
			{
				return false;
			}
		}
	}
	else
		return true;

}

void Hospital::sortDoctors()
{
	doctors.sort(compare);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1)
{
	unsigned nb = 0;
	list<Doctor>::const_iterator it = doctors.begin();
	list<Doctor>::const_iterator ite = doctors.end();

		while(it != ite)
		{
			if(it->getMedicalSpecialty() == medicalSpecialty1)
			{
				nb++;
			}
			it++;
		}

		if(nb<3)
		{
			Doctor p(codM1,medicalSpecialty1);
			doctors.push_back(p);
			return true;
		}
		else
			return false;
}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	queue<Patient> p1;

	list<Doctor>::const_iterator it = doctors.begin();
	list<Doctor>::const_iterator ite = doctors.end();

	while (it != ite)
	{
		if (it->getCode() == codM1)
		{
			p1 = it->getPatients();
			it = doctors.erase(it);
			return p1;
		}
		it++;
	}

	throw(DoctorInexistent());

}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1)
{
	list<Doctor>::iterator it = doctors.begin();
	list<Doctor>::iterator ite = doctors.end();

	size_t less=1000;
	while (it != ite)
	{
		if(it->getMedicalSpecialty() == medicalSpecialty1)
		{
			if(it->getPatients().size() < less)
			{
				less =it->getPatients().size();
			}
		}
		it++;
	}

	if(less == 1000)
	{
		return false;
	}

	it = doctors.begin();
	ite = doctors.end();

	Patient p(cod1,medicalSpecialty1);

	while (it != ite)
	{
		if(it->getPatients().size() == less)
		{
			it->addPatient(p);
			return true;
		}
		it++;
	}

}

void Hospital::processPatient(unsigned codM1) {

	Patient *a= new Patient();

	list<Doctor>::iterator it = doctors.begin();
	list<Doctor>::iterator ite = doctors.end();

	if(doctors.empty())
		return;

	while(it != ite)
	{
		if(it->getCode() == codM1)
		{
			try{
			*a = it->removeNextPatient();
			}
			catch(const PatientInexistent() &I)
			{

			}
			break;
		}
		cout << "b"<<endl;
		it++;
	}



	list<stack<Patient> >::iterator it2 = letterTray.begin();
	list<stack<Patient> >::iterator ite2 = letterTray.end();

	it2 = letterTray.begin();
	ite2 = letterTray.end();

	while (it2 != ite2)
	{
		if(it2->size() != trayCapacity)
		{
			it2->push(*a);
			cout << "c"<<endl;
			break;
		}
		else
		it++;
	}

	stack<Patient>newstack;
	newstack.push(*a);
	letterTray.push_back(newstack);

}


unsigned Hospital::removePatients(unsigned codP1) {

	list<stack<Patient> >::iterator it =  letterTray.begin();
	list<stack<Patient> >::iterator ite =  letterTray.end();

	unsigned i = 0;

	while(it!=ite)
	{
		if(it->top().getCode() == codP1)
		{
			it->pop();
			i++;
		}
		it++;
	}

	return i;

}



