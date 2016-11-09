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
struct UCSComparator{
public:
    bool operator()(const Node* lhs, const Node* rhs) const{
        /*min heap*/
        return (lhs->pathcost > rhs->pathcost);
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
    void BFS(Node* initialState,int n_nodes_to_expand_to_ask) {

        if (initialState->goalStateTest()) {
            cout << "The number of nodes expanded is 0 and the # of loops detected is 0 and the pathcost is 0" << endl;
            cout << "A solution found has been found" << endl;
            initialState->printSolution();
            return;
        }


        queue <Node*> frontier;
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

            node = frontier.front();
            cout << endl << "the new expanded node # " << ++n_expension << endl;
            node->printState();
            cout << "the new expanded node-- END" << endl;
            if(node->goalStateTest()){
                cout << "A solution found has been found" << endl;
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << " and the pathcost to solution " << node->pathcost << endl;
                node->printSolution();
                return;
            }

            frontier.pop();
            exploredSet.add(node);

            vector <Node*> successors(node->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expension << endl;
            for (Node* successor: successors) {
                //check that the sucessor is not in the frontier and explored set*//*
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
        cout << "failure to find the solution"<< endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
        return;
    }

    void UCS(Node* initialState,int n_nodes_to_expand_to_ask) {

        if (initialState->goalStateTest()) {
            cout << "The number of nodes expanded is 0 and the # of loops detected is 0 and pathcost is 0" << endl;
            cout << "A solution found has been found" << endl;
            initialState->printSolution();
            return;
        }


        priority_queue<Node*, vector<Node*>,UCSComparator> frontier;
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
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected  << "and the pathcost to solution " << node->pathcost << endl;
                node->printSolution();
                return;
            }

            frontier.pop();
            exploredSet.add(node);

            vector <Node*> successors(node->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expension << endl;
            for (Node* successor: successors) {
                //check that the sucessor is not in the frontier and explored set*//*
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
        cout << "failure to find the solution"<< endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
        return;
    }

    void DFS(Node* initialState,int n_nodes_to_expand_to_ask) {
        if (initialState->goalStateTest()) {
            cout << "The number of nodes expanded is 0 and the # of loops detected is 0 and the pathcost is 0" << endl;
            cout << "A solution found has been found" << endl;
            initialState->printSolution();
            return;
        }
        stack <Node*> frontier;
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
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << " and the pathcost to solution " << node->pathcost << endl;
                node->printSolution();
                return;
            }
            frontier.pop();
            exploredSet.add(node);
            vector <Node*> successors(node->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expension << endl;
            for (Node* successor: successors) {
                /*check that the sucessor is not in the frontier and explored set*/
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
        cout << "failure to find the solution"<< endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
    
        return;
    }




void Greedy(Node* initialState,int n_nodes_to_expand_to_ask) {

    if (initialState->goalStateTest()) {
        cout << "The number of nodes expanded is 0 and the # of loops detected is 0 and the pathcost is 0" << endl;
        cout << "A solution found has been found" << endl;
        initialState->printSolution();
        return;
    }

    priority_queue<Node*, vector<Node*>,GreedyComparator> frontier;
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
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << " and the pathcost to solution " << node->pathcost << endl;
                node->printSolution();
                return;                
            }

            frontier.pop();
            exploredSet.add(node);

            vector <Node*> successors(node->successorFunction());
            cout << endl << "the children of the node expanded # "<< n_expension << endl;
            cout << "the children of the expended node( size: "<< successors.size() << endl;
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
        cout << "failure to find the solution" << endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;

            return;
    }


    void AStar(Node* initialState, int n_nodes_to_expand_to_ask) {
        if (initialState->goalStateTest()) {
            cout << "The number of nodes expanded is 0 and the # of loops detected is 0 and the pathcost is 0" << endl;
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
                cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << " and the pathcost to solution " << node->pathcost << endl;
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
        cout << "failure to find the solution" << endl;
        cout << "The number of nodes expanded is " << n_expension << "and the # of loops detected is " << loops_detected << endl;
        return;
    }


};

#endif //ASG2_SEARCHENGINE_H
