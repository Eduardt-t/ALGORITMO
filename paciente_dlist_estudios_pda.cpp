#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>  // Para std::fabs

struct Paciente {
    std::string nombre;
    int edad;
    double peso;
    double altura;
    double imc;
    double a1c;

    // Calcula el IMC del paciente basado en el peso y altura
    void calcularIMC() {
        imc = peso / (altura * altura);
    }
};

// Comparador para priorizar pacientes en la cola
struct CompararPrioridad {
    bool operator()(const Paciente& p1, const Paciente& p2) {
        if (p1.a1c == p2.a1c) {
            if (p1.imc == p2.imc) {
                return p1.edad < p2.edad;  // Mayor edad, mayor prioridad
            }
            return p1.imc < p2.imc;  // Mayor IMC, mayor prioridad
        }
        return p1.a1c < p2.a1c;  // Mayor A1C, mayor prioridad
    }
};

std::priority_queue<Paciente, std::vector<Paciente>, CompararPrioridad> colaPacientes;

// Función para cargar pacientes desde un archivo CSV
void cargarPacientes(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    std::getline(archivo, linea);  // Leer la primera línea (encabezado)

    std::unordered_set<std::string> nombresUnicos;  // Para evitar duplicados

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string nombre, edadStr, pesoStr, alturaStr, a1cStr;

        std::getline(ss, nombre, ',');
        std::getline(ss, edadStr, ',');
        std::getline(ss, alturaStr, ',');
        std::getline(ss, pesoStr, ',');
        std::getline(ss, a1cStr, ',');

        if (nombresUnicos.find(nombre) != nombresUnicos.end()) {
            continue;  // Saltar si el nombre ya está en el conjunto
        }

        Paciente paciente;
        paciente.nombre = nombre;
        paciente.edad = std::stoi(edadStr);
        paciente.altura = std::stod(alturaStr);
        paciente.peso = std::stod(pesoStr);
        paciente.a1c = std::stod(a1cStr);
        paciente.calcularIMC();

        colaPacientes.push(paciente);
        nombresUnicos.insert(nombre);
    }

    archivo.close();
    std::cout << "Pacientes cargados y ordenados por prioridad." << std::endl;
}

