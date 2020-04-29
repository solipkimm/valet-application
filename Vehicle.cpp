/*
Final Project Milestone - Seneca Valet Application
File : Vehicle.cpp
Date : 2020/04/01
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Vehicle.h"
using namespace std;
namespace sdds
{
	// Vehicle Constructor
	Vehicle::Vehicle()
	{
		setEmpty();
	}
	// Vehicle Constructor (const char*, const char*)
	Vehicle::Vehicle(const char* licenseP, const char* makeModel)
	{
		if (licenseP && makeModel && licenseP[0] != '\0' && makeModel[0] != '\0')
		{
			if (strlen(makeModel) >= 2 && strlen(licenseP) > 1 && strlen(licenseP) < 9)
			{
				makeAndModel = new char[61];
				strcpy(licensePlate, licenseP);
				strcpy(makeAndModel, makeModel);
				parkingSpotNumber = 1;
			}
			else
			{
				setEmpty();
			}
		}
		else
		{
			setEmpty();
		}
	}
	// Vehicle Destructor
	Vehicle::~Vehicle()
	{
		delete[] makeAndModel;
	}
	// Set Vihicle empty
	void Vehicle::setEmpty()
	{
		licensePlate[0] = '\0';
		makeAndModel = nullptr;
		parkingSpotNumber = 0;
	}
	// Check if Vehicle is empty / true = empty
	bool Vehicle::isEmpty() const
	{
		return licensePlate == nullptr || makeAndModel == nullptr || licensePlate[0] == '\0' || makeAndModel[0] == '\0';
	}
	// Get licensePlate
	const char* Vehicle::getLicensePlate()
	{
		return licensePlate;
	}
	// Get makeAndModel
	const char* Vehicle::getMakeModel()
	{
		return makeAndModel;
	}
	// Set licensePlate
	void Vehicle::setLicensePlate(const char* licenseP)
	{
		if (licenseP && licenseP[0] != '\0' && strlen(licenseP) <= MAX_LICENSE_CHAR)
		{
			strcpy(licensePlate, licenseP);
		}
		else
		{
			if (!isEmpty())
			{
				delete[] makeAndModel;
			}
			setEmpty();
		}
	}
	// Set makeAndModel
	void Vehicle::setMakeModel(const char* makeModel)
	{
		if (makeModel && strlen(makeModel) >= 2)
		{
			if (makeAndModel)
			{
				delete[] makeAndModel;
				makeAndModel = nullptr;
			}
			makeAndModel = new char[61];
			strcpy(makeAndModel, makeModel);
		}
		else
		{
			if (!isEmpty())
			{
				delete[] makeAndModel;
			}
			setEmpty();
		}
	}
	// Get parkingSpotNumber
	int Vehicle::getParkingSpot()
	{
		return parkingSpotNumber;
	}
	// Set parkingSpotNumber
	void Vehicle::setParkingSpot(int parkingSpot)
	{
		if (parkingSpot > 0)
		{
			parkingSpotNumber = parkingSpot;
		}
		else
		{
			if (!isEmpty())
			{
				delete[] makeAndModel;
			}
			setEmpty();
		}
	}
	// Check if licensePalte of another Vehicle and this licensePlate are same / true = same
	bool operator==(const Vehicle& v, const char* rhs)
	{
		int check;
		bool result = false;

		if (v.licensePlate || rhs)
		{
				check = strcmp(v.licensePlate, rhs);
				if (check == 0)
				{
					result = true;
				}
				else
				{
					result = false;
				}
		}
		else
		{
			result = false;
		}
		return result;
	}
	// Check if two string are same / true = same
	bool operator==(const Vehicle& lhs, const Vehicle& rhs)
	{
		int check;
		bool result;
		if (lhs.licensePlate || rhs.licensePlate)
		{
			check = strcmp(lhs.licensePlate, rhs.licensePlate);
			if (check == 0)
			{
				result = true;
			}
			else
			{
				result = false;
			}
		}
		else
		{
			result = false;
		}
		return result;
	}
	// Read Vehicle information
	std::istream& Vehicle::read(std::istream& istr)
	{
		char temp[61];
		char temp2[61];
		if (!isEmpty())
		{
			delete[] makeAndModel;
		}
		setEmpty();
		if (isCsv())
		{
			istr >> parkingSpotNumber;
			istr.ignore();
			istr.getline(licensePlate, MAX_LICENSE_CHAR + 1, ',');
			if (istr.fail())
			{
				istr.clear();
				istr.ignore(2000, '\n');
			}
			makeAndModel = new char[61];
			istr.getline(makeAndModel, 60, ',');
			if (istr.fail())
			{
				istr.clear();
				istr.ignore(2000, '\n');
			}
		}
		else
		{
			if (istr.fail())
			{
				istr.clear();
				istr.ignore(2000, '\n');
			}
			cout << "Enter Licence Plate Number: ";
			istr.getline(temp2, 10);
			while (strlen(temp2) < 1 || strlen(temp2) > 8)
			{
				cout << "Invalid Licence Plate, try again: ";
				istr.getline(temp2, 10);
			}
			setLicensePlate(temp2);
		
			cout << "Enter Make and Model: ";
			istr.getline(temp, 61);
			while (strlen(temp) < 2 || strlen(temp) > 60)
			{
				cout << "Invalid Make and model, try again: ";
				istr.getline(temp, 61);
			}
			setMakeModel(temp);
			parkingSpotNumber = 0;

		}
		if (istr.fail())
		{
			if (!isEmpty())
			{
				delete[] makeAndModel;
			}
			setEmpty();
		}
		else
		{
			int len = strlen(licensePlate);
			for (int i = 0; i < len; i++)
			{
				licensePlate[i] = toupper(licensePlate[i]);
			}
		}
		return istr;
	}
	//Write Vehicle information
	std::ostream& Vehicle::write(std::ostream& ostr) const
	{
		if (isEmpty())
		{
			ostr << "Invalid Vehicle Object" << endl;
		}
		else
		{
			if (isCsv())
			{
				ostr << parkingSpotNumber << "," << licensePlate << "," << makeAndModel << ",";
			}
			else
			{
				ostr << "Parking Spot Number: ";
				if (parkingSpotNumber == 0)
				{
					ostr << "N/A" << endl;
				}
				else
				{
					ostr << parkingSpotNumber << endl;
				}
				ostr << "Licence Plate: " << licensePlate << endl;
				ostr << "Make and Model: " << makeAndModel << endl;
			}
		}
		return ostr;
	}
}