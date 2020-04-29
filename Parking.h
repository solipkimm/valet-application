/*
Final Project Milestone - Seneca Valet Application
File : Parking.h
Date : 2020/04/12
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#ifndef _SDDS_PARKING_H__
#define _SDDS_PARKING_H__
#include "Menu.h"
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "ReadWritable.h"
namespace sdds
{
	const int MAX_PARK_SPOT = 100;
	class Parking
	{
		Vehicle* parkingSpots[MAX_PARK_SPOT];
		int noOfSpots; // < MAX_PARK_SPOT
		int noOfParkedVehicle; // < noOfSpots
		char* fileName;
		Menu* parkingMenu; // parking menu
		Menu* vehicleMenu; // vehicle selection menu;
		bool isEmpty();
		void parkingStatus();
		void parkVehicle();
		void returnVehicle();
		void listParkedVehicles();
		bool closeParking();
		bool exitParkingApp();
		bool loadDataFile();
		void saveDataFile();
	public:
		Parking();
		Parking(const char* fname, int maxNum);
		~Parking();
		Parking(const Parking& p) = delete;
		Parking& operator=(const Parking& p) = delete;
		int run();

	};
}
#endif