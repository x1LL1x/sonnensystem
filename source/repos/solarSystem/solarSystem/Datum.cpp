#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "Datum.h"
using namespace std;

actDate Datum::actdate;				//Memberdeklaration von statischem Objekt actdate (Struktur actDate)

Datum::Datum() : Jahr(0), Monat(0), Tag(0) {
	setactualDate();
	Jahr = actdate.aktJahr;
	Monat = actdate.aktMonat;
	Tag = actdate.aktTag;
}

Datum::Datum(int y, short m, short d) {
	this->setDate(y, m, d);
}

void Datum::setactualDate() {
	time_t temp =time(0);			// die Funktion mit dem Typ time_t überdeckt einen long-Wert und liefert die Anzahl der Sekunden seit dem 1.1.1970
	struct tm *actualtime;			// Zeiger auf die Struktur namens tm aus <time.h>
	actualtime = localtime(&temp);
	actdate.aktJahr = actualtime->tm_year+1900;
	actdate.aktMonat = actualtime->tm_mon+1;
	actdate.aktTag = actualtime->tm_mday;	
}

bool Datum::setDate(int year, unsigned short month, unsigned short day) {								
	
	if(year>=2010 && (year%4==0 && (year%400==0 || year%100 != 0)) && (0<month && month<=12)) {			// aktuelles Jahr ist Schaltjahr
		if(month==2 && (0<day && day<=29)) {
			Jahr=year;
			Monat=month;
			Tag=day;
		}else if(month%2==1 && month<=7 && (0<day && day<=31)) {
			Jahr=year;
			Monat=month;
			Tag=day;			
		}else if(month%2==0 && month<=6 && (0<day && day<=30)) {
			Jahr=year;
			Monat=month;
			Tag=day;
		}else if(month%2==1 && month>=9 && (0<day && day<=30)) {
			Jahr=year;
			Monat=month;
			Tag=day;			
		}else if(month%2==0 && month>=8 && (0<day && day<=31)) {
			Jahr=year;
			Monat=month;
			Tag=day;
		}else return false;			
	}else if (year>=2010 && (0<month && month<=12)) {																	// aktuelles Jahr ist kein Schaltjahr
		if(month == 2 && (0<day && day<=28)) {
			Jahr=year;
			Monat=month;
			Tag=day;			
		}else if(month%2==1 && month<=7 && (0<day && day<=31)) {
			Jahr=year;
			Monat=month;
			Tag=day;
		}else if(month%2==0 && month<=6 && (0<day && day<=30)) {
			Jahr=year;
			Monat=month;
			Tag=day;
		}else if(month%2==1 && month>=9 && (0<day && day<=30)) {
			Jahr=year;
			Monat=month;
			Tag=day;			
		}else if(month%2==0 && month>=8 && (0<day && day<=31)) {
			Jahr=year;
			Monat=month;
			Tag=day;
		}else return false;
	}else return false;
	return true;
} 

int Datum::getJahr() const {
	return 	this->Jahr;
}

unsigned short Datum::getMonat() const {
	return this->Monat;
}

unsigned short Datum::getTag() const {
	return this->Tag;
}

void Datum::printDate(string wDate) const {
	string date=wDate;
	if(date=="actual") {
		cout << setfill('0') << setw(2) << actdate.aktTag << ". " << setw(2) << actdate.aktMonat << ". " << actdate.aktJahr << endl;	// Terminalausgabe des aktuellen Datums
	}else if(date=="progress"){
		cout << setfill('0') << setw(2) << Tag << ". " << setw(2) << Monat << ". " << Jahr;				// Terminalausgabe des Datums in der Zukunft
	}else cout << " ungültiger Funktionsparameter! " << endl;
}

bool Datum::istSchaltjahr(actDate now) const {
	return now.aktJahr % 4 == 0 && (now.aktJahr % 100 != 0 || now.aktJahr % 400 == 0);	
}

bool Datum::istSchaltjahr(Datum date) const {
	return date.Jahr % 4 == 0 && (date.Jahr % 100 != 0 || date.Jahr % 400 == 0);	
}

bool Datum::istSchaltjahr(unsigned int j) const {
	return j % 4 == 0 && (j % 100 != 0 || j % 400 == 0);	
}





