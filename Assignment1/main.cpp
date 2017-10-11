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
#include "State.h"


std::vector<int> epsilonClosure(int currentState, std::vector<State*> states, std::map<int,bool> visited)
{
    std::vector<int> result;

    return result;
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
/*
std::vector<int> epsilonClosureHelper(int currentState, std::vector<State*> States, std::map<int,bool> visited)
{
    std::vector<int> result;
    if(visited[currentState])//if we've already visited this state
    {
        return result;
    }
    //note: if the map looksup something that isnt there, it returns false
}

std::vector<int> computeFullEpsilonClosure(int whichState, std::vector<State*> States)
{
    std::vector<int> result;
    if(States.at(whichState)->getEpsilonClosure().size()==0)
    {
        return result;
    }

    std::map<int, bool> visited;//records the states that we have visited
    visited[whichState] = true;
//    std::vector<int> tempState;
    State* tempState;
    for(int i=0; i< States.at(whichState)->getEpsilonClosure().size(); i++)
    {
        //temp state is the ith state in the epsilon Closure
        tempState = States.at(States.at(whichState)->getEpsilonClosure().at(i));
//        result.insert(result.end(), temp.begin(), temp.end());
    }

    std::sort(result.begin(), result.end());
//    result = std::unique(result.begin(), result.end());
    return result;
}
*/

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
            std::cout << intVec.at(i);
        }
        else
        {
            std::cout << intVec.at(i) << ", ";
        }
    }
    std::cout << "\n";
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
    }

    //initialState read logic
    std::cin >> read;
//    std::cout << read << ":" << read.length() << "\n";
    //erase block trims curly braces off
    read.erase(read.begin(), read.begin()+1);
    read.erase(read.end()-1, read.end());
    //std::cout << "Pretty read: " << read << "\n";
    initialState = std::stoi(read);
    std::cout << "InitialState: " << initialState << "\n";

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
    std::cout << "finalStates: ";
    printIntVector(finalStates);

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

    std::cout << "Number of States:" << numOfNFAStates << "\n";

    std::vector<char> stateInputs;
    std::cin >> read;
    if(read.compare("State")!=0)
    {
        std::cout << "Invalid input, expected fourth line to begin 'State'\n";
        std::cout << "Exiting\n";
    }
    int numInputs = 0;
    std::cin >> read;
    while(read.compare("E")!=0)//continues until the Epsilon closure is found
    {
        stateInputs.push_back(read.at(0));
        std::cin >> read;
        numInputs++;
    }
    std::cout << "StateInputs: ";
    printCharVector(stateInputs);
    std::cout << "num Of Inputs: " << numInputs << "\n";
    //std::cout << "charat0: " << read.at(0) << "\n";
    std::vector<State*> NFAStates;

    State* temp = new State();

    std::vector<int> emptyVec;
    emptyVec.push_back(0);
//if a vector holding states is 0 that represents that it holds no states

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
            std::cout << "state:" << (j+1) << " input:" << stateInputs.at(i) << " transfers: ";
            if(temp->getStateTransfer(i).at(0)==0)
            {
                std::cout << "none\n";
            }
            else
            {
                printIntVector(temp->getStateTransfer(i));
            }
//            std::cout << "\n";
        }

        std::cin >> read;//reads the epsilonClosure
//        std::cout << "state:" << (j+1) << " epsilonClosure:" << read << "\n";
        if(read.length()!=2)
        {
            read.erase(read.begin(), read.begin()+1);//tears off beggining curly
            read.erase(read.end()-1, read.end());//tears off end curly
//            std::cout << "epsilonClosure read: ";
//            printIntVector(stringToVec(read));
//            std::cout << "\n";
            temp->setEpsilonClosure(stringToVec(read));
        }
        else//no epsilon Closure
        {
            temp->setEpsilonClosure(emptyVec);
        }
        std::cout << "state:" << (j+1) << " epsilonClosure:    ";
        if(temp->getEpsilonClosure().at(0)==0)
        {
            std::cout << "empty\n";
        }
        else
        {
            printIntVector(temp->getEpsilonClosure());
        }
        std::cout << "\n";
        NFAStates.push_back(temp);
        temp->clear();
    }




    bool lcv = true;
    while(lcv)
    {

    }

    return 0;
}
