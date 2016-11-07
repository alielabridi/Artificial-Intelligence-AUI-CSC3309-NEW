//
// Created by Brandon on 11/4/2016.
//

#ifndef ASG2_MCPNODE_H
#define ASG2_MCPNODE_H

#include <iostream>
#include <vector>
#include <deque>
#include "Node.h"
using namespace std;

class NodeMCP : public Node {
public:
    /*  Represents the number of M & C NOT on the GOAL side of the river
        and what side the boat is on. state[2] = 1 means the boat is 
        on the wrong side. */
    vector<int> state;
    // More efficient with deque - order of 
    deque<vector<int> > listOfTravelOptions = initializeListOfTravelOptions();

    deque<vector<int>> initializeListOfTravelOptions(){
        deque<vector<int>> tempDeque;
        vector<int> temp1(3);
        vector<int> temp2(3);
        bool oddDivision = 0;
        int iterateTill = 0;

        
        // For each capacity of boat, starting at the given capacity and decreasing by one
        for (int i = problemSpecMCP[2]; i >= 1; i-- ){
                    //cout << "i = " << i << endl;
            oddDivision = i%2;
                    //cout << "oddDivision = " << oddDivision << ".......1 = Yes" << endl;
            // see if the boat capacity is odd
            if (oddDivision){
                // if so, add one to half that number
                iterateTill = i/2 + 1; 
            }
            else{
                iterateTill = i/2;
            }
                    //cout << "iterateTill = " << iterateTill << endl;

            // use the number generated in the division above for the limit of j
            // this keeps this boat capacity from intruding on the moves that will be generated 
            // by the next boat capacity
            for (int j = i; j >= iterateTill; j--){
                        // cout << "j = " << j << endl;
                        // cout << "i-j = " << i-j << endl;

                // if the two numbers are the same, only put that travel option in once
                if (j == i-j)
                {
                    temp1 = {j,i-j,1};
                    tempDeque.push_front(temp1);
                            // cout << "temp1: < ";
                            // for (int k = 0; k < temp1.size(); k++){
                                // cout << temp1[k] << " , ";
                            // }
                            // cout << " >" << endl;

                // if the two numbers are different, you need to make two travel options out of them
                }else{
                    temp1 = {j,i-j,1};
                    temp2 = {i-j,j,1};
                    tempDeque.push_front(temp1);
                    tempDeque.push_front(temp2);
                            // cout << "temp1: < ";
                            // for (int k = 0; k < temp1.size(); k++){
                            //     cout << temp1[k] << " , ";
                            // }
                            // cout << " >" << endl;
                            // cout << "temp2: < ";
                            // for (int k = 0; k < temp2.size(); k++){
                            //     cout << temp2[k] << " , ";
                            // }
                            // cout << " >" << endl;
                }
            }
        }

        // Need to make sure listOfTravelOptions has a size associated with it
        // Just filling it does not give it a size

                // for(int i = 0; i < listOfTravelOptions.size(); i++){
                //     cout << "listOfTravelOptions [" << i << "] : ";
                //     for (int j = 0; j < listOfTravelOptions[i].size(); j++)
                //         cout << listOfTravelOptions[i][j] << " , ";
                //     cout << endl;
                // }
                // cout << endl << endl;

        return tempDeque;
    }


    NodeMCP(){}

    NodeMCP(vector<int> state_ ):state(state_){
        HeuristicValue = numberOnStartSideHeuristic();
    }

    int stepCost(int move){
        return 1;
    }

    bool equals (Node* node){
            return (state == dynamic_cast<NodeMCP*>(node)->state);
    }

    void printState(){
        cout << "State: < ";
        for (int i = 0; i < state.size(); i++)
            cout << state[i] << ",";
        cout << ">" << endl;
    }

    bool goalStateTest (){  // link back to main
        for (int i = 0; i < 3; i++)
            if (state[i] != goalStateMCP[i])
                return false;
        return true;
    }

    int numberOnStartSideHeuristic() {
        int hCost = 0;
        for (int i = 0; i < state.size() - 1; i++){
            hCost += state[i];
        }

        // if boat on start side, the cost is less
        // cost will be around double the number of people on the start side
        if(state[2] == 1){
            hCost *= 2;
        } else {
            hCost *= 2;
            hCost++;
        }

        return hCost;
    }

