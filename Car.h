/*
Final Project Milestone - Seneca Valet Application
File : Car.h
Date : 2020/04/06
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#ifndef _SDDS_CAR_H__
#define _SDDS_CAR_H__
#include <iostream>
#include "Vehicle.h"
using namespace std;
namespace sdds
{
	class Car : public Vehicle
	{
		bool carWash;
	public:
		Car();
		Car(const char* licenseP, const char* makeModel);
		Car(const Car& c) = delete;
		Car& operator=(const Car& c) = delete;
		istream& read(istream& istr = cin);
		ostream& write(ostream& ostr = cout) const;
	};
}
#endif