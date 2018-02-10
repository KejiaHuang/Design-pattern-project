//
//  Pricing.cpp
//  OHFinal
//
//  Created by 惠鸥 on 11/27/16.
//  Copyright © 2016 XO. All rights reserved.
//
#include <iostream>
#include <cmath>
#include "Pricing.hpp"
#define M_PI 3.1415926
template <class T> const T& max(const T& a, const T& b)
{
    if(a >= b)
        return a;
    else
        return b;
}

//Base Class
double BasePricing::getPrice() const
{
    return Price;
}

void BasePricing::setVol(const double& Vol_)
{
    Vol = Vol_;
}

bool BasePricing::getTree(std::map<Coordinate, double>& _Tree)
{
    if(EmptyTree)
        return false;
    else
    {
        _Tree = Tree;
        return true;
    }
    
}


//BS
void BS::Pricing()
{
    EmptyTree = true;
    double standardDeviation = Vol * sqrt(T);
    double moneyness = log(S / K);
    double d1 =(moneyness +  r * T + 0.5 * standardDeviation* standardDeviation) / standardDeviation;
    double d2 = d1 - standardDeviation;
    Price =  S * CumulativeNormal(d1) - K * exp(-r * T) * CumulativeNormal(d2);
}

double BS::NormalDensity(const double& x)
{
    return 1 / sqrt(2 * M_PI) * exp(- x * x / 2);
}
//explain in the pdf
double BS::CumulativeNormal(const double& x)
{
    static double a[5] = {0.319381530,
        -0.356563782,
        1.781477937,
        -1.821255978,
        1.330274429};
    double result;
    
    if (x < -7.0)
        result = NormalDensity(x) / sqrt(1. + x * x);
    
    else
    {
        if (x > 7.0)
            result = 1.0 - CumulativeNormal(-x);
        else
        {
            double tmp = 1.0 / (1.0 + 0.2316419 * fabs(x));
            
            result = 1 - NormalDensity(x) *
            (tmp * (a[0] + tmp * (a[1] + tmp * (a[2] + tmp * (a[3] + tmp * a[4])))));
            
            if (x <= 0.0)
                result = 1.0 - result;
            
        }
    }
    return result;

}

void BS::Initialize()
{
    std::cout << "Please enter spot pirce:";
    std::cin >> S;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> S;
    }
    
    std::cout << "Please enter strike pirce:";
    std::cin >> K;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> K;
    }
    
    std::cout << "Please enter expiry:";
    std::cin >> T;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> T;
    }
    
    std::cout << "Please enter interest rate:";
    std::cin >> r;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> r;
    }
}


//BioTree
void BioTree::Pricing()
{
    EmptyTree = false;
    // precompute constants
    double dt = T / (double)step, v = Vol;
    u = exp(r - 0.5 * v * v) * dt + v * sqrt(dt);
    d = 1 / u;
    p = (exp(r * dt) - d) / (u - d);
    q = (u - exp(r * dt)) / (u - d);

    double Discount = exp(-r * dt);
    
    // initialise asset prices at maturity time step N
    double * ptr, payoff;
    ptr = new double[step + 1];
    ptr[0] = S * pow(d, step);
    for(unsigned long i = 0; i < step; i++)
        ptr[i + 1] = ptr[i] * u / d;
    
    // initialise option values at maturity
    for(unsigned long i = 0; i < step + 1; i++)
    {
        //call or put
        payoff = max(ptr[i] - K, 0.0);
        Tree.insert(std::make_pair(Coordinate(step, i), payoff));
    }
    
    // step back through the tree
    for(unsigned long i = 0; i < step; i++)
    {
        for(unsigned long j = 0; j < step - i; j++)
        {
            auto itq = Tree.find(Coordinate(step - i, j));
            auto itp = Tree.find(Coordinate(step - i, j + 1));
            payoff = Discount * (q * itq -> second + p * itp -> second);
            Tree.insert(std::make_pair(Coordinate(step - i - 1, j), payoff));
        }
    }
    Price = Tree.begin() -> second;
    delete[] ptr;
}

void BioTree::Initialize()
{
    
    std::cout << "Please enter spot pirce:";
    std::cin >> S;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> S;
    }
    
    std::cout << "Please enter strike pirce:";
    std::cin >> K;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> K;
    }
    
    std::cout << "Please enter expiry:";
    std::cin >> T;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> T;
    }
    
    std::cout << "Please enter interest rate:";
    std::cin >> r;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> r;
    }
    
    std::cout << "Please enter steps:";
    std::cin >> step;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> step;
    }
}

unsigned long BioTree::getStep()
{
    return step;
}




void TriTree::Pricing()
{
    // precompute constants
    EmptyTree = false;
    double v = Vol;
    double dt = T / (double)step;
    double nu = r - 0.5 * v * v;
    pu = 0.5*((v * v * dt + nu * nu * dt * dt) / dx / dx + nu * dt / dx);

    pm = 1 - ((v * v * dt + nu * nu * dt * dt) / dx / dx);
    pd = 0.5 * ((v * v * dt + nu * nu * dt * dt) / dx / dx - nu*dt / dx);
    
    double Discount = exp(-r * dt), payoff;
    double * ptr;
    
    // initialise asset prices at maturity
    ptr = new double[2 * step + 1];
    for(unsigned long i = 0; i < (2 * step + 1); i++)
        ptr[i] = S * exp((-step + i) * dx);
    
    // initialise open value at maturity
    for(unsigned long i = 0; i < (2 * step + 1); i++)
    {
        //payoff
        payoff = max(ptr[i] - K, 0.0);
        Tree.insert(std::make_pair(Coordinate(step, i), payoff));
    }
    
    // free memory
    delete[] ptr;
    
    //step back through lattice
    for(unsigned long i = 0; i < step; i++)
    {
        for (unsigned long j = 0; j < (2 * (step - i) - 1); j++)
        {
            auto it1 = Tree.find(Coordinate(step - i , j));
            auto it2 = Tree.find(Coordinate(step - i , j + 1));
            auto it3 = Tree.find(Coordinate(step - i , j + 2));
            payoff = Discount * (pd * it1 -> second + pm * it2 -> second + pu * it3 -> second);
            Tree.insert(std::make_pair(Coordinate(step - 1 - i, j), payoff));
        }
    }
    
    // return European price
    auto it = Tree.find(Coordinate(0, 0));
    
    Price = it -> second;
    

}


void TriTree::Initialize()
{
    std::cout << "Please enter spot pirce:";
    std::cin >> S;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> S;
    }
    
    std::cout << "Please enter strike pirce:";
    std::cin >> K;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> K;
    }
    
    std::cout << "Please enter expiry:";
    std::cin >> T;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> T;
    }
    
    std::cout << "Please enter interest rate:";
    std::cin >> r;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> r;
    }
    
    std::cout << "Please enter space step for trinomial tree:";
    std::cin >> dx;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> dx;
    }
    
    std::cout << "Please enter steps:";
    std::cin >> step;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong!! Please enter again:";
        std::cin >> step;
    }
}

unsigned long TriTree::getStep()
{
    return step;
}





