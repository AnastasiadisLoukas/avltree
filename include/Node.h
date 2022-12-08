#ifndef NODE_H
#define NODE_H
class Node{
    public:
        Node();
        Node(unsigned int datak) ;//constructor
        virtual ~Node(); //destructor
        //-----------------------------------------------------------//
        unsigned int getdata(); //getters
        Node *getchildleft();
        Node *getchildright();
        //-----------------------------------------------------------//
        void setdata(unsigned int datak); //setters
        void setchildright(Node *childright);
        void setchildleft(Node *childleft);

    private:

        Node *childleft;   //left child of a node.
        Node *childright; //right child of a node.
        unsigned int *data;        //value of a node.

};
#endif // NODE_H
