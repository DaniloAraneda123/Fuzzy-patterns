

#include <stdio.h>
#include <iostream>
#include "ItemFrecuente.h"
#include <map>
//#include <fstream>

using namespace std;

int main()
{


	// Constructor
	//ItemFrecuente itemfrecuente = ItemFrecuente(8, 3);


	int fila = 4;
	int col = 4;
	std::string** matriz = new std::string* [4];
	matriz[0] = new std::string[4];
	matriz[1] = new std::string[4];
	matriz[2] = new std::string[4];
	matriz[3] = new std::string[4];
	matriz[0][0] = "Soleado";
	matriz[0][1] = "bajo";
	matriz[0][2] = "viejo";
	matriz[0][3] = "si";
	matriz[1][0] = "Soleado";
	matriz[1][1] = "bajo";
	matriz[1][2] = "joven";
	matriz[1][3] = "si";
	matriz[2][0] = "Soleado";
	matriz[2][1] = "medio";
	matriz[2][2] = "alto";
	matriz[2][3] = "no";
	matriz[3][0] = "nublado";
	matriz[3][1] = "bajo";
	matriz[3][2] = "joven";
	matriz[3][3] = "no";



	// Crear ItemFrecuente
	ItemFrecuente frecuente1(4, 4, matriz, 0, 0);


	//frecuente1.obtenerSupport(frecuente1.items);
	frecuente1.obtenerItemFrecuentes();
	/*
	map<set<string>, float>::iterator it;
	map<set<string>, set<string>>::iterator it2;
	map<map<set<string>, set<string>>, float>::iterator it3;
	map<set<string>, set<string>>::iterator it4;

	for (int i = 0; i < frecuente1.item_frecuentes.size(); i++) {
		for (it = frecuente1.item_frecuentes.at(i).begin(); it != frecuente1.item_frecuentes.at(i).end(); it++) {
			for (const auto& e: it->first) {
				cout << e << " - " ;
			}
			cout << "         frecuencia: " << it->second;
			cout << "\n" << endl;
		}
	}
	*/
	frecuente1.obtenerReglas();










	map<set<string>, float>::iterator it;
	map<set<string>, set<string>>::iterator it2;
	map<map<set<string>, set<string>>, float>::iterator it3;
	map<set<string>, set<string>>::iterator it4;

	for (it2 = frecuente1.reglas.begin(); it2 != frecuente1.reglas.end(); it2++) {
		for (const auto& e : it2->first) {
			cout << e << "   ";
		}
		cout << "--------->";
		for (const auto& d : it2->second) {
			cout << d << "   ";
		}
		cout << "\n" << endl;
	}
	/*
	for (it3 = frecuente1.reglas_confianza.begin(); it3 != frecuente1.reglas_confianza.end(); it3++) {
		for (it4 = it3.first.begin(); it4 != it3->first.end(); it4++) {
			for (it2 = it4->first.begin(); it2 != it2->second; it2++) {

			}

		}
		for (const auto& e : it3) {
			cout << e << "   ";
		}
		cout << "--------->";
		for (const auto& d : it3) {
			cout << d << "   ";
		}
		cout << "\n" << endl;
	}
	*/
	// Obtenemos archivo de prueba
	//std::ifstream file;
	//file.open("prueba2.csv");
	//if (!file.is_open()) std::cout << "ERROR: No se pudo abrir el archivo" << std::endl;

	std::string str;
	//while (std::getline(file, str)) {
		//std::cout << str << "\n";
	//}
	//file.close();
	

}