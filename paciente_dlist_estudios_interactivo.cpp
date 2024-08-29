#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>

struct Paciente {
    std::string nombre;
    int edad;
    float peso;
    float altura;
};

struct Nodo {
    Paciente paciente;
    Nodo* siguiente;
};

// Función para agregar un paciente al principio de la lista
void agregarPaciente(Nodo*& cabeza, Paciente p) {
    Nodo* nuevo = new Nodo{p, cabeza};
    cabeza = nuevo;
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
        std::cout << "Paciente " << nombre << " no encontrado.\n";
    }
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

// Función para calcular el IMC de un paciente
float calcularIMC(const Paciente& p) {
    return p.peso / std::pow(p.altura, 2);
}

// Función para clasificar el IMC
std::string clasificarIMC(float imc) {
    if (imc < 18.5) return "Bajo peso";
    if (imc < 25) return "Sano";
    if (imc < 30) return "Sobrepeso";
    return "Obesidad";
}

// Función para calcular el promedio de edad y peso
void calcularPromedios(Nodo* cabeza, float& promedioEdad, float& promedioPeso) {
    int totalEdad = 0;
    float totalPeso = 0;
    int count = 0;

    Nodo* actual = cabeza;
    while (actual) {
        totalEdad += actual->paciente.edad;
        totalPeso += actual->paciente.peso;
        count++;
        actual = actual->siguiente;
    }

    if (count > 0) {
        promedioEdad = static_cast<float>(totalEdad) / count;
        promedioPeso = totalPeso / count;
    } else {
        promedioEdad = 0;
        promedioPeso = 0;
    }
}

// Función para cargar pacientes desde un archivo
void cargarPacientesDesdeArchivo(Nodo*& cabeza, const std::string& archivo) {
    std::ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        std::cout << "No se pudo abrir el archivo.\n";
        return;
    }

    std::string linea;
    while (std::getline(archivoEntrada, linea)) {
        std::stringstream ss(linea);
        Paciente paciente;
        std::getline(ss, paciente.nombre, ',');
        ss >> paciente.edad;
        ss.ignore();
        ss >> paciente.peso;
        ss.ignore();
        ss >> paciente.altura;

        agregarPaciente(cabeza, paciente);
    }
    archivoEntrada.close();
    std::cout << "Pacientes cargados desde el archivo.\n";
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

// Función para mostrar el menú y manejar la entrada del usuario
void mostrarMenu(Nodo*& cabeza) {
    int opcion;
    do {
        std::cout << "\nMenú:\n";
        std::cout << "1. Agregar paciente\n";
        std::cout << "2. Eliminar paciente\n";
        std::cout << "3. Imprimir pacientes\n";
        std::cout << "4. Calcular estadísticas\n";
        std::cout << "5. Cargar pacientes desde archivo\n";
        std::cout << "6. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();  // Ignorar el carácter de nueva línea restante

        switch (opcion) {
            case 1: {
                Paciente p;
                std::cout << "Nombre: ";
                std::getline(std::cin, p.nombre);
                std::cout << "Edad: ";
                std::cin >> p.edad;
                std::cout << "Peso (kg): ";
                std::cin >> p.peso;
                std::cout << "Altura (m): ";
                std::cin >> p.altura;
                std::cin.ignore();  // Ignorar el carácter de nueva línea restante
                agregarPaciente(cabeza, p);
                std::cout << "Paciente agregado.\n";
                break;
            }
            case 2: {
                std::string nombre;
                std::cout << "Nombre del paciente a eliminar: ";
                std::getline(std::cin, nombre);
                eliminarPaciente(cabeza, nombre);
                break;
            }
            case 3: {
                imprimirPacientes(cabeza);
                break;
            }
            case 4: {
                float promedioEdad, promedioPeso;
                calcularPromedios(cabeza, promedioEdad, promedioPeso);
                std::cout << "\nPromedio de edad: " << promedioEdad << " años\n";
                std::cout << "Promedio de peso: " << promedioPeso << " kg\n";

                Nodo* actual = cabeza;
                std::cout << "\nIMC y clasificación de cada paciente:\n";
                while (actual) {
                    float imc = calcularIMC(actual->paciente);
                    std::string clasificacion = clasificarIMC(imc);
                    std::cout << "Nombre: " << actual->paciente.nombre << ", IMC: " << imc << " (" << clasificacion << ")\n";
                    actual = actual->siguiente;
                }
                break;
            }
            case 5: {
                std::string archivo;
                std::cout << "Nombre del archivo (incluye .txt o .csv): ";
                std::getline(std::cin, archivo);
                cargarPacientesDesdeArchivo(cabeza, archivo);
                break;
            }
            case 6:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente nuevamente.\n";
                break;
        }
    } while (opcion != 6);
}

int main() {
    Nodo* cabeza = nullptr;
    mostrarMenu(cabeza);
    liberarLista(cabeza);
    return 0;
}
