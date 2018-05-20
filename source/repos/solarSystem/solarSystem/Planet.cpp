#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cmath>
#define PI 3.1415926535

#include"Planet.h"
#include <iomanip>
using namespace std;

int Planet::deltaT = 0;

//pBahn::pBahn() { }
//pBahn::pBahn(long double aChse ) { }
//pBahn::pBahn(long double aChse, long double rad) { }
//pBahn::pBahn(long double aChse, long double rad, double eXzentr) { }
//pBahn::pBahn(long double aChse, long double rad, double eXzentr, double echtAnom) : a(aChse), r(rad), epsilon(eXzentr), alpha(echtAnom) { }
Planet::Planet(std::string const n, long double aChse, long double rad, double echtAnom, double eXzentr, Datum initD) 
		: a(aChse), r(rad), epsilon(eXzentr), alpha(echtAnom), pName(n), d_ephim(initD)   {
		init_T = this->diffTime(initD);
		this->init_Pbahn();
}

void Planet::init_Pbahn(void) {
	long double  x0, y0, x_neu, y_neu, r_neu, ax_neu, ay_neu, m_T;
	long double e=a*epsilon;																// e...Exzentrizität
	long double b=sqrt(a*a-e*e);															// b...kleine Halbachse
																							
	if(pName == "Erde") {																	// Anfangskoordinaten zum Ephemeridendatum
		x0 = -e;																			// f. Ausnahmefall Erde
		y0 = b;																				
		r=sqrt(x0*x0+y0*y0);
	}else if(pName == "Uranus") {															// Spezialfall für Uranus: Planet hat einen anderen Brennpunkt
		x0 = 3.000538332E12;
		y0 = -1.829951399E11;
		r=sqrt(x0*x0+y0+y0);
	}else {																	
		x0 = r * cos(alpha * PI / 180);														// Anfangskoordinaten zum Ephemeridendatum allgemein															
		y0 = r * sin(alpha * PI / 180);
	}
																															
	if(pName == "Uranus") {
		m_T = b*(x0-e)/(a*sqrt(a*a-pow((x0-e),2.0)));										// Steigung für Ausnahmefall Uranus	
	}else { m_T = (y0>0) ? ( -b*(x0+e)/(a*sqrt(a*a-pow((x0+e),2.0))) ) : ( b*(x0+e)/(a*sqrt(a*a-pow((x0+e),2.0))) ); }		// Steigung der Tangente der Ellipse
																															// beim Punkt( x0,y0 )
	long double vx0 = sqrt(G*M*(2/r-1/a))*(sqrt(1/(m_T*m_T + 1)));															// Berechnung der Anfangsgeschwindigkeiten
	long double vy0 = sqrt( (G*M*(2/r-1/a)-pow(vx0, 2.0)) );																// durch Vis - Viva Gleichung: v = sqrt(G*M*(2/r-1/a))

	if(pName == "Uranus") {
		vx0 = (y0>0) ? -vx0 : vx0;											// Vorzeichen Startwerte f. Uranus
		vy0 = (x0<e) ? -vy0 : vy0;											
	}else {																	// Vorzeichen Startwerte allgemein
		vx0 = (y0>0) ? -vx0 : vx0;
		vy0 = (x0<-e) ? -vy0 : vy0;
	}
	long double ax0 = (-G*M)*x0/pow(r,3.0);																
	long double ay0 = (-G*M)*y0/pow(r,3.0);

	long double vx_dthlb = vx0 + ax0*Dt/2;									// Einleitungsschritt 
	long double vy_dthlb = vy0 + ay0*Dt/2;									// für Iterationsverfahren
	long double x_alt = x0;																												
	long double y_alt = y0;

	for(int d=0; d<init_T; ++d) {											// Halbschrittverfahren durch Iteration
		x_neu = x_alt + vx_dthlb * Dt;
		y_neu = y_alt + vy_dthlb * Dt;
		r_neu = sqrt(x_neu * x_neu + y_neu * y_neu);

		ax_neu = (-G * M) * x_neu / pow(r_neu, 3.0);
		ay_neu = (-G * M) * y_neu / pow(r_neu, 3.0);

		vx_dthlb = vx_dthlb + ax_neu * Dt;
		vy_dthlb = vy_dthlb + ay_neu * Dt;

		x_alt = x_neu;
		y_alt = y_neu;

		//cout << "Defaultfloat: " << defaultfloat << x_alt << " , " << y_alt << "\t\t\t";
		//cout << fixed << (x_alt) << ", " << (y_alt) << endl;
	}
	//cout << x_neu << ", " << y_neu << endl;
	actPDat.pX=x_alt;
	actPDat.pY=y_alt;
	actPDat.vX=vx_dthlb;
	actPDat.vY=vy_dthlb;
}

std::vector<long double> Planet::process_bahnCalc(Datum datX) {
	long double x_alt = actPDat.pX, y_alt = actPDat.pY, vx_dthlb = actPDat.vX, vy_dthlb = actPDat.vY;	// Übernahme der Planetendaten von P_DatenXY
	long double x_neu, y_neu, r_neu=0, ax_neu, ay_neu; 
	deltaT = diffTime(datX);
	vector<long double> pDaten(6);																		// Rückgabecontainer
	
	for(int d=0; d<deltaT; ++d) {																		// Halbschrittverfahren durch Iteration
		
		x_neu = x_alt + vx_dthlb * Dt;
		y_neu = y_alt + vy_dthlb * Dt;
		r_neu = sqrt(x_neu * x_neu + y_neu * y_neu);

		ax_neu = (-G * M) * x_neu / pow(r_neu, 3.0);
		ay_neu = (-G * M) * y_neu / pow(r_neu, 3.0);

		vx_dthlb = vx_dthlb + ax_neu * Dt;
		vy_dthlb = vy_dthlb + ay_neu * Dt;

		actPDat.d_str += sqrt( pow((x_neu-y_neu), 2.0) + pow((y_neu - y_alt), 2.0 ));					// Berechnung der zurückgelegten Strecke (Meter)

		x_alt = x_neu;
		y_alt = y_neu;
	}
	actPDat.pX=x_alt;
	actPDat.pY=y_alt;
	actPDat.vX=vx_dthlb;
	actPDat.vY=vy_dthlb;
	actPDat.r_SP=r_neu;
	return pDaten = {actPDat.pX, actPDat.pY, actPDat.r_SP, actPDat.vX, actPDat.vY, actPDat.d_str};
}

