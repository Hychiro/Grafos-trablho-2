#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.cpp"
#include "Node.cpp"
#include "Edge.cpp"

using namespace std;

Graph *leituraInstancia(ifstream &input_file)
{

    //Variáveis para auxiliar na criação dos nós no Grafo

    int order;
    int numeroRotulos;

    //Pegando a ordem do grafo
    input_file >> order >> numeroRotulos;
    int matrixCorAresta[order][order];

    for (int k = 0; k < order; k++)
    {
        for (int j = 0; j < order; j++)
        {
            matrixCorAresta[k][j] = -1;
        }
    }
    //Criando objeto grafo
    Graph *graph = new Graph(order, numeroRotulos);
    int coluna = 1;
    int linha = 0;
    //Leitura de arquivo
    while (input_file >> numeroRotulos)
    {
        if (coluna < order)
        {

            matrixCorAresta[coluna][linha] = numeroRotulos;
            coluna++;
        }
        else if (linha < order - 1)
        {
            linha++;
            coluna = linha + 1;
        }
        else
        {
            break;
        }
    }

    for (int o = 0; o < order; o++)
    {
        for (int p = 0; p < order; p++)
        {
            if (matrixCorAresta[o][p] != -1 && matrixCorAresta[o][p] != numeroRotulos)
            {
                graph->insertEdge(o, p, matrixCorAresta[o][p]);
            }
        }
    }

    return graph;
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1]  Algoritmo Guloso" << endl;
    cout << "[2] Algoritmo Guloso Randomizado" << endl;
    cout << "[3] Algoritmo Guloso Randomizado Reativo" << endl;
    cout << "[4] Árvore Geradora Mínima de Kruskal" << endl;
    cout << "[5] Árvore Geradora Mínima de Prim" << endl;
    cout << "[6] Imprimir caminhamento em Profundidade" << endl;
    cout << "[9] Printando o Grafo " << endl;

    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void selecionar(int selecao, Graph *graph, ofstream &output_file)
{

    switch (selecao)
    {
    //Algoritmo Guloso;
    case 1:
    {

        cout << "Algoritmo Guloso";

        Graph *novoGrafo = graph->guloso();
        novoGrafo->printGraph(output_file);
        break;
    }
    //Algoritmo Guloso Randomizado;
    case 2:
    {
        cout << "Algoritmo Guloso Radomizado";

        float alfa;
        cout << "Digite o alfa:" << endl;
        cin >> alfa;

        int numdInteracoes;
        cout << "Digite o numero de Iteracoes:" << endl;
        cin >> numdInteracoes;

        Graph *novoGrafo = graph->gulosoRandomizado(alfa, 0, numdInteracoes, graph);
        novoGrafo->printGraph(output_file);
        break;
    }
    //Algoritmo Guloso Radomizado Reativo
    case 3:
    {
        output_file << "Algoritmo Guloso Radomizado Reativo" << endl;

        int numAlfa; // encontra o num total de alfas
        cout << "Digite o Numero de alfas a serem adicionados:" << endl;
        cin >> numAlfa;
        float *alfa = new float[numAlfa];     // guarda todos os alfas em um mesmo vetor
        float *probAlfa = new float[numAlfa]; // guarda a probabilidade de todos os alfas, utilizar a posição do vetor alfa como referencia
        int *mediaAlfa = new int[numAlfa];
        int *vezesUsada = new int[numAlfa];
        for (int i = 0; i < numAlfa; i++)
        {
            cout << "Digite o alfa " << i << ":" << endl;
            cin >> alfa[i];

            probAlfa[i] = 0;
            mediaAlfa[i] = 0;
            vezesUsada[i] = 0;
        }

        int numdInteracoes;
        cout << "Digite o numero de Iteracoes:" << endl;
        cin >> numdInteracoes;

        Graph *novoGrafo = graph->gulosoRandomizadoReativo(0, numdInteracoes, graph, numAlfa, alfa,probAlfa, mediaAlfa,vezesUsada);
        novoGrafo->printGraph(output_file);
        break;
    }

    //AGM - Kruscal;
    case 4:
    {
        Graph *novoSubGrafo = graph->agmKuskal(output_file);
        novoSubGrafo->printGraph(output_file);
        break;
    }
    //AGM Prim;
    case 5:
    {
        Graph *grafoX = graph->agmPrim(output_file);
        grafoX->printGraph(output_file);
        break;
    }
    //Imprimir caminhamento em Profundidade
    case 6:
    {

        graph->printGraph(output_file);

        break;
    }
    default:
    {
        cout << " Error!!! invalid option!!" << endl;
    }
    }
}

int mainMenu(ofstream &output_file, Graph *graph)
{

    int selecao = 1;

    while (selecao != 0)
    {
        system("cls");
        selecao = menu();

        if (output_file.is_open())
            selecionar(selecao, graph, output_file);

        else
            cout << "Unable to open the output_file" << endl;

        output_file << endl;
    }

    return 0;
}

int main(int argc, char const *argv[])
{

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 3)
    {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file>" << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if (input_file_name.find("v") <= input_file_name.size())
    {
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    Graph *graph;

    if (input_file.is_open())
    {

        graph = leituraInstancia(input_file);
    }
    else
        cout << "Unable to open " << argv[1];

    mainMenu(output_file, graph);

    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}
