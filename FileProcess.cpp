//
//  FileProcess.cpp
//  OHFinal
//
//  Created by 惠鸥 on 12/3/16.
//  Copyright © 2016 XO. All rights reserved.
//

#include "FileProcess.hpp"
FileProcess::FileProcess(const std::vector<std::string>& File)
{
    unsigned long it = File[0].find("Close"), num = 0;

    for(unsigned long i = 0; i < it; i++)
        if(File[0][i] == ',')
            num++;
    
    
    for(unsigned long i = 1; i < File.size(); i++)
    {
        unsigned long k = 0;
        std::string tmp = "";
        
        for(unsigned long j = 0; j < File[i].size(); j++)
        {
            if(File[i][j] != ',')
                tmp += File[i][j];
            else
            {
                if(k == num)
                {
                    PriceList.push_back(std::stod(tmp));
                    break;
                }
                else
                {
                    tmp = "";
                    k++;
                }
            }
        }
    }
}


std::vector<double> FileProcess::getPriceList()
{
    return PriceList;
}
