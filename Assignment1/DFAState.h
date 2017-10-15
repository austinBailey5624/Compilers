/**
*   @file:          DFAState.h
*   @author:        AustinBailey
*   @date:          10/13/2017
*   @Class:         Compilers
*   @purpose:       Represents a DFA State
*/

#ifndef DFASTATE_H
#define DFASTATE_H

#include <map>
#include <vector>
#include <iostream>

class DFAState
{
    public:
        DFAState();
        DFAState(std::vector<int> NFAStates);
        ~DFAState();
        bool isFinal();
        std::vector<int> getNFAStates();
        std::map<char, DFAState*> getTransfers();

        void setNFAStates(std::vector<int> states);
        void setTransfers(std::map<char,DFAState*> transfers);


    private:
        bool m_isFinal;
        std::vector<int> m_NFAStates;
        std::map<char, DFAState*> m_transfers;
};

#endif
