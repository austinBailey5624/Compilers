/**
*   @file:          Main.cpp
*   @author:        Austin Bailey
*   @date:          10/3/2017
*   @Class:         Compilers
*   @purpose:       Preforms an NFA to DFA conversion
*/
#include "State.h"


State::State()
{

}

State::~State()
{

}

std::vector<int> State::getEpsilonClosure()
{
    return m_epsilonClosure;
}

void State::addStates(char index, std::vector<int> transfers)
{
    m_transfers.at(index) = transfers;
}
