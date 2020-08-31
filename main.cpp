#pragma warning (disable : 4996)

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



using namespace std;


int main()
{
	cout << setprecision(3);
	double** pertenecia, ** patrones;
	int num_data_points, num_clusters, num_dimensions;
	double borrosidad, epsilon;
	FILE* f;

	f = fopen("iris.dat", "r");

	if (f==NULL)
	{
		cout << "error";
	}
	else
	{
		fscanf(f, "%d %d %d", &num_data_points, &num_clusters, &num_dimensions);
		fscanf(f, "%lf %lf", &borrosidad, &epsilon);
		double** data_point = new double* [num_data_points];
		for (int i = 0; i < num_data_points; i++)
		{
			data_point[i] = new double[num_dimensions];

			for (int j = 0; j < num_dimensions; j++)

			{
				fscanf(f, "%lf", &data_point[i][j]);
			}
		}

		FuzzyCMeans instancia(num_data_points, num_clusters, num_dimensions, 100, epsilon, borrosidad, data_point);

		patrones = instancia.fcm(true);
		pertenecia = instancia.getPertenencia();

		cout << endl; cout << endl;
		cout << "centroides "<<endl;
		for (int i = 0; i < num_clusters; i++)
		{
			cout << "centroide " << i << ":  ";
			for (int j = 0; j < num_dimensions; j++)
			{

				cout << patrones[i][j] << " | ";
			}
			cout << endl;
		}


		cout << endl; cout << endl;
		cout << "pertenencia: "<<endl;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < num_clusters; j++)
			{
				cout << pertenecia[i][j] << " | ";
			}
			cout << endl;
		}

		cin.get();

		cout << "Evaluar Dato" << "  4.3 | 3.0 | 1.1 | 0.1"<<endl;
		double dato[] = { 4.3,3.0,1.1,0.1 };
		double* pertenencias=instancia.evaluarDato(dato);
		for (int i=0;i<3;i++)
		{
			cout << pertenencias[i]<<"  ";
		}
		cout << endl;
		instancia.guardarCentroides("");
		cin.get();
		system("cls");

	}

	Dataset d;
	d.addAtributo("Outlook"		,vector<string>({ "Sunny", "Cloudy", "Rain"				})	);
	d.addAtributo("Temprature"	,vector<string>({"Hot", "Mild", "Cool"					})	);
	d.addAtributo("Humidity"	,vector<string>({ "Humid", "Normal"						})	);
	d.addAtributo("Wind"		,vector<string>({ "Windy", "Not_Windy"					})	);
	d.addAtributo("Plan"		,vector<string>({ "Volleyball", "Swimming", "W_lifting"	})	);


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

	FuzzyID3 fdt (0.7, 0.5);

	cout << "MEDIR AMIGUEDAD " << endl;
	cout << "G(Outlook) = "<< fdt.getAmbiguedad(d, "Plan", "Outlook") << endl;
	cout << "G(Temprature) = "<< fdt.getAmbiguedad(d, "Plan", "Temprature") << endl;
	cout << "G(Humidity) = "<< fdt.getAmbiguedad(d, "Plan", "Humidity") << endl;
	cout << "G(Wind) = "<<fdt.getAmbiguedad(d, "Plan", "Wind")<<endl << endl << endl << endl;

	TreeNode root = fdt.construirArbol(d, "Plan");

	fdt.printTree(root, "");

	fdt.guardaArbol(root,"","arbol.txt","");

	fdt.guardarReglas(root, "", "reglas.txt");

	vector<string> rules = fdt.generarReglas(root);


	cout << endl << endl;
	cin.get();
	system("cls");

	cout << "Imprimiendo Reglas" << endl;
	for (string &rule:rules)
	{
		cout << rule << endl;
	}


	Dataset d1;

	d1.addAtributo("Outlook", vector<string>({ "Sunny", "Cloudy", "Rain" }));
	d1.addAtributo("Temprature", vector<string>({ "Hot", "Mild", "Cool" }));
	d1.addAtributo("Humidity", vector<string>({ "Humid", "Normal" }));
	d1.addAtributo("Wind", vector<string>({ "Windy", "Not_Windy" }));
	d1.addAtributo("Plan", vector<string>({ "Volleyball", "Swimming", "W_lifting" }));


	d1.addFila(vector<double>({ 0.9, 0.1, 0.0, 1.0, 0.0, 0.0, 0.8, 0.2, 1, 1, 0.0, 0.8, 0.2 }));
	d1.addFila(vector<double>({ 0.8, 0.2, 0.0, 0.6, 0.4, 0.0, 0.0, 1.0, 1, 1, 1.0, 0.7, 0.0 }));
	d1.addFila(vector<double>({ 0.0, 0.7, 0.3, 0.8, 0.2, 0.0, 0.1, 0.9, 1, 1, 0.3, 0.6, 0.1 }));
	d1.addFila(vector<double>({ 0.2, 0.7, 0.1, 0.3, 0.7, 0.0, 0.2, 0.8, 1, 1, 0.9, 0.1, 0.0 }));
	d1.addFila(vector<double>({ 0.0, 0.1, 0.9, 0.7, 0.3, 0.0, 0.5, 0.5, 1, 1, 0.0, 0.0, 1.0 }));
	d1.addFila(vector<double>({ 0.0, 0.7, 0.3, 0.0, 0.3, 0.7, 0.7, 0.3, 1, 1, 0.2, 0.0, 0.8 }));
	d1.addFila(vector<double>({ 0.0, 0.3, 0.7, 0.0, 0.0, 1.0, 0.0, 1.0, 1, 1, 0.0, 0.0, 1.0 }));
	d1.addFila(vector<double>({ 0.0, 1.0, 0.0, 0.0, 0.2, 0.8, 0.2, 0.8, 1, 1, 0.7, 0.0, 0.3 }));
	d1.addFila(vector<double>({ 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.6, 0.4, 1, 1, 0.2, 0.8, 0.0 }));
	d1.addFila(vector<double>({ 0.9, 0.1, 0.0, 0.0, 0.3, 0.7, 0.0, 1.0, 1, 1, 0.0, 0.3, 0.7 }));
	d1.addFila(vector<double>({ 0.7, 0.3, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1, 1, 0.4, 0.7, 0.0 }));
	d1.addFila(vector<double>({ 0.2, 0.6, 0.2, 0.0, 1.0, 0.0, 0.3, 0.7, 1, 1, 0.7, 0.2, 0.1 }));
	d1.addFila(vector<double>({ 0.9, 0.1, 0.0, 0.2, 0.8, 0.0, 0.1, 0.9, 1, 1, 0.0, 0.0, 1.0 }));
	d1.addFila(vector<double>({ 0.0, 0.9, 0.1, 0.0, 0.9, 0.1, 0.1, 0.9, 1, 1, 0.0, 0.0, 1.0 }));
	d1.addFila(vector<double>({ 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1, 1, 0.0, 0.0, 1.0 }));
	d1.addFila(vector<double>({ 1.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 1.0, 1, 1, 0.8, 0.6, 0.0 }));

	vector<double> clas;

	for (int i=0;i<16;i++)
	{
		clas = fdt.clasificar(i, d1, "Plan", rules);
		for (int j = 0; j < clas.size(); j++)
		{
			cout << clas[j] << " - ";
		}
		cout << endl;
	}
	cin.get();
	system("cls");




	int fila = 4;
	int col = 4;
	std::string** matriz = new std::string * [4];
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
	ItemFrecuente frecuente1(4, 4, matriz, 0.20, 0.2);


	//frecuente1.obtenerSupport(frecuente1.items);
	frecuente1.obtenerItemFrecuentes();

	map<set<string>, float>::iterator it;

	for (int i = 0; i < frecuente1.item_frecuentes.size(); i++) 
	{
		for (it = frecuente1.item_frecuentes.at(i).begin(); it != frecuente1.item_frecuentes.at(i).end(); it++) 
		{
			for (const auto& e : it->first) {
				cout << e << " - ";
			}
			cout << "         frecuencia: " << it->second;
			cout << endl;
		}
	}
	cout << endl<<endl<<"REGLAS de Item Frecuente"<<endl<<endl;

	frecuente1.obtenerReglas();

	map<set<string>, set<string>>::iterator it2;

	for (it2 = frecuente1.reglas.begin(); it2 != frecuente1.reglas.end(); it2++) {
		for (const auto& e : it2->first) {
			cout << e << "   ";
		}
		cout << "--------->";
		for (const auto& d : it2->second) {
			cout << d << "   ";
		}
		cout << endl;
	}
}
