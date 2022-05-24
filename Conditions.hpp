//Title:    classes of Atmospheric Variables (Conditions) 

#pragma once

#include <string>
#include "Gases.hpp"
using namespace std;


// class of the abstract Conditions
class Conditions
{
public:

    virtual Gases* transform(Gases* p) = 0;
    virtual ~Conditions() {}
};

// class of Thunderstorm
class Thunderstorm : public Conditions
{
public:
    static Thunderstorm* instance();

    Gases* transform(Gases* p) override 
    {
        return (p->transform(this));
    }
    static void destroy() ;
protected:
    Thunderstorm(){}
private:
    static Thunderstorm* _instance;
};

// class of Sunshine
class Sunshine : public Conditions
{
public:
    static Sunshine* instance();

    Gases* transform(Gases* p) override 
    {
        return (p->transform(this));
    }
    static void destroy() ;
protected:
    Sunshine(){}
private:
    static Sunshine* _instance;
};

// class of Other
class Other : public Conditions
{
public:
    static Other* instance();
    
    Gases* transform(Gases* p) override 
    {
        return (p->transform(this));
    }
    static void destroy() ;
protected:
    Other(){}
private:
    static Other* _instance;
};
