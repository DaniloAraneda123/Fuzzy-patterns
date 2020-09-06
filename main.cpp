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
#include <cstdlib>

using namespace std;

int main()
{
	string ruta;
	int opcion = -1;
	int manual = -1;
	int numero_clusters = 3;
	int iteraciones_fuzzy = 100;
	double error = 0.001;
	double borrosidad = 3;
	double grado_verdad = 0.3;
	double significancia = 1;
	string variable_clase = "Flor";
	double minimo_support = 0.25;
	double minimo_confianza = 0.25;
	bool porDefecto = true;
	
	cout << "Ingrese el nombre del archivo csv: ";
	cin >> ruta;
	system("cls");

	ifstream myFile(ruta);

	//if (!myFile.is_open()) throw runtime_error("No se pudo abrir el archivo");
	cout << "Ingrese el algoritmo que desea realizar: " << endl;
	cout << "\n" << endl;
	cout << "1)Fuzzy C-Means " << endl;
	cout << "2)Fuzzy ID3 " << endl;
	cout << "3)Fuzzy A-Priori " << endl;
	cout << "4)Todos " << endl;
	cout << "\n";
	cout << "0)Salir" << endl;

	cin >> opcion;
	system("cls");
	bool fc = false;
	bool id = false;
	bool ap = false;

	if (opcion == 1) {
		fc = true;
		cout << "Ingrese el tipo de entrenamiento: " << endl;
		cout << "\n" << endl;
		cout << "1)Automatico " << endl;
		cout << "2)Manual " << endl;
		cout << "\n";
		cout << "0)Salir" << endl;
		cin >> manual;
		system("cls");
		if (manual == 2) {
			cout << "Ingrese numero de clusters     : " ;
			cin >> numero_clusters;
			cout << "Ingrese numero de iteraciones  : " ;
			cin >> iteraciones_fuzzy;
			cout << "Ingrese error                  : " ;
			cin >> error;
			cout << "Ingrese borrosidad             : " ;
			cin >> borrosidad;
		}
	}
	if (opcion == 2) {
		id = true;
		cout << "Ingrese el tipo de entrenamiento: " << endl;
		cout << "\n" << endl;
		cout << "1)Automatico " << endl;
		cout << "2)Manual " << endl;
		cout << "\n";
		cout << "0)Salir" << endl;
		cin >> manual;
		system("cls");
		if (manual == 2) {
			porDefecto = false;
			cout << "Ingrese umbral de verdad       : " ;
			cin >> grado_verdad;
			cout << "Ingrese umbral de significancia: " ;
			cin >> significancia;
			cout << "Ingrese nombre de clase        : " ;
			cin >> variable_clase;
		}
	}
	if (opcion == 3) {
		ap = true;
		cout << "Ingrese el tipo de entrenamiento: " << endl;
		cout << "\n" << endl;
		cout << "1)Automatico " << endl;
		cout << "2)Manual " << endl;
		cout << "\n";
		cout << "0)Salir" << endl;
		cin >> manual;
		system("cls");
		if (manual == 2) {
			porDefecto = false;
			cout << "Ingrese umbral support         : " ;
			cin >> minimo_support;
			cout << "Ingrese umbral de confianza    : " ;
			cin >> minimo_confianza;
			cout << "\n";
		}
	}
	if (opcion == 4) {
		fc = true;
		id = true;
		ap = true;
		cout << "Ingrese el tipo de entrenamiento: " << endl;
		cout << "\n" << endl;
		cout << "1)Automatico " << endl;
		cout << "2)Manual " << endl;
		cout << "\n";
		cout << "0)Salir" << endl;
		cin >> manual;
		system("cls");
		if (manual == 2) {
			porDefecto = false;
			cout << "Ingrese numero de clusters     : " ;
			cin >> numero_clusters;
			cout << "Ingrese numero de iteraciones  : " ;
			cin >> iteraciones_fuzzy;
			cout << "Ingrese error                  : " ;
			cin >> error;
			cout << "Ingrese borrosidad             : " ;
			cin >> borrosidad;
			cout << "Ingrese umbral de verdad       : " ;
			cin >> grado_verdad;
			cout << "Ingrese umbral de significancia: " ;
			cin >> significancia;
			cout << "Ingrese nombre de clase        : " ;
			cin >> variable_clase;
			cout << "Ingrese umbral support         : " ;
			cin >> minimo_support;
			cout << "Ingrese umbral de confianza    : " ;
			cin >> minimo_confianza;
			cout << "\n";

		}
	}
	if (porDefecto) {
			numero_clusters = 3;
			iteraciones_fuzzy = 100;
			error = 0.001;
			borrosidad = 3;
			grado_verdad = 0.2;
			significancia = 1;
			variable_clase = "Flor";
			minimo_support = 0.25;
			minimo_confianza = 0.25;
			
	}


			
	

	//map< vector<string>, vector<vector<string>>> d = leerDatos("ComunasFCM.csv", ';');
	//crearReporte(" ", d, true, false, false, 2, 100, 0.001, 3.0, 0.9, 0.5, "Comuna", 0.8, 0);

	//crearReporte(" ", d, false, false, true, 2, 100, 0.05, 3.0, 0.5, 0.5, "datosCom.txt", 0.1, 0);

	//map< vector<string>, vector<vector<string>>> datos = leerDatos("datosCom.txt", ';');
	if (opcion != 0) {
		system("cls");
		map< vector<string>, vector<vector<string>>> datos = leerDatos(ruta, ';');

		crearReporte(" ", datos, fc, id, ap, numero_clusters, iteraciones_fuzzy, error, borrosidad, grado_verdad, significancia, variable_clase, minimo_support, minimo_confianza); // iteraciones, error, borrosidad, verdad, significancia, minimo support, confianza
	}
	return 0;
}
