#include <ClassInvertedIndex.h>
#include <iostream>
#include <fstream>
#include <string.h>      //The purpose of this program is to add website IDs and insert or delete links to these websites and then print them to a text document.
#include <cstdlib>       //In order to do that a website inside this program is described as 'avlnode' and its links as 'nodes'
#include <stdio.h>       //And that's because all website IDs are saved in the form of an avl tree(An avl tree contains all the website IDs).
#include <stdlib.h>      //Each avlnode from that tree contains another alvtree which is formed from the links to this website.
#include <iostream>      //The 'head' is the root of the tree made of avlnodes.The 'root' is the root of the tree made of nodes(links)
#include <ostream>       //Each Avlnode has such a 'root'.
                        //Insertion,search and deletion all take time ~log(n).
using namespace std;

int main(){
    unsigned int x,y;
    char nameoffile[30];
    string mission;
    ClassInvertedIndex tree;
    ifstream commands;
    commands.open("commands.txt"); //opens the commands.txt to follow instructions
    if(!commands){
        cerr<<"could not open commands.txt \n";
        return 0;
    }
    else{
        while(!commands.eof()){
            commands>>mission;
            if(mission=="READ_DATA"){
                commands>>nameoffile;
                ifstream input;
                input.open(nameoffile);
                if(!input){
                    cerr<<"could not open file : "<<nameoffile<<endl;
                    return 0;
                }
                else{
                    cout<<"reading data,please wait... (^_^)"<<endl;
                    while(!input.eof()){
                        input>>x;
                        input>>y;
                        tree.addavlnode(x);
                        //tree.addavlnode(y); // can be used if you want to make avlnodes from the right column of the input file
                        Avlnode *temp;
                        temp=tree.findavlnode(tree.head,x);
                        temp->addlink(y);
                    }
                    cout<<"program has finished reading data"<<endl;
                }
                input.close();
            }
            if(mission=="INSERT_LINK"){
                commands>>x;
                commands>>y;
                tree.addavlnode(x);
                //tree.addavlnode(y); //if reads command : INSERT_LINK 14  35 then makes 35 an avlnode
                Avlnode *temp;
                temp=tree.findavlnode(tree.head,x);
                temp->addlink(y);
            }
            if(mission=="DELETE_LINK"){
                commands>>x;
                commands>>y;
                Avlnode *temp;
                temp=tree.findavlnode(tree.head,x);
                temp->deletelink(y);
            }
            if(mission=="WRITE_INDEX"){
                commands>>nameoffile;
                tree.writetofile(nameoffile);

            }
        }
        cout<<"text document created named : " <<nameoffile<<endl<<endl<<endl;

    }
    commands.close();

    return 0;
}
