/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
		numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }


// TODO

bool Cinema::operator<(const Cinema & cr) const
{
	if(this->getDistance() == cr.getDistance())
			return this->getServices().size() < this->getServices().size();
		return this->getDistance() > cr.getDistance();
}

//a1
Film *Cinema::filmAtHour(unsigned &h1) const {

	Film *last = NULL;

	BSTItrIn<FilmTime> it(timetable);

	while(!it.isAtEnd())
	{
		if(it.retrieve().getHour() < h1)
		{
			last = it.retrieve().getFilm();
			it.advance();
		}
		else
		{
			if(it.retrieve().getHour() == h1)
				return it.retrieve().getFilm();
			else
			{
				return last;
			}
		}
	}
}


//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
	bool res;

	// TODO

	return res;
}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
	unsigned roomToUse = 0;

	// TODO

	return roomToUse;
}






