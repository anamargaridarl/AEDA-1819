/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {

	BSTItrIn<Expertize> it(expertizes);

	while(!it.isAtEnd())
	{
		if(it.retrieve().getName() == expertizeAvailable)
		{
			if(it.retrieve().getCost() == cost)
			{
				Expertize a = it.retrieve();
				a.addConsultant(student);
				expertizes.remove(it.retrieve());
				expertizes.insert(a);
				return;
			}
		}

			it.advance();
	}

	Expertize a(expertizeAvailable, cost);
	a.addConsultant(student);
	expertizes.insert(a);

}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;

	BSTItrIn<Expertize> it(expertizes);

	if(project->getConsultant() != NULL)
		return temp;

	while(!it.isAtEnd())
	{
		if(it.retrieve().getName() == project->getExpertize())
		{
			vector<Student*> consultants;
			consultants = it.retrieve().getConsultants();
			for(size_t i=0; i < consultants.size(); i++)
			{
				if(consultants.at(i)->getCurrentProject() == "")
				{
					temp.push_back(consultants.at(i));
				}
			}
		}

		it.advance();
	}

	return temp;

}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {

	string exp,title;
	unsigned int cost;

	exp = project->getExpertize();
	cost = project->getCost();
	title = project->getTitle();

	BSTItrIn<Expertize> it(expertizes);
	vector<Student*>temp;

	if(student->getCurrentProject() != "")
		return false;
	if(project->getConsultant() != NULL)
		return false;

	while(!it.isAtEnd())
	{
		if(it.retrieve().getName() == exp && it.retrieve().getCost() == cost)
		{
			temp = it.retrieve().getConsultants();
			if(find(temp.begin(),temp.end(), student) != temp.end())
			{
				student->addProject(title);
				project->setConsultant(student);
				return true;
			}
			else
				return false;

		}

		it.advance();

	}

	return false;
}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	students.insert(student);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	student->setEMail(newEMail);

}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates,
		int min) {

	unsigned int size;

	for (size_t i = 0; i < candidates.size(); i++) {
		size = candidates.at(i).getPastProjects().size();

		if ((int) size >= min) {
			vector<Student> temp;

			if (activeStudents.empty()) {
				activeStudents.push(candidates.at(i));
			} else {
				while (activeStudents.top().getPastProjects().size() > size) {
					temp.push_back(activeStudents.top());
					activeStudents.pop();
				}

				activeStudents.push(candidates.at(i));

				for (size_t n = temp.size(); n > 0; i--) {
					activeStudents.push(temp.at(n - 1));
				}
			}
		}

	}
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {

	vector<Student>temp;

	if(activeStudents.empty())
		return 0;

	temp.push_back(activeStudents.top());
	activeStudents.pop();

	if(activeStudents.top().getPastProjects().size() == temp[0].getPastProjects().size())
	{
		activeStudents.push(temp.at(0));
		return 0;
	}
	else
	{
		studentMaximus = temp[0];
		activeStudents.push(temp.at(0));
		return activeStudents.size();
	}


}





















