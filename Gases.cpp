//Title:    implementation of classes of Gases

#include "Gases.hpp"


using namespace std;

// implementation of class Ozone
    Gases* Ozone::transform(Thunderstorm *p)
    {
    double aaa;
    this->changeThickness(0,aaa);
    return this;
    }
    Gases* Ozone::transform(Sunshine *p)
    {
    double aaa;
    this->changeThickness(0,aaa);
    return this;
    }
    Gases* Ozone::transform(Other *p)
    {
    double aaa;
    this->changeThickness(5,aaa);
    Gases* temp = new Oxygen("Oxygen       ",aaa);
    return temp;
    }

// implementation of class Oxygen
    Gases* Oxygen::transform(Thunderstorm *p)
    {
    double aaa;
    this->changeThickness(50,aaa);
    Gases* temp = new Ozone("Ozone        ",aaa);
    return temp;
    }
    Gases* Oxygen::transform(Sunshine *p)
    {
    double aaa;
    this->changeThickness(5,aaa);
    Gases* temp = new Ozone("Ozone        ",aaa);
    return temp;
    }
    Gases* Oxygen::transform(Other *p)
    {
    double aaa;
    this->changeThickness(10,aaa);
    Gases* temp = new CarbonDioxide("Carbondioxide",aaa);
    return temp;
    }

// implementation of class CarbonDioxide
    Gases* CarbonDioxide::transform(Thunderstorm *p)
    {
    double aaa;
    this->changeThickness(0,aaa);
    return this;
    }
    Gases* CarbonDioxide::transform(Sunshine *p)
    {
    double aaa;
    this->changeThickness(5,aaa);
    Gases* temp = new Oxygen("Oxygen       ",aaa);
    return temp;
    }
    Gases* CarbonDioxide::transform(Other *p)
    {
    double aaa;
    this->changeThickness(0,aaa);
    return this;
    }

