/*
Final Project Milestone - Seneca Valet Application
File : Motorcycle.h
Date : 2020/04/06
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#ifndef _SDDS_MOTORCYCLE_H__
#define _SDDS_MOTORCYCLE_H__
#include <iostream>
#include "Vehicle.h"
using namespace std;
namespace sdds
{
	class Motorcycle : public Vehicle
	{
		bool hasSidecar;
	public:
		Motorcycle();
		Motorcycle(const char* licenseP, const char* makeModel);
		Motorcycle(const Motorcycle& m) = delete;
		Motorcycle& operator=(const Motorcycle& m) = delete;
		istream& read(istream& istr = cin);
		ostream& write(ostream& ostr = cout) const;
	};
}
#endif