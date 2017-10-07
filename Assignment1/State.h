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
#include <vector>

class State
{
    public:
        State();
        ~State();

        /*
        *   For a given identifier (of a state),
        *   return a map of all the states it can access
        */
//        std::map<int,bool> getTransfers(int identifier);

        std::vector<int> getEpsilonClosure();
        void addStates(char index, std::vector<int> transfers);

    private:
        int m_id;
        std::vector<std::vector<int>> m_transfers;
        std::vector<int> m_epsilonClosure;

};
#endif
