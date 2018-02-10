//
//  HisVolatility.cpp
//  OHFinal
//
//  Created by 惠鸥 on 11/27/16.
//  Copyright © 2016 XO. All rights reserved.
//

#include "HisVolatility.hpp"
#include <cmath>
HisVolatility::HisVolatility(const std::vector<double>& _price)
{
    GenerateHisVol(_price);
}
void HisVolatility::GenerateHisVol(const std::vector<double>& _price)
{
    //sum_m is the sum of every day change
    //sum_v is the sum of the every day difference with mean
    double sum_m = 0.0, sum_v = 0.0, _mean = 0.0;
    
    unsigned long _size = _price.size();
    // generate every day vol
    for(unsigned long i = 0; i < _size - 1; i++)
        sum_m += log(_price[i+1] / _price[i]);
    
    
    // calculate mean
    _mean = sum_m / (_size - 1);

    
    // calculate HisVolatility
    for(unsigned long i = 0; i < _size - 1; i++)
        sum_v += (log(_price[i+1] / _price[i]) - _mean) * (log(_price[i+1] / _price[i]) - _mean) ;

    sigma = sqrt(sum_v / (double)(_size - 1));
}