// Función para buscar pacientes por IMC
void buscarPorIMC(double imcBuscado) {
    std::priority_queue<Paciente, std::vector<Paciente>, CompararPrioridad> colaCopia = colaPacientes;
    bool encontrado = false;

    // Definir un margen de error para la comparación del IMC
    const double margenError = 0.01;

    while (!colaCopia.empty()) {
        Paciente p = colaCopia.top();
        colaCopia.pop();
        if (std::fabs(p.imc - imcBuscado) < margenError) {
            std::cout << "Paciente encontrado: " << p.nombre << ", IMC: " << p.imc << std::endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron pacientes con IMC cercano a " << imcBuscado << std::endl;
    }
}

// Función para buscar pacientes por A1C
void buscarPorA1C(double a1cBuscado) {
    std::priority_queue<Paciente, std::vector<Paciente>, CompararPrioridad> colaCopia = colaPacientes;
    bool encontrado = false;

    // Definir un margen de error para la comparación del A1C
    const double margenError = 0.01;

    while (!colaCopia.empty()) {
        Paciente p = colaCopia.top();
        colaCopia.pop();
        if (std::fabs(p.a1c - a1cBuscado) < margenError) {
            std::cout << "Paciente encontrado: " << p.nombre << ", A1C: " << p.a1c << std::endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron pacientes con A1C cercano a " << a1cBuscado << std::endl;
    }
}

// Función para mostrar los primeros N pacientes en la cola
void mostrarPrimerosPacientes(int cantidad) {
    std::priority_queue<Paciente, std::vector<Paciente>, CompararPrioridad> colaCopia = colaPacientes;
    std::unordered_set<std::string> nombresUnicos;  // Para evitar duplicados

    for (int i = 0; i < cantidad && !colaCopia.empty(); i++) {
        Paciente p = colaCopia.top();
        colaCopia.pop();
        if (nombresUnicos.find(p.nombre) == nombresUnicos.end()) {
            std::cout << "Paciente: " << p.nombre << ", Edad: " << p.edad
                      << ", IMC: " << p.imc << ", A1C: " << p.a1c << std::endl;
            nombresUnicos.insert(p.nombre);
        }
    }
}

// Función para agregar un nuevo paciente
void agregarPaciente() {
    Paciente paciente;
    std::cout << "Ingrese el nombre del paciente: ";
    std::cin.ignore();
    std::getline(std::cin, paciente.nombre);
    std::cout << "Ingrese la edad del paciente: ";
    std::cin >> paciente.edad;
    std::cout << "Ingrese la altura (en metros) del paciente: ";
    std::cin >> paciente.altura;
    std::cout << "Ingrese el peso (en kg) del paciente: ";
    std::cin >> paciente.peso;
    std::cout << "Ingrese el nivel de A1C del paciente: ";
    std::cin >> paciente.a1c;
    paciente.calcularIMC();
    colaPacientes.push(paciente);
    std::cout << "Paciente agregado y ordenado por prioridad." << std::endl;
}

// Función para mostrar el tamaño de la cola
void mostrarTamanoCola() {
    std::cout << "Tamaño de la cola: " << colaPacientes.size() << std::endl;
}

// Función para limpiar la cola
void limpiarCola() {
    while (!colaPacientes.empty()) {
        colaPacientes.pop();
    }
    std::cout << "Cola limpiada." << std::endl;
}

// Función para calcular la atención diaria
void calcularAtencionDiaria() {
    int personasPorGrupo, gruposPorDia;

    std::cout << "Ingrese el número de personas en un grupo: ";
    std::cin >> personasPorGrupo;
    std::cout << "Ingrese el número de grupos atendidos en un día: ";
    std::cin >> gruposPorDia;

    int totalPersonasPorDia = personasPorGrupo * gruposPorDia;
    int totalPacientes = colaPacientes.size();
    int diasParaAtender = (totalPacientes + totalPersonasPorDia - 1) / totalPersonasPorDia;  // Redondeo hacia arriba

    std::cout << "Total de personas atendidas en un día: " << totalPersonasPorDia << std::endl;
    std::cout << "Días para atender a todos los pacientes: " << diasParaAtender << std::endl;

    std::cout << "Pacientes del primer grupo: " << std::endl;
    std::priority_queue<Paciente, std::vector<Paciente>, CompararPrioridad> colaCopia = colaPacientes;
    std::unordered_set<std::string> nombresUnicos;  // Para evitar duplicados

    for (int i = 0; i < totalPersonasPorDia && !colaCopia.empty(); i++) {
        Paciente p = colaCopia.top();
        colaCopia.pop();
        if (nombresUnicos.find(p.nombre) == nombresUnicos.end()) {
            std::cout << "Paciente: " << p.nombre << ", Edad: " << p.edad
                      << ", IMC: " << p.imc << ", A1C: " << p.a1c << std::endl;
            nombresUnicos.insert(p.nombre);
        }
    }
}

// Menú interactivo
void menu() {
    int opcion;
    do {
        std::cout << "1. Cargar pacientes" << std::endl;
        std::cout << "2. Buscar por IMC" << std::endl;
        std::cout << "3. Buscar por A1C" << std::endl;
        std::cout << "4. Mostrar primeros N pacientes en la cola" << std::endl;
        std::cout << "5. Agregar paciente" << std::endl;
        std::cout << "6. Mostrar tamaño de la cola" << std::endl;
        std::cout << "7. Limpiar cola" << std::endl;
        std::cout << "8. Calcular atención diaria" << std::endl;
        std::cout << "9. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                {
                    std::string archivo;
                    std::cout << "Ingrese el nombre del archivo: ";
                    std::cin.ignore();
                    std::getline(std::cin, archivo);
                    cargarPacientes(archivo);
                }
                break;
            case 2:
                {
                    double imcBuscado;
                    std::cout << "Ingrese el IMC a buscar: ";
                    std::cin >> imcBuscado;
                    buscarPorIMC(imcBuscado);
                }
                break;
            case 3:
                {
                    double a1cBuscado;
                    std::cout << "Ingrese el A1C a buscar: ";
                    std::cin >> a1cBuscado;
                    buscarPorA1C(a1cBuscado);
                }
                break;
            case 4:
                {
                    int cantidad;
                    std::cout << "Ingrese el número de pacientes a mostrar: ";
                    std::cin >> cantidad;
                    mostrarPrimerosPacientes(cantidad);
                }
                break;
            case 5:
                agregarPaciente();
                break;
            case 6:
                mostrarTamanoCola();
                break;
            case 7:
                limpiarCola();
                break;
            case 8:
                calcularAtencionDiaria();
                break;
            case 9:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Inténtelo de nuevo." << std::endl;
                break;
        }
    } while (opcion != 9);
}

int main() {
    menu();
    return 0;
}
