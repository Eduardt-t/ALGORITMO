#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int TABLE_SIZE = 20;

// Función hash básica
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Método de prueba lineal con verificación de límite
int linearProbing(int key, vector<int>& table) {
    int index = hashFunction(key);
    int i = 0;
    while (table[(index + i) % TABLE_SIZE] != -1) {
        cout << "Colisión en la posición " << (index + i) % TABLE_SIZE << ", probando siguiente posición..." << endl;
        i++;
        if (i >= TABLE_SIZE) { // Verificación adicional para evitar ciclo infinito
            cout << "Error: Todas las posiciones están ocupadas, no se puede insertar la clave " << key << endl;
            return -1;
        }
    }
    return (index + i) % TABLE_SIZE;
}

// Método de prueba cuadrática con verificación de límite
int quadraticProbing(int key, vector<int>& table) {
    int index = hashFunction(key);
    int i = 0;
    while (table[(index + i * i) % TABLE_SIZE] != -1) {
        cout << "Colisión en la posición " << (index + i * i) % TABLE_SIZE << ", probando siguiente posición..." << endl;
        i++;
        if (i >= TABLE_SIZE) { // Verificación adicional para evitar ciclo infinito
            cout << "Error: Todas las posiciones están ocupadas, no se puede insertar la clave " << key << endl;
            return -1;
        }
    }
    return (index + i * i) % TABLE_SIZE;
}

// Método de doble dirección con verificación de límite
int doubleHashing(int key, vector<int>& table) {
    int index = hashFunction(key);
    int hash2 = 7 - (key % 7);
    int i = 0;
    while (table[(index + i * hash2) % TABLE_SIZE] != -1) {
        cout << "Colisión en la posición " << (index + i * hash2) % TABLE_SIZE << ", probando siguiente posición..." << endl;
        i++;
        if (i >= TABLE_SIZE) { // Verificación adicional para evitar ciclo infinito
            cout << "Error: Todas las posiciones están ocupadas, no se puede insertar la clave " << key << endl;
            return -1;
        }
    }
    return (index + i * hash2) % TABLE_SIZE;
}

// Insertar elemento en la tabla hash con paso a paso
void insert(int key, vector<int>& table, char method) {
    int index;
    cout << "\nInsertando clave " << key << ":" << endl;
    if (method == 'L' || method == 'l') {
        index = linearProbing(key, table);
    } else if (method == 'C' || method == 'c') {
        index = quadraticProbing(key, table);
    } else if (method == 'D' || method == 'd') {
        index = doubleHashing(key, table);
    }
    
    if (index != -1) { // Solo inserta si el índice es válido
        table[index] = key;
        cout << "Clave " << key << " insertada en la posición " << index << endl;
    } else {
        cout << "No se pudo insertar la clave " << key << " en la tabla." << endl;
    }
}

// Buscar elemento en la tabla hash
bool search(int key, vector<int>& table, char method) {
    int index = hashFunction(key);
    int i = 0;
    int pos = index;
    
    while (table[pos] != key) {
        if (method == 'L' || method == 'l') {
            pos = (index + i) % TABLE_SIZE;
        } else if (method == 'C' || method == 'c') {
            pos = (index + i * i) % TABLE_SIZE;
        } else if (method == 'D' || method == 'd') {
            int hash2 = 7 - (key % 7);
            pos = (index + i * hash2) % TABLE_SIZE;
        }
        
        if (table[pos] == -1) {
            cout << "Clave " << key << " no encontrada." << endl;
            return false;
        }
        i++;
    }
    cout << "Clave " << key << " encontrada en la posición " << pos << endl;
    return true;
}

int main() {
    vector<int> table(TABLE_SIZE, -1);
    vector<int> keys;
    char method;
    char choice;

    // Preguntar si desea ingresar sus propios números o usar los del profesor
    do {
        cout << "¿Desea ingresar sus propios números o usar los del profesor? (I para ingresar, P para profesor): ";
        cin >> choice;
        choice = toupper(choice);  // Convertir a mayúscula para facilitar la validación
        if (choice != 'I' && choice != 'P') {
            cout << "Opción no válida. Por favor, ingrese I o P." << endl;
        }
    } while (choice != 'I' && choice != 'P');

    if (choice == 'I') {
        int N;
        cout << "Ingrese la cantidad de números (N): ";
        cin >> N;

        cout << "Ingrese los números: ";
        for (int i = 0; i < N; i++) {
            int num;
            cin >> num;
            keys.push_back(num);
        }
    } else {
        keys = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};
    }

    // Pedir al usuario que seleccione un método válido para resolución de colisiones
    do {
        cout << "Seleccione el método de resolución de colisiones (L para Lineal, C para Cuadrática, D para Doble Dirección): ";
        cin >> method;
        method = toupper(method);  // Convertir a mayúscula para facilitar la validación
        if (method != 'L' && method != 'C' && method != 'D') {
            cout << "Método no válido. Por favor, ingrese L, C o D." << endl;
        }
    } while (method != 'L' && method != 'C' && method != 'D');

    for (int key : keys) {
        insert(key, table, method);
    }

    cout << "\nTabla Hash final:" << endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << ": " << table[i] << endl;
    }

    int searchKey;
    cout << "Ingrese clave a buscar: ";
    cin >> searchKey;
    search(searchKey, table, method);

    return 0;
}

