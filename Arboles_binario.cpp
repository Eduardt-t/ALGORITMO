#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits> // Para std::numeric_limits

using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol {
private:
    Node* root;

    // Método recursivo privado para insertar un nodo en el árbol binario de búsqueda
    Node* insertNode(Node* node, int data) {
        if (node == nullptr) {
            return createNode(data);
        }

        if (data < node->info) {
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            node->right = insertNode(node->right, data);
        } else {
            cout << "El nodo ya se encuentra en el árbol: " << data << endl;
        }
        return node;
    }

    // Método recursivo privado para imprimir el árbol en preorden
    void printPreOrder(Node* node) const {
        if (node == nullptr) return;
        cout << node->info << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

    // Método recursivo privado para imprimir el árbol en inorden
    void printInOrder(Node* node) const {
        if (node == nullptr) return;
        printInOrder(node->left);
        cout << node->info << " ";
        printInOrder(node->right);
    }

    // Método recursivo privado para imprimir el árbol en posorden
    void printPostOrder(Node* node) const {
        if (node == nullptr) return;
        printPostOrder(node->left);
        printPostOrder(node->right);
        cout << node->info << " ";
    }

    // Método recursivo privado para eliminar un nodo
    Node* deleteNode(Node* node, int data) {
        if (node == nullptr) return node;

        if (data < node->info) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->info) {
            node->right = deleteNode(node->right, data);
        } else {
            // Nodo encontrado
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Nodo con dos hijos
            Node* temp = minNode(node->right);
            node->info = temp->info;
            node->right = deleteNode(node->right, temp->info);
        }
        return node;
    }

    // Obtener el nodo con el valor mínimo
    Node* minNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Recorrer el árbol y escribir en el archivo para el grafo
    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << node->info << "->" << node->left->info << ";" << endl;
            } else {
                string cadena = to_string(node->info) + "i";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            if (node->right != nullptr) {
                fp << node->info << "->" << node->right->info << ";" << endl;
            } else {
                string cadena = to_string(node->info) + "d";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            recorrer(node->left, fp);
            recorrer(node->right, fp);
        }
    }

public:
    Arbol() : root(nullptr) {}

    // Método público para insertar un nodo en el árbol
    void insert(int data) {
        root = insertNode(root, data);
    }

    // Método público para imprimir el árbol en preorden
    void printPreOrder() const {
        printPreOrder(root);
        cout << endl;
    }

    // Método público para imprimir el árbol en inorden
    void printInOrder() const {
        printInOrder(root);
        cout << endl;
    }

    // Método público para imprimir el árbol en posorden
    void printPostOrder() const {
        printPostOrder(root);
        cout << endl;
    }

    // Método público para eliminar un nodo del árbol
    void deleteNode(int data) {
        root = deleteNode(root, data);
    }

    // Método para generar y visualizar el árbol
    void visualize() {
        ofstream fp("arbol.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo arbol.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=yellow];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;

        fp.close();

        // Generar y mostrar la imagen del árbol
        system("dot -Tpng -o arbol.png arbol.txt");
        system("eog arbol.png");
    }
};

void menu() {
    Arbol arbol;
    int opcion, num;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insertar número\n";
        cout << "2. Eliminar número\n";
        cout << "3. Modificar número\n";
        cout << "4. Mostrar Preorden\n";
        cout << "5. Mostrar Inorden\n";
        cout << "6. Mostrar Posorden\n";
        cout << "7. Generar grafo\n";
        cout << "8. Créditos\n"; // Opción de créditos
        cout << "9. Salir\n";     // Opción de salida
        cout << "Selecciona una opción: ";
        cin >> opcion;

        // Verifica si la entrada de opción es inválida
        if (cin.fail()) {
            cin.clear(); // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada inválida
            cout << "Opción no válida. Intente de nuevo.\n";
            continue; // Regresa al inicio del loop
        }

        switch (opcion) {
            case 1:
                cout << "Ingrese un número entero a insertar: ";
                cin >> num;
                // Verifica si la entrada de número es inválida
                if (cin.fail()) {
                    cin.clear(); // Limpia el estado de error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada inválida
                    cout << "Entrada inválida. Debe ingresar un número entero.\n";
                    break;
                }
                arbol.insert(num);
                break;

            case 2:
                cout << "Ingrese un número entero a eliminar: ";
                cin >> num;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Entrada inválida. Debe ingresar un número entero.\n";
                    break;
                }
                arbol.deleteNode(num);
                break;

            case 3: {
                int viejo, nuevo;
                cout << "Ingrese el número a modificar: ";
                cin >> viejo;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Entrada inválida. Debe ingresar un número entero.\n";
                    break;
                }
                cout << "Ingrese el nuevo número: ";
                cin >> nuevo;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Entrada inválida. Debe ingresar un número entero.\n";
                    break;
                }
                arbol.deleteNode(viejo);
                arbol.insert(nuevo);
                break;
            }

            case 4:
                cout << "Recorrido en preorden: ";
                arbol.printPreOrder();
                break;

            case 5:
                cout << "Recorrido en inorden: ";
                arbol.printInOrder();
                break;

            case 6:
                cout << "Recorrido en posorden: ";
                arbol.printPostOrder();
                break;

            case 7:
                arbol.visualize();
                break;

            case 8: // Créditos
                cout << "\nCréditos:\n";
                cout << "Eduardo Toledo\n";
                cout << "UNIVERSIDAD DE TALCA\n";
                cout << "FACULTAD DE INGENIERÍA\n";
                cout << "ESCUELA DE INGENIERÍA CIVIL EN BIOINFORMÁTICA\n";
                cout << "Algoritmos y Estructuras de Datos\n";
                cout << "Laboratorio 4 - Unidad I\n";
                break;

            case 9: // Salir
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 9);
}

int main() {
    menu();
    return 0;
}
