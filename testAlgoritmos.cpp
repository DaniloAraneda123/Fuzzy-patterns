//#pragma warning (disable : 4996)

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
//
//	cout << setprecision(3);
//	double** pertenecia, ** patrones;
//	int num_data_points, num_clusters, num_dimensions;
//	double borrosidad, epsilon;
//	FILE* f;
//
//	f = fopen("irisCMeans.dat", "r");
//
//	if (f==NULL)
//	{
//		cout << "error";
//	}
//	else
//	{
//		fscanf(f, "%d %d %d", &num_data_points, &num_clusters, &num_dimensions);
//		fscanf(f, "%lf %lf", &borrosidad, &epsilon);
//		double** data_point = new double* [num_data_points];
//		for (int i = 0; i < num_data_points; i++)
//		{
//			data_point[i] = new double[num_dimensions];
//
//			for (int j = 0; j < num_dimensions; j++)
//
//			{
//				fscanf(f, "%lf", &data_point[i][j]);
//			}
//		}
//
//		FuzzyCMeans instancia(num_data_points, num_clusters, num_dimensions, 100, epsilon, borrosidad);
//		instancia.setData(data_point);
//
//		patrones = instancia.fcm(true);
//		pertenecia = instancia.getPertenencia();
//
//		cout << endl; cout << endl;
//		cout << "centroides "<<endl;
//		for (int i = 0; i < num_clusters; i++)
//		{
//			cout << "centroide " << i << ":  ";
//			for (int j = 0; j < num_dimensions; j++)
//			{
//
//				cout << patrones[i][j] << " | ";
//			}
//			cout << endl;
//		}
//
//
//		cout << endl; cout << endl;
//		cout << "pertenencia: "<<endl;
//
//		for (int i = 0; i < 10; i++)
//		{
//			for (int j = 0; j < num_clusters; j++)
//			{
//				cout << pertenecia[i][j] << " | ";
//			}
//			cout << endl;
//		}
//
//		cin.get();
//
//		cout << "evaluar dato" << "  4.3 | 3.0 | 1.1 | 0.1"<<endl;
//		double dato[] = { 4.3,3.0,1.1,0.1 };
//		double* pertenencias=instancia.evaluarDato(dato);
//		for (int i=0;i<3;i++)
//		{
//			cout << pertenencias[i]<<"  ";
//		}
//		cout << endl;
//		instancia.guardarCentroides("");
//		cin.get();
//		system("cls");
//
//	}

	Dataset d;
	d.addAtributo("outlook"		,vector<string>({ "sunny", "cloudy", "rain"				})	);
	d.addAtributo("temprature"	,vector<string>({"hot", "mild", "cool"					})	);
	d.addAtributo("humidity"	,vector<string>({ "humid", "normal"						})	);
	d.addAtributo("wind"		,vector<string>({ "windy", "not_windy"					})	);
	d.addAtributo("plan"		,vector<string>({ "volleyball", "swimming", "w_lifting"	})	);


	d.addFila(vector<double>({ 0.9, 0.1, 0.0, 1.0, 0.0, 0.0, 0.8, 0.2, 0.4, 0.6, 0.0, 0.8, 0.2	}));
	d.addFila(vector<double>({ 0.8, 0.2, 0.0, 0.6, 0.4, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.7, 0.0	}));
	d.addFila(vector<double>({ 0.0, 0.7, 0.3, 0.8, 0.2, 0.0, 0.1, 0.9, 0.2, 0.8, 0.3, 0.6, 0.1	}));
	d.addFila(vector<double>({ 0.2, 0.7, 0.1, 0.3, 0.7, 0.0, 0.2, 0.8, 0.3, 0.7, 0.9, 0.1, 0.0	}));
	d.addFila(vector<double>({ 0.0, 0.1, 0.9, 0.7, 0.3, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, 0.0, 1.0	}));
	d.addFila(vector<double>({ 0.0, 0.7, 0.3, 0.0, 0.3, 0.7, 0.7, 0.3, 0.4, 0.6, 0.2, 0.0, 0.8	}));
	d.addFila(vector<double>({ 0.0, 0.3, 0.7, 0.0, 0.0, 1.0, 0.0, 1.0, 0.1, 0.9, 0.0, 0.0, 1.0	}));
	d.addFila(vector<double>({ 0.0, 1.0, 0.0, 0.0, 0.2, 0.8, 0.2, 0.8, 0.0, 1.0, 0.7, 0.0, 0.3	}));
	d.addFila(vector<double>({ 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.6, 0.4, 0.7, 0.3, 0.2, 0.8, 0.0  }));
	d.addFila(vector<double>({ 0.9, 0.1, 0.0, 0.0, 0.3, 0.7, 0.0, 1.0, 0.9, 0.1, 0.0, 0.3, 0.7	}));
	d.addFila(vector<double>({ 0.7, 0.3, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.2, 0.8, 0.4, 0.7, 0.0	}));
	d.addFila(vector<double>({ 0.2, 0.6, 0.2, 0.0, 1.0, 0.0, 0.3, 0.7, 0.3, 0.7, 0.7, 0.2, 0.1	}));
	d.addFila(vector<double>({ 0.9, 0.1, 0.0, 0.2, 0.8, 0.0, 0.1, 0.9, 1.0, 0.0, 0.0, 0.0, 1.0	}));
	d.addFila(vector<double>({ 0.0, 0.9, 0.1, 0.0, 0.9, 0.1, 0.1, 0.9, 0.7, 0.3, 0.0, 0.0, 1.0	}));
	d.addFila(vector<double>({ 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.8, 0.2, 0.0, 0.0, 1.0	}));
	d.addFila(vector<double>({ 1.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 1.0, 0.8, 0.6, 0.0	}));

	FuzzyID3 fdt (0.9,0.5);

	double s = fdt.getAmbiguedad(d, "plan", "outlook", vector<string>({ "temprature","hot" }));
	
	cout << s << endl;
	
	cout << "medir amiguedad " << endl;
	cout << "g(outlook) = "<< fdt.getAmbiguedad(d, "plan", "outlook") << endl;
	cout << "g(temprature) = "<< fdt.getAmbiguedad(d, "plan", "temprature") << endl;
	cout << "g(humidity) = "<< fdt.getAmbiguedad(d, "plan", "humidity") << endl;
	cout << "g(wind) = "<<fdt.getAmbiguedad(d, "plan", "wind")<<endl << endl << endl << endl;

	TreeNode root = fdt.construirArbol(d, "plan");

	fdt.printTree(root, "");

	fdt.guardaArbol(root,"","arbol.txt","");

	fdt.guardarReglas(root, "", "reglas.txt");

	vector<string> rules = fdt.generarReglas(root);


	cout << endl << endl;

	cout << "imprimiendo reglas" << endl;
	for (string &rule:rules)
	{
		cout << rule << endl;
	}
	

