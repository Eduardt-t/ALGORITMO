#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int TABLE_SIZE = 20;

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
        if (i >= TABLE_SIZE) {
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
        if (i >= TABLE_SIZE) {
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
        if (i >= TABLE_SIZE) {
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

// Buscar elemento en la tabla hash con reporte de colisiones y desplazamiento
bool search(int key, vector<int>& table, char method) {
    int index = hashFunction(key);
    int i = 0;
    int pos = index;
    bool collisionOccurred = false;

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

        // Si la posición ya está ocupada y no es la clave buscada, ocurrió una colisión
        if (i > 0) {
            cout << "Colisión en la posición " << pos << ", desplazamiento " << i << endl;
            collisionOccurred = true;
        }

        i++;
    }
    cout << "Clave " << key << " encontrada en la posición " << pos << endl;
    if (collisionOccurred) {
        cout << "Desplazamiento final: " << i - 1 << endl;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " {L|C|D}" << endl;
        return 1;
    }

    char method = toupper(argv[1][0]);  

    if (method != 'L' && method != 'C' && method != 'D') {
        cerr << "Método no válido. Por favor, ingrese L, C o D." << endl;
        return 1;
    }

    vector<int> table(TABLE_SIZE, -1);
    vector<int> keys;
    int N;

    // Solicitar la cantidad de números y los números a ingresar
    cout << "Ingrese la cantidad de números (N): ";
    cin >> N;

    cout << "Ingrese los números: ";
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        keys.push_back(num);
    }

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
