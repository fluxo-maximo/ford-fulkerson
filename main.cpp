#include "GrafoMatriz.h"
#include "GrafoMatriz.cpp"

int main(int argc, char **argv)
{
    GrafoMatriz grafoMatriz(6);
    std::cout << "Vertices: " << grafoMatriz.getVertices();
    cout << grafoMatriz.inserirAresta(0, 1, 8);
    cout << grafoMatriz.inserirAresta(0, 4, 3);
    cout << grafoMatriz.inserirAresta(1, 2, 9);
    cout << grafoMatriz.inserirAresta(2, 4, 7);
    cout << grafoMatriz.inserirAresta(2, 5, 2);
    cout << grafoMatriz.inserirAresta(3, 5, 5);
    cout << grafoMatriz.inserirAresta(4, 2, 7);
    cout << grafoMatriz.inserirAresta(4, 3, 4);

    std::cout << "\nArestas: " << grafoMatriz.getArestas();
    grafoMatriz.getAdjacencias(1);

    cout << "\n======================\n";

    cout << "Fluxo Maximo = " << grafoMatriz.fordFulkerson(0, 5) << "\n";
}
