// solarSystem.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "Menu.h"

using namespace std;


int main() {
	Menu myMenu;						
	myMenu.callMenu();				// Aufruf der Menüfunktion, um Programm einzuleiten
	return 0;
}
