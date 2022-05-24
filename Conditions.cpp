//Title:    implementation of classes of Conditions

#include "Conditions.hpp"

using namespace std;

// implementation of class Thunderstorm
Thunderstorm* Thunderstorm::_instance = nullptr;
Thunderstorm* Thunderstorm::instance()
{
    if(_instance == nullptr) {
        _instance = new Thunderstorm();
    }
    return _instance;
}
void Thunderstorm::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}

// implementation of class Sunshine
Sunshine* Sunshine::_instance = nullptr;
Sunshine* Sunshine::instance()
{
    if(_instance == nullptr) {
        _instance = new Sunshine();
    }
    return _instance;
}
void Sunshine::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}

// implementation of class Other
Other* Other::_instance = nullptr;
Other* Other::instance()
{
    if(_instance == nullptr) {
        _instance = new Other();
    }
    return _instance;
}
void Other::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}