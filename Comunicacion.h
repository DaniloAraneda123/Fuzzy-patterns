#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>



using namespace std;



int mostrar_pantalla_datos(map<string, vector<string>> datos);



map<vector<string>, vector<vector<string>>> leerDatos(string ruta, char delimitador);

// Funcion que entregue un reporte

void crearReporte(string ruta, map<string, vector<string>> datos, bool fuzzycmeans, bool id3Difuso, bool itemFrecuente);










