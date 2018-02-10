//
//  PrintOut.cpp
//  OHFinal
//
//  Created by 惠鸥 on 12/3/16.
//  Copyright © 2016 XO. All rights reserved.
//

#include "PrintOut.hpp"
#include <map>
#include <iostream>
#include <fstream>
PrintOut::PrintOut(double price_): PricePrint(price_)
{}

NumPrint::NumPrint(double price_): PrintOut(price_)
{}


void NumPrint::print()
{
    std::cout << "The price is " << PricePrint << std::endl;
}

TreePrint::TreePrint(double price_, std::map<Coordinate, double> T_, unsigned long step_): PrintOut(price_), T(T_), step(step_)
{}

void TreePrint::print()
{
    std::cout << "The price is " << PricePrint << std::endl;
    
    
    double ** M;
    unsigned long Max = 2 * step + 1;
    M = new double * [Max];
    for(unsigned long i = 0; i < Max; i++)
        M[i] = new double[step];
    
    for(unsigned long i = 0; i < Max; i++)
        for(unsigned long j = 0; j < step; j++)
            M[i][j] = -1;
    
    for(auto it : T)
    {
        unsigned long x, y;
        x = (it.first).first;
        y = (it.first).second;
        y =  (2 * y - x) + step + 1;
        M[x][y] = it.second;
    }
    
    std::ofstream fout;
    fout.open("Result.csv");
    for(unsigned long i = 0; i < Max; i++)
    {
        for(unsigned long j = 0; j < step; j++)
        {
            if(M[i][j] == -1)
                fout << ',';
            else
                fout << M[i][j];
        }
        fout << std::endl;
    }
    fout.close();
    
    for(unsigned long i = 0; i < Max; i++)
        delete [] M[i];
    
    delete [] M;
}
