#include <iostream>
#include <string>

// Estructura para un paciente
struct Paciente {
    std::string nombre;
    int edad;
    float peso;
    float altura;
};

// Nodo de la lista dinámica
struct Nodo {
    Paciente paciente;
    Nodo* siguiente;
};

// Función para agregar un paciente al principio de la lista
void agregarPaciente(Nodo*& cabeza, Paciente p) {
    Nodo* nuevo = new Nodo{p, cabeza};
    cabeza = nuevo;
}

// Función para imprimir la información de los pacientes
void imprimirPacientes(Nodo* cabeza) {
    Nodo* actual = cabeza;
    if (!actual) {
        std::cout << "La lista está vacía.\n";
        return;
    }
    while (actual) {
        std::cout << "Nombre: " << actual->paciente.nombre << ", Edad: " << actual->paciente.edad 
                  << " años, Peso: " << actual->paciente.peso << " kg, Altura: " 
                  << actual->paciente.altura << " m\n";
        actual = actual->siguiente;
    }
}

// Función para eliminar un paciente por nombre
void eliminarPaciente(Nodo*& cabeza, const std::string& nombre) {
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

    while (actual && actual->paciente.nombre != nombre) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual) {
        if (anterior) {
            anterior->siguiente = actual->siguiente;
        } else {
            cabeza = actual->siguiente;
        }
        delete actual;
        std::cout << "Paciente " << nombre << " eliminado.\n";
    } else {
        std::cout << "Paciente no encontrado.\n";
    }
}

// Función para liberar la memoria de la lista
void liberarLista(Nodo*& cabeza) {
    Nodo* actual = cabeza;
    Nodo* siguiente = nullptr;

    while (actual) {
        siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
}

void menu(Nodo*& cabeza) {
    int opcion;
    std::string nombre;
    Paciente paciente;
    
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Agregar paciente\n";
        std::cout << "2. Eliminar paciente\n";
        std::cout << "3. Mostrar pacientes\n";
        std::cout << "4. Salir\n";
        std::cout << "Elija una opción: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                std::cout << "Ingrese el nombre del paciente: ";
                std::cin.ignore(); // Para limpiar el buffer de entrada
                std::getline(std::cin, paciente.nombre);
                std::cout << "Ingrese la edad del paciente: ";
                std::cin >> paciente.edad;
                std::cout << "Ingrese el peso del paciente: ";
                std::cin >> paciente.peso;
                std::cout << "Ingrese la altura del paciente: ";
                std::cin >> paciente.altura;
                agregarPaciente(cabeza, paciente);
                break;
            case 2:
                std::cout << "Ingrese el nombre del paciente a eliminar: ";
                std::cin.ignore(); // Para limpiar el buffer de entrada
                std::getline(std::cin, nombre);
                eliminarPaciente(cabeza, nombre);
                break;
            case 3:
                std::cout << "Lista de pacientes:\n";
                imprimirPacientes(cabeza);
                break;
            case 4:
                liberarLista(cabeza);
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción no válida. Inténtelo de nuevo.\n";
                break;
        }
    } while (opcion != 4);
}

int main() {
    Nodo* cabeza = nullptr;

    menu(cabeza);

    return 0;
}
