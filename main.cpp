//
//  main.cpp
//  OHFinal
//
//  Created by 惠鸥 on 11/27/16.
//  Copyright © 2016 XO. All rights reserved.
//
#include <iostream>
#include "Pricing.hpp"
#include "HisVolatility.hpp"
#include "Database.hpp"
#include "PrintOut.hpp"
#include "FileProcess.hpp"


int main(int argc, const char * argv[]) {
    
    //Read the data
    std::vector<std::string> StockInfo;
    Database::instance() -> setFileName("AAPL.csv");
    Database::instance() -> readFile(StockInfo);
    
    //choose the close price we need
    FileProcess StockDetail(StockInfo);
    std::vector<double> tmpVol = StockDetail.getPriceList();
    
    //calculate the volatility
    HisVolatility vol(tmpVol);
    double Vol = vol.getHisVol();
    
    std::cout << Vol << std::endl;
    
    BS bs;
    bs.setVol(Vol);
    bs.Initialize();
    bs.Pricing();
    
    NumPrint numprint(bs.getPrice());
    numprint.print();
    
    
    BioTree BT;
    BT.setVol(Vol);
    BT.Initialize();
    BT.Pricing();
    std::cout << BT.getPrice() << std::endl;
    
    std::map<std::pair<unsigned long, unsigned long>, double> Tree;
    
    if(!(BT.getTree(Tree)))
        std::cout << "There is no tree in this case" << std::endl;
    else
    {
        TreePrint treeprint(BT.getPrice(), Tree, BT.getStep());
        treeprint.print();
    }

    
    
    
    TriTree TT;
    TT.setVol(Vol);
    TT.Initialize();
    TT.Pricing();
    
    std::cout << TT.getPrice() << std::endl;
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
