#pragma once
#ifndef DATUM_H
#define DATUM_H
#include <string>
#include <ctime>

struct actDate {
	int aktJahr;
	short aktMonat, aktTag;
};

class Datum {
private:
	int Jahr;
	short Monat, Tag;

public:
	static actDate actdate;

	Datum();
	Datum(int, short, short);
	
	static void setactualDate();
	bool setDate(int, unsigned short, unsigned short);	
	
	int getJahr() const;
	unsigned short getMonat() const ;
	unsigned short getTag() const;
	
	bool istSchaltjahr(actDate) const;								// function-Overloading von istSchaltjahr
	bool istSchaltjahr(Datum) const;
	bool istSchaltjahr(unsigned int) const;

	void printDate(std::string) const;
};

#endif

