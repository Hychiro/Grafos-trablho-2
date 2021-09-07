/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

// Definition of the Edge class
class Edge{

    // Attributes
    private:
        int target_id;
        Edge* next_edge;
        int rotulo;

    public:
        // Constructor
        Edge(int target_id);
        // Destructor
        ~Edge();
        // Getters
        int getTargetId();
        Edge* getNextEdge();
        int getRotulo();
        // Setters
        void setNextEdge(Edge* edge);
        void setRotulo(int rotulo); 

}; 

#endif // EDGE_H_INCLUDED