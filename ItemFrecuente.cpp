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

		cout << "Termina la busqueda de ItemFrecuentes" << endl;

		obtenerReglas();

		cout << "Termina la generacion de reglas" << endl;

		map<set<string>, set<string>>::iterator it2;
		ofstream archivo;
		archivo.open(ruta + "reglas_asociativas.txt");
		archivo << "Reglas asociativas" << "\n";
		cout << reglas.size();
		int cont = 0;
		int por_reglas = 0;
		for (it2 = reglas.begin(); it2 != reglas.end(); it2++) {
			archivo << "Si  ";
			cont = 0;
			for (const auto& e : it2->first){
				cont += 1;
				if (cont == it2->first.size()) {
					archivo << e;
				}
				else {
					archivo << e << " y ";
				}
				
			}
			cont = 0;
			archivo << "  Entonces  ";
			for (const auto& d : it2->second) {
				cont += 1;
				if (cont == it2->second.size()) {
					archivo << d  ;
					//archivo << reglas_confianza.at(por_reglas);
				}
				else {
					archivo << d << " y ";
				}
				
			}
			archivo << "\n";
			por_reglas += 1;
		}

				
		archivo.close();
	}



	float ItemFrecuente::obtenerSupportSet(set<string> conjunto) {

		float total_transacciones = float(lista_transaccion.size());
		float support = 0;
		for (int j = 0; j < lista_transaccion.size(); j++) {
			if (includes(lista_transaccion.at(j).begin(), lista_transaccion.at(j).end(), conjunto.begin(), conjunto.end())) {
				support += 1. / total_transacciones;
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
				}
			}	
			if (support > minimo_support) {
				item_frecuente.insert({ c_items.at(i), support });
			}
			support = 0;	
		}
		return item_frecuente;
		
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
			
			cout << "Calculando conjunto_item_frecuentes de tamano :    "<< to_string(k) + "    Total de conjuntos: " + to_string(aux_item_frecuentes.size()) << endl;

			if (aux_item_frecuentes.size() == 0) { 
				fin = 0;
			}
			else {
				item_frecuentes.push_back(aux_item_frecuentes);
				k = k + 1;
			}
		}

	}

	
	vector<set<string>> ItemFrecuente::subconjuntos(set<string> conjunto)
	{
		int n = conjunto.size();
		int cont = 0;
		set<string> aux;
		vector<set<string>> subconjuntos;
		set<string>::iterator it;
		int count = pow(2, n);
		for (int i = 0; i < count; i++) {

			for (it = conjunto.begin(); it != conjunto.end(); it++) {

				if ((i & (1 << cont)) != 0) {
					aux.insert(*it);
				}
				cont += 1;
			}
			cont = 0;
			subconjuntos.push_back(aux);
			aux.clear();
		}

		return subconjuntos;
	}
	
	void ItemFrecuente::obtenerReglas()
	{

		map<set<string>, float>::iterator it;
		set<string>::iterator it2;
		set<string> antecedente;
		set<string> consecuente;
		set<string> total;
		vector<set<string>> aux;
		set<string> xy;
		float confianza;

		for (int i = 0; i < item_frecuentes.size(); i++) {
			cout << "ItemFrecuente: " << i << item_frecuentes.size()  << "Completado" << endl;
			for (it = item_frecuentes.at(i).begin(); it != item_frecuentes.at(i).end(); it++)
			{
				if ((it->first).size() > 1) {
					total = it->first;
					aux = subconjuntos(total);
					for (int j = 0; j < aux.size(); j++) {
						antecedente = aux.at(j);
						set_difference(total.begin(), total.end(), antecedente.begin(), antecedente.end(), inserter(consecuente, consecuente.begin()));
						if ((consecuente.size() > 0) && (antecedente.size() > 0)) {
							set_union(begin(antecedente), end(antecedente), begin(consecuente), end(consecuente), inserter(xy, begin(xy)));
							if (obtenerSupportSet(antecedente) == 0) {
								confianza = 0;
							}
							else {
								confianza = obtenerSupportSet(xy) / obtenerSupportSet(antecedente);
							}
	
							if (confianza >= min_confianza ) {

								
								reglas.insert({ antecedente, consecuente });
								reglas_confianza.push_back(confianza);
							}
							antecedente.clear();
							consecuente.clear();
						}
					}
				}

			}
			
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


      