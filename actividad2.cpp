#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

struct Contenedor {
    int numero;
    string empresa;
};

class PilaContenedores {
    stack<Contenedor> pila;
    int capacidad;

public:
    PilaContenedores(int cap) : capacidad(cap) {}

    bool estaLlena() const {
        return pila.size() >= capacidad;
    }

    bool estaVacia() const {
        return pila.empty();
    }

    bool agregarContenedor(const Contenedor& cont) {
        if (estaLlena()) {
            return false;
        }
        pila.push(cont);
        return true;
    }

    bool retirarContenedor(int numero) {
        stack<Contenedor> aux;
        bool encontrado = false;

        while (!pila.empty()) {
            if (pila.top().numero == numero) {
                encontrado = true;
                break;
            }
            aux.push(pila.top());
            pila.pop();
        }

        while (!aux.empty()) {
            pila.push(aux.top());
            aux.pop();
        }

        if (encontrado) {
            pila.pop();
        }

        return encontrado;
    }

    Contenedor obtenerContenedor() const {
        if (!pila.empty()) {
            return pila.top();
        }
        return Contenedor{-1, ""};  // Retorna un contenedor vacío en caso de pila vacía
    }

    void mostrarPila() const {
        stack<Contenedor> aux = pila;
        while (!aux.empty()) {
            Contenedor cont = aux.top();
            cout << "Contenedor " << cont.numero << "/" << cont.empresa << endl;
            aux.pop();
        }
        if (pila.empty()) {
            cout << "La pila está vacía" << endl;
        }
    }
};

class GestorPilas {
    vector<PilaContenedores> pilas;
    int capacidad;

public:
    GestorPilas(int numPilas, int cap) : capacidad(cap) {
        for (int i = 0; i < numPilas; ++i) {
            pilas.emplace_back(cap);
        }
    }

    void agregarContenedores() {
        int numContenedores;
        cout << "Ingrese el número de contenedores a agregar: ";
        cin >> numContenedores;

        if (numContenedores <= 0) {
            cout << "Número de contenedores no válido." << endl;
            return;
        }

        for (int i = 0; i < numContenedores; ++i) {
            if (i >= 1 && todasPilasLlenas()) {
                cout << "No hay espacio en ninguna pila para agregar nuevos contenedores." << endl;
                return;
            }

            Contenedor cont;
            cout << "Ingrese el número del contenedor: ";
            cin >> cont.numero;
            cout << "Ingrese el nombre de la empresa: ";
            cin >> cont.empresa;

            bool agregado = false;
            for (auto& pila : pilas) {
                if (pila.agregarContenedor(cont)) {
                    agregado = true;
                    break;
                }
            }

            if (!agregado) {
                cout << "No se pudo agregar el contenedor " << cont.numero << " en ninguna pila." << endl;
            }
        }
    }

    void retirarContenedor() {
        int numero;
        cout << "Ingrese el número del contenedor a retirar: ";
        cin >> numero;

        vector<Contenedor> moverContenedores;
        bool encontrado = false;

        // Buscar el contenedor y almacenar los que están encima
        for (auto& pila : pilas) {
            while (!pila.estaVacia() && pila.obtenerContenedor().numero != numero) {
                moverContenedores.push_back(pila.obtenerContenedor());
                pila.retirarContenedor(pila.obtenerContenedor().numero);
            }
            if (!pila.estaVacia() && pila.obtenerContenedor().numero == numero) {
                encontrado = true;
                pila.retirarContenedor(numero);
                break;
            }
        }

        if (!encontrado) {
            cout << "El contenedor " << numero << " no se encontró." << endl;
            return;
        }

        // Intentar reubicar los contenedores
        for (auto& cont : moverContenedores) {
            bool reubicado = false;
            for (auto& pila : pilas) {
                if (!pila.estaLlena()) {
                    pila.agregarContenedor(cont);
                    reubicado = true;
                    break;
                }
            }
            if (!reubicado) {
                cout << "No se pudo mover algunos contenedores a otras pilas. Contenedores que no se movieron:" << endl;
                for (const auto& c : moverContenedores) {
                    cout << "Contenedor " << c.numero << "/" << c.empresa << endl;
                }
                mostrarPrimerosContenedores();
                cout << "Por favor, asegúrese de tener espacio en las pilas antes de intentar retirar más contenedores." << endl;
                return;
            }
        }

        cout << "Contenedor " << numero << " retirado." << endl;
    }

    void mostrarPilas() const {
        for (size_t i = 0; i < pilas.size(); ++i) {
            cout << "Pila " << (i + 1) << ":" << endl;
            pilas[i].mostrarPila();
        }
    }

    void mostrarPrimerosContenedores() const {
        cout << "Primeros contenedores en cada pila:" << endl;
        for (size_t i = 0; i < pilas.size(); ++i) {
            if (!pilas[i].estaVacia()) {
                Contenedor cont = pilas[i].obtenerContenedor();
                cout << "Pila " << (i + 1) << ": Contenedor " << cont.numero << "/" << cont.empresa << endl;
            } else {
                cout << "Pila " << (i + 1) << ": La pila está vacía" << endl;
            }
        }
    }

private:
    bool todasPilasLlenas() const {
        for (const auto& pila : pilas) {
            if (!pila.estaLlena()) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    int n, m;
    cout << "Ingrese el número máximo de contenedores por pila (n): ";
    cin >> n;
    cout << "Ingrese el número máximo de pilas (m): ";
    cin >> m;

    GestorPilas gestor(m, n);

    while (true) {
        int opcion;
        cout << "Ingrese operación:" << endl;
        cout << "Agregar contenedor [1]" << endl;
        cout << "Retirar contenedor [2]" << endl;
        cout << "Mostrar pilas [3]" << endl;
        cout << "Salir [0]" << endl;
        cout << "----------------" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                gestor.agregarContenedores();
                break;
            case 2:
                gestor.retirarContenedor();
                break;
            case 3:
                gestor.mostrarPilas();
                break;
            case 0:
                return 0;
            default:
                cout << "Opción no válida." << endl;
        }
    }
}
