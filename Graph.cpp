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

            output_file << p->getId() << " -- " << aux->getTargetId() << "  [ label = " << aux->getRotulo() <<" ]"<< endl;
            aux = aux->getNextEdge();
        }
        p = p->getNextNode();
    }
    output_file << "}" << endl;
}

// Getters
int Graph::getNumRotulos()
{
    return this->numeroRotulos;
}
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
        Node *p = new Node(i);
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

bool Graph::verificaAresta(int id, int target_id)
{
    Node *p = getNode(id);
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

            for (Node *i = first_node; i != NULL; i->getNextNode())
            {
                Edge *k = i->getFirstEdge();
                while (k != NULL)
                {
                    sup = k;
                    k->getNextEdge();

                    if (k->getTargetId() == p->getId())
                    {
                        sup->setNextEdge(k->getNextEdge());
                        k = NULL;
                        k = sup->getNextEdge();
                    }
                }
            }

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

Graph *Graph::guloso(ofstream &output_file)
{
    //// função pra ver se é conexo
    if (this->verificaConexo(this)) //verifica se o grafo gerADOR É CONEXO
    {
        //INICIO FUNÇÃO ORDENA CANDIDATOS
        std::list<int> arestasPorRotulo; //fila que aramzena os rotulos em ordem decrecente
        std::list<int>::iterator iterador;
        int vetorarestasPorRotulo[this->numeroRotulos]; //vetor que faz relação posição=Rotulo e valor da posição=numero de arestas;
        int vetorAux[this->numeroRotulos];
        for (int i = 0; i < this->numeroRotulos; i++)
        {                                              //repetir para o numero de rotulos
            vetorarestasPorRotulo[i] = contaRotulo(i); //para a posição i(que representa o Rótulo i) atribui o valor numero de arestas do Rotulo i
            vetorAux[i] = 0;
        }

        pair<int, int> maiorRotulo; //par que representa o maior rotulo atual <numero de arestas,Rotulo>
        maiorRotulo.first = 0;      //inicia o numero de arestas como 0
        maiorRotulo.second = -1;    //inicia o Rotulo como -1

        while (arestasPorRotulo.size() < this->numeroRotulos) //enquanto o tamanho da fila for menor que o numero de Rotulos
        {

            for (int j = 0; j < this->numeroRotulos; j++) //repetir para o numero de rotulos
            {
                if (maiorRotulo.first <= vetorarestasPorRotulo[j]) //se o numero de arestas do maior Rotulo Atual for menor ou igual do numero de arestas do rotulo a ser analisado (precisa ser menor ou IGUAL pq caso exista um Rotulo com 0 arestas iria bugar o codigo)
                {
                    maiorRotulo.first = vetorarestasPorRotulo[j]; //numero de arestas do maior rotulo igual ao numero de arestas do rotulo analisado
                    maiorRotulo.second = j;                       //maior Rotulo igual ao Rotulo analisado
                }
            }
            vetorAux[maiorRotulo.second] = maiorRotulo.first;
            arestasPorRotulo.push_back(maiorRotulo.second); //adiciona na parte de tras da fila o maior Rotulo da iteração

            vetorarestasPorRotulo[maiorRotulo.second] = -1; //modifica no vetor o RRotulo que ja foi adicionado para que ele não se repita

            maiorRotulo.first = 0;   //reinicia o numero de arestas como 0
            maiorRotulo.second = -1; //reinicia o Rotulo como -1
        }
        //FIM FUNÇÃO ORDENA CANDIDATOS

        Graph *q = new Graph(this->order, 0); //-1 pois começamos a contar os rotulos do 0, então -1 significa que não a rotulos
        while (!q->verificaConexo(q))         //Enquanto o grafo solução não for conexo repita
        {
            //Heuristica
            int rotuloAdicionado = arestasPorRotulo.front();
            q->adicionaRotulo(rotuloAdicionado, q, this); //chama a função q coloca o Rotulo no grafo e adiciona as arestas desse Rotulo
            arestasPorRotulo.pop_front();                 //remove o topo da fila
        }

        return q;
    }
    else
    {
        return NULL;
    }
}

Graph *Graph::gulosoRandomizado(float alfa, int instancia, int numIteracoes, Graph *melhorSolucao, ofstream &output_file)
{ //deve ser iniciado com Instancia 0 e Grafo melhorSolução==GrafoGerador

    if (instancia < numIteracoes)
    {
        //INICIO FUNÇÃO ORDENA CANDIDATOS
        std::list<int> arestasPorRotulo; //fila que aramzena os rotulos em ordem decrecente
        std::list<int>::iterator iterador;
        int vetorarestasPorRotulo[this->numeroRotulos]; //vetor que faz relação posição=Rotulo e valor da posição=numero de arestas;
        int vetorAux[this->numeroRotulos];
        for (int i = 0; i < this->numeroRotulos; i++)
        {                                              //repetir para o numero de rotulos
            vetorarestasPorRotulo[i] = contaRotulo(i); //para a posição i(que representa o Rótulo i) atribui o valor numero de arestas do Rotulo i
            vetorAux[i] = 0;
        }

        pair<int, int> maiorRotulo; //par que representa o maior rotulo atual <numero de arestas,Rotulo>
        maiorRotulo.first = 0;      //inicia o numero de arestas como 0
        maiorRotulo.second = -1;    //inicia o Rotulo como -1

        while (arestasPorRotulo.size() < this->numeroRotulos) //enquanto o tamanho da fila for menor que o numero de Rotulos
        {
            for (int i = 0; i < this->numeroRotulos; i++) //repetir para o numero de rotulos
            {
                if (maiorRotulo.first <= vetorarestasPorRotulo[i]) //se o numero de arestas do maior Rotulo Atual for menor ou igual do numero de arestas do rotulo a ser analisado (precisa ser menor ou IGUAL pq caso exista um Rotulo com 0 arestas iria bugar o codigo)
                {
                    maiorRotulo.first = vetorarestasPorRotulo[i]; //numero de arestas do maior rotulo igual ao numero de arestas do rotulo analisado
                    maiorRotulo.second = i;                       //maior Rotulo igual ao Rotulo analisado
                }
            }
            vetorAux[maiorRotulo.second] = maiorRotulo.first;
            arestasPorRotulo.push_back(maiorRotulo.second); //adiciona na parte de tras da fila o maior Rotulo da iteração

            vetorarestasPorRotulo[maiorRotulo.second] = -1; //modifica no vetor o RRotulo que ja foi adicionado para que ele não se repita

            maiorRotulo.first = 0;   //reinicia o numero de arestas como 0
            maiorRotulo.second = -1; //reinicia o Rotulo como -1
        }
        //FIM FUNÇÃO ORDENA CANDIDATOS

        Graph *q = new Graph(this->order, 0); //-1 pois começamos a contar os rotulos do 0, então -1 significa que não a rotulos
        while (!q->verificaConexo(q))         //Enquanto o grafo solução não for conexo repita
        {

            int numeroCadidatosPlausiveis = ceil(arestasPorRotulo.size() * alfa); //usa o alfa para saber quantas posições da fila temos que analisar
                                                                                  //sorteia um numero entre 0 e numeroCadidatosPlausiveis
            srand((unsigned)time(NULL));
            int k = (rand() % numeroCadidatosPlausiveis);

            int contador = 0;
            for (iterador = arestasPorRotulo.begin(); iterador != arestasPorRotulo.end(); iterador++) //percorre todos os valores da lista
            {

                if (contador == k)
                {                                                 //quando o contador for igual ao numero sorteado
                    int rotuloAdicionado = *iterador;             //rotulo adicionado recebe o valor que esta no iterador
                    q->adicionaRotulo(rotuloAdicionado, q, this); //chama a função q coloca o Rotulo no grafo e adiciona as arestas desse Rotulo
                    arestasPorRotulo.erase(iterador);
                    break; //remove a posição sorteada da fila
                }
                contador++;
            }
        }

        //saiu do while e a solução já foi encontrada
        //compara a solução atual com a melhor solução

        if ((q->getNumRotulos()) < (melhorSolucao->getNumRotulos()))
        {
            melhorSolucao = q;
        }

        //chama o método recursivamente
        gulosoRandomizado(alfa, instancia + 1, numIteracoes, melhorSolucao, output_file);
    }
    else
    {
        Graph *aux = melhorSolucao;
        return aux;
    }
    return melhorSolucao;
}

Graph *Graph::gulosoRandomizadoReativo(int instancia, int numIteracoes, Graph *melhorSolucao, int numAlfa, float *alfa, float *probAlfa, int *mediaAlfa, int *vezesUsada, ofstream &output_file)
{ //deve ser iniciado com Instancia 0 e Grafo melhorSolução==GrafoGerador

    // func atualiza as probabilidades dos alfas

    if (instancia < numIteracoes)
    {
        if (instancia < numAlfa)
        {

            std::list<int> arestasPorRotulo; //fila que aramzena os rotulos em ordem decrecente
            std::list<int>::iterator iterador;
            int vetorarestasPorRotulo[this->numeroRotulos]; //vetor que faz relação posição=Rotulo e valor da posição=numero de arestas;
            int vetorAux[this->numeroRotulos];
            for (int i = 0; i < this->numeroRotulos; i++)
            {                                              //repetir para o numero de rotulos
                vetorarestasPorRotulo[i] = contaRotulo(i); //para a posição i(que representa o Rótulo i) atribui o valor numero de arestas do Rotulo i
                vetorAux[i] = 0;
            }

            pair<int, int> maiorRotulo; //par que representa o maior rotulo atual <numero de arestas,Rotulo>
            maiorRotulo.first = 0;      //inicia o numero de arestas como 0
            maiorRotulo.second = -1;    //inicia o Rotulo como -1

            while (arestasPorRotulo.size() < this->numeroRotulos) //enquanto o tamanho da fila for menor que o numero de Rotulos
            {
                for (int i = 0; i < this->numeroRotulos; i++) //repetir para o numero de rotulos
                {
                    if (maiorRotulo.first <= vetorarestasPorRotulo[i]) //se o numero de arestas do maior Rotulo Atual for menor ou igual do numero de arestas do rotulo a ser analisado (precisa ser menor ou IGUAL pq caso exista um Rotulo com 0 arestas iria bugar o codigo)
                    {
                        maiorRotulo.first = vetorarestasPorRotulo[i]; //numero de arestas do maior rotulo igual ao numero de arestas do rotulo analisado
                        maiorRotulo.second = i;                       //maior Rotulo igual ao Rotulo analisado
                    }
                }
                vetorAux[maiorRotulo.second] = maiorRotulo.first;
                arestasPorRotulo.push_back(maiorRotulo.second); //adiciona na parte de tras da fila o maior Rotulo da iteração

                vetorarestasPorRotulo[maiorRotulo.second] = -1; //modifica no vetor o RRotulo que ja foi adicionado para que ele não se repita

                maiorRotulo.first = 0;   //reinicia o numero de arestas como 0
                maiorRotulo.second = -1; //reinicia o Rotulo como -1
            }
            //FIM FUNÇÃO ORDENA CANDIDATOS

            Graph *q = new Graph(this->order, 0); //-1 pois começamos a contar os rotulos do 0, então -1 significa que não a rotulos
            while (!q->verificaConexo(q))         //Enquanto o grafo solução não for conexo repita
            {

                int numeroCadidatosPlausiveis = ceil(arestasPorRotulo.size() * alfa[instancia]); //usa o alfa para saber quantas posições da fila temos que analisar

                //sorteia um numero entre 0 e numeroCadidatosPlausiveis
                
                int k = (rand() % numeroCadidatosPlausiveis);

                int contador = 0;
                for (iterador = arestasPorRotulo.begin(); iterador != arestasPorRotulo.end(); iterador++) //percorre todos os valores da lista
                {

                    if (contador == k)
                    {                                                 //quando o contador for igual ao numero sorteado
                        int rotuloAdicionado = *iterador;             //rotulo adicionado recebe o valor que esta no iterador
                        q->adicionaRotulo(rotuloAdicionado, q, this); //chama a função q coloca o Rotulo no grafo e adiciona as arestas desse Rotulo
                        arestasPorRotulo.erase(iterador);             //remove a posição sorteada da fila
                    }
                    contador++;
                }
            }

            vezesUsada[instancia] = vezesUsada[instancia] + 1; //aumenta a quantidade de vezes usada daquele alfa
            //saiu do while e a solução já foi encontrada

            mediaAlfa[instancia] = (mediaAlfa[instancia] * (vezesUsada[instancia] - 1) + q->getNumRotulos()) / vezesUsada[instancia]; // atualiza o valor meido de suluções daquele alfa
            //compara a solução atual com a melhor solução
            if ((q->getNumRotulos()) < (melhorSolucao->getNumRotulos()))
            {
                melhorSolucao = q;
            }
            //chama o método recursivamente
            gulosoRandomizadoReativo(instancia + 1, numIteracoes, melhorSolucao, numAlfa, alfa, probAlfa, mediaAlfa, vezesUsada, output_file);
        }

        else
        {
            funcAtualizaProbAlfas(melhorSolucao, numAlfa, alfa, probAlfa, mediaAlfa, output_file);

            //INICIO FUNÇÃO ORDENA CANDIDATOS
            std::list<int> arestasPorRotulo; //fila que aramzena os rotulos em ordem decrecente
            std::list<int>::iterator iterador;
            int vetorarestasPorRotulo[this->numeroRotulos]; //vetor que faz relação posição=Rotulo e valor da posição=numero de arestas;
            int vetorAux[this->numeroRotulos];
            for (int i = 0; i < this->numeroRotulos; i++)
            {                                              //repetir para o numero de rotulos
                vetorarestasPorRotulo[i] = contaRotulo(i); //para a posição i(que representa o Rótulo i) atribui o valor numero de arestas do Rotulo i
                vetorAux[i] = 0;
            }

            pair<int, int> maiorRotulo; //par que representa o maior rotulo atual <numero de arestas,Rotulo>
            maiorRotulo.first = 0;      //inicia o numero de arestas como 0
            maiorRotulo.second = -1;    //inicia o Rotulo como -1

            while (arestasPorRotulo.size() < this->numeroRotulos) //enquanto o tamanho da fila for menor que o numero de Rotulos
            {
                for (int i = 0; i < this->numeroRotulos; i++) //repetir para o numero de rotulos
                {
                    if (maiorRotulo.first <= vetorarestasPorRotulo[i]) //se o numero de arestas do maior Rotulo Atual for menor ou igual do numero de arestas do rotulo a ser analisado (precisa ser menor ou IGUAL pq caso exista um Rotulo com 0 arestas iria bugar o codigo)
                    {
                        maiorRotulo.first = vetorarestasPorRotulo[i]; //numero de arestas do maior rotulo igual ao numero de arestas do rotulo analisado
                        maiorRotulo.second = i;                       //maior Rotulo igual ao Rotulo analisado
                    }
                }
                vetorAux[maiorRotulo.second] = maiorRotulo.first;
                arestasPorRotulo.push_back(maiorRotulo.second); //adiciona na parte de tras da fila o maior Rotulo da iteração

                vetorarestasPorRotulo[maiorRotulo.second] = -1; //modifica no vetor o RRotulo que ja foi adicionado para que ele não se repita

                maiorRotulo.first = 0;   //reinicia o numero de arestas como 0
                maiorRotulo.second = -1; //reinicia o Rotulo como -1
            }
            //FIM FUNÇÃO ORDENA CANDIDATOS

            int alfaEscolhido = 0;
            alfaEscolhido = funcEscolheAlfa(numAlfa, alfa, probAlfa, output_file); //faz o bagulho de probabilidade pra achar qual alfa q usa
            vezesUsada[alfaEscolhido] = vezesUsada[alfaEscolhido] + 1; //aumenta a quantidade de vezes usada daquele alfa

            Graph *q = new Graph(this->order, 0); //-1 pois começamos a contar os rotulos do 0, então -1 significa que não a rotulos
            while (!q->verificaConexo(q))         //Enquanto o grafo solução não for conexo repita
            {

                int numeroCadidatosPlausiveis = ceil(arestasPorRotulo.size() * alfa[alfaEscolhido]); //usa o alfa para saber quantas posições da fila temos que analisar

                //sorteia um numero entre 0 e numeroCadidatosPlausiveis
                
                int k = (rand() % numeroCadidatosPlausiveis);

                int contador = 0;
                for (iterador = arestasPorRotulo.begin(); iterador != arestasPorRotulo.end(); iterador++) //percorre todos os valores da lista
                {
                    if (contador == k)
                    {                                                 //quando o contador for igual ao numero sorteado
                        int rotuloAdicionado = *iterador;             //rotulo adicionado recebe o valor que esta no iterador
                        q->adicionaRotulo(rotuloAdicionado, q, this); //chama a função q coloca o Rotulo no grafo e adiciona as arestas desse Rotulo
                        arestasPorRotulo.erase(iterador);             //remove a posição sorteada da fila
                    }
                    contador++;
                }
            }

            //saiu do while e a solução já foi encontrada
            mediaAlfa[alfaEscolhido] = (mediaAlfa[alfaEscolhido] * (vezesUsada[alfaEscolhido] - 1) + q->getNumRotulos()) / vezesUsada[alfaEscolhido];
            //compara a solução atual com a melhor solução
            if ((q->getNumRotulos()) < (melhorSolucao->getNumRotulos()))
            {
                melhorSolucao = q;
            }
            //chama o método recursivamente
            gulosoRandomizadoReativo(instancia + 1, numIteracoes, melhorSolucao, numAlfa, alfa, probAlfa, mediaAlfa, vezesUsada, output_file);
        }
    }
    else
    {
        return melhorSolucao;
    }
    return melhorSolucao;
}

void Graph::aumentaQtdRotulos()
{
    this->numeroRotulos = 1 + this->numeroRotulos;
}

void Graph::adicionaRotulo(int rotuloAnalisado, Graph *grafoNovo, Graph *grafoOriginal)
{
    //adiciona o Rotulo no grafoNovo
    list<int> aux = grafoNovo->rotulos;
    aux.push_back(rotuloAnalisado);
    grafoNovo->rotulos = aux;
    grafoNovo->aumentaQtdRotulos();

    //percorre todas as arestas
    for (Node *it = grafoOriginal->getFirstNode(); it != NULL; it = it->getNextNode())
    {

        for (Edge *it2 = it->getFirstEdge(); it2 != NULL; it2 = it2->getNextEdge())
        {
            if (it2->getRotulo() == rotuloAnalisado) //se o rotulo da aresta for igual ao rotuloAnalisado
            {
                grafoNovo->insertEdge(it->getId(), it2->getTargetId(), rotuloAnalisado); //adiciona a aresta no grafoNovo
            }
        }
    }
}

bool Graph::verificaConexo(Graph *grafo) // ta errado
{

    //com o id do vértice acha o vertice que deve ser analisado
    int idParametro = grafo->getFirstNode()->getId();
    //cria um vetor que marca quais vértices ja foram analisados
    bool visitados[grafo->getOrder()];
    //cria o vetor ligacao que verifica se tem caminho entre os vertices dizendo quais vértices se ligam de alguma maneira ao primeiro vertice
    bool ligacao[grafo->getOrder()];
    //cria uma fila que diz quais vertices ainda precisam ser analisados
    list<int> fila;
    //adiciona o vertice inicial nele
    fila.push_front(idParametro);

    for (int i = 0; i < grafo->getOrder(); i++)
    {
        visitados[i] = false;
        ligacao[i] = false;
    }

    //começa iteração (enquanto a fila não estiver vazia repita)
    while (!(fila.empty()))
    {
        //pega um vértice a ser analisado da fila
        int aux = fila.front();
        int IdAnalisado = aux;
        Node *V;
        V = getNode(fila.front());
        //exclui ele da fila
        fila.pop_front();
        //verifica se o vértice a ser analisado ja foi analisado. (se ele ja foi acaba essa iteração)
        if (visitados[IdAnalisado] == false)
        {
            //marca o vértice como visitado;
            visitados[IdAnalisado] = true;
            //marca ele como fazendo parrte da ligacao

            // tem caminho
            ligacao[IdAnalisado] = true;
            //adiciona todos os vértices adjacentes a ele na fila
            for (Edge *it = V->getFirstEdge(); it != NULL; it = it->getNextEdge())
            {
                int verticeAdjacente = it->getTargetId();
                fila.push_front(verticeAdjacente);
            }
        }
    }

    bool conexo = true;
    for (int j = 0; j < grafo->getOrder(); j++)
    {
        if (ligacao[j] == false)
        {

            conexo = false;
            grafo->conexGraph = false;
        }
        else
        {
            grafo->conexGraph = true;
        }
    }
    return conexo;
}

int Graph::contaRotulo(int rotuloAnalisado)
{

    int numeroArestas = 0;

    for (Node *it = this->getFirstNode(); it != NULL; it = it->getNextNode())
    {

        for (Edge *it2 = it->getFirstEdge(); it2 != NULL; it2 = it2->getNextEdge())
        {
            if (it2->getRotulo() == rotuloAnalisado)
            {
                numeroArestas++;
            }
        }
    }
    return numeroArestas / 2; // tem q voltar dividido por 2 pq todas arestas foram adicionados 2 vezes, logo serão somadas duas vezes
}

void Graph::funcAtualizaProbAlfas(Graph *melhorSolucao, int numAlfa, float *alfa, float *probAlfa, int *mediaAlfa, ofstream &output_file)
{

    float qualidade[numAlfa];
    float somaDasQualidades = 0;
    for (int i = 0; i < numAlfa; i++)
    {
        qualidade[i] = ((float)melhorSolucao->getNumRotulos()) / (float)mediaAlfa[i];
        somaDasQualidades = somaDasQualidades + qualidade[i];
    }
    for (int j = 0; j < numAlfa; j++)
    {
        probAlfa[j] = qualidade[j] / somaDasQualidades;
    }
}

int Graph::funcEscolheAlfa(int numAlfa, float *alfa, float *probAlfa, ofstream &output_file)
{

    int vetValoresDaProbabilidade[numAlfa];
    int posicao = 0;
    for (int i = 0; i < numAlfa; i++)
    {
        vetValoresDaProbabilidade[i] = 0;
    }

    for (int j = 0; j < numAlfa; j++)
    {
        vetValoresDaProbabilidade[j] = posicao + probAlfa[j] * 100;
        posicao = vetValoresDaProbabilidade[j];
    }
    int valorProb = (int)(rand() % 100);
    int alfaRetornado = -1;
    for (int k = 0; k < numAlfa; k++)
    {
        if (valorProb <= vetValoresDaProbabilidade[k])
        {
            if (k == 0)
            {
                alfaRetornado = k;
            }
            else
            {
                if (valorProb > vetValoresDaProbabilidade[k - 1])
                {
                    alfaRetornado = k;
                }
            }
        }
    }
    return alfaRetornado;
}

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

    //começa iteração (enquanto a fila não estiver vazia repita)
    while (!(fila.empty()))
    {
        //pega um vértice a ser analisado da fila
        int aux = fila.front();
        int IdAnalisado = aux - 1;
        Node *V;
        V = getNode(fila.front());
        //exclui ele da fila
        fila.pop_front();
        //verifica se o vértice a ser analisado ja foi analisado. (se ele ja foi acaba essa iteração)
        if (visitados[IdAnalisado] == false)
        {
            //marca o vértice como visitado;
            visitados[IdAnalisado] = true;
            //adiciona ele no vetor fecho transitivo direto
            FTD[IdAnalisado] = true;
            //adiciona todos os vértices adjacentes a ele na fila
            for (Edge *it = V->getFirstEdge(); it != NULL; it = it->getNextEdge())
            {
                int verticeAdjacente = it->getTargetId();
                fila.push_front(verticeAdjacente);
            }
        }
    }

    //imprimir o FTD
    output_file << "O conjunto FTD do vértice " << id << " é: {";
    int contador = 0;
    for (int i = 0; i < this->order; i++)
    {
        if (FTD[i] == true)
        {
            contador++;
        }
    }
    for (int i = 0; i < this->order; i++)
    {
        if (FTD[i] == true)
        {
            if (contador - 1 > 0)
            {
                output_file << i + 1 << ", ";
                contador--;
            }
            else if (contador - 1 == 0)
            {
                output_file << i + 1;
            }
        }
    }
    output_file << "}" << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////CAMINHAMENTO,ALGORITMOS E ORDENACAO TOPOLOGICA///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
