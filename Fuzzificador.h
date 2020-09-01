#pragma once


#include <string>
#include <vector>
#include <map>
#include <set>


using namespace std;



float funcionTrapezoidal(float valorEvaluado, float a, float b, float c, float d);

float funcionTrapezoidalABInfinitoNegativo(float valorEvaluado, float c, float d);

float funcionTrapezoidalCDInfinitoPositivo(float valorEvaluado, float a, float b);

float funcionTriangular(float valorEvaluado, float a, float b, float c);

bool is_number(const string& s);

int getNumeroDatos(map<vector<string>, vector<vector<string>>> datos);

int getNumeroDimensiones(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding);

vector<vector<string>> getDatosItemFrecuente(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding);

vector<vector<double>> getDatosFuzzyCMeans(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding);

vector<string> getHeaderFuzzyCMeans(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding);

vector<vector<double>> getDatosFuzzyID3(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding);

vector<string>getHeaderFuzzyID3(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding);

vector<double> obtenerFuzzificacion(double valor, float min, float max);

map<int, vector<float>>obtenerMaximosyMinimos(map<vector<string>, vector<vector<string>>> datos);

vector<string> getOneHotEncoding(string columna, vector<string> valores);

map<int, vector<string>> getOneHotEncodingValores(map<vector<string>, vector<vector<string>>> datos);





