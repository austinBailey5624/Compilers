/**
*   @file:          Main.cpp
*   @author:        Austin Bailey
*   @date:          10/3/2017
*   @Class:         Compilers
*   @purpose:       Preforms an NFA to DFA conversion
*/
//./assignment1 < exampleInput.txt
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include "State.h"
#include "DFAState.h"



void printIntVectorBraces(std::vector<int> intvec)
{
    if(intvec.empty())
    {
        std::cout << "Vector is empty\n";
        return;
    }
    std::cout << "{";
    for(unsigned int i=0; i<intvec.size(); i++)
    {
        if( (i+1)== intvec.size())
        {
            std::cout << intvec.at(i);        }
        else
        {
            std::cout << intvec.at(i) << ", ";
        }
        //std::cout << "here?";
    }
    //std::cout << "not here?";
    std::cout << "}";
    return;
}

void printIntVector(std::vector<int> intVec)
{
    if(intVec.empty())
    {
        std::cout << "Vector is empty\n";
        return;
    }
    for(unsigned int i=0; i<intVec.size(); i++)
    {
        if( (i+1)== intVec.size())
        {
            std::cout << intVec.at(i);        }
        else
        {
            std::cout << intVec.at(i) << ", ";
        }
        //std::cout << "here?";
    }
    //std::cout << "not here?";
    std::cout << "\n";
    return;
}

int stateAlreadyUsed(std::vector<int> states, std::vector<DFAState*> DFAvec)
{
    for(unsigned int i = 1; i < DFAvec.size(); i++)
    {
        if(DFAvec.at(i)->getNFAStates() == states)
        {
            return i;
        }
    }
    return -1;
}

/*
*   This function is meant to combine sorted vectors while maintaining the
*   uniqueness of the result vector. That is, all of the elements in the
*   result vector will be unique
*/
std::vector<int> combineIntVectors(std::vector<int> first, std::vector<int> second)
{
    std::vector<int> result;
    while(!second.empty()||!first.empty())
    {
        if(first.empty())
        {
            result.insert(result.end(),second.begin(),second.end());
            return result;
        }
        if(second.empty())
        {
            result.insert(result.end(),first.begin(),first.end());
            return result;
        }
        if(first.front()==second.front())
        {
            result.push_back(first.front());
            first.erase(first.begin());
            second.erase(second.begin());
        }
        else if(first.front()<second.front())
        {
            result.push_back(first.front());
            first.erase(first.begin());
        }
        else
        {
            result.push_back(second.front());
            second.erase(second.begin());
        }
    }
    return result;
}

std::vector<int> fullEpsilonClosure(int currentState, std::vector<State*> states, std::map<int,bool> visited)
{
    bool debug = false;
    std::vector<int> result;
    if(visited[currentState])
    {
        if(debug)
        {
            std::cout << "State: " <<currentState << "Already Visited.  Returning empty";
        }
        return result;
    }
    visited[currentState]=true;
    if(debug)
    {
        std::cout << "State: " << currentState << " Not vistied previously\n";
        std::cout << "partial e closure of state " << currentState << " is : ";//currentState+1 since zero indexed
        printIntVector(states.at(currentState)->getEpsilonClosure());
        std::cout << "\n";
    }
    if(states.at(currentState)->getEpsilonClosure().empty())
    {
        return result;
    }
    //if there's only one item in the immediate epsilon closure
    if(states.at(currentState)->getEpsilonClosure().size()==1)
    {
        //if that item is the zero placeholder,
        result.push_back((currentState));//+1 for zero indexing
        if(debug)
        {
            std::cout << "returning a size=1 epsilon closure\n";
        }
        return result;

    }
    result = states.at(currentState)->getEpsilonClosure();
    if(debug)
    {
        std::cout << "computing the EpsilonClosure for all states in "<<    currentState+1 <<"'s epsilon Closure\n";
    }
//    std::cout << "states.at(currentState)->getEpsilonClosure.Size(): " << states.at(currentState)->getEpsilonClosure().size() << " \n";
    for(unsigned int i=0; i<states.at(currentState)->getEpsilonClosure().size(); i++)
    {
        if(debug)
        {
            std::cout << "states.at(currentState)eclosure at i="<<i << " is:"   << states.at(currentState)->getEpsilonClosure().at(i) << std::endl;
        }
        result = combineIntVectors(result, fullEpsilonClosure(states.at(currentState)->getEpsilonClosure().at(i),states,visited));
        if(debug)
        {
            std::cout << "Current Partial Result = ";
            printIntVector(result);
            std::cout << std::endl;
        }
    }
    if(debug)
    {
        std::cout << "Final Result = ";
        printIntVector(result);
        std::cout << "\n";
    }
//    std::cout << "do we get here?" << std::flush;
    return result;
}

