#ifndef CLASSINVERTEDINDEX_H
#define CLASSINVERTEDINDEX_H
#include <Avlnode.h>
class ClassInvertedIndex
{
    public:
        Avlnode *head;                 //the root of the avl tree made of avlnodes.
        ClassInvertedIndex();          //constructor.
        virtual ~ClassInvertedIndex(); //destructor.
        //----------------------------------------------------------------------------------------------------------------------------------------//
        void addavlnode(unsigned int valueofnode);           //adds an avlnode,the value of which refers to a website's ID.
        void deleteavlnode(unsigned int valueofavlnode) ;    //deletes an avlnode.
        //---------------------------------------------------------------------------------------------------------------------------------------//
        unsigned int getavltreesize(Avlnode *head); //getters.
        unsigned int gettotalsize();
        //--------------------------------------------------------------------------------------------------------------------------------------//
        void setavltreesize(unsigned int k);        //setters.
        void settotalsize(unsigned int k);
        //-------------------------------------------------------------------------------------------------------------------------------------//

        Avlnode* findavlnode(Avlnode *head,unsigned int key);//searching function.
        //------------------------------------------------------------------------------------------------------------------------------------//

        void writetofile(char filename[]);          //function that writes the avltree(avlnodes+links) at a file named *(filename).
        //-----------------------------------------------------------------------------------------------------------------------------------//

    private:

        int height(Avlnode *temp);                  //functions that are related to balancing an Avlnode.
        int heightdifference(Avlnode *temp);
        Avlnode* balance(Avlnode *temp);
        //----------------------------------------------------------------------------------------------------------------------------------//
        //A V L _ N O D E   R O T A T I O N   F U N C T I O N S
        Avlnode* rr_rotation(Avlnode *parent);
        Avlnode* lr_rotation(Avlnode *parent);
        Avlnode* ll_rotation(Avlnode *parent);
        Avlnode* rl_rotation(Avlnode *parent);
        // --------------------------------------------------------------------------------------------------------------------------------//
        Avlnode* minimumvaluenode(Avlnode *minimum);                     //returns the avlnode with the smallest value.
        Avlnode* timetoinsertnode(Avlnode* head,unsigned int valueofnode);       //inserts  an avlnode,(in cooperation with function addavlnode).
        Avlnode* timetodeleteavlnode(Avlnode *head,unsigned int valueofavlnode); //deletes an avlnode (in cooperation with function deleteavlnode).
        //-------------------------------------------------------------------------------------------------------------------------------//
        bool existanceofelement(Avlnode *k,unsigned int element);                //checks if a website ID is already in the tree.
        //-------------------------------------------------------------------------------------------------------------------------------//
        void write(Avlnode *head,ostream &output);
        //------------------------------------------------------------------------------------------------------------------------------//
        unsigned int *avltreesize;
        unsigned int *totalsize;
};
#endif // CLASSINVERTEDINDEX_H
