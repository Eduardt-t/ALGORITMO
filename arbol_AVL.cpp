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

    // Busca el lugar para insertar el nuevo nodo
    while (actual != nullptr && dat != actual->dato) {
        padre = actual;
        if (dat < actual->dato) {
            actual = actual->izquierdo;
        } else if (dat > actual->dato) {
            actual = actual->derecho;
        }
    }

    if (actual != nullptr) {
        return; // El dato ya existe, no se permite duplicados
    }

    // Crear nuevo nodo
    pNodo nuevoNodo = new Nodo{dat, 0, nullptr, nullptr, padre};

    if (padre == nullptr) {
        *a = nuevoNodo; // Primer nodo, es la raíz
    } else if (dat < padre->dato) {
        padre->izquierdo = nuevoNodo; // Insertar en la izquierda
    } else {
        padre->derecho = nuevoNodo; // Insertar en la derecha
    }

    // Aquí puedes llamar a la función de balanceo después de la inserción
    bool bo = true;
    if (padre != nullptr) {
        if (padre->izquierdo == nuevoNodo) {
            Reestructura_der(a, padre, bo);
        } else {
            Reestructura_izq(a, padre, bo);
        }
    }
}

void Borrar(Arbol* a, int dat) {
    pNodo actual = *a;
    pNodo padre = nullptr;

    // Busca el nodo a eliminar
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

    // Caso 1: Nodo con un solo hijo o sin hijos
    if (actual->izquierdo == nullptr || actual->derecho == nullptr) {
        pNodo nodoReemplazo = (actual->izquierdo != nullptr) ? actual->izquierdo : actual->derecho;

        if (padre == nullptr) {
            *a = nodoReemplazo; // Nodo raíz
        } else if (actual == padre->izquierdo) {
            padre->izquierdo = nodoReemplazo;
        } else {
            padre->derecho = nodoReemplazo;
        }

        if (nodoReemplazo != nullptr) {
            nodoReemplazo->padre = padre; // Actualiza el padre del nodo reemplazo
        }
        delete actual; // Elimina el nodo actual
    } else { // Caso 2: Nodo con dos hijos
        pNodo sucesor = actual->derecho;
        while (sucesor->izquierdo != nullptr) {
            sucesor = sucesor->izquierdo;
        }

        actual->dato = sucesor->dato; // Copia el dato del sucesor
        Borrar(&(actual->derecho), sucesor->dato); // Elimina el sucesor
    }
}

void Reestructura_izq(Arbol* a, pNodo& nodo, bool& bo) {
    if (bo) {
        if (nodo->FE == -1) {
            nodo->FE = 0; // Se equilibró
            bo = false;
        } else if (nodo->FE == 0) {
            nodo->FE = 1; // Aumentó la altura de la rama izquierda
            bo = false;
        } else if (nodo->FE == 1) { // Se requiere reestructuración
            pNodo nodo1 = nodo->derecho;

            if (nodo1->FE > 0) { // Rotación derecha-derecha
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
                nodo = nodo1; // Actualizamos el nodo
            } else { // Rotación derecha-izquierda
                pNodo nodo2 = nodo1->izquierdo;
                nodo->derecho = nodo2->izquierdo;
                nodo2->izquierdo = nodo;
                nodo1->izquierdo = nodo2->derecho;
                nodo2->derecho = nodo1;

                if (nodo2->FE == 1) {
                    nodo->FE = -1;
                } else {
                    nodo->FE = 0;
                }

                if (nodo2->FE == -1) {
                    nodo1->FE = 1;
                } else {
                    nodo1->FE = 0;
                }

                nodo2->FE = 0; // Nodo2 queda equilibrado
                nodo = nodo2; // Actualizamos el nodo
            }
        }
    }
}

void Reestructura_der(Arbol* a, pNodo& nodo, bool& bo) {
    if (bo) {
        if (nodo->FE == 1) {
            nodo->FE = 0; // Se equilibró
            bo = false;
        } else if (nodo->FE == 0) {
            nodo->FE = -1; // Aumentó la altura de la rama derecha
            bo = false;
        } else if (nodo->FE == -1) { // Se requiere reestructuración
            pNodo nodo1 = nodo->izquierdo;

            if (nodo1->FE < 0) { // Rotación izquierda-izquierda
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
                nodo = nodo1; // Actualizamos el nodo
            } else { // Rotación izquierda-derecha
                pNodo nodo2 = nodo1->derecho;
                nodo->izquierdo = nodo2->derecho;
                nodo2->derecho = nodo;
                nodo1->derecho = nodo2->izquierdo;
                nodo2->izquierdo = nodo1;

                if (nodo2->FE == -1) {
                    nodo->FE = 1;
                } else {
                    nodo->FE = 0;
                }

                if (nodo2->FE == 1) {
                    nodo1->FE = -1;
                } else {
                    nodo1->FE = 0;
                }

                nodo2->FE = 0; // Nodo2 queda equilibrado
                nodo = nodo2; // Actualizamos el nodo
            }
        }
    }
}

void Inserta_balanceado(Arbol* a, int dat) {
    bool bo = true; // Inicializamos bo como verdadero para indicar que la altura ha crecido
    Insertar(a, dat);

    // Equilibrar el árbol después de la inserción
    pNodo nodo = *a; // Asegurarse de trabajar con el nodo raíz
    if (nodo != nullptr) {
        if (nodo->dato < dat) {
            Reestructura_der(a, nodo, bo);
        } else {
            Reestructura_izq(a, nodo, bo);
        }
    }
}

void Elimina_balanceado(Arbol* a, int dat) {
    bool bo = false;
    Borrar(a, dat);
    // Aquí se llama a la reestructuración correspondiente
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
