#pragma once
#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include "Datum.h"

const long double G = 6.671911E-11;					// GRAVITATIONSKONSTANTE m³/(kg*s²)6,67191
const long double M = 1.989E30;						// SONNENMASSE kg
const size_t Dt = 86400;							// Dt ist ein Tag in Sekunden


class Planet : protected Datum {

private:
	long double a, r;											// große Halbachse, r(radius)...Abstand zur Sonne zum Ephimeridendatum
	double epsilon, alpha;										// num. Exzentrizität, Winkel(alpha) zur gr. Halbachse zum Ephimeridendatzum 
	unsigned int init_T;
	std::string pName;											// Name Planet
	Datum d_ephim;												// Ephemeridendatum - Objekt wird initialisiert mit dem Datum der Ephemeridenwerte (.CSV-Datei)

	struct P_DatenXY {
		long double pX, pY, vX, vY, r_SP, d_str=0;		
	} actPDat;
		
public:
	static int deltaT;
	
	Planet(std::string const, long double, long double, double, double, Datum);	//Konstruktor
	
	void init_Pbahn(void);														//Initialisierung der Planetenposition und Berechnung der Bahndaten durch Iteration
	std::vector<long double> process_bahnCalc(Datum );							//Methode zur Berechnung der Planetendaten zu einem gew. Zeitpunkt
	std::vector<long double> process_bahnCalc(void);							//Überladen d. obigen Methode ohne Formalparameter
	unsigned int diffTime(Datum);												//zwei Datumobjekte werden miteinander verglichen und die Differenz in Tagen zurückgegeben

};

#endif


