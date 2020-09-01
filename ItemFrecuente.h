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

        //int nroAtributos;
        //int nroDatos;
        //std::vector<std::string> item;
        //std::vector<std::set<std::string>> lista_transaccion;
        //std::vector<std::set<std::string>> lista_item_frecuentes;
        //std::map<std::string, std::vector<std::set<std::string>>> item_frecuentes;
        //std::vector<std::string> reglas;
        //float minimo_support;
        //float confianza;

    public:

        int nroAtributos;
        int nroDatos;
        vector<set<string>> items;
        

        
        vector<set<string>> lista_transaccion;
        vector<vector<string>> lista_item_frecuentes;
        //std::map<std::string, std::vector<std::set<std::string>>> aux_item_frecuentes;
        vector<map<set<string>, float>> item_frecuentes;
        map<set<string>, set<string>> reglas;
        map<map<set<string>, set<string>>, float> reglas_confianza;
        float minimo_support = 0;
        float min_confianza = 0;


        ItemFrecuente(int numeroAtributos, int nroDatos, vector<vector<string>> datos, float minimo_support, float min_confianza);
        float obtenerSupportSet(set<string> conjunto);
        map<set<string>, float> obtenerSupport(vector<set<string>> c_items);
        vector<set<string>> une(map<set<string>, float> l, int k);
        vector<set<string>> allPossibleSubset(set<string> conjunto);
        void obtenerItemFrecuentes();
        void obtenerReglas();
        void guardarReglas(string ruta);
        int subconjunto(set<string> con1, set<string> con2);
        int printPowerSet(int arr[], int n);
        void showPowerSet(string* set, int longitud_set);
        

    };
