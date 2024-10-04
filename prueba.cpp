#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits> // Para std::numeric_limits

struct Nodo {
    int dato;
    int FE; // Factor de equilibrio
    Nodo* derecho;
    Nodo* izquierdo;
    Nodo* padre;
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;

void Insertar(Arbol* a, int dat);
void Borrar(Arbol* a, int dat);
void PreOrden(Arbol, std::ofstream &fp);
void Reestructura_izq(Arbol* a, pNodo& nodo, bool& bo);
void Reestructura_der(Arbol* a, pNodo& nodo, bool& bo);
void Inserta_balanceado(Arbol* a, int dat);
void Elimina_balanceado(Arbol* a, int dat);
void ModificarElemento(Arbol* a, int viejo, int nuevo);
void GenerarGrafo(Arbol);
void MenuPrincipal();
void Podar(Arbol* a);
int LeerOpcion();
int LeerNumero();

int main() {
    Arbol ArbolInt = NULL;
    int opcion = 0;
    int valor;

    while (opcion != 5) {
        MenuPrincipal();
        opcion = LeerOpcion();  // Lectura segura de la opción

        switch (opcion) {
            case 1:
                valor = LeerNumero();  // Lectura segura de un número
                Inserta_balanceado(&ArbolInt, valor);
                break;
            case 2:
                valor = LeerNumero();  // Lectura segura de un número
                Elimina_balanceado(&ArbolInt, valor);
                break;
            case 3: {  // Modificar un número
                int viejo = LeerNumero();
                int nuevo = LeerNumero();
                ModificarElemento(&ArbolInt, viejo, nuevo);
                break;
            }
            case 4:
                GenerarGrafo(ArbolInt);
                break;
            case 5:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    }

    Podar(&ArbolInt);
    return 0;
}

int LeerOpcion() {
    int opcion;
    while (true) {
        std::cout << "Ingrese su opción: ";
        std::cin >> opcion;

        if (std::cin.fail()) {  // Si la entrada falla (se ingresa algo que no es un número)
            std::cin.clear();  // Limpia el estado de error de cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignora el resto de la entrada
            std::cout << "Entrada no válida. Por favor ingrese un número.\n";
        } else {
            return opcion;  // Entrada válida
        }
    }
}

int LeerNumero() {
    int numero;
    while (true) {
        std::cout << "Ingrese un número: ";
        std::cin >> numero;

        if (std::cin.fail()) {  // Si la entrada falla (se ingresa algo que no es un número)
            std::cin.clear();  // Limpia el estado de error de cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignora el resto de la entrada
            std::cout << "Entrada no válida. Por favor ingrese un número.\n";
        } else {
            return numero;  // Entrada válida
        }
    }
}

void Insertar(Arbol* a, int dat) {
    pNodo padre = nullptr;
    pNodo actual = *a;

    while (actual != nullptr && dat != actual->dato) {
        padre = actual;
        if (dat < actual->dato) {
            actual = actual->izquierdo;
        } else if (dat > actual->dato) {
            actual = actual->derecho;
        }
    }

    if (actual != nullptr) {
        return; // El dato ya existe
    }

    if (padre == nullptr) {
        *a = new Nodo{dat, 0, nullptr, nullptr, nullptr}; // Primer nodo
    } else if (dat < padre->dato) {
        actual = new Nodo{dat, 0, nullptr, nullptr, padre};
        padre->izquierdo = actual;
    } else {
        actual = new Nodo{dat, 0, nullptr, nullptr, padre};
        padre->derecho = actual;
    }
}

void Borrar(Arbol* a, int dat) {
    pNodo actual = *a;
    pNodo padre = nullptr;
    pNodo nodoReemplazo;

    while (actual != nullptr && actual->dato != dat) {
        padre = actual;
        if (dat < actual->dato) {
            actual = actual->izquierdo;
        } else {
            actual = actual->derecho;
        }
    }

    if (actual == nullptr) {
        std::cout << "El dato no existe en el árbol.\n";
        return;
    }

    if (actual->izquierdo == nullptr || actual->derecho == nullptr) {
        nodoReemplazo = (actual->izquierdo != nullptr) ? actual->izquierdo : actual->derecho;

        if (padre == nullptr) {
            *a = nodoReemplazo; // Nodo raíz
        } else if (actual == padre->izquierdo) {
            padre->izquierdo = nodoReemplazo;
        } else {
            padre->derecho = nodoReemplazo;
        }

        delete actual;
    } else {
        pNodo sucesor = actual->derecho;
        pNodo sucesorPadre = actual;

        while (sucesor->izquierdo != nullptr) {
            sucesorPadre = sucesor;
            sucesor = sucesor->izquierdo;
        }

        actual->dato = sucesor->dato;

        if (sucesorPadre->izquierdo == sucesor) {
            sucesorPadre->izquierdo = sucesor->derecho;
        } else {
            sucesorPadre->derecho = sucesor->derecho;
        }

        delete sucesor;
    }
}

void Reestructura_izq(Arbol* a, pNodo& nodo, bool& bo) {
    if (bo) {
        if (nodo->FE == -1) {
            nodo->FE = 0;
            bo = false;
        } else if (nodo->FE == 0) {
            nodo->FE = 1;
            bo = false;
        } else if (nodo->FE == 1) {
            pNodo nodo1 = nodo->derecho;
            if (nodo1->FE >= 0) {
                nodo->derecho = nodo1->izquierdo;
                nodo1->izquierdo = nodo;
                if (nodo1->FE == 0) {
                    nodo->FE = 1;
                    nodo1->FE = -1;
                    bo = false;
                } else {
                    nodo->FE = 0;
                    nodo1->FE = 0;
                }
                nodo = nodo1;
            } else {
                pNodo nodo2 = nodo1->izquierdo;
                nodo->derecho = nodo2->izquierdo;
                nodo2->izquierdo = nodo;
                nodo1->izquierdo = nodo2->derecho;
                nodo2->derecho = nodo1;
                nodo->FE = (nodo2->FE == 1) ? -1 : 0;
                nodo1->FE = (nodo2->FE == -1) ? 1 : 0;
                nodo2->FE = 0;
                nodo = nodo2;
            }
        }
    }
}

void Reestructura_der(Arbol* a, pNodo& nodo, bool& bo) {
    if (bo) {
        if (nodo->FE == 1) {
            nodo->FE = 0;
            bo = false;
        } else if (nodo->FE == 0) {
            nodo->FE = -1;
            bo = false;
        } else if (nodo->FE == -1) {
            pNodo nodo1 = nodo->izquierdo;
            if (nodo1->FE <= 0) {
                nodo->izquierdo = nodo1->derecho;
                nodo1->derecho = nodo;
                if (nodo1->FE == 0) {
                    nodo->FE = -1;
                    nodo1->FE = 1;
                    bo = false;
                } else {
                    nodo->FE = 0;
                    nodo1->FE = 0;
                }
                nodo = nodo1;
            } else {
                pNodo nodo2 = nodo1->derecho;
                nodo->izquierdo = nodo2->derecho;
                nodo2->derecho = nodo;
                nodo1->derecho = nodo2->izquierdo;
                nodo2->izquierdo = nodo1;
                nodo->FE = (nodo2->FE == -1) ? 1 : 0;
                nodo1->FE = (nodo2->FE == 1) ? -1 : 0;
                nodo2->FE = 0;
                nodo = nodo2;
            }
        }
    }
}

void Inserta_balanceado(Arbol* a, int dat) {
    bool bo = false;
    Insertar(a, dat);
    // Aquí puedes agregar las llamadas a Reestructura_izq o Reestructura_der según sea necesario
}

void Elimina_balanceado(Arbol* a, int dat) {
    bool bo = false;
    Borrar(a, dat);
    // Aquí puedes agregar las llamadas a Reestructura_izq o Reestructura_der según sea necesario
}

void ModificarElemento(Arbol* a, int viejo, int nuevo) {
    Borrar(a, viejo); // Elimina el viejo
    Inserta_balanceado(a, nuevo); // Inserta el nuevo
}

void GenerarGrafo(Arbol ArbolInt) {
    std::ofstream fp("grafo.txt");
    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=yellow];\n";
    if (ArbolInt)
        fp << "nullraiz->" << ArbolInt->dato << ";\n";
    PreOrden(ArbolInt, fp);
    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

void PreOrden(Arbol a, std::ofstream &fp) {
    if (a) {
        fp << a->dato << ";\n";
        if (a->izquierdo)
            fp << a->dato << "->" << a->izquierdo->dato << ";\n";
        if (a->derecho)
            fp << a->dato << "->" << a->derecho->dato << ";\n";
        PreOrden(a->izquierdo, fp);
        PreOrden(a->derecho, fp);
    }
}

void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        delete *a;
        *a = nullptr;
    }
}

void MenuPrincipal() {
    std::cout << "\n";
    std::cout << "<1> Ingresar número\n";
    std::cout << "<2> Eliminar número\n";
    std::cout << "<3> Modificar número\n";
    std::cout << "<4> Generar grafo\n";
    std::cout << "<5> Salir\n";
    std::cout << "\n";
}

