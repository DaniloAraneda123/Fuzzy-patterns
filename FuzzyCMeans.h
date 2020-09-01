#pragma once
#include <iostream>
#include<fstream>
#include<windows.h>
#include <sstream>
#include <vector>

using namespace std;

class FuzzyCMeans
{
private:
	int num_datos;
	int num_clusters;
	int num_dimensiones;
	int iteraciones=500;
	double** grado_pertenencia= nullptr;
	double epsilon;
	double borrosidad;
	double** data_puntos=nullptr;
	double** centroides	=nullptr;
	bool ejecucion;

public:
	FuzzyCMeans();


	FuzzyCMeans(int nDatos, int nClusters, int nDimensiones, int it, double error, double gradoFuzzy);

	void setData(vector<vector<double>> datos);

	double** fcm(bool verIteraciones);

	bool guardarCentroides(string ruta);

	void cargarCentroides(string matriz);

	double** getCentroides();

	double** getPertenencia();

	void setData(double** datos);

	double* evaluarDato(double* datos);

private:
	void imprimirIteracion(double max_dif,int iteracion);

	void calcular_vectores_centroides();

	double get_norm(int i, int j);

	double get_norm(double* datos, int j);

	double get_new_pertenecia(int i, int j);

	double actualizar_pertenencias();
};
