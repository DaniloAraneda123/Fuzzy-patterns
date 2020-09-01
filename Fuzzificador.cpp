#include "Fuzzificador.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <set>

using namespace std;

float funcionTrapezoidal(float valorEvaluado, float a, float b, float c, float d)
{
    float resultado = 0;

    if (valorEvaluado <= a || valorEvaluado > d)
    {
        resultado = 0;
    }

    else if (valorEvaluado > a && valorEvaluado <= b) {
        resultado = ((valorEvaluado - a) / (b - a));
    }

    else if (valorEvaluado > b && valorEvaluado <= c) {
        resultado = 1;
    }

    else if (valorEvaluado > c && valorEvaluado <= d) {
        resultado = ((d - valorEvaluado) / (d - c));
    }

    return resultado;
}


float funcionTrapezoidalABInfinitoNegativo(float valorEvaluado, float c, float d) {

    float resultado = 0;

    if (valorEvaluado > d)
    {
        resultado = 0;
    }

    else if (valorEvaluado >= c && valorEvaluado <= d) {
        resultado = ((d - valorEvaluado) / (d - c));
    }

    else if (valorEvaluado < c) {
        resultado = 1;
    }

    return resultado;
}
float funcionTrapezoidalCDInfinitoPositivo(float valorEvaluado, float a, float b) {

    float resultado = 0;

    if (valorEvaluado < a)
    {
        resultado = 0;
    }

    else if (valorEvaluado >= a && valorEvaluado <= b) {
        resultado = ((valorEvaluado - a) / (b - a));
    }

    else if (valorEvaluado > b) {
        resultado = 1;
    }



    return resultado;
}



float funcionTriangular(float valorEvaluado, float a, float b, float c)
{
    float resultado = 0;

    if (valorEvaluado <= a || valorEvaluado > c) {
        resultado = 0;
    }

    else if (valorEvaluado > a && valorEvaluado <= b) {
        resultado = ((valorEvaluado - a) / (b - a));
    }

    else if (valorEvaluado > b && valorEvaluado <= c) {
        resultado = ((c - valorEvaluado) / (c - b));
    }

    return resultado;
}

bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && (isdigit(*it) || *it == '.')) ++it;
    return !s.empty() && it == s.end();
}

vector<double> obtenerFuzzificacion(double valor, float min, float max) {

    vector<double> fuzzificador;
    float numero_atributos = 3;
    float delta = (max - min) / 2;
    float minimo;
    float medio;
    float maximo;
    medio = min + delta;
    maximo = medio + delta;
    minimo = maximo + delta;
    //cout << medio << maximo << minimo << endl;
    fuzzificador.push_back(funcionTrapezoidalABInfinitoNegativo(valor, min, medio));
    fuzzificador.push_back(funcionTriangular(valor, min, medio, maximo));
    fuzzificador.push_back(funcionTrapezoidalCDInfinitoPositivo(valor, medio, maximo));


    return fuzzificador;

}


//double *
//
//
//int getNumeroDatos(map<vector<string>, vector<vector<string>>> datos) {
//
//    return datos.begin()->second.size();
//
//}

map<int, vector<float>> obtenerMaximosyMinimos(map<vector<string>, vector<vector<string>>> datos) {

    map<int, vector<float>> resultados;
    vector<vector<string>> aux;
    vector<float> conjunto;
    vector<string> one_hot_n;
    float minimo = INT_MAX;
    float maximo = INT_MIN;
    aux = datos.begin()->second;
    for (int j = 0; j < aux[0].size(); j++) {
        if (is_number(aux[0][j])) {
            for (int k = 0; k < aux.size(); k++) {
                if (stod(aux[k][j]) < minimo) {
                    minimo = stod(aux[k][j]);
                }
                if (stod(aux[k][j]) > maximo) {
                    maximo = stod(aux[k][j]);
                }

            }
            cout << minimo << endl;
            cout << maximo << endl;
            conjunto.push_back(minimo);
            conjunto.push_back(maximo);
            resultados.insert({ j, conjunto });
            conjunto.clear();
            minimo = INT_MAX;
            maximo = INT_MIN;
        }
    }
    return resultados;

}
vector<vector<double>>getDatosFuzzyID3(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding) {

    map<int, vector<float>> funcion = obtenerMaximosyMinimos(datos);
    map<int, vector<string>> one_hot_n = getOneHotEncodingValores(datos);
    vector<vector<double>> resultados;
    vector<double> fila;
    vector<vector<string>> aux;
    vector<string> valores;
    vector<double> fuzzificacion;
    aux = datos.begin()->second;
    if (one_hot_encoding) {

        for (int i = 0; i < aux.size(); i++) {
            for (int j = 0; j < aux[i].size(); j++) {
                if (!is_number(aux[i][j])) {
                    valores = one_hot_n[j];
                    for (int k = 0; k < valores.size(); k++) {
                        if (aux[i][j] == valores[k]) {
                            fila.push_back(1);
                        }
                        else {
                            fila.push_back(0);
                        }
                    }
                }
                else {

                    fuzzificacion = obtenerFuzzificacion(stod(aux[i][j]), funcion[j].at(0), funcion[j].at(1));
                    for (int k = 0; k < fuzzificacion.size(); k++) {
                        cout << fuzzificacion[k];
                        fila.push_back(fuzzificacion[k]);
                    }
                }
            }
            resultados.push_back(fila);
            fila.clear();
        }
    }
    else {
        for (int i = 0; i < aux.size(); i++) {
            for (int j = 0; j < aux[i].size(); j++) {

                fuzzificacion = obtenerFuzzificacion(stod(aux[i][j]), funcion[j][0], funcion[j][1]);
                for (int k = 0; k < fuzzificacion.size(); k++) {

                    fila.push_back(fuzzificacion[k]);
                }
            }
            resultados.push_back(fila);
            fila.clear();  
        }

    }
    return resultados;
}

