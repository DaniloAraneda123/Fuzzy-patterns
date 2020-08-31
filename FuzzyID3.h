#pragma once

#include <string>
#include "Dataset.h"
#include <vector> 
#include "TreeNodo.h"

class FuzzyID3
{
private:

    double nivelVerdad;

    double nivelSignificacia;

public:

    FuzzyID3(double truthLevel, double significantLevel);

    TreeNode construirArbol(Dataset dataset, string nombreClase);

    double getAmbiguedad(Dataset dataset, string nombreClase, string nombreAtributo, vector<string >evidence);

    double getAmbiguedad(Dataset dataset, string className, vector<string> evidence);

    double getAmbiguedad(Dataset dataset, string nombreClase, string nombreAtributo);

    vector<string> generarReglas(TreeNode node);

    void printTree(TreeNode root, string tabs);

    void guardaArbol(TreeNode root, string tabs, string fileName, string ruta);

    void guardarReglas(TreeNode root, string fileName, string ruta);

    vector<double> clasificar(int inputIdx, Dataset dataset, string nombreClase, vector<string> reglas);

private:

    TreeNode growTree(Dataset dataset, vector<string> padre, vector<string> atributos, string nombreClase);

    double degreeOfClassificationTruth(Dataset dataset, vector<string> atributo_termino);

    string generateRules(TreeNode node, string prefix);

    string getStringTree(TreeNode root, string tabs);
};