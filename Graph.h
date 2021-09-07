/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/
/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>
#include <sstream>
#include<string>

using namespace std;

class Graph{

    
    //Atributes
    private:
        int order;
        int number_edges;
        bool conexGraph;
        Node* first_node;
        Node* last_node;
        std::list<int> rotulos;
        std::list<int>::iterator iteradorRotulos;
        int numeroRotulos;

    public:
        //Constructor
        Graph(int order, int numeroRotulos);
        //Destructor
        ~Graph();
        //Getters
        int getOrder();
        int getNumberEdges();
        Node* getFirstNode();
        Node* getLastNode();
        bool getConexGraph();
        //Other methods
        void insertNode(int id);
        void insertEdge(int id, int target_id, int rotulo);
        void removeNode(int id);
        bool searchNode(int id);
        Node* getNode(int id);
        void insertAllNodes();
        bool verificaAresta(id, target_id);

        int contaRotulo(int rotuloAnalisado,Graph *grafoOriginal);
       
        void fechoTransitivoIndireto(ofstream &output_file, int id);

        bool deepthFirstSearch1(int id, int start);
        void deepthFirstSearch(Graph *novoGrafo, int start);

        void auxDeepthFirstSearch1(bool verify[], Node *v);
        void auxDeepthFirstSearch(bool verify[], Graph *novoGrafo, Node *v);

        Graph* caminhamentoDeProfundidade(int x);
        Graph *getVertexInduced(int *listIdNodes, int tam);
        
        Graph *agmKuskal(ofstream &output_file);
        void getWeithlessEdge( int *nohAresta);
        int getWeightFromEdgeNodeCombo(int idNoh, int idAresta, Graph *subGrafo);
        bool verificaSubarvore(int v1, int v2, Graph *subGrafo);

        Graph *agmPrim(ofstream &output_file);
        void printGraph(ofstream &output_file);
        
        //methods phase1
        float greed();
        float greedRandom();
        float greedRactiveRandom();
    private:
        //Auxiliar methods
        

};

#endif // GRAPH_H_INCLUDED