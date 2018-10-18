#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Menu.h"
using namespace std;

Menu::Menu() { 			// Konstruktor f. Menu
	this->getData();	// Initialisierung d. 2-Dim Vektoren
	this->heute.setactualDate();
}

void Menu::callMenu() {
	Datum const ephem(2017, 3, 5);									//, heute, zeitPtX;
	vector<long double> v_enrtyPl(6), v_wahlPl(6);
	int menRoll;
		
	do{	//************* Menüeinstieg *************
		cout<<"\n<----- Simulation d. Sonnensystems - 2D -----> \n\n";
		cout<<"Bitte wählen Sie einen Planeten durch Eingabe der entsprechenden Ziffer: \n";
		cout<<"\t[1]:"<<initTables[1][0]<<"\t [2]:"<<initTables[2][0]<<"\t [3]:"<<initTables[3][0]<<"\n\t[4]:"<<initTables[4][0]<<"\t [5]:"<<initTables[5][0]
		<<"\t [6]:"<<initTables[6][0]<<"\n\t[7]:"<<initTables[7][0]<<"\t [8]:"<<initTables[8][0]<<"\t [9]:Pluto"<<"\n\t[0]:Programmende" << endl;
		cout << ": "; menRoll=-1;														// Defaultwert von menRoll auf -1 (ungültig) setzen
		cin >> menRoll;																	// Variable für Auswahlmenü und Datensatz
		if(0<=menRoll && menRoll<=9) {
			setInitData(menRoll);														// Datensatz aus .CSV-Datei auswählen und den Eigenschaften von Menu.h zuweisen
			cout << "\nDatum (heute):\t";
			Planet::deltaT=0;
			this->zeitPtX.setDate(Datum::actdate.aktJahr, Datum::actdate.aktMonat, Datum::actdate.aktTag);
			heute.printDate("actual"); cout<<endl;
		}
		switch (menRoll) {
		case 1: cout << "Merkur: " << endl;
			cout << "Groesse (Durchmesser): 4878km \nMasse: 3,3022*10^23kg \nmittl.Entfernung zur Sonne: " 
			<<  gr_hA/1000 <<"km\nSchwerkraft: 3,7 m/s^2" << "\nRotationsperiode: 58d 15h 36min" << endl; 
			break;
		case 2: cout << "Venus: " << endl;
			cout << "Groesse (Durchmesser): 12.103,6km \nMasse: 4,869*10^24kg \nmittl.Entfernung zur Sonne: " 
			<<  gr_hA/1000 <<"km\nSchwerkraft: 8,87 m/s^2" << "\nRotationsperiode: 243d 27min" << endl; 
			break;
		case 3: cout << "Erde: " << endl;
			cout << "Groesse (Durchmesser): 12.756,32km \nMasse: 5,974*10^24kg \nmittl.Entfernung zur Sonne: " 
			<<  gr_hA/1000 <<"km\nSchwerkraft: 9,81 m/s^2" << "\nRotationsperiode: 23h 56min 4,1s\nMonde: 1(Mond)" << endl;
			break;
		case 4: cout << "Mars: " << endl;
			cout << "Groesse (Durchmesser): 6.792,4km \nMasse: 6,419*10^23kg \nmittl.Entfernung zur Sonne: " 
			<<  gr_hA/1000 <<"km\nSchwerkraft: 3,69 m/s^2" << "\nRotationsperiode: 24h 37min 22s\nMonde: 2 (Phobos und Deimos)" << endl;
			break;
		case 5: cout << "Jupiter: " << endl;
			cout << "Groesse (Durchmesser): 142.984km \nMasse: 1,899*10^27kg \nmittl.Entfernung zur Sonne: " 
			<<  gr_hA/1000 <<"km\nSchwerkraft: 24,79 m/s^2" << "\nRotationsperiode: 9h 55min 30s\nAnzahl d. Monde: 69" << endl;
			break;
		case 6: cout << "Saturn: " << endl ;
			cout << "Groesse (Durchmesser): 120.536km \nMasse: 5,685*10^26kg \nmittl.Entfernung zur Sonne: " 
			<<  gr_hA/1000 <<"km\nSchwerkraft: 10,44 m/s^2" << "\nRotationsperiode: 10h 33min\n Anz. d. Monde: 62 + Ringsystem " << endl;
			break;
		case 7: cout << "Uranus: " << endl;
			cout << "Groesse (Durchmesser): 51.118km \nMasse: 8,683*10^25kg \nmittl.Entfernung zur Sonne: " 
			<<  gr_hA/1000 <<"km\nSchwerkraft: 8,87 m/s^2" << "\nRotationsperiode: 17h 14min 24s\nAnz. d. Monde: 27 + Ringsystem" << endl;
			break;
		case 8: cout << "Neptun: " << endl ;
			cout << "Groesse (Durchmesser): 49.528km \nMasse: 1,0243*10^26kg \nmittl.Entfernung zur Sonne: " 
			<<  gr_hA/1000 <<"km\nSchwerkraft: 11,15 m/s^2" << "\nRotationsperiode: 15h 57min 59s\Anz. d. Monde: 14 + Ringsystem" << endl;
			break;
		case 9: cout << "Pluto:";
			cout << "Groesse (Durchmesser): 2374km \nMasse: 1,303*10^22kg \nmittl.Entfernung zur Sonne: 5,906376*10^9km"; 
			cout <<"\nSchwerkraft: 0,62 m/s^2" << "\nRotationsperiode: 6d 9h 17min 34s\nAnz. d. Monde: 5" << endl;
			cout << "\nPuto's Bahndaten können aufgrund seiner extremen Bahnneigung(17,1Grad) in einem 2D-Modell nicht mehr\n";
			cout << "realistisch dargestellt werden, bitte treffen Sie eine andere Wahl.\n" << endl;
			break;
		case 0: 
			break;
		default: cout << "ungueltige Eingabe! - Programm wird beendet.\n" << endl;
			break;
		}
		if(menRoll==0){ break; }
		else if(menRoll==9){continue;}
		else if (1<=menRoll && menRoll<=8){
			Planet entry_Planet(p_Name, gr_hA, r_Abst, e_Anom, n_Exz, ephem);	// Planet-Objekt erstellen und mit den Daten aus dem .CSV-File initialisieren.
			v_enrtyPl = entry_Planet.process_bahnCalc();							// einstiegs Vektor mit den Daten von entry_Planet-Objekt belegen
			cout << "\nheutige Position :\nX:" << v_enrtyPl[0] << "  Y:" << v_enrtyPl[1] << "\nderzeitige Entfernung zur Sonne: " << v_enrtyPl[2] << " km" << endl;
			cout << "momentane Geschwindigkeit: " << sqrt( pow(v_enrtyPl[3], 2.0) + pow(v_enrtyPl[4], 2.0) )<<"m/s"<<endl;;
			putData(v_enrtyPl);
			
			cout << "\nBitte Datum fuer neue Position eingeben (yy, mm, dd) ";  // , oder Programm beenden mit X: ";			//int eXit; cin >> eXit;
			cout << "\n\nJahr: "; int yy; cin >> yy; 
			cout << "\Monat: "; short mm; cin >> mm;
			cout << "\Tag: "; short dd; cin >> dd;
			zeitPtX.setDate(yy, mm, dd);
			v_enrtyPl = entry_Planet.process_bahnCalc(zeitPtX);					// Daten für neue Position berechnen und in v_entryPl speichern	
			cout << "\nneue Postition:\nX:" << v_enrtyPl[0] << "  Y:" << v_enrtyPl[1] << "\tEntfernung zur Sonne am "; 
			zeitPtX.printDate("progress"); cout << ": " << v_enrtyPl[2]/1000 << " km"<< endl;
			cout << "Anzahl der (Erd-)Tage von heute bis zum angegebenen Zeitraum: \t " << Planet::deltaT << " Tage." << endl;
			cout << "Die zurueckgelegte Strecke von heute bis zum eingegebenen Datum:  " << v_enrtyPl[5]/1000 << " km." << endl;
			cout << "Die Geschwindigkeit d. Planeten am: "; zeitPtX.printDate("progress"); cout<<": "<< sqrt(pow(v_enrtyPl[3], 2.0) + pow(v_enrtyPl[4], 2.0))<<"m/s"<<endl;
			putData(v_enrtyPl);
			do {
				cout << "\nSoll die Entfernung zu einem anderem Planeten berechnet werden? (y/n)";
				char quest; cin >> quest;
				if (quest == 'n') break;
				else if (quest == 'y') {
					int wahl;
					do {
						cout << "Bitte den Planeten wählen : [1]Pluto, [2]Venus,... usw.(siehe oben)\nWahl: ";
						cin >> wahl;
						if(wahl==menRoll) {cout << "\nPlanet wurde bereits ausgewählt: " << endl;}
						if(wahl==9) cout<<"Plutos Position kann nicht bestimmt werden! - Bitte eine andere Wahl treffen." << endl; continue;
					}while(wahl==menRoll);
					setInitData(wahl);														//anderen Planeten initialisieren
					Planet wahl_Planet(p_Name, gr_hA, r_Abst, e_Anom, n_Exz, ephem);		//neues Planetenobjekt erstellen für anderen Planeten
					v_wahlPl = wahl_Planet.process_bahnCalc();								//neue Bahnpositionen d. Planeten berechnen zum eingegebenen Datum
					cout << "\ndie Enfernung zum Planeten " << p_Name << " betraegt:    ";
					cout << sqrt(pow((v_enrtyPl[0] - v_wahlPl[0]), 2.0) + pow((v_enrtyPl[1] - v_wahlPl[1]), 2.0)) / 1000 << " km." << endl;
				}																							//else if (eXit=='X'){ break; }
				else {
					cout << "\nungueltige Option!" << endl;
					continue;
				}
			}while (1<=menRoll && menRoll<=9);
		}else { break; }
	}while( (menRoll!=0) && 1<=menRoll && menRoll<=9 ); 
}

