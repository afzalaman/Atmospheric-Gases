//Title:    classes of gases

#pragma once

#include <string>

class Thunderstorm;
class Sunshine;
class Other;

using namespace std;


// class of the abstract gases
class Gases
{
protected:
    string _name;
    double thickness;
    Gases (const string &str,double e = 0) : _name(str),thickness(e) {}
public:
    string name() const { return _name; }
    bool exist() const { return thickness >= 0.5; }
    double getThickess() const { return thickness;}
    void addThickness(double a)
    {
        thickness +=a;
    }
    void changeThickness(double e,double &aa) 
    {
        aa = (e/100)*thickness;
        thickness -= aa;
    }

    virtual Gases* transform(Thunderstorm *p) = 0;
    virtual Gases* transform(Sunshine *p) = 0;
    virtual Gases* transform(Other *p) = 0;
    
    virtual ~Gases () {}
};

// class of Ozone
class Ozone : public Gases {
public:
    Ozone(const string &str,double e = 0) : Gases(str,e){}

    Gases* transform(Thunderstorm *p) override;
    Gases* transform(Sunshine *p) override;
    Gases* transform(Other *p) override;
};

// class of Oxygen
class Oxygen : public Gases {
public:
    Oxygen(const string &str,double e = 0) : Gases(str,e){}

    Gases* transform(Thunderstorm *p) override;
    Gases* transform(Sunshine *p) override;
    Gases* transform(Other *p) override;
};

// class of Carbon Dioxide
class CarbonDioxide : public Gases {
public:
    CarbonDioxide(const string &str,double e = 0) : Gases(str,e){}

    Gases* transform(Thunderstorm *p) override;
    Gases* transform(Sunshine *p) override;
    Gases* transform(Other *p) override;
};

