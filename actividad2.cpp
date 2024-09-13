#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

struct Contenedor {
    int numero;
    string empresa;
};

int EncontrarPilaConContenedor(vector<stack<Contenedor>>& pilas, int numero) {
    for (size_t i = 0; i < pilas.size(); ++i) {
        stack<Contenedor> tempStack;
        while (!pilas[i].empty()) {
            if (pilas[i].top().numero == numero) {
                // Devolver los contenedores a la pila original
                while (!tempStack.empty()) {
                    pilas[i].push(tempStack.top());
                    tempStack.pop();
                }
                return i;
            }
            tempStack.push(pilas[i].top());
            pilas[i].pop();
        }
        // Devolver los contenedores a la pila original
        while (!tempStack.empty()) {
            pilas[i].push(tempStack.top());
            tempStack.pop();
        }
    }
    return -1;
}

void MostrarPila(stack<Contenedor> pila) {
    if (pila.empty()) {
        cout << "La pila está vacía" << endl;
        return;
    }
    while (!pila.empty()) {
        Contenedor c = pila.top();
        cout << "Contenedor " << c.numero << "/" << c.empresa << endl;
        pila.pop();
    }
}

void RetirarContenedor(vector<stack<Contenedor>>& pilas, int numero, size_t n) {
    int pilaIndex = EncontrarPilaConContenedor(pilas, numero);
    if (pilaIndex == -1) {
        cout << "El contenedor no se encontró en ninguna pila." << endl;
        return;
    }

    stack<Contenedor> pilaAux;

    // Remover contenedores encima del contenedor retirado
    while (!pilas[pilaIndex].empty()) {
        if (pilas[pilaIndex].top().numero == numero) {
            pilas[pilaIndex].pop();
            cout << "Contenedor " << numero << " retirado" << endl;
            break;
        } else {
            pilaAux.push(pilas[pilaIndex].top());
            pilas[pilaIndex].pop();
        }
    }

    // Mover los contenedores retirados a otras pilas con espacio
    while (!pilaAux.empty()) {
        bool movido = false;
        for (size_t j = 0; j < pilas.size(); ++j) {
            if (j != pilaIndex && pilas[j].size() < n) {
                pilas[j].push(pilaAux.top());
                pilaAux.pop();
                movido = true;
                break;
            }
        }
        if (!movido) {
            cout << "No hay espacio disponible para los contenedores." << endl;
            break;
        }
    }
}

int main() {
    size_t n, m;

    cout << "Ingrese el número máximo de contenedores por pila (n): ";
    cin >> n;
    cout << "Ingrese el número máximo de pilas (m): ";
    cin >> m;

    vector<stack<Contenedor>> pilas(m);

    int opcion;
    do {
        cout << "Ingrese operación:" << endl;
        cout << "Agregar contenedor [1]" << endl;
        cout << "Retirar contenedor [2]" << endl;
        cout << "Mostrar pilas [3]" << endl;
        cout << "Salir [0]" << endl;
        cout << "----------------" << endl;
        cout << "Opción: ";
        cin >> opcion;

        if (opcion == 1) {
            int numContenedores;
            cout << "Ingrese el número de contenedores a agregar: ";
            cin >> numContenedores;

            for (int i = 0; i < numContenedores; ++i) {
                Contenedor c;
                cout << "Ingrese el número del contenedor: ";
                cin >> c.numero;
                cout << "Ingrese el nombre de la empresa: ";
                cin >> c.empresa;

                bool agregado = false;
                for (size_t j = 0; j < pilas.size(); ++j) {
                    if (pilas[j].size() < n) {
                        pilas[j].push(c);
                        agregado = true;
                        break;
                    }
                }

                if (!agregado) {
                    cout << "No hay espacio en ninguna pila para el contenedor " << c.numero << endl;
                }
            }

        } else if (opcion == 2) {
            int numero;
            cout << "Ingrese el número del contenedor a retirar: ";
            cin >> numero;
            RetirarContenedor(pilas, numero, n);
        } else if (opcion == 3) {
            for (size_t i = 0; i < pilas.size(); ++i) {
                cout << "Pila " << i + 1 << ":" << endl;
                MostrarPila(pilas[i]);
            }
        }

        if (opcion != 0) {
            cout << "Presione cualquier tecla para continuar ..." << endl;
            cin.ignore();
            cin.get();
        }

    } while (opcion != 0);

    return 0;
}
