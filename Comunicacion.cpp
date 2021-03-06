#include "Comunicacion.h"
#include "Fuzzificador.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <utility> 
#include <stdexcept> 
#include <sstream> 
#include "FuzzyCMeans.h"
#include "FuzzyID3.h"
#include "Dataset.h"
#include "ItemFrecuente.h"

using namespace std;


Dataset llenarDataSet(vector <string> header, vector<vector<double>> datos)
{
    Dataset baseDatos;
    string atributo;
    vector<string> atributos, terminosLinguisticos;
    int pos;
    baseDatos.setDatos(datos);
    for (int i = 0; i < header.size(); i++)
    {
        pos = header[i].find("_");
        atributos.push_back(header[i].substr(0, pos));
        terminosLinguisticos.push_back(header[i].substr(pos + 1));
    }
    baseDatos.setHeader(atributos, terminosLinguisticos);

    return baseDatos;
}

void crearReporte(string ruta, map<vector<string>,vector<vector<string>>> datos, bool fuzzycmeans, bool id3Difuso,
                  bool itemFrecuente,int numero_clusters,int iteracion_fuzzycmeans, double error_fuzzy, double gradoFuzzy,
                   double nivelVerdad,double nivelSignificancia,string variableClass, float minimo_support, float minimo_confianza)
{

    if (fuzzycmeans)
    {
        cout << "Se inicia fuzzy C-Means" << endl;
        int one_hot_encoding = 1;
        vector<string> header = getHeaderFuzzyCMeans(datos, one_hot_encoding);
        vector<vector<double>> matriz = getDatosFuzzyCMeans(datos, one_hot_encoding);
        int nroDatos = getNumeroDatos(datos);
        int nroDimensiones = getNumeroDimensiones(datos, one_hot_encoding);
        FuzzyCMeans fuzzyCMeans = FuzzyCMeans(nroDatos, numero_clusters, nroDimensiones, iteracion_fuzzycmeans, error_fuzzy, gradoFuzzy);
        fuzzyCMeans.setData(matriz);
        fuzzyCMeans.fcm(true);
        fuzzyCMeans.guardarReporte(ruta, iteracion_fuzzycmeans, error_fuzzy, gradoFuzzy);
        cout << " " << endl;
        cout << "Termina fuzzy C-Means" << endl;
    }

    if (id3Difuso) 
    {
        cout << "Se inicia fuzzy ID3" << endl;
        //Retorna variables Linguisticas
        vector<string> header= getHeaderFuzzyID3(datos,1);

        //Retorna matriz de datos
        vector<vector<double>>dataID3 = getDatosFuzzyID3(datos,1);

        Dataset baseDatos=llenarDataSet(header, dataID3);
        FuzzyID3 fdt (nivelVerdad, nivelSignificancia);

        cout << "Se construye el arbol  ................" << endl;
        cout << "\n";
        TreeNode root = fdt.construirArbol(baseDatos, variableClass);
        fdt.guardaArbol(root,ruta,"arbol.txt","");
        fdt.guardarReglas(root, "reglas.txt", "");
        fdt.guardarReporte(root, "Reporte_FuzzyID3.txt", "",nivelVerdad, nivelSignificancia);

        cout << " " << endl;
        cout << "Termina fuzzy ID3" << endl;
    }

    if (itemFrecuente) 
    {
        cout << " Se inicia Fuzzy A-Priori  " << endl;
        int one_hot_encoding = 1;
        int nroDatos1 = getNumeroDatos(datos);
        int nroDimensiones1 = getNumeroDimensiones(datos, one_hot_encoding);
        vector<vector<string>> matriz = getDatosItemFrecuente(datos, one_hot_encoding);

        ItemFrecuente itemFrecuente = ItemFrecuente(nroDimensiones1, nroDatos1, matriz, minimo_support, minimo_confianza);
        itemFrecuente.guardarReporte(ruta, minimo_support, minimo_confianza);

        cout << " Termina Fuzzy A-Priori  " << endl;
    }
    
}



map<vector<string>, vector<vector<string>>> leerDatos(string ruta, char delimitador) {



  vector<vector<string>> matriz;

    vector<string> header;
    vector<string> aux;
    map<vector<string>, vector<vector<string>>> resultados;

    ifstream myFile(ruta);

    
    if (!myFile.is_open()) throw runtime_error("No se pudo abrir el archivo");

    // Helper vars
    string linea;
    string columna;
    string valor;

//    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, linea);

        // Create a stringstream from line
        stringstream ss(linea);

        // Extract each column name
        while (getline(ss, columna, delimitador)) {

            // Initialize and add <colname, int vector> pairs to result
           // cout << columna << "Columna";
            header.push_back(columna);

        }
    }

    while (getline(myFile, linea))
    {
        // Create a stringstream of the current line
        std::stringstream ss(linea);

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each integer
        for(int i=0; i < header.size(); i++){

            getline(ss, valor, delimitador);
            // Add the current integer to the 'colIdx' column's values vector

            //cout << valor << "Valor";
            aux.push_back(valor);

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