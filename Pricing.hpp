//
//  Pricing.hpp
//  OHFinal
//
//  Created by 惠鸥 on 11/27/16.
//  Copyright © 2016 XO. All rights reserved.
//

#ifndef Pricing_hpp
#define Pricing_hpp
#include <map>
#include "HisVolatility.hpp"

template <class T> const T& max(const T& a, const T& b);


class BasePricing
{
protected:
    double S, K, T, r, Price, Vol;
    bool EmptyTree;
    typedef std::pair<unsigned long, unsigned long> Coordinate;
    std::map<Coordinate, double> Tree;
    //Payoff payoff;

public:
    virtual void Pricing() = 0;
    double getPrice() const;
    void setVol(const double& Vol_);
    //注意负数S0输入
    virtual void Initialize() = 0;
    bool getTree(std::map<Coordinate, double>& _Tree);
    
};



//
class BS: public BasePricing
{
private:
    double NormalDensity(const double& x);
    double CumulativeNormal(const double& x);
    
public:
    virtual void Pricing();
    virtual void Initialize();
};






//
class BioTree: public BasePricing
{
private:
    double u, d, p, q;
    unsigned long step;
    
    
public:
    virtual void Pricing();
    virtual void Initialize();
    unsigned long getStep();
};


//
class TriTree: public BasePricing
{
private:
    double dx, pu, pm, pd;
    unsigned long step;
    
    
    
public:
    virtual void Pricing();
    virtual void Initialize();
    unsigned long getStep();
    
};



#endif /* Pricing_hpp */
