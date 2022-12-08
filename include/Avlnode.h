#ifndef AVLNODE_H
#define AVLNODE_H
#include <Node.h>
#include <ostream>
using namespace std;
class Avlnode{
    public:
        Avlnode(){}         //void constructor
        Avlnode(unsigned int datak);//constructor
        virtual ~Avlnode();//destructor
        //-----------------------------------------------------------------------------------------------------------//
        //G E T T E R S
        unsigned int getavlnodesize(Node *root);
        unsigned int getdata();
        Node *getroot();
        Avlnode *getchildleft();
        Avlnode *getchildright();
        //----------------------------------------------------------------------------------------------------------//
        //S E T T E R S
        void setavlsize(unsigned int num);
        void setdata(unsigned int datak);
        void setroot(Node *root);
        void setchildright(Avlnode *childright);
        void setchildleft(Avlnode *childleft);
        //--------------------------------------------------------------------------------------------------------//
        void addlink(unsigned int valueofnode);    //adds a simple node,the value of which refers to a link of a website's ID
        void deletelink(unsigned int valueofnode); //deletes a link (link to a website)
        //-------------------------------------------------------------------------------------------------------//
        //printing to file function
        void inordernodestofile(Node *root,ostream &os);

    private:

        Node *root;          //the root of the avltree made of nodes.
        Avlnode *childleft;  //the left child of an avlnode.
        Avlnode *childright; //the right child of an avlnode.
        //--------------------------------------------------------------------------------------------------------//
        //functions that are related to balancing an Avlnode
        int height(Node *temp);
        int heightdifference(Node *temp);
        Node* balance(Node *temp);
        //---------------------------------------------------------------------------------------------------------//
        bool existanceofelement(Node *k,unsigned int element);//checks if a node exists.
        //--------------------------------------------------------------------------------------------------------//
         Node* timetoinsertnode(Node* root,unsigned int valueofnode);  //inserts a node
         Node* timetodeletenode(Node *root,unsigned int valueofnode); //deletes a link  (in cooperation with deletelink)
         Node* minimumvaluenode(Node *minimum);              //returns the node with the smallest value.
         //------------------------------------------------------------------------------------------------------//
        //N O D E   R O T A T I O N   F U N C T I O N S
        Node* rr_rotation(Node *parent);
        Node* lr_rotation(Node *parent);
        Node* ll_rotation(Node *parent);
        Node* rl_rotation(Node *parent);
        // ------------------------------------------------------------------------------------------------------//
        unsigned int *data; //the value of an avlnode
        int *avlsize;

};
#endif // AVLNODE_H
