#include "ClassInvertedIndex.h"
#include <fstream>
#include <iostream>
using namespace std;

ClassInvertedIndex::ClassInvertedIndex(){ //constructor
    this->head=NULL;
}

ClassInvertedIndex::~ClassInvertedIndex(){ //destructor
    delete head;
}

//-------------------------------------------------------------------------------------------------------------------------------------//
//G E T T E R S

unsigned int ClassInvertedIndex::getavltreesize(Avlnode *head){ //gets the total number of the website IDs (number of avlnodes)
    if(head==NULL){
			return 0;
		}
		return 1 + getavltreesize(head->getchildleft()) + getavltreesize(head->getchildright());
}

unsigned int ClassInvertedIndex::gettotalsize(){                //gets the total size of the tree (website IDs*website links) not needed in this project.
    return *totalsize;
}

//--------------------------------------------------------------------------------------------------------------------------------------//
// S E T T E R S

void ClassInvertedIndex::setavltreesize(unsigned int k){ //not reeded in this project.
    *avltreesize=k;
}

void ClassInvertedIndex::settotalsize(unsigned int k){            //not needed in this project.
    *totalsize=k;
}

//-----------------------------------------------------------------------------------------------------------------------------------//
//F U N C T I O N S   T H A T   A R E   R E L A T E D   T O   B A L A N C I N G   A N   A V L N O D E.

int ClassInvertedIndex::height(Avlnode *temp){            //calculates the maximum height of an avlnode. This can be used later to calculate
    int h = 0;                                 //the height differece of childleft and childright.See next function.
    if (temp != NULL)
    {
        int leftheight = height (temp->getchildleft());
        int righeight = height (temp->getchildright());
        int maximumheight = max (leftheight, righeight);
        h = maximumheight + 1;
    }
    return h;
}

int ClassInvertedIndex::heightdifference(Avlnode *temp){ //calculates the diffrence in height of the left and right subtrees of Avlnodes.

    int leftheight = height (temp->getchildleft());
    int rightheight = height (temp->getchildright());
    int balancingfactor= leftheight - rightheight;
    return balancingfactor;
}

