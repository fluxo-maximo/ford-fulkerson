#include "GrafoMatriz.h"

#include <vector>
#include <iomanip>
#include <queue>
#include <climits>

#define INFINITO INT_MAX

using std::cout;

GrafoMatriz::GrafoMatriz()
{
    grafoMatriz = new int *[3];

    for (int i = 0; i < 3; i++)
    {

        grafoMatriz[i] = new int[3];
        for (int j = 0; j < 3; j++)
        {
            grafoMatriz[i][j] = 0;
        }
        VerticeMatriz *v = new VerticeMatriz(i, 0);
        vertices.push_back(v);
        visitados.push_back(false);
    }
}

GrafoMatriz::GrafoMatriz(int num_vertice)
{
    this->num_vertice = num_vertice;
    grafoMatriz = new int *[num_vertice];
    for (int i = 0; i < num_vertice; i++)
    {
        grafoMatriz[i] = new int[num_vertice];
        for (int j = 0; j < num_vertice; j++)
        {
            grafoMatriz[i][j] = 0;
        }
        VerticeMatriz *v = new VerticeMatriz(i, 0);
        vertices.push_back(v);
        visitados.push_back(false);
    }
}

GrafoMatriz::~GrafoMatriz()
{
    for (int i = 0; i < num_vertice; i++)
    {
        delete[] vertices[i];
        delete[] grafoMatriz[i];
    }
    delete[] grafoMatriz;
}

string GrafoMatriz::inserirAresta(int origem, int destino)
{
    if ((origem <= 10 || origem >= 0) && (destino <= 10 || destino >= 0))
    {
        grafoMatriz[origem][destino] = 1;
        return "\nAresta adicionada!";
    }
    return "\nVértices não encontrados";
}

string GrafoMatriz::inserirAresta(int origem, int destino, int valor)
{
    if ((origem <= 10 || origem >= 0) && (destino <= 10 || destino >= 0))
    {
        grafoMatriz[origem][destino] = valor;
        return "\nAresta ponderada adicionada!";
    }
    return "\nVértices não encontrados";
}

vector<int> GrafoMatriz::getAdjacencias(int vertice)
{
    vector<int> adjacentes;

    // // INDO DOS OUTROS VERTICES ATE O VERTICE ESCOLHIDO
    // for (int i = 0; i < num_vertice; i++)
    // {
    //     if (i == vertice)
    //         continue;

    //     if (grafoMatriz[i][vertice] > 0)
    //         adjacentes.push_back(i);
    // }

    // DO VERTICE ESCOLHIDO ATE OS OUTROS VERTICES
    for (int j = 0; j < num_vertice; j++)
    {
        if (grafoMatriz[vertice][j] > 0)
        {
            adjacentes.push_back(j);
        }
    }

    return adjacentes;
}

int GrafoMatriz::countAdjacencias(int vertice)
{
    int adjacencia_total = 0;

    // for (int i = 0; i < num_vertice; i++)
    // {
    //     if (i == vertice)
    //         continue;

    //     if (grafoMatriz[i][vertice] > 0)
    //     {
    //         cout << "\nAresta: " << i << "->" << vertice;
    //         adjacencia_total += 1;
    //     }
    // }

    for (int j = 0; j < num_vertice; j++)
    {
        if (grafoMatriz[vertice][j] > 0)
        {
            cout << "\nAresta: " << vertice << "->" << j;
            adjacencia_total += 1;
        }
    }

    cout << "\nVertice (" << vertice << ") tem " << adjacencia_total << " adjacencias";
    return adjacencia_total;
}

int GrafoMatriz::getVertices()
{
    return num_vertice;
}

int GrafoMatriz::getArestas()
{
    /*
     * Apenas para grafoMatriz direcionado
     */
    int aresta_total = 0;
    for (int i = 0; i < num_vertice; i++)
    {
        for (int j = 0; j < num_vertice; j++)
        {
            if (grafoMatriz[i][j] > 0)
            {
                aresta_total += 1;
            }
        }
    }
    return aresta_total;
}


void GrafoMatriz::deletarAresta(int origem, int destino)
{
    grafoMatriz[origem][destino] = 0;
    cout << "\nAresta " << origem << "->" << destino << " deletada com sucesso!";
}

bool GrafoMatriz::bfs(int fonte, int sumidouro, vector<int> &parent)
{
    fill(visitados.begin(), visitados.end(), false);
    std::queue<int> fila;
    fila.push(fonte);

    visitados[fonte] = true;
    parent[fonte] = -1;

    while (!fila.empty())
    {
        int verticeAtual = fila.front();
        fila.pop();

        for (int proximoVertice = 0; proximoVertice < num_vertice; proximoVertice++)
        {
            if (!visitados[proximoVertice] && capacidade[verticeAtual][proximoVertice] > 0)
            {
                fila.push(proximoVertice);
                parent[proximoVertice] = verticeAtual;
                visitados[proximoVertice] = true;
            }
        }
    }

    return (visitados[sumidouro]);
}

int GrafoMatriz::fordFulkerson(int fonte, int sumidouro)
{
    int maxFluxo = 0;

    capacidade.resize(num_vertice, vector<int>(num_vertice));

    for (int i = 0; i < num_vertice; i++)
    {
        for (int j = 0; j < num_vertice; j++)
        {
            capacidade[i][j] = grafoMatriz[i][j];
        }
    }

    vector<int> parent(num_vertice);

    while (bfs(fonte, sumidouro, parent))
    {
        int caminhoFluxo = INFINITO;

        for (int v = sumidouro; v != fonte; v = parent[v])
        {
            int u = parent[v];
            caminhoFluxo = std::min(caminhoFluxo, capacidade[u][v]);
        }

        for (int v = sumidouro; v != fonte; v = parent[v])
        {
            int u = parent[v];
            capacidade[u][v] -= caminhoFluxo;
            capacidade[v][u] += caminhoFluxo;
        }

        maxFluxo += caminhoFluxo;
    }

    return maxFluxo;
}
