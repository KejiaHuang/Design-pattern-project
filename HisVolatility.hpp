//
//  HisVolatility.hpp
//  OHFinal
//
//  Created by 惠鸥 on 11/27/16.
//  Copyright © 2016 XO. All rights reserved.
//

#ifndef HisVolatility_hpp
#define HisVolatility_hpp
#include <vector>
class HisVolatility
{
private:
    double sigma;
    void GenerateHisVol(const std::vector<double>& _price);
public:
    HisVolatility(const std::vector<double>& _price);
    double getHisVol() const;
};

inline double HisVolatility::getHisVol() const
{
    return sigma;
}

#endif /* HisVolatility_hpp */