std::vector<long double> Planet::process_bahnCalc() {
	long double x_alt = actPDat.pX, y_alt = actPDat.pY, vx_dthlb = actPDat.vX, vy_dthlb = actPDat.vY;	// Übernahme der Planetendaten von P_DatenXY
	long double x_neu, y_neu, r_neu, ax_neu, ay_neu;
	vector<long double> pDaten(6);																		// Rückgabecontainer
		
	for(int d=0; d<deltaT; ++d) {																		// Halbschrittverfahren durch Iteration
		
		x_neu = x_alt + vx_dthlb * Dt;
		y_neu = y_alt + vy_dthlb * Dt;
		r_neu = sqrt(x_neu * x_neu + y_neu * y_neu);

		ax_neu = (-G * M) * x_neu / pow(r_neu, 3.0);
		ay_neu = (-G * M) * y_neu / pow(r_neu, 3.0);

		vx_dthlb = vx_dthlb + ax_neu * Dt;
		vy_dthlb = vy_dthlb + ay_neu * Dt;

		actPDat.d_str += sqrt( pow((x_neu-y_neu), 2.0) + pow((y_neu - y_alt), 2.0 ));

		x_alt = x_neu;
		y_alt = y_neu;		
		
	}
	actPDat.pX=x_alt;
	actPDat.pY=y_alt;
	actPDat.vX=vx_dthlb;
	actPDat.vY=vy_dthlb;
	actPDat.r_SP=sqrt(x_alt * x_alt + y_alt * y_alt);
	return pDaten = {actPDat.pX, actPDat.pY, actPDat.r_SP, actPDat.vX, actPDat.vY, actPDat.d_str};	
}

unsigned int Planet::diffTime(Datum date) {						
	unsigned int bisEnde=0, bisDatum=0, sumJahre=0, sumDays=0;
	vector<unsigned short> days1(12), days2(12);
	
	for(unsigned short i=0; i<=6; ++i) {
		days1[i] = (i%2 == 0) ? 31 : 30;
		days1[1] = (istSchaltjahr(actdate.aktJahr)) ? 29 : 28;
		days2[i] = (i%2 == 0) ? 31 : 30;
		days2[1] = (istSchaltjahr(date)) ? 29 : 28;		
	}

	for(unsigned short i=7; i<12; ++i) {
		days1[i] = (i%2 == 0) ? 30 : 31;
		days2[i] = (i%2 == 0) ? 30 : 31;
	}
	
	if( (actdate.aktJahr < date.getJahr()) ){
		for (unsigned short i = (actdate.aktMonat-1); i<12; ++i) {
			bisEnde += ( i==(actdate.aktMonat-1) ) ? (days1[i]-actdate.aktTag) : days1[i]; 
		}

		for (unsigned short i=0; i <= (date.getMonat()-1); ++i) {
			bisDatum += ( i==(date.getMonat()-1) ) ? date.getTag() : days2[i];
		}

		for (unsigned int i=(actdate.aktJahr+1); i<date.getJahr(); ++i) {
			sumJahre += (istSchaltjahr(i)) ? 366 : 365;
		} sumDays = bisEnde + sumJahre + bisDatum;
		
	}else if (actdate.aktJahr > date.getJahr()) {
		for (unsigned short i = (date.getMonat()-1); i<12; ++i) {
			bisEnde += ( i==(date.getMonat()-1) ) ? (days1[i]-date.getTag()) : days1[i]; 
		}

		for (unsigned short i=0; i <= (actdate.aktMonat-1); ++i) {
			bisDatum += ( i==(actdate.aktMonat-1) ) ? actdate.aktTag : days2[i];
		}

		for (unsigned int i=(date.getJahr()+1); i<actdate.aktJahr; ++i) {
			sumJahre += (istSchaltjahr(i)) ? 366 : 365;
		} sumDays = bisEnde + sumJahre + bisDatum;
		
	} else if (actdate.aktJahr == date.getJahr()) {
		if(actdate.aktMonat < date.getMonat()) {
			bisEnde = days1[actdate.aktMonat-1]-actdate.aktTag;
			for(unsigned short i = (actdate.aktMonat); i < (date.getMonat()-1); ++i) { sumDays += days1[i]; }
			bisDatum = date.getTag();
			sumDays = bisEnde+sumDays+bisDatum;
		}else if(actdate.aktMonat > date.getMonat()) {
			bisEnde = days1[date.getMonat()-1]-date.getTag();
			for(unsigned int i = date.getMonat(); i < (actdate.aktMonat-1); ++i) { sumDays += days1[i]; }
			bisDatum = actdate.aktTag;
			sumDays = bisEnde+sumDays+bisDatum;
		}else if(actdate.aktMonat == date.getMonat()) { sumDays = (actdate.aktTag<date.getTag()) ? (date.getTag()-actdate.aktTag) : (actdate.aktTag - date.getTag()); }
		
	}	
	return sumDays;
}







