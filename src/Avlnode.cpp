#include "Avlnode.h"
#include <iostream>
using namespace std;

Avlnode::Avlnode(unsigned int datak){ //constructor
    data=new unsigned int;
    *data=datak;
    avlsize=new int;
    this->childright=NULL;
    this->childleft=NULL;
    this->root=NULL;
}

Avlnode::~Avlnode(){        //destructor
    delete data;
    delete avlsize;
    delete root;
}

//---------------------------------------------------------------------------------------------------------------------------------------------//
//G E T T E R S

unsigned int Avlnode::getavlnodesize(Node *root){//gets the number of nodes of an avlnode (number of links to a website)
		if(root==NULL){
			return 0;
		}
		return 1 + getavlnodesize(root->getchildleft()) + getavlnodesize(root->getchildright());
}

unsigned int Avlnode::getdata(){                 //gets the value of an avlnode.
    return *data;
}

Node *Avlnode::getroot(){               //gets the root node.(the start of the node avltree)
    return root;
}

Avlnode *Avlnode::getchildleft(){       //gets the left child avlnode.
    return childleft;
}

Avlnode *Avlnode::getchildright(){      //gets the right child avlnode.
    return childright;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
// S E T T E R S

 void Avlnode::setavlsize(unsigned int num){
    *avlsize=num;
}

void Avlnode::setdata(unsigned int datak){
    *data=datak;
}

void Avlnode::setroot(Node *root){
    this->root=root;
}

void Avlnode::setchildright(Avlnode *childright){
    this->childright=childright;
}

void Avlnode::setchildleft(Avlnode *childleft){
    this->childleft=childleft;
}

//------------------------------------------------------------------------------------------------------------------------------------------------//
//F U N C T I O N S   T H A T   A R E   R E L A T E D   T O   B A L A N C I N G    A   N O D E.

int Avlnode::height(Node *temp){            //calculates the maximum height of a node. This can be used later to calculate
    int h = 0;                   //the height differece of childleft and childright.See next function.
    if (temp != NULL)
    {
        int leftheight = height (temp->getchildleft());
        int righeight = height (temp->getchildright());
        int maximumheight = max (leftheight, righeight);
        h = maximumheight + 1;
    }
    return h;
}

int Avlnode::heightdifference(Node *temp) { //calculates the diffrence in height of the left and right subtrees of nodes.

    int leftheight = height (temp->getchildleft());
    int rightheight = height (temp->getchildright());
    int balancingfactor= leftheight - rightheight;
    return balancingfactor;
}

Node *Avlnode::balance(Node *temp){         //uses rotation functions to rebalance a node tree.
    int balancingfactor = heightdifference(temp);
    if (balancingfactor > 1)
    {
        if (heightdifference(temp->getchildleft()) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (balancingfactor < -1)
    {
        if (heightdifference(temp->getchildright()) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}

//----------------------------------------------------------------------------------------------------------------------------------//
//I N S E R T I O N   A N D   D E L E T I O N   F U N C T I O N S   O F   N O D E S.

bool Avlnode::existanceofelement(Node *k,unsigned int element){
    if(k==NULL)
        return false;
    else if (element==(k->getdata()))
        return true;
    else if (element<(k->getdata()))
    {
        return existanceofelement(k->getchildleft(),element);
    }
    else
    {
        return existanceofelement(k->getchildright(),element);
    }
}

void Avlnode::addlink(unsigned int valueofnode){                         //adds a simple node,the value of which refers to a link of a website's ID
    if (existanceofelement(this->getroot(),valueofnode)==false)          //checks
    {
        this->setroot(timetoinsertnode(this->getroot(),valueofnode));  //if there isn't such node(link) inserts
    }
}

 Node* Avlnode::timetoinsertnode(Node* root,unsigned int valueofnode) { //inserts a node
    if (root==NULL){
        root=new Node(valueofnode);
        return root;
    }
    else if (valueofnode<(root->getdata())){
        root->setchildleft(timetoinsertnode((root->getchildleft()),valueofnode));
        root=balance(root);
    }
    else if(valueofnode>(root->getdata())){
        root->setchildright(timetoinsertnode((root->getchildright()),valueofnode));
        root=balance(root);
    }
    return root;
 }

void Avlnode::deletelink(unsigned int valueofnode){                    //deletes a node from an avlnode(link from a website)
    if (existanceofelement(this->getroot(),valueofnode)==true)
    {
        //cout<<"it exists"<<endl;
        this->setroot(timetodeletenode(this->getroot(),valueofnode));
    }
}

Node* Avlnode::timetodeletenode(Node *root,unsigned int valueofnode){  //returns the root of the node tree after deleting a node(link to a website).

    if (root==NULL){
        return root;
    }
    //if value of node is smaller than the value of the root then it exists in the left subtree.
    if (valueofnode<root->getdata()){
        root->setchildleft(timetodeletenode(root->getchildleft(),valueofnode));
    }
    //if value of node is greater than the value of the root then it exists in the right subtree.
    else if (valueofnode>root->getdata()){
        root->setchildright(timetodeletenode(root->getchildright(),valueofnode));
    }
    //node to be deleted found...value of node==value of root.
    else{
        //if node has one or zero childs do the following:
        if((root->getchildleft()==NULL) || (root->getchildright()==NULL))
        {
            Node *temp=root->getchildleft()?root->getchildleft() : root->getchildright();
            // zero childs
            if(temp==NULL){
                temp=root;
                root=NULL;
            }
            //one child
            else{
                *root=*temp;//copy the contents of the child
            }
            delete(temp);
        }
        else{
            //two children : get the smallest in the right subtree
            //and replace it with the root.
            Node *temp;
            temp=minimumvaluenode(root->getchildright());
            unsigned int tempvalue=temp->getdata();
            root->setdata(tempvalue);
            root->setchildright(timetodeletenode(root->getchildright(),temp->getdata()));
        }
    }
    if (root==NULL){
        return root;
    }
    root=balance(root);
    return root;

}

Node* Avlnode::minimumvaluenode(Node *minimum){                //returns the node with the smallest value .
    Node *current;
    current=minimum;
    while (current->getchildleft()!=NULL)
    {
        current=current->getchildleft();
    }
    return current;

}

//-----------------------------------------------------------------------------------------------------------------------------------//

//N O D E   R O T A T I O N   F U N C T I O N S

//RIGHT ROTATION
 Node* Avlnode::rr_rotation(Node *parent){

    Node *temp;
    temp = parent->getchildright();
    parent->setchildright(temp->getchildleft());
    temp->setchildleft(parent);
    return temp;
}

//LEFT ROTATION
Node *Avlnode::ll_rotation(Node *parent){

    Node *temp;
    temp = parent->getchildleft();
    parent->setchildleft(temp->getchildright());
    temp->setchildright(parent);
    return temp;
}

//RIGHT LEFT ROTATION
Node *Avlnode::rl_rotation(Node *parent){
    Node *temp;
    temp = parent->getchildright();
    parent->setchildright(ll_rotation (temp)) ;
    return rr_rotation (parent);
}

//LEFT RIGHT ROTATION
Node *Avlnode::lr_rotation(Node *parent){
    Node *temp;
    temp = parent->getchildleft();
    parent->setchildleft(rr_rotation (temp));
    return ll_rotation (parent);
}

//------------------------------------------------------------------------------------------------//
void Avlnode::inordernodestofile(Node *root,ostream &os){
    if (root == NULL){
        return;
    }
    else{
        inordernodestofile (root->getchildleft(),os);
        os<<root->getdata()<<"  ";
        inordernodestofile (root->getchildright(),os);
    }
}
