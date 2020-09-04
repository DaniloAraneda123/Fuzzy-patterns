#include <stdio.h>
#include <iostream>
#include "FuzzyCMeans.h"
#include "Dataset.h"
#include "FuzzyID3.h"
#include <set>
#include "TreeNodo.h"
#include <stdlib.h>
#include"Utils.h"
#include <iomanip>
#include <map>
#include "ItemFrecuente.h"
#include "Comunicacion.h"

using namespace std;

int main()
{
	map< vector<string>, vector<vector<string>>> d = leerDatos("ComunasFCM.csv", ';');
	//crearReporte(" ", d, true, false, false, 2, 100, 0.001, 3.0, 0.9, 0.5, "Comuna", 0.8, 0);

	crearReporte(" ", d, false, false, true, 2, 100, 0.05, 3.0, 0.5, 0.5, "Comuna", 0.3, 0);

	map< vector<string>, vector<vector<string>>> datos = leerDatos("datosCom.txt", ';');
	crearReporte(" ", datos, false, true, false, 2, 100, 0.05, 3.0, 0.1, 1, "comuna", 0.8, 0);

	return 0;
}
