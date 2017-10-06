/**
*   @file:          Main.cpp
*   @author:        Austin Bailey
*   @date:          10/3/2017
*   @Class:         Compilers
*   @purpose:       Preforms an NFA to DFA conversion
*/
//./assignment1 < exampleInput.txt
#include <iostream>
#include <string>
#include <vector>
#include "State.h"

int main()
{
    int initialState;
    std::vector<int> finalStates;
    std::string read;
//    std::cout << "Hello world\n";
    std::cin >> read;
    std::cout << read << "\n";
    if(read.compare("Initial") != 0)
    {
        std::cout << "Invalid Input, input must begin 'Initial State:'\n";
        std::cout << "exiting\n";
        return 0;
    }
    std::cin >> read;
    std::cout << read << "\n";
    if(read.compare("State:") != 0)
    {
        std::cout << "Invalid Input, input must begin 'Initial State'\n";
        std::cout << "exiting\n";
    }

    //initialState read logic
    std::cin >> read;
    std::cout << read << ":" << read.length() << "\n";
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

    std::cout << "read pre erase:  " << read <<" ;size: " << read.length() << "\n";

    read.erase(read.begin(), read.begin()+1);//tears off beggining curly
    read.erase(read.end()-1, read.end());//tears off end curly
    std::cout << "read post erase: " << read << "\n";
    //std::cout << "charat0: " << read.at(0) << "\n";
    return 0;
}
