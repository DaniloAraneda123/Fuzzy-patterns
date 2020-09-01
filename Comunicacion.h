#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>



using namespace std;






map<vector<string>, vector<vector<string>>> leerDatos(string ruta, char delimitador);

// Funcion que entregue un reporte

void crearReporte(string ruta, map<vector<string>, vector<vector<string>>> datos, bool fuzzycmeans, bool id3Difuso,
    bool itemFrecuente, int numero_clusters, int iteracion_fuzzycmeans, double error_fuzzy, double gradoFuzzy,
    double nivelVerdad, double nivelSignificacia, string variableClass, float minimo_support, float minimo_confianza);










