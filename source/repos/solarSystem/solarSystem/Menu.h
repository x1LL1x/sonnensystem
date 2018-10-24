#pragma once
#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <iomanip>
#include <vector>
#include "Datum.h"
#include "Planet.h"

class Menu{
	Datum heute, zeitPtX;
	std::vector< std::vector<std::string> > initTables; 
	std::string inpfile1, outfile, p_Name;
	long double gr_hA, r_Abst;
	double e_Anom, n_Exz;
	//int cnt_zl;


public:
	Menu();
	
	void callMenu();
	void getData();										//Methode geht Zeile für Zeile durch eine .CSV-Datei und speichert die Werte in einem 2x2 Vektor --> einlesen
	void setInitData(int);								//Initialwerte für einzelne Planeten den Eingangsparametern (gr. Halbachse, usw...) zuweisen
	void putData(std::vector<long double> const);				//Methode zum Schreiben in .CSV-Datei
};
#endif

