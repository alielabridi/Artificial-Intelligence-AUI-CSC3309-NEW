//
// Created by Ali on 11/2/2016.
//

#ifndef ASG2_EXPLOREDSET_H
#define ASG2_EXPLOREDSET_H

#include "Node.h"
class ExploredSet{
public:
    vector<Node *> Vec;
    //vector<Node*> Hashtable[81]; // the largest number of pegs in all games

    void add(Node * node){
        Vec.push_back(node);
    }
    bool exists(Node * node){
        for(Node * V : Vec){
            if(V->equals(node))
                return true;
        }
        return false;
    }
/*    int numOfPegs(Node *node){
        int size = dynamic_cast<NodePegs *>(node)->size;
        int Pegs = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size ; ++j) {
                if(dynamic_cast<NodePegs *>(node)->state[i][j] == '1')
                    Pegs++;
            }
        }
        return Pegs;
    }*/
};

#endif //ASG2_EXPLOREDSET_H
