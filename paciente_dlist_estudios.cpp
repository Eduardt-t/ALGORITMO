#include <iostream>
#include <string>
#include <cmath> // Para std::pow

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

int main() {
    Nodo* cabeza = nullptr;

    // Crear algunos pacientes
    Paciente paciente1 = {"Juan", 30, 70.5, 1.75};
    Paciente paciente2 = {"Maria", 25, 65.0, 1.65};
    Paciente paciente3 = {"Pedro", 40, 80.0, 1.80};

    // Agregar pacientes a la lista
    agregarPaciente(cabeza, paciente1);
    agregarPaciente(cabeza, paciente2);
    agregarPaciente(cabeza, paciente3);

    // Imprimir la lista de pacientes
    std::cout << "Lista de pacientes:\n";
    imprimirPacientes(cabeza);

    // Calcular el promedio de edad y peso
    float promedioEdad, promedioPeso;
    calcularPromedios(cabeza, promedioEdad, promedioPeso);

    std::cout << "\nPromedio de edad: " << promedioEdad << " años\n";
    std::cout << "Promedio de peso: " << promedioPeso << " kg\n";

    // Calcular e imprimir el IMC y la clasificación de cada paciente
    Nodo* actual = cabeza;
    std::cout << "\nIMC y clasificación de cada paciente:\n";
    while (actual) {
        float imc = calcularIMC(actual->paciente);
        std::string clasificacion = clasificarIMC(imc);
        std::cout << "Nombre: " << actual->paciente.nombre << ", IMC: " << imc << " (" << clasificacion << ")\n";
        actual = actual->siguiente;
    }

    // Liberar la memoria
    liberarLista(cabeza);

    return 0;
}
