#include "ItemFrecuente.h"
//#include "Conjuntos.h"
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <ostream>
#include <fstream>


using namespace std;


ItemFrecuente::ItemFrecuente(int _nroAtributos, int _nroDatos, vector<vector<string>> datos, float _minimo_support, float _min_confianza)
{

	nroAtributos = _nroAtributos;
	nroDatos = _nroDatos;
	min_confianza = _minimo_support;
	minimo_support = _min_confianza;
	set<string> item;
	set<string> aux_set;
	set<string> aux_lista;

	for (int i = 0; i < datos.size(); i++) {
		for (int j = 0; j < datos[i].size(); j++) {
			item.insert(datos[i][j]);
			if (aux_set.find(datos[i][j]) == aux_set.end()) {
				items.push_back(item);
			}
			aux_lista.insert(datos[i][j]);
			aux_set.insert(datos[i][j]);
			item.clear();
		}
		lista_transaccion.push_back(aux_lista);
		aux_lista.clear();
		aux_set.clear();
	}
}
	void ItemFrecuente::guardarReglas(string ruta)
	{

		obtenerItemFrecuentes();

		cout << "Termino ItemFrecuente" << endl;
		obtenerReglas();

		cout << "Terimno ObtenerReglas" << endl;

		map<set<string>, set<string>>::iterator it2;
		ofstream archivo;
		archivo.open(ruta + "reglas_asociativas.txt");
		archivo << "Reglas asociativas" << "\n";
		for (it2 = reglas.begin(); it2 != reglas.end(); it2++) {
			archivo << "Si  ";
			for (const auto& e : it2->first) {
				archivo << e << "   ";
			}
			archivo << " entonces  ";
			for (const auto& d : it2->second) {
				cout << it2->second.size();
				cout << d << "   ";
			}
			archivo << "\n";
		}

				
		archivo.close();
	}



	float ItemFrecuente::obtenerSupportSet(set<string> conjunto) {

		float total_transacciones = float(lista_transaccion.size());
		float support = 0;
		for (int j = 0; j < lista_transaccion.size(); j++) {
			if (includes(lista_transaccion.at(j).begin(), lista_transaccion.at(j).end(), conjunto.begin(), conjunto.end())) {

				support += 1. / total_transacciones;
				//cout << support;
			}

		}
		return support;



	}
	map<set<string>, float> ItemFrecuente::obtenerSupport(vector<set<string>> c_items)
	{
		float total_transacciones = float(lista_transaccion.size());
		float support = 0;
		map<set<string>, float> item_frecuente;
		for (int i = 0; i < c_items.size(); i++) {
			for (int j = 0; j < lista_transaccion.size(); j++) {
				if (includes(lista_transaccion.at(j).begin(), lista_transaccion.at(j).end(), c_items.at(i).begin(), c_items.at(i).end())){

					support += 1. / total_transacciones;
					//cout << support;
				}

			}	
			if (support > minimo_support) {

				item_frecuente.insert({ c_items.at(i), support });
			}
			support = 0;	
		}
		return item_frecuente;
		/*
		for (int i = 0; i < c_items.size(); i++) {
			for (set<string>::iterator it = c_items.at(i).begin(); it != c_items.at(i).end(); it++) {
				for (int j = 0; j < lista_transaccion.size(); j++) {
					for (int r = 0; r < lista_transaccion.at(j).size(); r++) {

						if (lista_transaccion.at(j).at(r).find(*it) != lista_transaccion.at(j).at(r).end()) {
							support += 1. / total_transacciones;
						}
					}
				}
				cout << "ITEM   " << *it << "    Support  " << support << std::endl;
				showPowerSet(*it, c_items.at(i).size());
				item_frecuente.insert({ c_items.at(i), support });
				//}
				support = 0;
			}
			//if (support > minimo_support) {
	
		}

		
		
		map<set<string>, float>::iterator it;
		for (it = item_frecuente.begin(); it != item_frecuente.end(); it++)
		{
			cout << (*it->first.begin())  << ':' << it->second << std::endl;
		}
		*/
		//return item_frecuente;

		
		//map<vector<vector<string>>, float> aux_item_frecuentes;
		//for (int i = 0; i < items.size(); i++) {
			//for (int j = 0; j < lista_transaccion.size(); j++) {
				//if (find(lista_transaccion.begin(), lista_transaccion.end(), items[i]) != lista_transaccion.end()) {
					//support = support + 1 / (total_transacciones);
			//	}
				//aux_item_frecuentes[items] = support;
			//}
			
		//}
		
		//return aux_item_frecuentes;
	}

	void ItemFrecuente::obtenerItemFrecuentes()
	{
		int k = 1;
		int fin = 1;
		map<set<string>, float> aux_item_frecuentes;
		vector<set<string>> c_items;
		set<string> aux;
		while (fin) {

			if (k > 1) {
				c_items = une(aux_item_frecuentes, k);
			}
			else {
				c_items = items;
				
			}
			aux_item_frecuentes = obtenerSupport(c_items);
			
			cout << "Tamano aux_item_frecuentes para k:    "<< to_string(k) + " " + to_string(aux_item_frecuentes.size()) << endl;

			if (aux_item_frecuentes.size() == 0) { 
				fin = 0;
			}
			else {
				item_frecuentes.push_back(aux_item_frecuentes);
				k = k + 1;
			}
		}

	}

	
	vector<set<string>> ItemFrecuente::allPossibleSubset(set<string> conjunto)
	{
		int n = conjunto.size();
		int cont = 0;
		set<string> aux;
		vector<set<string>> subconjuntos;
		set<string>::iterator it;
		int count = pow(2, n);
		// The outer for loop will run 2^n times to print all subset .
		// Here variable i will act as a binary counter
		for (int i = 0; i < count; i++) {
			// The inner for loop will run n times , 
			// As the maximum number of elements a set can have is n
			// This loop will generate a 
			for (it = conjunto.begin(); it != conjunto.end(); it++) {

				// This if condition will check if jth bit in 
				// binary representation of  i  is set or not
				// if the value of (i & (1 << j)) is not 0 , 
				// include arr[j] in the current subset
				// otherwise exclude arr[j]
				if ((i & (1 << cont)) != 0) {
					aux.insert(*it);
				}
				cont += 1;
			}
			cont = 0;
			subconjuntos.push_back(aux);
			aux.clear();
			//cout << "\n";
		}
		/*
		for (int i = 0; i < subconjuntos.size(); i++) {
			for (const auto& e : subconjuntos.at(i)) {
				cout << e << "  ";
			}
			cout <<"\n" << endl;
		}
		*/
		return subconjuntos;
	}
	
	void ItemFrecuente::obtenerReglas()
	{
		//def get_rules(f_itemset, min_confidence, min_lift):
		
		//vector<map<set<string>, float>> item_frecuentes;
		map<set<string>, float>::iterator it;
		set<string>::iterator it2;
		set<string> antecedente;
		set<string> consecuente;
		set<string> total;
		vector<set<string>> aux;
		set<string> xy;
		float confianza;

		for (int i = 0; i < item_frecuentes.size(); i++) {
			for (it = item_frecuentes.at(i).begin(); it != item_frecuentes.at(i).end(); it++)
			{
				cout << "ItemFrecuente: " << i << endl;
				if ((it->first).size() > 1) {
					total = it->first;
					//cout << "Total " << i;
					aux = allPossibleSubset(total);
					for (int j = 0; j < aux.size(); j++) {
						cout << "ItemFrecuente: Elemento en la posicion " << j << endl;
						antecedente = aux.at(j);
						set_difference(total.begin(), total.end(), antecedente.begin(), antecedente.end(), inserter(consecuente, consecuente.begin()));
						if (consecuente.size() > 0 & antecedente.size() > 0) {
							set_union(begin(antecedente), end(antecedente), begin(consecuente), end(consecuente), inserter(xy, begin(xy)));
							if (obtenerSupportSet(antecedente) == 0) {
								confianza = 0;
							}
							else {
								confianza = obtenerSupportSet(xy) / obtenerSupportSet(antecedente);
							}
							
							//cout << "xy: "<<obtenerSupportSet(xy) <<endl;
							//cout << "antecdente: "<<obtenerSupportSet(antecedente) <<endl;
							//cout << confianza<< endl;
							if (confianza >= min_confianza ) {
								//cout <<min_confianza << "CONFIANZA: "<<confianza;
								reglas.insert({ antecedente, consecuente });
								reglas_confianza.insert({ reglas, confianza });
							}
							antecedente.clear();
							consecuente.clear();
						}
					}
				}
					//reglas[antecedente] = consecuente;
			}
			
		}
	
	}


	void showPowerSet(string* set, int longitud_set) {
		unsigned int size = pow(2, longitud_set);
		for (int contador = 0; contador < size; contador++) {
			cout << "{";
			for (int j = 0; j < size; j++) {
				if (contador & (1 << j)) // revisar <<
					cout << set[j] << " ";
			}
			cout << "}" << endl;
		}
	}
	vector<set<string>> ItemFrecuente::une(map<set<string>, float> aux_item_frecuentes, int k) {

		set<string> aux_items;
		vector<set<string>> c_items;  
		map<set<string>, float>::iterator it1;
		map<set<string>, float>::iterator it2;
		for (it1 = aux_item_frecuentes.begin(); it1 != aux_item_frecuentes.end(); it1++) {
			for (it2 = it1; it2 != aux_item_frecuentes.end(); it2++) {
				set_union(begin(it1->first), end(it1->first),begin(it2->first), end(it2->first), inserter(aux_items, begin(aux_items)));
				if (aux_items.size() == k) {
					c_items.push_back(aux_items);
				}
				aux_items.clear();
			}
		}
		return c_items;
	}

	int subconjunto(set<string> con1, set<string> con2) {

		for (set<string>::iterator it = con1.begin(); it != con1.end(); it++) {
			if (con2.find(*it) != con2.end()) {
				return 1;
			}
		}
		return 0;
	}
	int printPowerSet(int arr[], int n)
	{
		vector<string> list;

		/* Run counter i from 000..0 to 111..1*/
		for (int i = 0; i < (int)pow(2, n); i++)
		{
			string subset = "";

			// consider each element in the set 
			for (int j = 0; j < n; j++)
			{
				// Check if jth bit in the i is set. If the bit 
				// is set, we consider jth element from set 
				if ((i & (1 << j)) != 0)
					subset += to_string(arr[j]) + "|";
			}

			// if subset is encountered for the first time 
			// If we use set<string>, we can directly insert 
			if (find(list.begin(), list.end(), subset) == list.end())
				list.push_back(subset);
		}

		// consider every subset 
		for (string subset : list)
		{
			// split the subset and print its elements 
			//vector<string> arr = string.split(subset, '|');
			//for (string str : arr)
				//cout << str << " ";
			cout << endl;
		}
		return 1;
	}

      