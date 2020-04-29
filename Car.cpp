/*
Final Project Milestone - Seneca Valet Application
File : Car.cpp
Date : 2020/04/06
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#include <iostream>
#include <cstring>
#include "Car.h"
using namespace std;
namespace sdds
{
	// Car constructor
	Car::Car()
	{
		setEmpty();
		carWash = false;
	}
	// Car constructor (const char*, const char*)
	Car::Car(const char* licenseP, const char* makeModel)
	{
		carWash = false;
		if (licenseP && makeModel && licenseP[0] != '\0' && makeModel[0] != '\0')
		{
			setLicensePlate(licenseP);
			setMakeModel(makeModel);
			setParkingSpot(0);
		}
		else
		{
			setEmpty();
		}
	}
	// Read car information
	istream& Car::read(istream& istr)
	{
		char* temp = new char [10];
		bool check = false;
		if (isCsv())
		{
			Vehicle::read(istr);
			istr >> carWash;
			istr.ignore();
		}
		else
		{
			cout << endl;
			cout << "Car information entry" << endl;
			Vehicle::read(istr);
			cout << "Carwash while parked? (Y)es/(N)o: ";
			do
			{
				istr >> temp;
				if (strlen(temp) == 1)
				{
					temp[0] = tolower(temp[0]);
					if (temp[0] == 'y')
					{
						carWash = true;
						check = true;
					}
					if (temp[0] == 'n')
					{
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
	// Write car information
	ostream& Car::write(ostream& ostr) const
	{
		if (isEmpty())
		{
			ostr << "Invalid Car Object" << endl;
		}
		else
		{
			if (isCsv())
			{
				ostr << "C,";
			}
			else
			{
				ostr << "Vehicle type: Car" << endl;
			}
			Vehicle::write(ostr);
			if (isCsv())
			{
				if (carWash) { ostr << carWash << endl; }
				else { ostr << carWash << endl; }
			}
			else
			{
				if (carWash) { ostr << "With Carwash" << endl; }
				else { ostr << "Without Carwash" << endl; }
			}
		}
		return ostr;
	}
}