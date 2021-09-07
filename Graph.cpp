#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
#include <string>
#include <bits/stdc++.h>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, int numeroRotulos)
{

    this->order = order;
    this->conexGraph = false;
    this->first_node = NULL;
    this->last_node = NULL;
    this->number_edges = 0;
    this->numeroRotulos = numeroRotulos;
    insertAllNodes();
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != NULL)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

void Graph::printGraph(ofstream &output_file)
{
    Node *p = this->first_node;
    Edge *aux = p->getFirstEdge();

    output_file << "strict graph{" << endl;
    while (p != NULL)
    {

        aux = p->getFirstEdge();
        while (aux != NULL)
        {

            output_file << p->getId() << " -- " << aux->getTargetId() << endl;
            aux = aux->getNextEdge();
        }
        p = p->getNextNode();
    }
    output_file << "}" << endl;
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{
    return this->number_edges / 2;
}
//Function that verifies if the graph is directed

Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

bool Graph::getConexGraph()
{
    return this->conexGraph;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/

//implementacao abaixo:

void Graph::insertNode(int id)
{
    // so cria o no e deixa ele no espaço
    Node *p = new Node(id);
    if (this->first_node == NULL)
    {
        this->first_node = p;
    }
    else
    {
        this->last_node->setNextNode(p);
    }
    this->last_node = p;
    this->last_node->setNextNode(NULL);
    this->order++;
}
void Graph::insertAllNodes()
{
    for (int i = 0; i < this->order; i++)
    {
        Node *p = new Node(i + 1);
        if (this->first_node == NULL)
        {
            this->first_node = p;
        }
        else
        {
            this->last_node->setNextNode(p);
        }
        this->last_node = p;
    }
}

bool Graph::verificaAresta(id, target_id)
{
    Node *p = getId(id);
    for (Edge *g = p->getFirstEdge(); g != NULL; g = g->getNextEdge())
    {

        if (g->getTargetId() == target_id)
        {
            return true;
        }
    }
    return false;
}

void Graph::insertEdge(int id, int target_id, int rotulo)
{
    // junta os nos entre si
    if (searchNode(id)) //<-- ta sendo direcionado prestar atenção nisso.
    {

        if (!verificaAresta(id, target_id))
        {
            Node *p = getNode(id);
            Node *sup = getNode(target_id);
            p->insertEdge(target_id, rotulo);
            sup->insertEdge(id, rotulo);
            this->number_edges += 1;

            bool found = (std::find(rotulos.begin(), rotulos.end(), rotulo) != rotulos.end());

            if (!(found))
            {
                this->rotulos.push_back(rotulo);
            }
        }
    }
}

void Graph::removeNode(int id) // pfv dps me ajudem a revisar esse removeNode
{
    Node *p;
    if (this->last_node != NULL)
    {
        if (this->first_node == this->last_node)
        {
            this->first_node = NULL;
            p = NULL;
        }
        else
        {
            Node *previousN = this->first_node;
            Node *nextN;
            Node *aux;
            Edge *sup;
            int count_edges = 0;

            p = getNode(id);

            while (p != previousN->getNextNode())
            {
                previousN->getNextNode();
            }
            nextN = p->getNextNode();

            previousN->setNextNode(nextN);
            if (previousN->getNextNode() == NULL)
            {
                last_node = previousN;
            }
            // dps arrumar pra ser algo mais bonito, usando  remove edge, q eu n sei usar...
            sup->setNextEdge(k->getNextEdge());
            k = NULL;
            k = sup->getNextEdge();
            p->removeAllEdges();
            p = NULL;
        }
        order--;
    }
    else
        cout << "ERRO: o grafo esta vazio!" << endl;
}

bool Graph::searchNode(int id)
{
    // so verifica se exste o no ali ou nao

    for (Node *p = this->first_node; p != NULL; p = p->getNextNode())
    {
        if (p->getId() == id)
        {
            return true;
        }
    }
    return false;
}

Node *Graph::getNode(int id)
{
    //pega o no na lista de nos
    Node *p = first_node;
    if (searchNode(id))
    {
        while (p != NULL && p->getId() != id)
        {
            p = p->getNextNode();
        }
        return p;
    }
    return p;
}

///////////////////////GULOSOS///////////////////////FAMINTOS////////////////////

int Graph::greed()
{
    //// função pra ver se é conexo
    if (this->conexGraph)
    {
        Graph q = new Graph(this->order, 0);
        while (!q->getConexGraph())
        {
            rotulo = //seleciona 1 coloração com maior numero de arestas G// heuristica
            //Q->aumentaNumCor();
            
            Node *p = this->first_node;
            Edge *aux = p->getFirstEdge();            
            while (p != NULL)
            {

                aux = p->getFirstEdge();
                while (aux != NULL)
                {
                    if(aux->getRotulo()==rotulo){
                        
                    }
                   
                    aux = aux->getNextEdge();
                }
                p = p->getNextNode();
            }
            adiciona as arestas dessa cor em Q
        }
    }
    else
    {
        return null;
    }
    return q;
}

void Graph::adicionaRotulo(int rotuloAnalisado, Graph *grafoOriginal)
{
    
}

int Graph::contaRotulo(int rotuloAnalisado)
{

    int numeroArestas;

    for (Node *it = this->getFirstNode(); it != NULL; it = it->getNextNode())
{

    int numeroArestas;

    for (Node *it = this->getFirstNode(); it != NULL; it = it->getNextNode())
    {
        for (Edge *it2 = it->getFirstEdge(); it2 != NULL; it2 = it2->getNextEdge())
        {
            if (it2->getRotulo == rotuloAnalisado)
            {
                numeroArestas++;
            }
        }
    }
    return numeroArestas;
}

//Function that prints a set of edges belongs breadth tree

///////////////////////GULOSOS///////////////////////FAMINTOS//////////////////////Function that prints a set of edges belongs breadth tree

///////////////////////GULOSOS///////////////////////FAMINTOS//////////////////////Function that prints a set of edges belongs breadth tree
///////////////////////GULOSOS///////////////////////FAMINTOS//////////////////////Function that prints a set of edges belongs breadth tree

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////FECHO TRANSITIVO E BUSCAS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Graph::fechoTransitivoDireto(ofstream &output_file, int id)
{

    //com o id do vértice acha o vertice que deve ser analisado
    int idParametro = id - 1;
    //cria um vetor que marca quais vértices ja foram analisados
    bool visitados[this->order];
    //cria o vetor fecho transitivo direto
    bool FTD[this->order];
    //cria uma fila que diz quais vertices ainda precisam ser analisados
    list<int> fila;
    //adiciona o vertice inicial nele
    fila.push_front(id);

    for (int i = 0; i < this->order; i++)
    {
        visitados[i] = false;
        FTD[i] = false;
    }

    if (!verify[idParametro])
    {

        aux = getNode(p->getTargetId());
        //AUX-BuscaPorProfundidade (G,w)
        auxDeepthFirstSearch1(verify, aux);
    }
}


////deepthFirstSearch realizar a busca por profundidade a partir de um ponto de referencia do grafo.
void Graph::deepthFirstSearch(Graph *novoGrafo, int start)
{

    //Cria vetor verificador e o vetor predecessor de profundidade
    bool *verify = new bool[this->order];

    int idParametro;
    for (int i = 0; i < this->order; i++)
    {
        verify[i] = false;
    }
    //cria o vetor auxiliar
    Node *p;
    //verifica o no de entrada para começar a busca

    //Para todo v em G
    for (p = getNode(start); NULL != p; p = p->getNextNode())
    {

        idParametro = p->getId() - 1;
        //Se v não visitado entao
        if (!verify[idParametro])
        {
            novoGrafo->insertNode(p->getId());
            //AUX-BuscaPorProfundidade (G,v)
            auxDeepthFirstSearch(verify, novoGrafo, p);
            break;
        }
    }
}

void Graph::auxDeepthFirstSearch(bool verify[], Graph *novoGrafo, Node *v)
{
    //Protocolo inicial.
    int idParametro = v->getId() - 1;

    Node *aux;
    //Marca v como visitado

    verify[idParametro] = true;

    //Para todo w em Adj(v)
    for (Edge *p = v->getFirstEdge(); p != NULL; p = p->getNextEdge())
    {

        idParametro = p->getTargetId() - 1;
        //Se w não visitado então

        if (!verify[idParametro])
        {
            novoGrafo->insertNode(p->getTargetId());
            //Inserir aresta na arvore
            novoGrafo->insertEdge(v->getId(), p->getTargetId(), p->getWeight());

            aux = getNode(p->getTargetId());
            //AUX-BuscaPorProfundidade (G,w)
            auxDeepthFirstSearch(verify, novoGrafo, aux);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////CAMINHAMENTO,ALGORITMOS E ORDENACAO TOPOLOGICA///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Graph *Graph::caminhamentoDeProfundidade(int x)
{

    Graph *novoGrafo = new Graph(this->directed, this->weighted_edge, this->weighted_node);
    deepthFirstSearch(novoGrafo, x);
    return novoGrafo;
}

// função que imprime uma classificação topológica
int *Graph::topologicalSorting()
{
    int *vetor = new int(this->order); //alocando o vetor para ordenaçao topologica
    if (this->graphtemCiclo())
        // verifica se o grafo tem circuito ou nao
        return NULL;
    else
    {
        int i = 0;
        Edge *auxAres;
        Node *auxNo;
        queue<Node *> filaTopologica; //fila auxiliar para os nos de origem
                                      //procurando nos com enttrada =0
        for (auxNo = this->first_node; auxNo != NULL; auxNo = auxNo->getNextNode())
        {
            if (auxNo->getInDegree() == 0) // se entrada  = 0
            {
                filaTopologica.push(auxNo); //coloca os nos corretos na fila
            }
        }
        while (!filaTopologica.empty()) // enquanto fila e vazia
        {
            vetor[i] = filaTopologica.front()->getId();       //coloca o id do no a ser removido da fila
            auxAres = filaTopologica.front()->getFirstEdge(); // obtendo a primeiro no
            filaTopologica.pop();                             //remve da fila
            while (auxAres != NULL)
            {
                auxNo = this->getNode(auxAres->getTargetId()); //pega o no vizinho
                auxNo->decrementInDegree();                    //decrementa a entrada
                i
                    f(auxNo->getInDegree() == 0)
                { //se a entrada = 0
                    filaTopologica.push(auxNo);
                }
            }
            i++;
        }
        return vetor; //retorna a classificação topologica em um vetor
    }
}
}

    int pesoTotal = 0;
while (!listaAux.empty())
{
    pair<int, int> distancia_no = listaAux.front(); //copia par (id do vertice e distancia) do topo
    int v1 = distancia_no.first;
    int v2 = distancia_no.second;
    pesoTotal = pesoTotal + getWeightFromEdgeNodeCombo(v1, v2, arvoreGerMin);
    listaAux.pop_front();
}
output_file << "Peso da Arvore Geradora Minima: " << pesoTotal << endl;

    return fti[v1 - 1];
}

//pega o peso da aresta atravez do int idNoh, int idAresta, Graph *subGrafo
int Graph::getWeightFromEdgeNodeCombo(int idNoh, int idAresta, Graph *subGrafo)
{
    Node *p = subGrafo->getNode(idNoh);
    Edge *aux;
    for (aux = p->getFirstEdge(); aux != NULL; aux = aux->getNextEdge())
    {
        if (aux->getTargetId() == idAresta)
        {
            break;
        }
    }
    return aux->getWeight();
}

//procura a aresta de menor peso e adiciona os dados dos vertices de entrada, saida e o seu proprio peso no vetor
void Graph::getWeithlessEdge(int *nohAresta)
{

    Node *p = this->first_node;
    Edge *aux = p->getFirstEdge();
    int menor = 9999999;
    while (p != NULL)
    {

        aux = p->getFirstEdge();
        while (aux != NULL)
        {
            if (aux->getWeight() < menor)
            {
                nohAresta[0] = p->getId();
                nohAresta[1] = aux->getTargetId();
                nohAresta[2] = aux->getWeight();
                menor = aux->getWeight();
            }
            aux = aux->getNextEdge();
        }
        p = p->getNextNode();
    }
}