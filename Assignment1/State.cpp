/**
*   @file:          Main.cpp
*   @author:        Austin Bailey
*   @date:          10/3/2017
*   @Class:         Compilers
*   @purpose:       Preforms an NFA to DFA conversion
*/
#include "State.h"
#include <iostream>


State::State()
{

}

void State::clear()
{
    m_epsilonClosure.clear();
    m_transfers.clear();
}

State::~State()
{
    State::clear();
}



std::vector<int> State::getEpsilonClosure()
{
    return m_epsilonClosure;
}

void State::setEpsilonClosure(std::vector<int> epsilonClosure)
{
    m_epsilonClosure=epsilonClosure;
    return;
}

void State::addStates(std::vector<int> transfers)
{
    m_transfers.push_back(transfers);
}

std::vector<int> State::getStateTransfer(int whichInput)
{
    if((unsigned int)whichInput>m_transfers.size()||whichInput<0)
    {
        std::cout << "Asked for index outside of bounds of vector\n";
        std::cout << "Vector's size: " << m_transfers.size();
        std::cout << "Index attempted: " << whichInput <<"\n";
        std::vector<int> empty;
        return empty;
    }
    else
    {
        return m_transfers.at(whichInput);
    }
}