std::vector<int> sortedInsertIntoVector(int element, std::vector<int> myVector)
{
    if(myVector.empty())
    {
        myVector.push_back(element);
        return myVector;
    }
    if(element<myVector.front())//if my element belongs in the front
    {
        std::vector<int> result;
        result.push_back(element);
        result.insert(result.end(),myVector.begin(),myVector.end());
        return result;
    }
    if(element > myVector.back())//if my element belongs at the end
    {
        myVector.push_back(element);
        return myVector;
    }
    for(unsigned int i=0; i<myVector.size()-1; i++)
    {
        if(element>myVector.at(i)&&element<myVector.at(i+1))
        {
            std::vector<int>::iterator myiterator = myVector.begin();
            myVector.insert(myiterator+i+1,element);
            return myVector;
        }
    }
    return myVector;
}

bool elementIsInside(int element, std::vector<int> container)
{
    for(unsigned int i=0; i<container.size(); i++)
    {
        if(container.at(i)==element)
        {
            return true;
        }
    }
    return false;
}

void printCharVector(std::vector<char> charVec)
{
    if(charVec.empty())
    {
        std::cout << "Vector is empty\n";
        return;
    }
    for(unsigned int i=0; i<charVec.size(); i++)
    {
        if((i+1) == charVec.size())
        {
            std::cout << charVec.at(1);
        }
        else
        {
            std::cout << charVec.at(i) << ",";
        }
    }
    std::cout << "\n";
}

std::vector<int> stringToVec(std::string str)
{
    std::vector<int> result;
    int head = 0;
//    std::cout << "got here 2\n";
    for(unsigned int i=0; i<str.length(); i++)
    {
        if(i+1==str.length())
        {
//            std::cout << "substr(head,i+1-head): " << str.substr(head,(i+1-head)) <<"\n";
            result.push_back(std::stoi(str.substr(head,(i+1-head))));
            return result;
        }
        if(str.at(i)==',')
        {
            result.push_back(std::stoi(str.substr(head,(i+1-head))));
            head = i+1;
        }
    }
    return result;
}