void Menu::getData(){
	inpfile1 = "Planetendaten.csv";
	ifstream in(inpfile1);											// Input-Stream Objekt erzeugen
			
	if(in) {
		string zeile = "";
		while (getline(in, zeile)) {								// durch jede Zeile durchiterieren in datei1
			stringstream sep(zeile);
			string feld;
			vector<string> z;
			while(getline(sep, feld, ',')){ z.push_back(feld); }
			this->initTables.push_back(z);					
		}
	} in.close();
}

void Menu::setInitData(int x) {
	if (x==0){ exit(0);}
	else if (x==9){ return;}
	else{
	p_Name = initTables[x][0];
	gr_hA = stold(initTables[x][1]);
	r_Abst = stold(initTables[x][2]);
	e_Anom = stod(initTables[x][3]);
	n_Exz = stod(initTables[x][4]);
	}
}

//template <typename T>
void Menu::putData(vector<long double> vec) {
	outfile="planet_Positions.csv";
	ofstream outPt(outfile, ios_base::out | ios_base::app);
	
	//outPt.open( outfile, std::ios::out | ((cnt_zl) ? std::ios::app : std::ios::trunc));
	//for( ;first != last; ) {
	//	outPt << *first;
	//	if(first!=last) { outPt<<komma; }
	//}
	//for(int i=1; i<=cnt_zl; ++i) outPt<<"\n"; 
	outPt <<"\n"<< p_Name <<":"<< zeitPtX.getTag() <<"."<<zeitPtX.getMonat()<<"."<<zeitPtX.getJahr()<<" : ";
	for(const auto &o : vec) { outPt << o << "\t\t";}
	outPt.close();
}



 
