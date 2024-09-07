#include <iostream>
#include <string>

// Función para determinar si un número es par
bool esPar(int numero) {
    return numero % 2 == 0;
}

// Función para determinar la longitud de un string
std::size_t longitudCadena(const std::string& cadena) {
    return cadena.length();
}

int main() {
    int opcion;
    
    do {
        std::cout << "\n--- Menú de opciones ---\n";
        std::cout << "1. Verificar si un número es par o impar\n";
        std::cout << "2. Mostrar si los números del 1 al 10 son pares o impares\n";
        std::cout << "3. Determinar la longitud de un string ingresado\n";
        std::cout << "4. Determinar la longitud de un string almacenado en el código\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        
        switch (opcion) {
            case 1: {
                int numero;
                std::cout << "Ingrese un número: ";
                std::cin >> numero;
                if (esPar(numero)) {
                    std::cout << numero << " es un número par.\n";
                } else {
                    std::cout << numero << " es un número impar.\n";
                }
                break;
            }
            case 2: {
                std::cout << "Verificando los números del 1 al 10:\n";
                for (int i = 1; i <= 10; ++i) {
                    if (esPar(i)) {
                        std::cout << i << " es un número par.\n";
                    } else {
                        std::cout << i << " es un número impar.\n";
                    }
                }
                break;
            }
            case 3: {
                std::string cadenaUsuario;
                std::cout << "Ingrese un string: ";
                std::cin >> cadenaUsuario;
                std::cout << "La longitud del string ingresado es: " << longitudCadena(cadenaUsuario) << "\n";
                break;
            }
            case 4: {
                std::string cadenaDirecta = "Hola, Mundo!";
                std::cout << "La longitud del string \"" << cadenaDirecta << "\" es: " << longitudCadena(cadenaDirecta) << "\n";
                break;
            }
            case 5: {
                std::cout << "Saliendo del programa...\n";
                break;
            }
            default: {
                std::cout << "Opción no válida. Por favor, intente de nuevo.\n";
                break;
            }
        }
        
    } while (opcion != 5);

    return 0;
}