int main()
{
    bool debug = false;

    int initialState;
    std::string read;
//    std::cout << "Hello world\n";
    std::cin >> read;
//    std::cout << read << "\n";
    if(read.compare("Initial") != 0)
    {
        std::cout << "Invalid Input, input must begin 'Initial State:'\n";
        std::cout << "exiting\n";
        return 0;
    }
    std::cin >> read;
//    std::cout << read << "\n";
    if(read.compare("State:") != 0)
    {
        std::cout << "Invalid Input, input must begin 'Initial State'\n";
        std::cout << "exiting\n";
        return 0;
    }

    //initialState read logic
    std::cin >> read;
//    std::cout << read << ":" << read.length() << "\n";
    //erase block trims curly braces off
    read.erase(read.begin(), read.begin()+1);
    read.erase(read.end()-1, read.end());
    //std::cout << "Pretty read: " << read << "\n";
    initialState = std::stoi(read);
    if(debug)
    {
        std::cout << "InitialState: " << initialState << "\n";
    }
    //finalStates read logic
    std::cin >> read;
    if(read.compare("Final") != 0)
    {
        std::cout << "Invalid input, input must read 'Final States:' on second line\n";
        std::cout << "Exiting\n";
        return 0;
    }
    std::cin >> read;
    if(read.compare("States:")!=0)
    {
        std::cout << "Invalid input, input must read 'Final States:' on second line\n";
        std::cout << "Exiting\n";
        return 0;
    }

    std::cin >> read;

//    std::cout << "read pre erase:  " << read <<" ;size: " << read.length() << "\n";
    std::vector<int> finalStates;
    read.erase(read.begin(), read.begin()+1);//tears off beggining curly
    read.erase(read.end()-1, read.end());//tears off end curly
//    std::cout << "read post erase: " << read << "\n";
    std::string tempString;
    int head= 0;//represents the last read integer in the string
    for(unsigned int i=0; i< read.length(); i++)
    {
        if(i+1==read.length())
        {
            tempString = read.substr(head,(i+1-head));
//            std::cout << "read.substr(head,i): " <<tempString << "\n";
            finalStates.push_back(std::stoi(tempString));
        }
        if(read.at(i)==',')
        {
//            std::cout << "head indexed: " << head << " Head Value: " << read.at(head) << "\n";
//            std::cout << "i index:      " << i    << "  i value:   " << read.at(i) << "\n";
            tempString = read.substr(head,i-head);
            finalStates.push_back(std::stoi(tempString));
//            std::cout << "read.substr(head,i): " <<tempString <<"\n";
            head = i+1;
        }
    }
    if(finalStates.empty())
    {
        std::cout << "Invalid input, there must be at least one final state\n";
        std::cout << "exiting\n";
        return 0;
    }
    if(debug)
    {
        std::cout << "finalStates: ";
        printIntVector(finalStates);
    }
    std::cin >> read;
    if(read.compare("Total")!=0)
    {
        std::cout << "Invalid input, input must read 'Total States:' on Third line\n";
        std::cout << "Exiting\n";
        return 0;
    }

    std::cin >> read;
    if(read.compare("States:")!=0)
    {
        std::cout << "Invalid input, input must read 'Total States:' on third line\n";
        std::cout << "Exiting\n";
        return 0;
    }
    int numOfNFAStates;
    try
    {
        std::cin >> numOfNFAStates;
    }
    catch(int e)
    {
        std::cout << "Invalid input, expected an integer on thrid line following 'Total States'\n";
        std::cout << "Exiting\n";
        return 0;
    }
    if(debug)
    {
        std::cout << "Number of States:" << numOfNFAStates << "\n";
    }
    std::vector<char> stateInputs;
    std::cin >> read;
    if(read.compare("State")!=0)
    {
        std::cout << "Invalid input, expected fourth line to begin 'State'\n";
        std::cout << "Exiting\n";
        return 0;
    }
    int numInputs = 0;
    std::cin >> read;
    while(read.compare("E")!=0)//continues until the Epsilon closure is found
    {
        stateInputs.push_back(read.at(0));
        std::cin >> read;
        numInputs++;
    }
    if(debug)
    {
        std::cout << "StateInputs: ";
        printCharVector(stateInputs);
        std::cout << "num Of Inputs: " << numInputs << "\n";
    }
    //std::cout << "charat0: " << read.at(0) << "\n";
    std::vector<State*> NFAStates;
    State* temp = new State();
    State* blank = new State();
    NFAStates.push_back(blank);//to go one-indexed
    std::vector<int> tempVec;
    std::vector<int> emptyVec;
    emptyVec.push_back(-1);
//if a vector holding states is -1 that represents that it holds no states

    for(int j=0; j<numOfNFAStates; j++)
    {
        std::cin >> read;
        if(read.compare(std::to_string(j+1))!=0)
        {
            std::cout << "Error, bad column title compare\n";
            return 0;
        }
        else
        {
//            std::cout << "Compare Success\n";
        }
        //reads the state transitions based on inputs
        for(int i=0; i<numInputs; i++)
        {
    //        std::cout << "got here\n";
            std::cin >> read;
//            std::cout << "read i=" << i << " j=" << j << " :" << read <<"\n";
    //        std::cout << "did not get here\n";

            if(read.length()!=2)
            {
                read.erase(read.begin(), read.begin()+1);//tears off beggining curly
                read.erase(read.end()-1, read.end());//tears off end curly
//                std::cout << "read(" << i <<"):" << read << "\n";
                temp->addStates(stringToVec(read));
    //            std::cout <<"dumpd core yet?\n";
//                printIntVector(stringToVec(read));
            }
            else
            {
                temp->addStates(emptyVec);
            }
            if(debug)
            {
                std::cout << "state:" << (j+1) << " input:" << stateInputs.at(i) << " transfers: ";
                if(temp->getStateTransfer(i).at(0)==0)
                {
                    std::cout << "none\n";
                }
                else
                {
                    if(temp->getStateTransfer(i)==emptyVec)
                    {
                        std::cout << "empty\n";
                    }
                    else
                    {
                        printIntVector(temp->getStateTransfer(i));
                    }
                }
            }
        }

        std::cin >> read;//reads the epsilonClosure
        if(read.length()!=2)
        {
            read.erase(read.begin(), read.begin()+1);//tears off beggining curly
            read.erase(read.end()-1, read.end());//tears off end curly

            tempVec.push_back(j+1);
            temp->setEpsilonClosure(combineIntVectors(stringToVec(read),tempVec));

        }
        else//no epsilon Closure
        {
            tempVec.push_back(j+1);
            temp->setEpsilonClosure(tempVec);
        }
        if(debug)
        {
            std::cout << "state:" << (j+1) << " epsilonTransitions:    ";
            printIntVector(temp->getEpsilonClosure());
        }

        if(debug)
        {
            std::cout << "\n";
        }
        NFAStates.push_back(temp);
        temp = new State();
        tempVec.clear();
    }
    //end parsing logic
    std::map<int, bool> visitedLookup;
    if(debug)
    {
        std::cout << "Starting fullEpsilonClosure at initialState: " <<     initialState << "\n";
    }
    std::vector<int> eclosure;

    //std::map<int, DFAState*> stateHolder;
    std::vector<DFAState*> DFAvec;
    std::queue<DFAState*> stateQueue;
    DFAState* next;
    std::vector<int> transitionHolder;
    eclosure = fullEpsilonClosure(initialState, NFAStates, visitedLookup);//-1 to go from one index to zero index
    std::cout << "E-closure(IO) = ";
//    std::cout << "We got here right?\n";
    printIntVectorBraces(eclosure);
//    std::cout << "But not here?";
    std::cout << " = 1\n\n";
//to fix off by one, now 1-index vector
    DFAState* current=new DFAState();
    DFAState* current2;
    current->setNFAStates(eclosure);
    DFAvec.push_back(current);
    stateQueue.emplace(current);
    std::map<char,DFAState*>* tempTransfers;
    std::vector<int> result;
    std::vector<int> epsilonClosureSummation;
    int lastStateInQueue=1;
    int whichState = 1;
    //debug = true;
    while(!stateQueue.empty())
    {
        std::cout << "\nMark " << whichState << "\n";
        current = new DFAState();
        if(debug)
        {
            std::cout << "imax = " << numInputs << "\n";
        }
        for(int i=0; i<numInputs; i++)
        {
            if(debug)
            {
                std::cout << "i =" << i <<"\n";

                std::cout << "jmax = " << stateQueue.front()->getNFAStates().size() << "\n";
            }

            result.clear();
            //this loop calculates the result
            for(unsigned int j=0; j < stateQueue.front()->getNFAStates().size();j++)
            {
                if(debug)
                {
                    std::cout << "j = " << j <<"\n";
                }
                if(NFAStates.at( stateQueue.front()->getNFAStates().at(j))->getStateTransfer(i).at(0)==-1)
                {
                    if(debug)
                    {
                        std::cout << "Combined Empty\n";
                    }
                }
                else
                {
                    if(debug)
                    {
                        std::cout << "Combined result: ";
                        printIntVectorBraces(result);
                        std::cout << "\nand front->getNFAStates.at(" << j <<"): ";
                        printIntVectorBraces(NFAStates.at(stateQueue.front()->getNFAStates().at(j))->getStateTransfer(i));
                        std::cout << "\n";
                    }
                    result = combineIntVectors(result,NFAStates.at( stateQueue.front()->getNFAStates().at(j))->getStateTransfer(i));
                }
                if(debug)
                {
                    std::cout << "result = ";
                    printIntVectorBraces(result);
                    std::cout << "\n";
                }
            }
            if(debug)
            {
                std::cout << "Exited J loop\n";
                std::cout << "final result= ";
                printIntVectorBraces(result);
            }
            //if result is empty
            if(result.empty()||result.at(0)==-1)
            {
                if(debug)
                {
                    std::cout<<"triggered empty if\n";
                }//do nothing
            }
            else //if result is a new DFA, make it and add it to the Queue/Vector
            {
                printIntVectorBraces((stateQueue.front()->getNFAStates()));
                std::cout << " --" << stateInputs[i] << "--> ";
                printIntVectorBraces(result);
                current2 = new DFAState();
                //combines the epsilon closures for every NFA state in result
                //debug = true;

                if(result.size()==1)
                {
                    visitedLookup.clear();
                    epsilonClosureSummation = fullEpsilonClosure(result.at(0),NFAStates,visitedLookup);
                }
                else
                {
                    for(unsigned int k = 0; k<result.size(); k++)
                    {
                        //TODO: add full epsilonClosure;
                        if(debug)
                        {
                            std::cout << "k: " << k << "\n";
                        }
                        visitedLookup.clear();
                        if(debug)
                        {
                            std::cout << "epsilon " << result[k] << " =";
                            printIntVector(NFAStates.at(result[k])->getEpsilonClosure());
                            std::cout << "\n";
                        }
                        combineIntVectors(epsilonClosureSummation, fullEpsilonClosure(result[k],NFAStates, visitedLookup));
                        //combineIntVectors(epsilonClosureSummation, NFAStates.at(result[k])->getEpsilonClosure());
                        if(debug)
                        {
                            std::cout << "union: ";
                            printIntVectorBraces(epsilonClosureSummation);
                            std::cout << "\n";
                        }
                    }
                }
                lastStateInQueue++;
                current2->setNFAStates(epsilonClosureSummation);
                std::cout << "\nE-closure";
                printIntVectorBraces(result);
                std::cout << " = ";
                printIntVectorBraces(epsilonClosureSummation);
                std::cout << " = " << lastStateInQueue << "\n";
                //stateQueue.push(current2);
                if(stateAlreadyUsed(current2->getNFAStates(),DFAvec)==-1)
                {
                    stateQueue.push(current2);
                    DFAvec.push_back(current2);
                }
            }

        }
        whichState++;
        stateQueue.pop();
    }

    return 0;
}
