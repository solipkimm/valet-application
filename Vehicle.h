/*
Final Project Milestone - Seneca Valet Application
File : Vehicle.h
Date : 2020/04/01
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#ifndef _SDDS_VEHICLE_H__
#define _SDDS_VEHICLE_H__
#include <iostream>
#include "ReadWritable.h"
using namespace std;
namespace sdds
{
	const int MAX_LICENSE_CHAR = 8;
	class Vehicle : virtual public ReadWritable
	{
		char licensePlate[MAX_LICENSE_CHAR + 1]; // 1-8 characters
		char* makeAndModel; // more than 2 characters
		int parkingSpotNumber; // >= 0
	public:
		Vehicle();
		Vehicle(const char* licensePlate, const char* makeModel);
		Vehicle(const Vehicle& v) = delete;
		Vehicle& operator=(const Vehicle& v) = delete;
		~Vehicle();
		int getParkingSpot();
		void setParkingSpot(int parkingSpot);
		friend bool operator==(const Vehicle& v, const char* rhs);
		friend bool operator==(const Vehicle& lhs, const Vehicle& rhs);
		istream& read(istream& istr = cin);
		ostream& write(ostream& ostr = cout) const;
	protected:
		void setEmpty();
		bool isEmpty() const;
		const char* getLicensePlate();
		const char* getMakeModel();
		void setMakeModel(const char* makeModel);
		void setLicensePlate(const char* licensePlate);
	};
}
#endif