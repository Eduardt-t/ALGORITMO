#include <iostream>
#include <string>

struct Paciente {
    std::string nombre;
    int edad;
    float peso;
    float altura;
};

int main() {
    // Creación de los pacientes
    Paciente paciente1 = {"Juan", 30, 70.5, 1.75};
    Paciente paciente2 = {"Maria", 25, 65.0, 1.65};
    Paciente paciente3 = {"Pedro", 40, 80.0, 1.80};

    // Arreglo de pacientes
    Paciente pacientes[3] = {paciente1, paciente2, paciente3};

    // Imprimir la información de cada paciente
    for(int i = 0; i < 3; i++) {
        std::cout << "Paciente " << i+1 << ": " << pacientes[i].nombre << ", " << pacientes[i].edad << " años, "
                  << pacientes[i].peso << " kg, " << pacientes[i].altura << " m\n";
    }

    return 0;
}
