/**
*   @file:      DFAState.cpp
*   @author:    Austin Bailey
*   @date:      10/3/2017
*   @Class:     Compilers
*   @purpose:   represent DFA states
*/

#include "DFAState.h"


DFAState::DFAState()
{

}

DFAState::DFAState(std::vector<int> NFAStates)
{
    m_NFAStates = NFAStates;
}

DFAState::~DFAState()
{

}

bool DFAState::isFinal()
{
    return m_isFinal;
}

std::vector<int> DFAState::getNFAStates()
{
    return m_NFAStates;
}

std::map<char, DFAState*> DFAState::getTransfers()
{
    return m_transfers;
}

void DFAState::setNFAStates(std::vector<int> states)
{
    m_NFAStates = states;
}

void DFAState::setTransfers(std::map<char, DFAState*> transfers)
{
    m_transfers = transfers;
}
