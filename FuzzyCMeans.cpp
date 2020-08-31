#include <math.h>
#include "FuzzyCMeans.h"

using namespace std;


/*
¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡NOTA IMPORTANTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
El disenio por contranto aun no es documentando en el codigo.
*/

	FuzzyCMeans::FuzzyCMeans()
	{
		ejecucion = false;
	}

//Construcctor
	FuzzyCMeans::FuzzyCMeans(int nDatos, int nClusters, int nDimensiones, int it, double error, double gradoFuzzy, double** datos)
	{
		num_datos = nDatos;
		num_clusters = nClusters;
		num_dimensiones = nDimensiones;
		iteraciones = it;
		epsilon = error;
		borrosidad = gradoFuzzy;
		data_puntos = datos;


		//Crear Matriz Centroides
		centroides = new double* [num_clusters];
		for (int i = 0; i < num_clusters; i++)
		{
			centroides[i] = new double[num_dimensiones];

			for (int j = 0; j < num_dimensiones; j++)
			{
				centroides[i][j] = 0;
			}
		}

		//Crear Matriz grados de pertencia 
		double s;
		int r, rval;
		grado_pertenencia = new double* [num_datos];

		for (int i = 0; i < num_datos; i++) 
		{
			s = 0.0;
			r = 100;
			grado_pertenencia[i] = new double[num_clusters];
			for (int j = 0; j < num_clusters; j++) 
			{
				rval = rand() % (r + 1);
				r -= rval;
				grado_pertenencia[i][j] = rval / 100.0;
				s += grado_pertenencia[i][j];
			}
			grado_pertenencia[i][0] = 1.0 - s;
		}
		ejecucion = false;
	}


	/*
	*mientras la el error sea mayor que el permitido o  el numero de iteraciones actual es menor que el limite,
	El algoritmo seguira recalculando la posicion de los centroides.
	*/
	double** FuzzyCMeans::fcm(bool verIteraciones)
	{
		double max_dif=0;
		int iteracion = 0,subIteracion=0;

		do {
			calcular_vectores_centroides();
			max_dif = actualizar_pertenencias();
			iteracion++;
			subIteracion++;

			if (subIteracion==5 && verIteraciones==true)
			{
				imprimirIteracion(max_dif, iteracion);
				subIteracion = 0;
			}

		} while (max_dif > epsilon && iteracion < iteraciones);
		ejecucion = true;
		return centroides;
	}

	//guarda los en la ruta destino
	bool FuzzyCMeans::guardarCentroides(string ruta)
	{
		if (ejecucion==true)
		{
			ofstream archivo;
			archivo.open(ruta+"centroides.txt");
			archivo << num_clusters <<";"<<num_dimensiones<<"\n";
			for (int i = 0; i < num_clusters; i++) 
			{
				archivo << centroides[i][0];
				for (int j = 1; j < num_dimensiones; j++)
				{
					archivo <<";"<<centroides[i][j];
				}
				archivo << "\n";
			}
			archivo.close();
			return true;
		}
		return false;
	}

	//Carga los los centroides almacenados en un archivo .csv y establece libera y establece los demas parametros en null 
	void FuzzyCMeans::cargarCentroides(string ruta)
	{
		char delimitador = ';';
		string linea, campo;
		stringstream ss;
		ifstream fichero(ruta);

		if (!fichero)
		{
			cout << "Archivo no encontrado, ERROR";
			exit(1); // terminate si no se encuentra el archivo
		}

		// Rescatamos el numero de cluster y el numero de dimensiones
		getline(fichero, linea);
		ss = stringstream(linea);
		getline(ss, campo, delimitador);
		num_clusters = std::stoi(campo);
		getline(ss, campo, delimitador);
		num_dimensiones = std::stoi(campo);

		//eliminamos la matriz de datos anterior
		free(centroides);
		free(data_puntos);
		free(grado_pertenencia);
		grado_pertenencia = nullptr;
		centroides= nullptr;
		data_puntos= nullptr;

		//Saltamos Linea
		getline(fichero, linea);

		double** matriz;
		matriz = new double*[num_clusters];
		for (int i=0;i< num_clusters;i++)
		{
			ss = stringstream(linea);
			matriz[i] = new double[num_dimensiones];
			for (int j=0;j< num_dimensiones;i++)
			{
				//Leemos el numero
				getline(ss, campo, delimitador);
				matriz[i][j] = stod(campo);
			}
			//Avanzamos a la siguiente linea
			getline(fichero, linea);
		}
		fichero.close();
		centroides = matriz;
		actualizar_pertenencias();
	}

	//setea el conjunto de datos usar para entrenar
	void FuzzyCMeans::setData(double** datos)
	{
		data_puntos=datos;
		ejecucion = true;
	}

	//Evalua la pertenencia de un dato a cada Cluster
	double* FuzzyCMeans::evaluarDato(double* datos)
	{
		double t, p, sum;
		double* petenencias = new double[num_clusters];

		for (int i = 0; i < num_clusters; i++)
		{
			sum = 0.0;
			p = 2 / (borrosidad - 1);

			for (int k = 0; k < num_clusters; k++)
			{
				t = get_norm(datos, i) / get_norm(datos, k);
				t = pow(t, p);
				sum += t;
			}

			petenencias[i]= 1.0 / sum;

		}
		return petenencias;
	}

	// Calcula la norma del vecto entre el punto i y el centroide j.
	double FuzzyCMeans::get_norm(double* datos, int j)
	{
		int k;//dimension
		double sum = 0.0;
		for (k = 0; k < num_dimensiones; k++)
		{
			sum += pow(datos[k] - centroides[j][k], 2);
		}
		return sqrt(sum);
	}

	// Calcula la norma del vecto entre el punto i y el centroide j.
	double FuzzyCMeans::get_norm(int i, int j)
	{
		int k;//dimension
		double sum = 0.0;

		for (k = 0; k < num_dimensiones; k++)
		{
			sum += pow(data_puntos[i][k] - centroides[j][k], 2);
		}

		return sqrt(sum);
	}

	//retorna los clusters resultantes
	double** FuzzyCMeans::getCentroides()
	{
		return centroides;
	}

	//Retorna los grados de pertenencia de cada tupla
	double** FuzzyCMeans::getPertenencia()
	{
		return grado_pertenencia;
	}

	/*
	* Imprime los datos de la itecion actual
	*/
	void FuzzyCMeans::imprimirIteracion(double max_dif, int iteracion)
	{
		cout << "Iteracion: " << iteracion << "  , error: " << max_dif << endl;
		for (int i = 0; i < num_clusters; i++)
		{
			cout << "Centroide " << (i + 1) << ":  ";
			for (int j = 0; j < num_dimensiones; j++)
			{
				cout << centroides[i][j] << " | ";
			}
			cout << endl;
		}
		cout << endl<<endl;
	}

	/*
	A partir de la distancia de la dintacia de los puntos a los centroides viejos, se calcula los nuevo centroides.
	*/
	void FuzzyCMeans::calcular_vectores_centroides()
	{
		double numerator, denominator;
		double** t;
		t = new double* [num_datos];

		for (int i = 0; i < num_datos; i++)
		{
			t[i] = new double [num_clusters];
			for (int j = 0; j < num_clusters; j++)
			{
				t[i][j] = pow(grado_pertenencia[i][j], borrosidad);
			}
		}

		for (int j = 0; j < num_clusters; j++)
		{
			for (int k = 0; k < num_dimensiones; k++)
			{
				numerator = 0.0;
				denominator = 0.0;
				for (int i = 0; i < num_datos; i++)
				{
					numerator += t[i][j] * data_puntos[i][k];
					denominator += t[i][j];
				}
				centroides[j][k] = numerator / denominator;
			}
		}
	}

	/*
	Se calcula la pertenencia de una tupla i a un centride j
	*/
	double FuzzyCMeans::get_new_pertenecia(int i, int j)
	{
		int k;
		double t, p, sum;
		sum = 0.0;
		p = 2 / (borrosidad - 1);

		for (k = 0; k < num_clusters; k++)
		{
			t = get_norm(i, j) / get_norm(i, k);
			t = pow(t, p);
			sum += t;
		}

		return 1.0 / sum;
	}

	/*
	Este metodo actualiza la matriz la pertenencia de cada
	punto por cada cluster , ademas retorna la diferencia entre
	la maxima diferencia entre la nueva pertenencia y la pertenencia anterior de un dato
	*/
	double FuzzyCMeans::actualizar_pertenencias()
	{
		int i, j;
		double new_Wij;
		double max_dif = 0, dif;
		for (j = 0; j < num_clusters; j++)
		{

			for (i = 0; i < num_datos; i++)
			{

				new_Wij = get_new_pertenecia(i, j);
				dif = new_Wij - grado_pertenencia[i][j];

				if (dif > max_dif)
				{
					max_dif = dif;
				}

				grado_pertenencia[i][j] = new_Wij;

			}

		}
		return max_dif;
	}