Avlnode *ClassInvertedIndex::balance(Avlnode *temp){    //uses rotation functions to rebalance a avlnode tree.
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

//------------------------------------------------------------------------------------------------------------------------------------//

//I N S E R T I O N   A N D   D E L E T I O N   F U N C T I O N S   O F   A V L N O D E S.

bool ClassInvertedIndex::existanceofelement(Avlnode *k,unsigned int element){            //checks if an avlnode already exists.
    if (k==NULL)
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

void ClassInvertedIndex::addavlnode(unsigned int valueofnode){                            //adds an avlnode,the value of which refers to a website ID.

    if (existanceofelement(this->head,valueofnode)==false) //checks
    {
        this->head=timetoinsertnode(this->head,valueofnode); //if there isn't such avlnode inserts
    }
}

Avlnode* ClassInvertedIndex::timetoinsertnode(Avlnode* head,unsigned int valueofnode){   //inserts an avlnode

    if (head==NULL){
        head=new Avlnode(valueofnode);
        return head;
    }
    else if (valueofnode<(head->getdata())){
        head->setchildleft(timetoinsertnode(head->getchildleft(),valueofnode));
        head=balance(head);
    }
    else if (valueofnode>(head->getdata())){
        head->setchildright(timetoinsertnode(head->getchildright(),valueofnode));
        head=balance(head);
    }
    return head; //does not insert avlnode with the same value.
}

void ClassInvertedIndex::deleteavlnode(unsigned int valueofavlnode){                     //not really needed in this project ,but could be used to delete a website (avlnode).
    if (existanceofelement(this->head,valueofavlnode)==true)
    {
        this->head=timetodeleteavlnode(this->head,valueofavlnode);
    }
}

Avlnode* ClassInvertedIndex::timetodeleteavlnode(Avlnode *head,unsigned int valueofnode){//not really needed in this project ,but could be used to delete a website (avlnode).
                                                                                //links are not deleted if this code is used(only the avlnode is deleted,not the nodes that it includes)
    if (head==NULL){
        return head;
    }
    //if value of avlnode is smaller than the value of the head then it exists in the left subtree.
    if (valueofnode<head->getdata()){
        head->setchildleft(timetodeleteavlnode(head->getchildleft(),valueofnode));
    }
    //if value of node is greater than the value of the head then it exists in the right subtree.
    else if (valueofnode>head->getdata()){
        head->setchildright(timetodeleteavlnode(head->getchildright(),valueofnode));
    }
    //avlnode to be deleted found...value of node==value of head.
    else{
        //if avlnode has one or zero childs do the following:
        if((head->getchildleft()==NULL) || (head->getchildright()==NULL))
        {
            Avlnode *temp=head->getchildleft()?head->getchildleft() : head->getchildright();
            // zero childs
            if(temp==NULL){
                temp=head;
                head=NULL;
            }
            //one child
            else{
                *head=*temp;//copy the contents of the child
            }
            delete(temp);
        }
        else{
            //two children : get the smallest in the right subtree
            //and replace it with the root.
            Avlnode *temp;
            temp=minimumvaluenode(head->getchildright());
            unsigned int tempvalue=temp->getdata();
            head->setdata(tempvalue);
            head->setchildright(timetodeleteavlnode(head->getchildright(),temp->getdata()));
        }
    }
    if (head==NULL){
        return head;
    }
    head=balance(head);
    return head;

}

Avlnode* ClassInvertedIndex::minimumvaluenode(Avlnode *minimum){                //returns the avlnode with the smallest value .
    Avlnode *current;
    current=minimum;
    while (current->getchildleft()!=NULL)
    {
        current=current->getchildleft();
    }
    return current;

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------//

//A V L _ N O D E   R O T A T I O N   F U N C T I O N S

//RIGHT ROTATION
 Avlnode* ClassInvertedIndex::rr_rotation(Avlnode *parent){

    Avlnode *temp;
    temp = parent->getchildright();
    parent->setchildright(temp->getchildleft());
    temp->setchildleft(parent);
    return temp;
}

//LEFT ROTATION
Avlnode *ClassInvertedIndex::ll_rotation(Avlnode *parent){

    Avlnode *temp;
    temp = parent->getchildleft();
    parent->setchildleft(temp->getchildright());
    temp->setchildright(parent);
    return temp;
}

//RIGHT LEFT ROTATION
Avlnode *ClassInvertedIndex::rl_rotation(Avlnode *parent){
    Avlnode *temp;
    temp = parent->getchildright();
    parent->setchildright( ll_rotation (temp));
    return rr_rotation (parent);
}

//LEFT RIGHT ROTATION
Avlnode *ClassInvertedIndex::lr_rotation(Avlnode *parent){
    Avlnode *temp;
    temp = parent->getchildleft();
    parent->setchildleft(rr_rotation (temp));
    return ll_rotation (parent);
}

//----------------------------------------------------------------------------------------------------------------------------------------------

Avlnode* ClassInvertedIndex::findavlnode(Avlnode *head,unsigned int key){ //finds and returns the address of an avlnode based on value provided(key).this can be used to add or
    if (head==NULL){                                             //delete a link.
            return NULL;
    }
    if (key==head->getdata()){
            return head;
    }
    if (key<head->getdata()){
        return findavlnode(head->getchildleft(),key);
    }
    else{
        return findavlnode(head->getchildright(),key);
    }
}

void ClassInvertedIndex::writetofile(char nameoffile[]){
    ofstream output;
    output.open(nameoffile);
    if(!output){
        cerr<<"couldnt open file output";
        return ;
     }
     else{
        //output<<"There are " << this->getavltreesize(this->head) << " websites with links. These are : " <<endl<<endl;
        write(head,output);
        output.close();
     }
}

void ClassInvertedIndex::write(Avlnode *head,ostream &output){
    if(head==NULL){
        return;
    }
    write(head->getchildleft(),output);
    output<<"website_ID : "<<head->getdata()<<", "<<"num_of_link_IDs : "<<head->getavlnodesize(head->getroot())<<" ,"<<"link_IDs:"<<" " ;
    head->inordernodestofile(head->getroot(),output);
    output<<"\n";
    write(head->getchildright(),output);
}



