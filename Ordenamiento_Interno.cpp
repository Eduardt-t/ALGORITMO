#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función de ordenamiento por Selección
void seleccion(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Función de ordenamiento Quicksort
void quicksort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Función para imprimir el vector en el formato deseado
void imprimirVector(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << "a[" << i << "]=" << arr[i];
        if (i != arr.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

// Función principal
int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Uso: " << argv[0] << " <N> <s/n para mostrar el contenido del vector>" << endl;
        return 1;
    }

    int N = atoi(argv[1]);
    
    // Validación de que N sea un valor positivo
    if (N <= 0) {
        cout << "Error: El valor de N debe ser un número entero positivo." << endl;
        return 0;
    }

    bool mostrar = argv[2][0] == 's';

    vector<int> arr(N);
    
    // Generar valores aleatorios para el vector
    srand(time(0));
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 10000;  // Genera números entre 0 y 9999
    }

    // Crear una copia del vector para cada método de ordenamiento
    vector<int> arrSeleccion = arr;
    vector<int> arrQuicksort = arr;

    // Mostrar el vector inicial si se solicitó
    if (mostrar) {
        imprimirVector(arr);
    }

    // Medir tiempo de Selección
    auto inicioSeleccion = high_resolution_clock::now();
    seleccion(arrSeleccion);
    auto finSeleccion = high_resolution_clock::now();
    auto duracionSeleccion = duration_cast<milliseconds>(finSeleccion - inicioSeleccion).count();

    // Medir tiempo de Quicksort
    auto inicioQuicksort = high_resolution_clock::now();
    quicksort(arrQuicksort, 0, N - 1);
    auto finQuicksort = high_resolution_clock::now();
    auto duracionQuicksort = duration_cast<milliseconds>(finQuicksort - inicioQuicksort).count();

    // Mostrar tabla de tiempos
    cout << "-----------------------------------------" << endl;
    cout << "Metodo\t\t|\tTiempo" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Seleccion\t|\t" << duracionSeleccion << " milisegundos" << endl;
    cout << "Quicksort\t|\t" << duracionQuicksort << " milisegundos" << endl;
    cout << "-----------------------------------------" << endl;

    // Mostrar vectores ordenados si se solicitó
    if (mostrar) {
        cout << "Seleccion ";
        imprimirVector(arrSeleccion);
        cout << "Quicksort ";
        imprimirVector(arrQuicksort);
    }

    return 0;
}

