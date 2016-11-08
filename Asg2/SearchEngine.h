//
// Created by Ali on 11/2/2016.
//

#ifndef ASG2_SEARCHENGINE_H
#define ASG2_SEARCHENGINE_H

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "ExploredSet.h"
#include "Node.h"

struct GreedyComparator{
public:
    bool operator()(const Node* lhs, const Node* rhs) const{
        /*min heap*/
        return (lhs->HeuristicValue > rhs->HeuristicValue);
    }
};
struct AStarComparator{
public:
    bool operator()(const Node* lhs, const Node* rhs) const{
        /*min heap*/
        return ((lhs->HeuristicValue+lhs->pathcost) > (rhs->HeuristicValue+rhs->pathcost));
    }
};


class SearchEngine {
public:
    /*void BFS(Node* initialState) {

        if (initialState->goalStateTest()) {
            cout << "solution found";
            return;
        }


        queue <Node*> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSetBFS;*//*to be later transofrmed to a hashtable*//*
        int n_expension = 0;
        while (!frontier.empty()) {


            node = frontier.front();
            *//*cout << endl << "THE NEW EXPANDED NODE " << ++n_expension << endl;
            node->printState();
            cout << "THE NEW EXPANDED NODE -- END" << endl;*//*
            if(node->goalStateTest()){
                cout << "solution found"<< n_expension << endl;
                return;
            }
            cout << "it went here1 " << endl;

            frontier.pop();
            exploredSetBFS.add(node);
            cout << "it went here2" << endl;

            vector <Node*> successors(node->successorFunction());
            //cout << endl << "THE CHILDREN NODE" << endl;
            for (Node* successor: successors) {
                *//*check that the sucessor is not in the frontier and explored set*//*
                if(!exploredSetBFS.exists(successor)){
                    frontier.push(successor);
                    //successor->printState();
                }
                cout << "it went here3 " << endl;
            }
            //cout << "THE CHILDREN NODE -- END" << endl;


        }
        cout << "failure to find the solution"<< n_expension << endl;
        return;
    }*/


    void DFS(Node* initialState) {
        if (initialState->goalStateTest()) {
            cout << "solution found";
            return;
        }
        stack <Node*> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSetBFS;/*to be later transofrmed to a hashtable*/
        int n_expension = 0;
        while (!frontier.empty()) {
            node = frontier.top();
            cout << endl << "THE NEW EXPANDED NODE " << ++n_expension << endl;
            node->printState();
            cout << "THE NEW EXPANDED NODE -- END" << endl;

            if(node->goalStateTest()){
                cout << "solution found" << endl;
                goto solution;
                return;
            }
            frontier.pop();
            exploredSetBFS.add(node);
            vector <Node*> successors(node->successorFunction());
            cout << "the children of the expended node( size: "<< successors.size() << endl;

            for (Node* successor: successors) {
                /*check that the sucessor is not in the frontier and explored set*/

                if(!exploredSetBFS.exists(successor)){
                    frontier.push(successor);
                    successor->printState();
                }

            }

            cout << "end of the children of the expanded node" << endl;

        }
        cout << "failure to find the solution" << endl;
        solution:
        int steps = 0;
        cout << "path cost to reach solution " << node->pathcost << endl;
        while(node != NULL){
            node->printState();
            node = node->prev;
            steps++;
        }
        cout << "the steps are " << steps << endl;
        return;
    }




    void Greedy(Node* initialState) {

    if (initialState->goalStateTest()) {
        cout << "solution found";
        return;
    }

    priority_queue<Node*, vector<Node*>,GreedyComparator> frontier;
    Node* node;
    frontier.push(initialState);
    ExploredSet exploredSetBFS;
        int n_expension = 0;
        while (!frontier.empty()) {


            node = frontier.top();
            cout << endl << "THE NEW EXPANDED NODE " << ++n_expension << endl;
            node->printState();
            cout << "THE NEW EXPANDED NODE -- END" << endl;
            if(node->goalStateTest()){
                cout << "solution found"<< n_expension << endl;
                return;
            }

            frontier.pop();
            exploredSetBFS.add(node);

            vector <Node*> successors(node->successorFunction());
            //cout << endl << "THE CHILDREN NODE" << endl;
            cout << "the children of the expended node( size: "<< successors.size() << endl;
            for (Node* successor: successors) {
                //check that the sucessor is not in the frontier and explored set
                if(!exploredSetBFS.exists(successor)){
                    frontier.push(successor);
                    cout << "the value of the heuristic is " << successor->HeuristicValue <<endl;
                    successor->printState();
                }
            }
            cout << "end of the children of the expanded node" << endl;
            //cout << "THE CHILDREN NODE -- END" << endl;


        }
        cout << "failure to find the solution"<< n_expension << endl;
        return;
    }


    void AStar(Node* initialState, int n_nodes_to_expand_to_ask) {
        if (initialState->goalStateTest()) {
            cout << "The number of nodes expanded is 0 and the # of loops detected is 0" << endl;
            cout << "A solution found has been found" << endl;
            initialState->printSolution();
            return;
        }
        priority_queue<Node*, vector<Node*>,AStarComparator> frontier;
        Node* node;
        frontier.push(initialState);
        ExploredSet exploredSet;
        int n_expension = 0;
        int loops_detected = 0;
        while (!frontier.empty()) {
            if(n_nodes_to_expand_to_ask != 0 && n_expension != 0 && n_expension % n_nodes_to_expand_to_ask == 0){
                int i;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
                cout << "Do you want to continue the search? if yes enter 1 otherwise 0" << endl;
                cin >> i;
                if(i == 0){
                    cout << "The search has ended!" << endl;
                    return;
                }
            }
            node = frontier.top();
            cout << endl << "the new expanded node # " << ++n_expension << endl;
            node->printState();
            cout << "the new expanded node-- END" << endl;
            if(node->goalStateTest()){
                cout << "A solution found has been found" << endl;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
                node->printSolution();
                return;
            }
            frontier.pop();
            exploredSet.add(node);

            vector <Node*> successors(node->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expension << endl;
            for (Node* successor: successors) {
                //check that the sucessor is not in the frontier and explored set
                if(!exploredSet.exists(successor)){
                    cout << "the following node is NOT in the closed list and thus will be expanded" << endl;
                    frontier.push(successor);
                    successor->printState();
                }
                else{
                    cout << "the following node is in the closed list and thus will NOT be expanded" << endl;
                    successor->printState();
                    loops_detected++;
                }
            }
            cout << "the children of the node expanded - END" << endl;
        }
        cout << "failure to find the solution"<< n_expension << endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
        return;
    }


};

#endif //ASG2_SEARCHENGINE_H