    vector <Node* > successorFunction(){
        vector <Node* > successorSet;
        cout << "Created Successor Set" << endl;
        /*  Test which side boat (state[2]) is on
            then either add or subtract
            (<1,0,1>, <2,0,1>, <0,1,1>, <0,2,1>, and <1,1,1>)
            then test if it is a valid move
            if it is, add new node to successor set*/

        // Boat is on the goal side of the river
        if(state[2] == 0)
        {
            // Next states will be generated from vector addition
            // Move boat, n missionaries, and n cannibal to the non goal side of river
            
            for (int i = 0; i < listOfTravelOptions.size(); i++)
            {
                vector<int> temp = {0, 0, 0};
                // Vector addition - add a travel option to the current state
                // Attempt to move to the non goal side of the river
                for (int j = 0; j < state.size(); j++)
                    temp[j] = listOfTravelOptions[i][j] + state[j];
                
                // Check to see if the option was valid
                // Check to see if the option was in bounds
                if(temp[0] >= 0 && temp[0] <= problemSpecMCP[0] && temp[1] >= 0 && temp[1] <= problemSpecMCP[1] ){
                    // No missionaries on the Goal Side
                    if (temp[0] == problemSpecMCP[0]){
                        if(temp[0] >= temp[1]){
                            // Add temp to the list of successors
                            NodeMCP* newNode = new NodeMCP(temp);
                            newNode->prev = this;
                            successorSet.push_back(newNode);
                        }
                    }
                        // No missionaries on the initial side
                    else if (temp[0] == 0){
                        if(problemSpecMCP[0] - temp[0] >= problemSpecMCP[1] - temp[1]){
                            // Add temp to the list of successors
                            NodeMCP* newNode = new NodeMCP(temp);
                            newNode->prev = this;
                            successorSet.push_back(newNode);
                        }
                    }else {
                        // If #C do not outnumber #M on the Goal side AND the initial side
                        if ((temp[0] >= temp[1]) && (problemSpecMCP[0] - temp[0] >= problemSpecMCP[1] - temp[1])) {
                            // Add temp to the list of successors
                            NodeMCP *newNode = new NodeMCP(temp);
                            newNode->prev = this;
                            successorSet.push_back(newNode);
                        }
                    }
                }
            }
        }
        // Boat is on the NON-goal side of the river
        else if(state[2] == 1)
        {
            // Next states will be generated by vector subtraction
            for (int i = 0; i < listOfTravelOptions.size(); i++)
            {
                vector<int> temp = {0,0,0};
                // Vector subtraction - subtract a travel option from the current state
                // Attempt to move to the goal side of the river
                for (int j = 0; j < state.size(); j++)
                    temp[j] = state[j] - listOfTravelOptions.at(i).at(j);
                
                // Check to see if the option was in bounds
                if(temp[0] >= 0 && temp[0] <= problemSpecMCP[0] && temp[1] >= 0 && temp[1] <= problemSpecMCP[1]){
                    // No missionaries on the Goal Side
                    if (temp[0] == 3){
                        if(temp[0] >= temp[1]){
                            // Add temp to the list of successors
                            NodeMCP* newNode = new NodeMCP(temp);
                            newNode->prev = this;
                            successorSet.push_back(newNode);
                        }
                    }
                        // No missionaries on the initial side
                    else if (temp[0] == 0){
                        if(problemSpecMCP[0] - temp[0] >= problemSpecMCP[1] - temp[1]){
                            // Add temp to the list of successors
                            NodeMCP* newNode = new NodeMCP(temp);
                            newNode->prev = this;
                            successorSet.push_back(newNode);
                        }
                    }else {
                        // If #C do not outnumber #M on the Goal side AND the initial side
                        if ((temp[0] >= temp[1]) && (problemSpecMCP[0] - temp[0] >= problemSpecMCP[1] - temp[1])) {
                            // Add temp to the list of successors
                            NodeMCP *newNode = new NodeMCP(temp);
                            newNode->prev = this;
                            successorSet.push_back(newNode);
                        }
                    }
                }
            }
        }
        return successorSet;

    }
};

#endif // ASG2_MCPNODE_H
