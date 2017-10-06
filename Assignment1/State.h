/**
*   @file:          State.h
*   @author:        Austin Bailey
*   @date:          10/3/2017
*   @Class:         Compilers
*   @purpose:       Represents a NFA State
*/

#ifndef STATE_H
#define STATE_H

#include <map>

class State
{
    public:
        State();

        /*
        *   For a given identifier (of a state),
        *   return a map of all the states it can access
        */
//        std::map<int,bool> getTransfers(int identifier);

        std::map<int,bool> getEpsilonClosure();
    private:
        int identifier;
        std::map<char, int> m_stateTransfers;
        std::map<int,bool> m_epsilonClosure;
};
#endif
