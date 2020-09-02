//#pragma warning (disable : 4996)
//
//#include <stdio.h>
//#include <iostream>
//#include "FuzzyCMeans.h"
//#include "Dataset.h"
//#include "FuzzyID3.h"
//#include <set>
//#include "TreeNodo.h"
//#include <stdlib.h>
//#include"Utils.h"
//#include <iomanip>
//#include <map>
//#include "ItemFrecuente.h"
//#include "Comunicacion.h"
//
//
//
//using namespace std;
//
//
//int main()
//{
//
//	
///*
//	// Declaracion de hiperparametros
//
//	bool fuzzyCMeans;
//	int fuzzyCMeans_opcion;
//	bool fuzzyID3;
//	bool fuzzyItemFrecuente = true;
//
//	// Recibe nombre de archivo
//	string ruta;
//	cout << "Ingrese el nombre del archivo en el que desea buscar patrones: ";
//	cin >> ruta;
//
//	// Verifica si existe el archivo
//	ifstream myFile(ruta);
//	if (!myFile.is_open()) throw runtime_error("No se pudo abrir el archivo");
//
//	// Pregunta por los tipos de algoritmo que desea utilizar
//	cout << "Desea utilizar fuzzy-cmeans: ";
//	cout << "\n " << endl;;
//	cout << "Si: 1 ";
//	cout << "No: 0 ";
//	cin >> fuzzyCMeans_opcion;
//	if (fuzzyCMeans_opcion == 1) {
//			cout << "Desea detectar patrones con valores predeterminados fuzzy-cmeans: ";
//
//		}
//
//	cout << "\n " << endl;;
//	cout << "Si: 1 ";
//	cout << "No: 0 ";
//	cin >> fuzzyCMeans_opcion;
//	
//
//
//	
//
//
//
//
//	
//    // Corroborar si el archivo existe
//
//*/
//
//	map< vector<string>, vector<vector<string>>> datos = leerDatos("iris.csv", ';');
//
//
//  //crearReporte(" ", datos, true, true, true, 3, 100, 0.05, 3.0, 0.5, 0.5, "Flor", 0.8, 0);
//	crearReporte(" ", datos, false, true, false, 3, 100, 0.05, 3.0, 1, 0, "Flor", 0.8, 0);
//
//	return 0;
//}
