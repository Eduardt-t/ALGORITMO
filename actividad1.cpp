#include <iostream>
using namespace std;

class Pila {
private:
    int* PILA;
    int TOPE;
    int MAX;
public:
    Pila(int max) {
        MAX = max;
        PILA = new int[MAX];
        TOPE = -1; // Inicialmente la pila está vacía
    }

    ~Pila() {
        delete[] PILA;
    }

    bool Pila_vacia() {
        return (TOPE == -1);
    }

    bool Pila_llena() {
        return (TOPE == MAX - 1);
    }

    void Push(int DATO) {
        if (Pila_llena()) {
            cout << "Desbordamiento, Pila llena" << endl;
        } else {
            PILA[++TOPE] = DATO;
        }
    }

    void Pop() {
        if (Pila_vacia()) {
            cout << "Subdesbordamiento, Pila vacía" << endl;
        } else {
            cout << "Elemento eliminado: " << PILA[TOPE--] << endl;
        }
    }

    void Ver_pila() {
        if (Pila_vacia()) {
            cout << "La pila está vacía" << endl;
        } else {
            cout << "Pila:" << endl;
            for (int i = TOPE; i >= 0; i--) {
                cout << "|" << PILA[i] << "|" << endl;
            }
        }
    }
};

int main() {
    int maxPila;

    cout << "Ingrese el tamaño Máximo de la Pila: ";
    cin >> maxPila;

    Pila pila(maxPila);
    int opcion, valor;

    do {
        cout << "Agregar/push [1]" << endl;
        cout << "Remover/pop [2]" << endl;
        cout << "Ver pila [3]" << endl;
        cout << "Salir [0]" << endl;
        cout << "----------------" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese valor: ";
                cin >> valor;
                pila.Push(valor);
                break;
            case 2:
                pila.Pop();
                break;
            case 3:
                pila.Ver_pila();
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }

        if (opcion != 0) {
            cout << "Presione cualquier tecla para continuar ..." << endl;
            cin.ignore().get();
        }

    } while (opcion != 0);

    return 0;
}
