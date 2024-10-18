#include <iostream>
#include <vector>
#include <limits.h>
#include <fstream>
#include <cstdlib>

using namespace std;

class Graph {
    int N; // Número de nodos
    vector<vector<int>> adjMatrix; // Matriz de adyacencia

public:
    Graph(int n) : N(n), adjMatrix(n, vector<int>(n, 0)) {}

    // Método para agregar una arista
    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; // Grafo no dirigido
    }

    // Imprimir la matriz de adyacencia
    void printAdjMatrix() {
        cout << "Matriz de adyacencia del grafo:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Algoritmo de Prim para encontrar el MST
    void primMST() {
        vector<int> parent(N); // Para almacenar el MST
        vector<int> key(N, INT_MAX); // Para encontrar la arista mínima
        vector<bool> inMST(N, false); // Para verificar si el nodo está en el MST

        key[0] = 0; // El nodo inicial siempre se selecciona primero
        parent[0] = -1; // El primer nodo no tiene padre

        for (int count = 0; count < N - 1; count++) {
            int u = minKey(key, inMST);
            inMST[u] = true;

            // Actualizar los valores de los nodos adyacentes
            for (int v = 0; v < N; v++) {
                if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }
        printMST(parent);
    }

    // Encuentra el vértice con el valor mínimo en key[] que aún no ha sido incluido en el MST
    int minKey(vector<int>& key, vector<bool>& inMST) {
        int min = INT_MAX, min_index = -1;
        for (int v = 0; v < N; v++) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                min_index = v;
            }
        }
        return min_index;
    }

    // Imprime el MST y genera un archivo Graphviz
    void printMST(vector<int>& parent) {
        cout << "Árbol abarcador de costo mínimo:\n";
        cout << "Arista \tPeso\n";
        ofstream graphFile("mst.dot");
        graphFile << "graph G {\n";
        graphFile << "    graph [rankdir=LR];\n";
        graphFile << "    node [style=filled fillcolor=\"#00ff00\"];\n"; // Color verde claro

        for (int i = 1; i < N; i++) {
            cout << parent[i] + 1 << " - " << i + 1 << "\t" << adjMatrix[i][parent[i]] << "\n"; // Mostrar índices desde 1
            graphFile << "    " << parent[i] + 1 << " -- " << i + 1 << " [label=" << adjMatrix[i][parent[i]] << "];\n";
        }

        graphFile << "}\n";
        graphFile.close();

        if (system("dot -Tpng mst.dot -o mst.png") != 0) {
            cerr << "Error: No se pudo generar la imagen del MST." << endl;
        }
    }

    // Genera el grafo original con Graphviz
    void generateOriginalGraph() {
        ofstream graphFile("original.dot");
        graphFile << "graph G {\n";
        graphFile << "    graph [rankdir=LR];\n";
        graphFile << "    node [style=filled fillcolor=\"#00ff00\"];\n"; // Color verde claro

        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                if (adjMatrix[i][j]) {
                    graphFile << "    " << i + 1 << " -- " << j + 1 << " [label=" << adjMatrix[i][j] << "];\n"; // Mostrar índices desde 1
                }
            }
        }
        graphFile << "}\n";
        graphFile.close();

        if (system("dot -Tpng original.dot -o original.png") != 0) {
            cerr << "Error: No se pudo generar la imagen del grafo original." << endl;
        }
    }
};

int main() {
    int N;
    cout << "Ingrese el número de nodos (N): ";
    cin >> N;

    if (N < 2) {
        cout << "El número de nodos debe ser mayor a 2." << endl;
        return 1;
    }

    Graph g(N);
    int edges, u, v, weight;
    cout << "Ingrese el número de aristas: ";
    cin >> edges;

    cout << "Ingrese las aristas (u v peso):\n";
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> weight;
        if (u >= 1 && v >= 1 && u <= N && v <= N) {
            g.addEdge(u - 1, v - 1, weight); // Ajustar el índice para que empiece desde 0
        } else {
            cout << "Error: nodos fuera de rango.\n";
        }
    }

    g.printAdjMatrix(); // Imprimir la matriz de adyacencia
    g.generateOriginalGraph(); // Generar el grafo original
    g.primMST(); // Ejecutar el algoritmo de Prim para encontrar el MST

    return 0;
}
