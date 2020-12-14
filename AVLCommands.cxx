#include <iostream>
#include "AVL.h"
#include "BST.h"
#include "json.hpp"
#include <fstream>
#include <string.h>


nlohmann::json inputFile(const std::string& fileName);

int main(int argc, char **argv)
{

    //checks for correct input
    if(argc < 2){
        std::cerr << "Usage: " << argv[0] << " file1.json";
        return 1;
    }
    //creates output objects
    nlohmann::json commands;
    nlohmann::json finalTree;

    //tries to get json object data from file
    try {
        commands = inputFile(argv[1]);
    }catch (std::invalid_argument & e){
        //throws error if one occured
        std::cerr << e.what() << '\n';
        return 1;
    }
    //creates variables
    int numOps = commands["metadata"]["numOps"];
    int key;
    std::string operation;
    //creates AVLTree
    AVLTree tree;

    //finds number of digits in numOperations
    int numDigits = (int) floor(log10((double) numOps)) + 1;
    int numDigitsCurr;
    
    //iterates for each operation
    for(int i = 1; i <= numOps; i++)
    {
        //identifies the number of digits in the current operation
        if(i == 0)
        {
            numDigitsCurr = 1;
        }else
        {
            numDigitsCurr = (int) floor(log10((double) i)) + 1;
        }

        //start making key name
        std::string currentOp = "";
        //adds a zero to make sure the number of digits in the key is correct
        for(int j = numDigitsCurr; j < numDigits; j++)
        {
            currentOp += "0";
        }
        //add number to key
        currentOp += std::to_string(i);

        key = commands[currentOp]["key"];
        operation = commands[currentOp]["operation"];


        if(operation.compare("Insert")== 0)
        {
            tree.AVLInsert(key);
        }
    }
    //outputs object
    std::cout << tree.JSON();

    return 0;
}


nlohmann::json inputFile(const std::string& fileName)
{
    //creates instream
    std::ifstream inFile;
    //opens file
    inFile.open(fileName);

    nlohmann::json newObject;
    //checks if file is open
    if(!inFile.is_open()){
        throw std::invalid_argument("Error: " + fileName + " cannot be opened");
    }
    //moves file to json object
    inFile >> newObject;
    //closes file
    inFile.close();
    //returns json object
    return newObject;
}