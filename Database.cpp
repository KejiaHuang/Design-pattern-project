//
//  Data.cpp
//  OHFinal
//
//  Created by 惠鸥 on 11/27/16.
//  Copyright © 2016 XO. All rights reserved.
//


#include <fstream>
#include <iostream>
#include "Database.hpp"


Database * Database::data_ptr = nullptr;

Database::Database(std::string FileName_)
{
    FileName = FileName_;
}

bool Database::readFile(std::vector<std::string>& _File)
{
    std::ifstream fin;
    fin.open(FileName.c_str(), std::ios::in);
    std::string line;
    if(fin.is_open())
    {
        while(getline(fin, line))
            _File.push_back(line);
        fin.close();
        return true;
    }
    else
    {
        std::cout << "No such file to open!!" << std::endl;
        fin.close();
        return false;
    }
    
}






