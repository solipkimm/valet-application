/*
Final Project Milestone - Seneca Valet Application
File : Motorcycle.cpp
Date : 2020/04/06
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#include <iostream>
#include <cstring>
#include "Motorcycle.h"
using namespace std;
namespace sdds
{
	// Motorcycle constructor
	Motorcycle::Motorcycle()
	{
		setEmpty();
		hasSidecar = false;
	}
	// Motorcycle constructor (const char*, const char*)
	Motorcycle::Motorcycle(const char* licenseP, const char* makeModel)
	{
		hasSidecar = false;
		if (licenseP && makeModel && licenseP[0] != '\0' && makeModel[0] != '\0')
		{
			setLicensePlate(licenseP);
			setMakeModel(makeModel);
			setParkingSpot(1);
		}
		else
		{
			setEmpty();
		}
	}
	// Read motorcycle information
	istream& Motorcycle::read(istream& istr)
	{
		char *temp = new char [10];
		bool check = false;
		if (isCsv())
		{
			Vehicle::read(istr);
			istr >> hasSidecar;
			istr.ignore();
		}
		else
		{
			cout << endl;
			cout << "Motorcycle information entry" << endl;
			Vehicle::read(istr);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			do
			{
				istr >> temp;
				if (strlen(temp) == 1)
				{
					temp[0] = tolower(temp[0]);
					if (temp[0] == 'y')
					{
						hasSidecar = true;
						check = true;
					}
					if (temp[0] == 'n')
					{
						hasSidecar = false;
						check = true;
					}
				}
				if (!check)
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
			} while (!check);
		}
		delete[] temp;
		return istr;
	}
	// Write motorcycle information
	ostream& Motorcycle::write(ostream& ostr) const
	{
		if (isEmpty())
		{
			ostr << "Invalid Motorcycle Object" << endl;
		}
		else
		{
			if (isCsv())
			{
				ostr << "M,";
			}
			else
			{
				ostr << "Vehicle type: Motorcycle" << endl;
			}
			Vehicle::write(ostr);
			if (isCsv())
			{
				if (hasSidecar) { ostr << hasSidecar << endl; }
				else { ostr << hasSidecar << endl; }
			}
			else
			{
				if (hasSidecar) { ostr << "With Sidecar" << endl; }
			}
		}
		return ostr;
	}
}