//	Dataset d1;
//
//	d1.addAtributo("outlook", vector<string>({ "sunny", "cloudy", "rain" }));
//	d1.addAtributo("temprature", vector<string>({ "hot", "mild", "cool" }));
//	d1.addAtributo("humidity", vector<string>({ "humid", "normal" }));
//	d1.addAtributo("wind", vector<string>({ "windy", "not_windy" }));
//	d1.addAtributo("plan", vector<string>({ "volleyball", "swimming", "w_lifting" }));
//
//
//	d1.addFila(vector<double>({ 0.9, 0.1, 0.0, 1.0, 0.0, 0.0, 0.8, 0.2, 1, 1, 0.0, 0.8, 0.2 }));
//	d1.addFila(vector<double>({ 0.8, 0.2, 0.0, 0.6, 0.4, 0.0, 0.0, 1.0, 1, 1, 1.0, 0.7, 0.0 }));
//	d1.addFila(vector<double>({ 0.0, 0.7, 0.3, 0.8, 0.2, 0.0, 0.1, 0.9, 1, 1, 0.3, 0.6, 0.1 }));
//	d1.addFila(vector<double>({ 0.2, 0.7, 0.1, 0.3, 0.7, 0.0, 0.2, 0.8, 1, 1, 0.9, 0.1, 0.0 }));
//	d1.addFila(vector<double>({ 0.0, 0.1, 0.9, 0.7, 0.3, 0.0, 0.5, 0.5, 1, 1, 0.0, 0.0, 1.0 }));
//	d1.addFila(vector<double>({ 0.0, 0.7, 0.3, 0.0, 0.3, 0.7, 0.7, 0.3, 1, 1, 0.2, 0.0, 0.8 }));
//	d1.addFila(vector<double>({ 0.0, 0.3, 0.7, 0.0, 0.0, 1.0, 0.0, 1.0, 1, 1, 0.0, 0.0, 1.0 }));
//	d1.addFila(vector<double>({ 0.0, 1.0, 0.0, 0.0, 0.2, 0.8, 0.2, 0.8, 1, 1, 0.7, 0.0, 0.3 }));
//	d1.addFila(vector<double>({ 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.6, 0.4, 1, 1, 0.2, 0.8, 0.0 }));
//	d1.addFila(vector<double>({ 0.9, 0.1, 0.0, 0.0, 0.3, 0.7, 0.0, 1.0, 1, 1, 0.0, 0.3, 0.7 }));
//	d1.addFila(vector<double>({ 0.7, 0.3, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1, 1, 0.4, 0.7, 0.0 }));
//	d1.addFila(vector<double>({ 0.2, 0.6, 0.2, 0.0, 1.0, 0.0, 0.3, 0.7, 1, 1, 0.7, 0.2, 0.1 }));
//	d1.addFila(vector<double>({ 0.9, 0.1, 0.0, 0.2, 0.8, 0.0, 0.1, 0.9, 1, 1, 0.0, 0.0, 1.0 }));
//	d1.addFila(vector<double>({ 0.0, 0.9, 0.1, 0.0, 0.9, 0.1, 0.1, 0.9, 1, 1, 0.0, 0.0, 1.0 }));
//	d1.addFila(vector<double>({ 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1, 1, 0.0, 0.0, 1.0 }));
//	d1.addFila(vector<double>({ 1.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 1.0, 1, 1, 0.8, 0.6, 0.0 }));
//
//	vector<double> clas;
//
//	for (int i=0;i<16;i++)
//	{
//		clas = fdt.clasificar(i, d1, "plan", rules);
//		for (int j = 0; j < clas.size(); j++)
//		{
//			cout << clas[j] << " - ";
//		}
//		cout << endl;
//	}
//	cin.get();
//	system("cls");
//
//
//
//
//	int fila = 4;
//	int col = 4;
//	vector<vector<string>> matriz = { {"soleado", "bajo", "viejo","no"}, {"soleado", "bajo", "viejo", "si"} , {"soleado", "bajo", "viejo", "si"} ,{"soleado", "bajo", "viejo", "si"} };
//
//
//
//	// crear itemfrecuente
//	ItemFrecuente frecuente1(4, 4, matriz, 0.20, 0.2);
//
//
//	//frecuente1.obtenersupport(frecuente1.items);
//	frecuente1.obtenerItemFrecuentes();
//
//	map<set<string>, float>::iterator it;
//
//	for (int i = 0; i < frecuente1.item_frecuentes.size(); i++) 
//	{
//		for (it = frecuente1.item_frecuentes.at(i).begin(); it != frecuente1.item_frecuentes.at(i).end(); it++) 
//		{
//			for (const auto& e : it->first) {
//				cout << e << " - ";
//			}
//			cout << "         frecuencia: " << it->second;
//			cout << endl;
//		}
//	}
//	cout << endl<<endl<<"reglas de item frecuente"<<endl<<endl;
//
//	frecuente1.obtenerReglas();
//
//	map<set<string>, set<string>>::iterator it2;
//
//	for (it2 = frecuente1.reglas.begin(); it2 != frecuente1.reglas.end(); it2++) {
//		for (const auto& e : it2->first) {
//			cout << e << "   ";
//		}
//		cout << "--------->";
//		for (const auto& d : it2->second) {
//			cout << d << "   ";
//		}
//		cout << endl;
//	}
}


