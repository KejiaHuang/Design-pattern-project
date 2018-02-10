//
//  FileProcess.hpp
//  OHFinal
//
//  Created by 惠鸥 on 12/3/16.
//  Copyright © 2016 XO. All rights reserved.
//

#ifndef FileProcess_hpp
#define FileProcess_hpp
#include <vector>
#include <string>

class FileProcess
{
private:
    std::vector<double> PriceList;
public:
    FileProcess(const std::vector<std::string>& File);
    std::vector<double> getPriceList();
};





#endif /* FileProcess_hpp */
