
#include "Comunicacion.h"
#include "Fuzzificador.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include "FuzzyID3.h"

using namespace std;



void crearReporte(string ruta, map<vector<string>, vector<vector<string>>> datos, bool fuzzycmeans, bool id3Difuso, bool itemFrecuente) {


    if (fuzzycmeans) {
        int one_hot_encoding = 1;
        vector<vector<double>> matriz = getDatosFuzzyCMeans(datos, one_hot_encoding);
        int nroDatos = getNumeroDatos(datos);
        int nroDimensiones = getNumeroDimensiones(datos, one_hot_encoding);

    }

    if (id3Difuso) 
    {
        FuzzyID3 fdt (nivelVerdad, nivelSignificacia);
        TreeNode root = fdt.construirArbol(d, variableClass);
        fdt.guardaArbol(root,"","arbol.txt","");
        vector<string> rules = fdt.generarReglas(root);
    }

    if (itemFrecuente) {


    }



}
int mostrar_pantalla_datos(map<string, vector<string>> datos) {


    return 1;
}

map<vector<string>, vector<vector<string>>> leerDatos(string ruta, char delimitador) {


    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    vector<vector<string>> matriz;
    map<string, vector<string>> datos;
    vector<string> header;
    map<vector<string>, vector<vector<string>>> resultados;

    // Create an input filestream
    ifstream myFile(ruta);

    // Make sure the file is open
    if (!myFile.is_open()) throw runtime_error("No se pudo abrir el archivo");

    // Helper vars
    string linea;
    string columna;
    string valor;

    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, linea);

        // Create a stringstream from line
        stringstream ss(linea);

        // Extract each column name
        while (getline(ss, columna, delimitador)) {

            // Initialize and add <colname, int vector> pairs to result

            header.push_back(columna);


        }
    }

    // Read data, line by line
    while (getline(myFile, linea))
    {
        // Create a stringstream of the current line
        stringstream ss(linea);

        // Keep track of the current column index
        int colIdx = 0;
        vector<string> aux;
        // Extract each integer
        while (ss >> valor) {

            // Add the current integer to the 'colIdx' column's values vector
           //cout << valor << endl;
            datos[header.at(colIdx)].push_back(valor);
            aux.push_back(valor);
            //cout << datos.at(header.at(colIdx)).at(0) << endl;
            // If the next token is a comma, ignore it and move on
            if (ss.peek() == delimitador) ss.ignore();

            // Increment the column index
            colIdx++;
        }
        matriz.push_back(aux);
        aux.clear();
    }
    // Close file
    myFile.close();
    resultados.insert({ header, matriz });

    return resultados;
}






/*

map<vector<string>, vector<vector<string>>> leerDatos(string ruta, char delimitador) {


    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    vector<vector<string>> matriz;
    map<string, vector<string>> datos;
    vector<string> header;
    map<vector<string>, vector<vector<string>>> resultados;

    // Create an input filestream
    ifstream myFile(ruta);

    // Make sure the file is open
    if (!myFile.is_open()) throw runtime_error("No se pudo abrir el archivo");

    // Helper vars
    string linea;
    string columna;
    string valor;

    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, linea);

        // Create a stringstream from line
        stringstream ss(linea);

        // Extract each column name
        while (getline(ss, columna, delimitador)) {

            // Initialize and add <colname, int vector> pairs to result

            header.push_back(columna);


        }
    }

    // Read data, line by line
    while (getline(myFile, linea))
    {
        // Create a stringstream of the current line
        stringstream ss(linea);

        // Keep track of the current column index
        int colIdx = 0;
        vector<string> aux;
        // Extract each integer
        while (ss >> valor) {

            // Add the current integer to the 'colIdx' column's values vector
           //cout << valor << endl;
            datos[header.at(colIdx)].push_back(valor);
            aux.push_back(valor);
            //cout << datos.at(header.at(colIdx)).at(0) << endl;
            // If the next token is a comma, ignore it and move on
            if (ss.peek() == delimitador) ss.ignore();

            // Increment the column index
            colIdx++;
        }
        matriz.push_back(aux);
        aux.clear();
    }
    // Close file
    myFile.close();
    resultados.insert({ header, matriz });

    return resultados;
}
*/