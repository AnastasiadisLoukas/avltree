#include "Node.h"
#include <iostream>
Node::Node(){}              //void constructor of a node
Node::Node(unsigned int datak){      //constructor of a node setting the value of the same node.
    data=new unsigned int;
    *data=datak;
    this->childleft=NULL;
    this->childright=NULL;
}

Node::~Node(){              //destructor of a node
    delete data;
};

//----------------------------------------------------------------------------//

unsigned int Node::getdata(){        //gets the value of the node.
    return *data;
}

Node* Node::getchildleft(){ //gets the left child node.
    return childleft;
}

Node* Node::getchildright(){ //gets the right child node.
    return childright;
}

//---------------------------------------------------------------------------//

void Node::setdata(unsigned int datak){              //sets the value of the node.
    *data=datak;
}

void Node::setchildright(Node *childright){ //sets the right child node.
    this->childright=childright;
}

 void Node::setchildleft(Node *childleft){ //sets the left child node.
    this->childleft=childleft;
}
