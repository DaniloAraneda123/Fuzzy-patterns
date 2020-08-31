#pragma once
#include<vector>
#include <math.h> 
#include <algorithm>
#include <cctype>
#include <locale>

using namespace std;

class Utils 
{

public:
    static double vagueness(vector<double> vals) 
    {
        double vag = 0;
        for (double &v : vals)
        {
            vag += (v * ln(v) + (1 - v) * ln(1 - v));
        }
        if (vag == 0) 
        {
            return 0;
        }
        vag /= (vals.size());
        return vag * -1;
    }

    double getMax(vector<double> arr)
    {
        double max = arr[0];
        for (double &a : arr) {
            if (a > max) {
                max = a;
            }
        }

        return max;
    }

    static double ln(double x)
    {
        if (x == 0) {
            return 0;
        }
        return log(x) / log(2);
    }

    static void normalizeWith(vector<double>* arr, double v)
    {
        for (int i = 0; i < (*arr).size(); i++)
        {
            (*arr)[i]= (*arr)[i]/v;
        }
    }

    //Retorna -1 si es infinito el resultado
    static double subSetHood(vector<double>  a, vector<double>  b) 
    {
        double s = sum(a);
        if (s == 0) 
        {
            return -1;
        }
        return sumOfMinimum(a, b) / sum(a);
    }

    static double sum(vector<double>  a) 
    {
        double s = 0.0;
        for (double &v : a) 
        {
            s += v;
        }
        return s;
    }

    static double average(vector<double> a) 
    {
        return sum(a) / a.size();
    }

    static double ambiguity(vector<double> a)
    {
        int n = a.size();
        sort(a.begin(),a.end());

        vector<double> ap(n+1);

        for (int i = 0; i < n; i++) 
        {
            ap[i] = a[n-i-1];
        }

        double s = 0;
        for (int i = 0; i < n; i++) 
        {
            s += (ap[i] - ap[i + 1]) * log((i+1));
        }

        return s;
    }

    static double ambiguityOfAttribute() 
    {
        return 0;
    }

    
    static double ambiguity(vector<double> a, double alpha) 
    {
        int n = a.size();
        for (int i = 0; i < n; i++) 
        {
            a[i] = a[i] < alpha ? 0 : a[i];
        }
        sort(a.begin(),a.end());

        normalizeWith(&a, a[n - 1]);

        double s = a[0] * log((double)n);

        for (int j = n - 1, k = 1; j > 0; j--, k++) 
        {
            s += (a[j] - a[j - 1]) * log(k);
        }
        return s;
    }

    static double sumOfMinimum(vector<double> a, vector<double> b) 
    {

        double s = 0.0;
        for (int i = 0, n = a.size(); i < n; i++) {
            s += a[i] < b[i] ? a[i] : b[i];
        }

        return s;

    }

    static vector<double> mini(vector<double> a, vector<double>  b) 
    {

        int n = a.size();
        vector<double> c(n); 
        for (int i = 0; i < n; i++) 
        {
            c[i] = a[i] < b[i] ? a[i] : b[i];
        }
        return c;
    }

    static vector<double> toDoubleArray(vector<string> arr) 
    {
        int n = arr.size();
        vector<double> da(n);
        int i = 0;
        for (string &e : arr) 
        {
            da[i++] = stod(e);
        }
        return da;
    }

    static vector<double> toDoubleArray(vector<string> arr, int startFrom)
    {
        int n = arr.size();
        vector<double> da(n - startFrom);

        int i = 0;
        for (int k = startFrom; k < n; k++) 
        {
            da[i++] = stod(arr[k]);
        }

        return da;
    }

    static vector<double> toDoubleArray(vector<string> arr, int startFrom, int to)
    {
        int n = arr.size();

        vector<double> da(to - startFrom + 1);
        int i = 0;
        for (int k = startFrom; k <= to; k++) 
        {
            da[i++] = stod(arr[k]);
        }
        return da;
    }

    static double entropy(vector<double> vals)
    {
        double entropy = 0;
        for (double &v : vals) 
        {
            entropy += v * ln(v);
        }
        return -entropy;
    }

    // trim from start (in place)
    static inline void ltrim(string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
            }));
    }

    // trim from end (in place)
    static inline void rtrim(string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
            }).base(), s.end());
    }

    // trim from both ends (in place)
    static inline string trim(string& s) {
        ltrim(s);
        rtrim(s);
        return s;
    }

    // trim from start (copying)
    static inline std::string ltrim_copy(std::string s) {
        ltrim(s);
        return s;
    }

    // trim from end (copying)
    static inline std::string rtrim_copy(std::string s) {
        rtrim(s);
        return s;
    }

    // trim from both ends (copying)
    static inline std::string trim_copy(std::string s) {
        trim(s);
        return s;
    }

    static vector<string> split(string cadena,string delimitador)
    {
        size_t pos = 0;

        string token;
        vector<string> tokens;
        while ((pos = cadena.find(delimitador)) != string::npos)
        {
            token = cadena.substr(0, pos);
            tokens.push_back(token);
            cadena.erase(0, pos + delimitador.length());
        }
        tokens.push_back(cadena)
            ;
        return tokens;
    }

private:
    static bool myfunction(int i, int j) { return (i < j); }
};