vector<string>getHeaderFuzzyID3(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding) {

    map<int, vector<float>> funcion = obtenerMaximosyMinimos(datos);
    map<int, vector<string>> one_hot_n = getOneHotEncodingValores(datos);
    vector<string> header;
    vector<vector<double>> resultados;
    vector<double> fila;
    vector<vector<string>> aux;
    vector<string> valores;
    vector<double> fuzzificacion;
    vector<string> etiquetas = { "bajo", "medio", "alto" };
    aux = datos.begin()->second;
    if (one_hot_encoding) {


        for (int j = 0; j < aux[0].size(); j++) {
            if (!is_number(aux[0][j])) {
                valores = one_hot_n[j];
                for (int k = 0; k < valores.size(); k++) {
                    header.push_back(datos.begin()->first.at(j) + "_" + valores[k]);

                }
            }
            else {

                //fuzzificacion = obtenerFuzzificacion(stod(aux[i][j]), funcion[j].at(0), funcion[j].at(1));
                for (int k = 0; k < etiquetas.size(); k++) {

                    header.push_back(datos.begin()->first.at(j) + "_" + etiquetas[k]);
                }
            }
        }
    }
    else {
        for (int j = 0; j < aux[0].size(); j++) {

            //fuzzificacion = obtenerFuzzificacion(stod(aux[i][j]), funcion[j][0], funcion[j][1]);
            for (int k = 0; k < etiquetas.size(); k++) {

                header.push_back(datos.begin()->first.at(j) + "_" + etiquetas[k]);
            }
        }

    }
    return header;
}




int getNumeroDimensiones(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding) {

    return getHeaderFuzzyCMeans(datos, one_hot_encoding).size();

}
vector<string> getHeaderFuzzyCMeans(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding) 
{
    vector<string> header;
    if (one_hot_encoding) {
        map<int, vector<string>> one_hot_n = getOneHotEncodingValores(datos);
        vector<vector<double>> resultados;
        vector<double> fila;
        vector<vector<string>> aux;
        vector<string> valores;
        aux = datos.begin()->second;
        for (int j = 0; j < aux[0].size(); j++) {
            if (!is_number(aux[0][j])) {
                valores = one_hot_n[j];
                for (int k = 0; k < valores.size(); k++) {
                    header.push_back(datos.begin()->first.at(j) + " " + valores[k]);
                }
            }
            else {
                header.push_back(datos.begin()->first.at(j));
            }
        }
        return header;
    }
    else {
        return datos.begin()->first;
    }

}


vector<vector<double>> getDatosFuzzyCMeans(map<vector<string>, vector<vector<string>>> datos, int one_hot_encoding) {


    map<int, vector<string>> one_hot_n = getOneHotEncodingValores(datos);
    vector<vector<double>> resultados;
    vector<double> fila;
    vector<vector<string>> aux;
    vector<string> valores;
    aux = datos.begin()->second;

    if (one_hot_encoding) {
        for (int i = 0; i < aux.size(); i++) {
            for (int j = 0; j < aux[i].size(); j++) {
                if (!is_number(aux[i][j])) {
                    valores = one_hot_n[j];
                    for (int k = 0; k < valores.size(); k++) {
                        if (aux[i][j] == valores[k]) {
                            fila.push_back(1);
                        }
                        else {
                            fila.push_back(0);
                        }
                    }
                }
                else {
                    fila.push_back(stod(aux[i][j]));
                }
            }
            resultados.push_back(fila);
            fila.clear();
        }
    }
    else {
        for (int i = 0; i < aux.size(); i++) {
            for (int j = 0; j < aux[i].size(); j++) {
                fila.push_back(stod(aux[i][j]));
            }
            resultados.push_back(fila);
            fila.clear();
        }

    }
    return resultados;
}

map<int, vector<string>> getOneHotEncodingValores(map<vector<string>, vector<vector<string>>> datos) {

    map<int, vector<string>> resultados;
    vector<vector<string>> aux;
    set<string> conjunto;
    vector<string> one_hot_n;
    aux = datos.begin()->second;
    for (int j = 0; j < aux[0].size(); j++) {
        if (!is_number(aux[0][j])) {
            for (int k = 0; k < aux.size(); k++) {
                conjunto.insert(aux[k][j]);
            }
            for (auto const& e : conjunto) {
                one_hot_n.push_back(e);
            }
            resultados.insert({ j, one_hot_n });
            conjunto.clear();
            one_hot_n.clear();
        }
    }
    return resultados;

}







