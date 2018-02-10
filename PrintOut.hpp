//
//  PrintOut.hpp
//  OHFinal
//
//  Created by 惠鸥 on 12/3/16.
//  Copyright © 2016 XO. All rights reserved.
//

#ifndef PrintOut_hpp
#define PrintOut_hpp
#include <map>
class PrintOut
{
protected:
    double PricePrint;
    
public:
    PrintOut(double price);
    virtual void print() = 0;
};

class NumPrint: public PrintOut
{
public:
    NumPrint(double price_);
    virtual void print();
};

class TreePrint: public PrintOut
{
private:
    typedef std::pair<unsigned long, unsigned long> Coordinate;
    std::map<Coordinate, double> T;
    unsigned long step;
    
public:
    TreePrint(double price_, std::map<Coordinate, double> T_, unsigned long step_);
    virtual void print();
    
};





#endif /* PrintOut_hpp */
