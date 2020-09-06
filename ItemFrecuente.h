#pragma once
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <map>




using namespace std;

    class ItemFrecuente
    {

    private:

        // Atributos de la clase
        int nroAtributos;
        int nroDatos;
        float minimo_support;
        float min_confianza;
        vector <set<string>> items;
        vector<set<string>> lista_transaccion;
        vector<vector<string>> lista_item_frecuentes;
        vector<map<set<string>, float>> item_frecuentes;
        //map<set<string>, set<string>> reglas;
        vector < set<string>> reglas_antecedente;
        vector < set<string>> reglas_consecuente;
        vector<float> reglas_confianza;

        // Metodos de la clase
        float obtenerSupportSet(set<string> conjunto);
        map<set<string>, float> obtenerSupport(vector<set<string>> c_items);
        vector<set<string>> une(map<set<string>, float> l, int k);
        vector<set<string>> subconjuntos(set<string> conjunto);
        void obtenerItemFrecuentes();
        void obtenerReglas();
      
   

    public:

        // Metodos de la clase publicos
        ItemFrecuente(int numeroAtributos, int nroDatos, vector<vector<string>> datos, float minimo_support, float min_confianza);
        void guardarReglas(string ruta);
        void guardarReporte(string ruta, double minimo_support, double minimo_confianza);

    };
