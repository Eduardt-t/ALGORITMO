#include <iostream>  // Necesario para std::cout
#include <string>    // Necesario para std::string

struct Paciente {
    std::string nombre;
    int edad;
    float peso;
    float altura;
};

int main() {
    Paciente paciente1 = {"Juan", 30, 70.5, 1.75};
    Paciente paciente2 = {"Maria", 25, 65.0, 1.65};
    Paciente paciente3 = {"Pedro", 40, 80.0, 1.80};

    std::cout << "Paciente 1: " << paciente1.nombre << ", " << paciente1.edad << " años, " 
              << paciente1.peso << " kg, " << paciente1.altura << " m\n";
    std::cout << "Paciente 2: " << paciente2.nombre << ", " << paciente2.edad << " años, " 
              << paciente2.peso << " kg, " << paciente2.altura << " m\n";
    std::cout << "Paciente 3: " << paciente3.nombre << ", " << paciente3.edad << " años, " 
              << paciente3.peso << " kg, " << paciente3.altura << " m\n";

    return 0;
}
