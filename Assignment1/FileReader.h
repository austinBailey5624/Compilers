/**
*   @file:      FileReader.h
*   @author:    AustinBailey
*   @date:      10/6/2017
*   @class:     Compilers
*   @Purpose:   Read and convert the input file into a form that the
*               rest of the program can use
*/

#ifndef FILEREADER_H
#define FILEREADER_H

#include <map>
#include <string>

class FILEREADER_H
{
    public:
        FileReader();

        read(std::string filename);
};
#endif
