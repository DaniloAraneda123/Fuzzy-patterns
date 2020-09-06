#include "FuzzyID3.h"
#include <string>
#include "Dataset.h"
#include "Utils.h"
#include <stdlib.h> 
#include <vector> 
#include "TreeNodo.h"
#include <iostream>
#include<fstream>
#include<windows.h>
#include <sstream>
#include <algorithm> 

using namespace std;

    FuzzyID3::FuzzyID3(double truthLevel, double significantLevel)
    {
        nivelVerdad = min(0.99999, truthLevel); 
        nivelSignificacia = significantLevel;
    }

    //Metodo principal por el cual se empieza a construir el arbol
    TreeNode FuzzyID3::construirArbol(Dataset dataset, string nombreClase)
    {
        vector<string> atributos = dataset.getNombreAtributos(nombreClase);
        vector<string> listavacia(0);
        return growTree(dataset, listavacia, atributos, nombreClase);
    }

    TreeNode FuzzyID3::growTree(Dataset dataset, vector<string> padre, vector<string> atributos, string nombreClase)
    {
        //Si no hay atributos crea un nodo hoja basico
        if (atributos.size() == 0) {
            TreeNode hojita = TreeNode("HOJA", "UnKnown");
            return hojita;
        }

        //Si es la raiz
        TreeNode node, c, c1,c2, root;

        if (padre.size() == 0)
        {
            double AmbiguedadMinima = 1000000;
            string bestAtributo="";

            //Buscamos el atributo con la menor Ambiguedad
            for (string &atr : atributos) 
            {
                double ambResult = getAmbiguedad(dataset, nombreClase, atr);
                if (ambResult < AmbiguedadMinima)
                {
                    AmbiguedadMinima = ambResult;
                    bestAtributo = atr;
                }
            }

            //Creo La Raiz que es de tipo atributo
            root= TreeNode("ATRIBUTO", bestAtributo);

            //Obtengo los terminos linguisticos
            vector<string> terminos = dataset.getTerminosLinguisticos(bestAtributo);
            vector<string> terminosClase = dataset.getTerminosLinguisticos(nombreClase);

            //Para cada termino del mejor atributo se obtiene el grado de clasificacion de verdad recpecto a cada termino de la clase


            for (int i=0; i<terminos.size();i++)
            {
                bool canBelongeToClass = false;
                for (string &classTerm : terminosClase)
                {

                    double dot = degreeOfClassificationTruth(dataset, vector<string>({ bestAtributo, terminos[i], nombreClase, classTerm }));

                    //Si el grado de verdad de la casificacion es mayor que el nivel de verdad minimo, se crean los hijos del del termino y se asignan
                    if (dot > nivelVerdad)
                    {
                        c=  TreeNode("VALOR", terminos[i]);
                        c2=  TreeNode("HOJA", classTerm);
                        c2.setValue(dot);
                        c.addChild(&c2);
                        root.addChild(&c);
                        canBelongeToClass = true;
                        break;
                    }
                }
                //puede pertenecer al sub arbol
                if (!canBelongeToClass) 
                {
                    
                    //Removemos el best Atributo ,  que fue ocupado ya
                    vector <string> newAtributos(atributos.size() - 1);
                    for (int j = 0, k = 0; j < atributos.size(); j++)
                    {
                        if (!(atributos[j]==bestAtributo))
                        {
                            newAtributos[k++] = atributos[j];
                        }
                    }

                    //Ahora, el best atribbuto el nuevo padre
                    vector <string> newArgs(2);
                    newArgs[0] = bestAtributo;
                    newArgs[1] = terminos[i];

                    node= TreeNode("VALOR", terminos[i]);

                    c = growTree(dataset, newArgs, newAtributos, nombreClase);
                    //Se uno como hijo el nuevo sub arbol generado
                    node.addChild(&c);
                    root.addChild(&node);

                }
            }

            return root;
        }
        else//Hay atributos Padres
        {
            string bestAtributo = "";
            if (atributos.size() > 1)
            {
                vector<string> args1(padre.size() + 1);
                args1.push_back(nombreClase);

                double ambg = getAmbiguedad(dataset, nombreClase, padre);
                for (string& atr : atributos)
                {
                    vector<string>  args2(args1.size() + 1);
                    for (int i = 0; i < args1.size(); i++)
                        args2[i+1]=args1[i];
                    args2[0] = atr;


                    double ambg2 = getAmbiguedad(dataset, nombreClase, atr, padre);


                    if (ambg2 <= ambg)
                    {
                        //cout << "cambio" << endl;
                        bestAtributo = atr;
                        ambg = ambg2;
                    }

                }
                if ("" == bestAtributo)
                {
                    vector<string> args1;
                    for (int q = 0; q < padre.size(); q++)
                        args1.push_back(padre[q]);
                    args1.push_back(nombreClase);
                    args1.push_back("");
                    vector<string> terminosClase = dataset.getTerminosLinguisticos(nombreClase);
                    string bestClass = "";
                    double bestDOT = -1;

                    for (string& classTerm : terminosClase)
                    {
                        args1[padre.size() + 1] = classTerm;
                        double dot = degreeOfClassificationTruth(dataset, args1);
                        if (dot > bestDOT)
                        {
                            bestDOT = dot;
                            bestClass = classTerm;
                        }
                    }

                    c2= TreeNode("HOJA", bestClass);
                    c2.setValue(bestDOT);
                    return c2;
                }
                else
                {
                    root= TreeNode("ATRIBUTO", bestAtributo);
                    vector <string> terms = dataset.getTerminosLinguisticos(bestAtributo);
                    vector <string> classTerms = dataset.getTerminosLinguisticos(nombreClase);
                    vector <string> args2(padre.size() + 4);
                    for (int i = 0; i < padre.size(); i++)
                        args2[i + 2] = padre[i];
                    args2[0] = bestAtributo;
                    args2[args2.size() - 2] = nombreClase;


                    for (string& term : terms)
                    {
                        bool canBelongeToClass = false;
                        args2[1] = term;

                        for (string& classTerm : classTerms)
                        {
                            args2[args2.size() - 1] = classTerm;
                            double dot = degreeOfClassificationTruth(dataset, args2);

                            if (dot > nivelVerdad)
                            {
                                c= TreeNode("VALOR", term);
                                c2= TreeNode("HOJA", classTerm);
                                c2.setValue(dot);
                                c.addChild(&c2);
                                root.addChild(&c);
                                canBelongeToClass = true;
                                break;
                            }
                        }
                        if (!canBelongeToClass)
                        {
                            //Remueve el mejor atributo
                            vector <string> newAttrs(atributos.size() - 1);
                            for (int j = 0, k = 0; j < atributos.size(); j++)
                            {
                                if (atributos[j] != bestAtributo)
                                {
                                    newAttrs[k++] = atributos[j];
                                }
                            }
                            //get the new args
                            vector <string> newArgs(padre.size() + 2);
                            newArgs[0] = bestAtributo;
                            newArgs[1] = term;
                            for (int i = 0; i < padre.size(); i++)
                                newArgs[i+2]=padre[i];

                            node=  TreeNode("VALOR", term);


                            c = growTree(dataset, newArgs, newAttrs, nombreClase);

                            node.addChild(&c);
                            root.addChild(&node);

                        }

                    }
                    return root;
                }
            }
            else
            {
                bestAtributo = atributos[0];
                root= TreeNode("ATRIBUTO", bestAtributo);
                vector <string> terms = dataset.getTerminosLinguisticos(bestAtributo);
                vector <string> terminosClase = dataset.getTerminosLinguisticos(nombreClase);

                vector <string> args2(padre.size() + 4);
                args2[0] = bestAtributo;
                args2[args2.size() - 2] = nombreClase;
                for (int i = 0; i < padre.size(); i++)
                    args2[i+2]=padre[i];


                for (string& term : terms)
                {
                    args2[1] = term;
                    double maxTruth = -1;
                    string bestClass = "";
                    for (string& classTerm : terminosClase)
                    {
                        args2[args2.size() - 1] = classTerm;
                        double dot = degreeOfClassificationTruth(dataset, args2);
                        if (dot > maxTruth)
                        {
                            maxTruth = dot;
                            bestClass = classTerm;
                        }
                    }
                    node= TreeNode("VALOR", term);
                    c= TreeNode("HOJA", bestClass);

                    c.setValue(maxTruth);
                    node.addChild(&c);
                    root.addChild(&node);
                }
                return root;
            }
        }
    }

  

    //Recibe pares de atribustos-termino
    double FuzzyID3::degreeOfClassificationTruth(Dataset dataset, vector<string> atributo_termino)
    {
        vector<double> a = dataset.getValoresCol(atributo_termino[0], atributo_termino[1]);

        int n = a.size();
        double v = 0;

        //Se queda con el menor valor de cada columnas atributo_termino
        for (int i = 0; i < n; i++)
        {
            for (int j = 2; j < atributo_termino.size() - 2; j += 2)
            {
                v = dataset.getValor(atributo_termino[j], atributo_termino[j + 1], i);
                a[i] = min(v, a[i]);
            }
        }

        int t = atributo_termino.size();
        vector<double> 
            b = dataset.getValoresCol(atributo_termino[t - 2], atributo_termino[t - 1]);

        return Utils::subSetHood(a, b);
    }


    double FuzzyID3::getAmbiguedad(Dataset dataset, string nombreClase, string nombreAtributo, vector<string >evidence)
    {
        vector<string> terms = dataset.getTerminosLinguisticos(nombreAtributo);
        vector<string>  classTerms = dataset.getTerminosLinguisticos(nombreClase);
        vector<double> a;

        for (int i = 0; i < evidence.size() - 1; i += 2) 
        {
            if (a.size()== 0) 
            {
                a = dataset.getValoresCol(evidence[i],evidence[i + 1]);
            }
            else 
            {
                vector<double> aPrime = dataset.getValoresCol(evidence[i],evidence[i + 1]);
                for (int j = 0; j < aPrime.size(); j++) 
                {
                    a[j] = min(a[j], aPrime[j]);
                }
            }
        }

        vector<vector<double>> b(terms.size());
        vector<double> weights(terms.size());
        double sum = 0;

        if (a.size()>0 ) 
        {
            for (int i = 0; i < a.size(); i++) 
            {
                if (a[i] < nivelSignificacia)
                {
                    a[i] = 0;
                }
            }

            int i = 0;

            for (string &term : terms) 
            {
                b[i] = dataset.getValoresCol(nombreAtributo,term);
                for (int j = 0; j < a.size(); j++) 
                {
                    b[i][j] = min(a[j], b[i][j]);
                }
                weights[i] = Utils::sum(b[i]);
                sum += weights[i++];
            }

            Utils::normalizeWith(&weights, sum);

            double g = 0;
            for (i = 0; i < weights.size(); i++) 
            {
                vector<double> normalizedPossibility(classTerms.size());
                double max = -1;
                for (int j = 0; j < classTerms.size(); j++) 
                {
                    vector<double> c = dataset.getValoresCol(nombreClase,classTerms[j]);
                    normalizedPossibility[j] = Utils::subSetHood(b[i], c);

                    if (normalizedPossibility[j] > max) 
                    {
                        max = normalizedPossibility[j];
                    }

                }

                Utils::normalizeWith(&normalizedPossibility, max);
                g += weights[i] * Utils::ambiguity(normalizedPossibility);
            }

            return g;
        }
        return -1;
    }

    double FuzzyID3::getAmbiguedad(Dataset dataset, string className, vector<string> evidence)
    {

        vector<string> classTerms = dataset.getTerminosLinguisticos(className);

        vector<double> a(0);
        for (int i = 0; i < evidence.size() - 1; i += 2) {
            if (a.size() == 0) 
            {
                a = dataset.getValoresCol(evidence[i],evidence[i + 1]);
            }
            else {
                vector<double> aPrime = dataset.getValoresCol(evidence[i],evidence[i + 1]);
                for (int j = 0; j < aPrime.size(); j++) 
                {
                    a[j] = min(a[j], aPrime[j]);
                }
            }
        }

        if (a.size() != 0) 
        {
            for (int i = 0; i < a.size(); i++) 
            {
                if (a[i] < nivelSignificacia)
                {
                    a[i] = 0;
                }
            }
            vector<double> normalizedPossibility(classTerms.size());
            double max = -1;
            for (int j = 0; j < classTerms.size(); j++) 
            {
                vector<double> b = dataset.getValoresCol(className,classTerms[j]);
                normalizedPossibility[j] = Utils::subSetHood(a, b);
                if (normalizedPossibility[j] > max) 
                {
                    max = normalizedPossibility[j];
                }
            }
            Utils::normalizeWith(&normalizedPossibility, max);

            return Utils::ambiguity(normalizedPossibility);
        }
        return -1;
    }



    //Rentorna la ambiguedad de atributo respecto a una clase
    double FuzzyID3::getAmbiguedad(Dataset dataset, string nombreClase, string nombreAtributo)
    {
        //Obtenemos los terminos linguisticos de la clase y del atributo
        vector<string> terminos        = dataset.getTerminosLinguisticos(nombreAtributo);
        vector<string> terminosClass   = dataset.getTerminosLinguisticos(nombreClase);

        vector<double> pesos (terminos.size());
        double sum = 0,sumaCol=0;

        //Matriz para almacenar los valores Fuzzy de los atributos
        vector<vector<double>> a(terminos.size());

        for (int i = 0;i< terminos.size(); i++) 
        {
            a[i] = dataset.getValoresCol(nombreAtributo,terminos[i]);

            for (int j = 0; j < a[i].size(); j++)
            {
                if (a[i][j] < nivelSignificacia)
                {
                    a[i][j] = 0;
                }
            }

            pesos[i] = Utils::sum(a[i]);;
            sum += pesos[i];
        }
        Utils::normalizeWith(&pesos, sum);

        double g = 0;
        for (int i = 0; i < terminos.size(); i++) 
        {
            vector<double> PosibilidadNormalizada(terminosClass.size());
            double max = -1;
            for (int j = 0; j < terminosClass.size(); j++) 
            {
                vector<double> b = dataset.getValoresCol(nombreClase, terminosClass[j]);
                PosibilidadNormalizada[j] = Utils::subSetHood(a[i], b);

                if (PosibilidadNormalizada[j] > max)
                {
                    max = PosibilidadNormalizada[j];
                }
            }
            Utils::normalizeWith(&PosibilidadNormalizada, max);

            g += pesos[i] * Utils::ambiguity(PosibilidadNormalizada);
        }
        return g;
    }

    vector<string> FuzzyID3::generarReglas(TreeNode node)
    {
        vector<string> lista;
        string rules = generateRules(node, "");
        int pos = 0;
        string delimitador = "\n";
        while (rules != "")
        {
            pos=rules.find(delimitador);
            lista.push_back(rules.substr(0, pos));
            rules= rules.substr(pos + delimitador.length());
        }
        return lista;
    }

    string FuzzyID3::generateRules(TreeNode node, string prefix)
    {

        if (node.isHoja()) 
        { 
            if (to_string(node.getValue()) != "inf")
            {
                return prefix + " THEN " + node.getTitulo() + " ( " + to_string(node.getValue()) + " )\n";
            }
            else
            {
                return prefix + " THEN " + node.getTitulo() + " ( " + to_string(0) + " )\n";
            }
        }
        else if (node.isRoot()) 
        {
            string rules = "";
            vector<TreeNode> childs = node.getHijos();
            for (TreeNode &child : childs) 
            {
                rules += generateRules(child.getHijos()[0], "IF " + node.getTitulo() + " IS " + child.getTitulo());
            }
            return rules;
        }
        else if (node.getTipoNodo() == "ATRIBUTO") 
        {
            string rules = "";
            vector<TreeNode> childs = node.getHijos();
            for (TreeNode &child : childs) 
            {
                rules += generateRules(child.getHijos()[0], prefix +" AND "+ node.getTitulo()+" IS "+child.getTitulo());
            }
            return rules;
        }
        return "";
    }

    void FuzzyID3::printTree(TreeNode root, string tabs)
    {
        if (root.getTipoNodo() == "ATRIBUTO") 
        {
            cout<<tabs + "|" + root.getTitulo() + "|"<<endl;
        }
        vector<TreeNode> children = root.getHijos();
        for (int i = 0; i < root.getChildrenCount(); i++) 
        {
            TreeNode node = children[i];
            if (node.isHoja()) 
            {
                if (to_string(node.getValue())!="inf" )
                {
                    cout << tabs + "\t\t" + "[" + node.getTitulo() + "](" + to_string(node.getValue()) + ")" << endl;
                }
                else
                {
                    cout << tabs + "\t\t" + "[" + node.getTitulo() + "](" + to_string(0) + ")" << endl;
                }
            }
            else if (node.getTipoNodo() == "VALOR") 
            {
                cout << tabs + "\t" + "<" + node.getTitulo() + ">"<<endl;
                printTree(node, "\t" + tabs);
            }
            else 
            {
                printTree(node, "\t" + tabs);
            }


        }
    }

    void FuzzyID3::guardarReglas(TreeNode root, string fileName, string ruta)
    {
        ofstream archivo;
        archivo.open(ruta + fileName);
        vector<string> lista = generarReglas(root);
        for (string &s:lista)
        {
            archivo << s+"\n";
        }
        archivo.close();
    }

    void FuzzyID3::guardaArbol(TreeNode root, string tabs, string fileName,string ruta)
    {
        ofstream archivo;
        archivo.open(ruta + fileName);
        string s = getStringTree(root, tabs);
        archivo << s;
        archivo.close();
    }

    string FuzzyID3::getStringTree(TreeNode root, string tabs)
    {
        string s = "";
        if (root.getTipoNodo() == "ATRIBUTO") 
        {
            s += (tabs + "|" + root.getTitulo() + "|\r\n");
        }
        vector<TreeNode> children = root.getHijos();

        for (int i = 0; i < root.getChildrenCount(); i++) 
        {
            TreeNode node = children[i];
            if (node.isHoja()) 
            {
                if (to_string(node.getValue()) != "inf")
                {
                    s += (tabs + "\t\t" + "[" + node.getTitulo() + "](" + to_string(node.getValue()) + ")") + "\r\n";
                }
                else
                {
                    s += (tabs + "\t\t" + "[" + node.getTitulo() + "](" + to_string(0) + ")") + "\r\n";
                }
            }
            else if (node.getTipoNodo() == "VALOR") 
            {
                s += tabs + "\t" + "<" + node.getTitulo() + ">\r\n";
                s += getStringTree(node, "\t" + tabs);
            }
            else 
            {
                s += getStringTree(node, "\t" + tabs);
            }
        }
        return s;
    }

    vector<double> FuzzyID3::clasificar(int inputIdx, Dataset dataset, string nombreClase, vector<string> reglas)
    {
        vector<string> classTerms = dataset.getTerminosLinguisticos(nombreClase);
        vector<double> classVals(classTerms.size());
        string terms, cls, regla;
        for (string &regla: reglas)
        {
            terms = regla.substr(3, regla.find(" THEN")-3);
            terms=Utils::trim_copy(terms);
            cls = regla.substr(regla.find("THEN")+5 , regla.find(" (")- regla.find("THEN") - 5);
            cls=Utils::trim_copy(cls);
            int classIdx = dataset.getTerminosLinguisticosIndex(nombreClase,cls);
            vector<string> condations = Utils::split(terms, " AND "); 
            vector<string> evidinces((int)(condations.size() * 2));

            for (int k = 0, i = 0; k < condations.size(); i += 2, k++) 
            {

                vector<string> condation = Utils::split(condations[k]," IS ");
                evidinces[i] = condation[0];
                evidinces[i + 1] = condation[1];
            }
            double v = dataset.getFuzzyValue(inputIdx, evidinces[0], evidinces[1]);
            for (int i = 2; i < evidinces.size(); i += 2) 
            {
                v = min(v, dataset.getFuzzyValue(inputIdx, evidinces[i], evidinces[i + 1]));
            }
            //cout << v << "-";
            classVals[classIdx] = max(v, classVals[classIdx]);
        }
        return classVals;
    }

    void FuzzyID3::guardarReporte(TreeNode root, string fileName, string ruta, float grado_verdad, double significancia) {

        ofstream archivo;
        archivo.open(ruta + fileName);
        archivo << "Umbral Grado de Verdad: " << grado_verdad << "\n";;
        archivo << "Umbral Significancia  : " << significancia << "\n";
        archivo << "\n";
        archivo << "\n";
        archivo << "Reglas Generadas por los datos:";
        archivo << "\n";
        archivo << "\n";
        vector<string> lista = generarReglas(root);
        for (string& s : lista)
        {
            archivo << s + "\n";
        }
        archivo.close();
    }