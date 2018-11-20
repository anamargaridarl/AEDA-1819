/*
 * Doctor.cpp
 */

#include "Doctor.h"
#include <iostream>

Patient::Patient()
{

}

Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS)
{}

string Patient::getMedicalSpecialty() const {
	return medicalSpecialty;
}

unsigned Patient::getCode() const {
	return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS)
{}


Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1)
{}

unsigned Doctor::getCode() const {
	return codeM;
}

string Doctor::getMedicalSpecialty() const {
	return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
	return patients;
}

void Doctor::addPatient(const Patient &p1) {
	patients.push(p1);
}

Patient Doctor::removeNextPatient() {
	if (!patients.empty()) {
		Patient p1 = patients.front();
		patients.pop();
		return p1;
	}
	else throw PatientInexistent();
}




void Doctor::moveToFront(unsigned codP1) {

	bool flag = false;

	if(!patients.empty())
	{
	queue<Patient> newpatients;

	Patient *old = new Patient();
	Patient *priority = new Patient();
	*old = patients.front();

	size_t size =  patients.size();

	if (old->getCode() != codP1)
	{
	for(size_t i = 0; i< size; i++)
	{
	*old = patients.front();
	if(old->getCode() != codP1)
	{
		newpatients.push(*old);
		patients.pop();
	}
	else
	{
	*priority= patients.front();
	patients.pop();
	flag= true;
	}
	}

	if(flag)
	{
	patients.push(*priority);
	}

	size_t newsize =  newpatients.size();

	for(size_t i =0; i< newsize; i++)
	{
	*old = newpatients.front();
	patients.push(*old);
	newpatients.pop();
	}
	}
	}

}

