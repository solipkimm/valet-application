/*
Final Project Milestone - Seneca Valet Application
File : Parking.cpp
Date : 2020/04/12
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include "Parking.h"
using namespace std;
namespace sdds
{
	// Parking Constructor
	Parking::Parking()
	{
		fileName = nullptr;
		noOfSpots = 0;
		parkingSpots[0] = nullptr;
		for (int i = 0; i < MAX_PARK_SPOT; i++)
		{
			parkingSpots[i] = nullptr;
		}
		noOfParkedVehicle = 0;
		parkingMenu = nullptr;
		vehicleMenu = nullptr;

	}
	// Parking Constructor(const char*, int)
	Parking::Parking(const char* fname, int maxNum)
	{
		if (!fname || fname[0] == '\0' || maxNum < 10 || maxNum > MAX_PARK_SPOT)
		{
			fileName = nullptr;
			noOfSpots = 0;
			for (int i = 0; i < MAX_PARK_SPOT; i++)
			{
				parkingSpots[i] = nullptr;
			}
			noOfParkedVehicle = 0;
		}
		else
		{
			fileName = new char[strlen(fname) + 1];
			strcpy(fileName, fname);
			for (int i = 0; i < MAX_PARK_SPOT; i++)
			{
				parkingSpots[i] = nullptr;
			}
			noOfSpots = maxNum;
			noOfParkedVehicle = 0;
		}
		if (loadDataFile())
		{
			parkingMenu = new Menu("Parking Menu, select an action:");
			parkingMenu->add("Park Vehicle");
			parkingMenu->add("Return Vehicle");
			parkingMenu->add("List Parked Vehicles");
			parkingMenu->add("Close Parking (End of day)");
			parkingMenu->add("Exit Program");

			vehicleMenu = new Menu("Select type of the vehicle:", 1);
			vehicleMenu->add("Car");
			vehicleMenu->add("Motorcycle");
			vehicleMenu->add("Cancel");
		}
		else
		{
			cout << "Error in data file" << endl;
			fileName = nullptr;
		}
	}
	// Parking Destructor
	Parking::~Parking()
	{
		saveDataFile();
		cin.ignore(100, '\n');
		for (int i = 0; i < MAX_PARK_SPOT; i++)
		{
			if (parkingSpots[i] != nullptr)
			{
				delete parkingSpots[i];
				parkingSpots[i] = nullptr;
			}
		}
		if (fileName || vehicleMenu || parkingMenu)
		{
			delete parkingMenu;
			parkingMenu = nullptr;
			delete vehicleMenu;
			vehicleMenu = nullptr;
			delete[] fileName;
			fileName = nullptr;
		}
	}
	// Check if the parking is empty ( if it is empty, return true )
	bool Parking::isEmpty()
	{
		return fileName == nullptr || fileName[0] == '\0';
	}
	// Show current parking status
	void Parking::parkingStatus()
	{
		cout << "****** Seneca Valet Parking ******" << endl;
		cout << "*****  Available spots: ";
		cout.width(4);
		cout.setf(ios::left);
		cout << noOfSpots - noOfParkedVehicle;
		cout << " *****" << endl;
	}
	// Park vehicle
	void Parking::parkVehicle()
	{
		if (noOfSpots == noOfParkedVehicle)
		{
			cout << "Parking is full" << endl;
		}
		else
		{
			Vehicle* temp = nullptr;
			int availableIndex = -1;
			bool flag = false;
			int option = vehicleMenu->run();
			if (option == 1)
			{
				temp = new Car;
				temp->setCsv(false);
				temp->read();
			}
			if (option == 2)
			{
				temp = new Motorcycle;
				temp->setCsv(false);
				temp->read();
			}
			if (option == 1 || option == 2)
			{
				if (temp)
				{
					for (int i = 0; i < noOfSpots && flag == false; i++)
					{
						if (parkingSpots[i] == nullptr)
						{
							flag = true;
							availableIndex = i;
						}
					}
					parkingSpots[availableIndex] = temp;
					noOfParkedVehicle++;
					parkingSpots[availableIndex]->setParkingSpot(availableIndex + 1);

					cout << endl << "Parking Ticket" << endl;
					parkingSpots[availableIndex]->write();
					cout << endl;
				}
			}
			if (option == 3) { cout << "Parking cancelled" << endl; }
		}
	}
	// Return parked vehicle
	void Parking::returnVehicle()
	{
		char* tempLicense = new char [9];
		cout << "Return Vehicle" << endl;
		cout << "Enter Licence Plate Number: ";
		cin >> tempLicense;
		while (strlen(tempLicense) < 1 && strlen(tempLicense) > MAX_LICENSE_CHAR)
		{
			cout << "Invalid Licence Plate, try again: ";
			cin >> tempLicense;
		}
		cout << endl;
		int len = strlen(tempLicense);
		for (int j = 0; j <len; j++)
		{
			tempLicense[j] = toupper(tempLicense[j]);
		}
		bool cmp = false;
		int index = -1;
		for (int i = 0; i < noOfSpots && cmp == false; i++)
		{
			cmp = *parkingSpots[i] == tempLicense;
			if (cmp) { index = i; }
		}
		if (cmp)
		{
			cout << "Returning: " << endl;
			parkingSpots[index]->setCsv(false);
			parkingSpots[index]->write();
			delete parkingSpots[index];
			parkingSpots[index] = nullptr;
			noOfParkedVehicle--;
		}
		else
		{
			cout << "License plate " << tempLicense << " Not found" << endl;
		}
		delete[] tempLicense;
		cout << endl;
	}
	// List parked vehicles information
	void Parking::listParkedVehicles()
	{
		cout << "*** List of parked vehicles ***" << endl;
		for (int i = 0; i < noOfSpots; i++)
		{
			if (parkingSpots[i])
			{
				parkingSpots[i]->setCsv(false);
				parkingSpots[i]->write();
				cout << "-------------------------------" << endl;		
			}
		}
	}
	// Close parking, return all vehicles parked
	bool Parking::closeParking()
	{
		string yes = "";
		bool result = false;
		if (isEmpty()) 
		{ 
			cout << "Closing Parking" << endl;
			result = true;
		}
		else
		{
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
			cout << "Are you sure? (Y)es/(N)o: ";
			while (yes != "y" && yes != "Y" && yes != "n" && yes != "N")
			{
				cin >> yes;
				if (yes != "y" && yes != "Y" && yes != "n" && yes != "N")
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
			}
			if (yes == "y" || yes == "Y")
			{
				result = true;
				cout << "Closing Parking" << endl;
				for (int i = 0; i < noOfSpots; i++)
				{
					if (parkingSpots[i])
					{
						cout << endl << "Towing request" << endl;
						cout << "*********************" << endl;
						parkingSpots[i]->setCsv(false);
						parkingSpots[i]->write();
					}
				}
				for (int i = 0; i < noOfSpots; i++)
				{
					delete parkingSpots[i];
					parkingSpots[i] = nullptr;
				}
			}
			if (yes == "n" || yes == "N")
			{
				cout << "Aborted!" << endl;
				result = false;
			}
		}
		return result;
	}
	// Exit parking app
	bool Parking::exitParkingApp()
	{
		string yes = "";
		bool result = false;
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";
		while (yes != "y" && yes != "Y" && yes != "n" && yes != "N")
		{
			cin >> yes;
			if (yes != "y" && yes != "Y" && yes != "n" && yes != "N")
			{
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			}
		}
		if (yes == "y" || yes == "Y")
		{
			result = true;
			cout << "Exiting program!" << endl;
		}
		return result;
	}
	// load data from file to Pakring app
	bool Parking::loadDataFile()
	{
		bool result = false;
		bool open = false;
		char pickVehicle;
		if (!isEmpty())
		{
			ifstream f;
			f.open(fileName);
			if (f.is_open()) { open = true; }
			if (open)
			{
				result = true;
				while (f.good() && noOfParkedVehicle < noOfSpots)
				{
					Vehicle* temp = nullptr;
					pickVehicle = f.get();
					f.ignore();
					if (pickVehicle == 'C' || pickVehicle == 'M')
					{
						if (pickVehicle == 'M') { temp = new Motorcycle; }
						if (pickVehicle == 'C') { temp = new Car; }
						temp->setCsv(true);
						temp->read(f);
						f.clear();

							bool empty = false;
							int index = -1;
							for (int i = 0; i < noOfSpots && empty == false; i++)
							{
								if (parkingSpots[i] == nullptr)
								{
									empty = true;
									index = i;
								}
							}
							if (empty)
							{
								parkingSpots[index] = temp;
								noOfParkedVehicle++;
								parkingSpots[index]->setParkingSpot(index + 1);
								result = true;
							}
							else
							{
								delete temp;
								result = false;
							}
//						}
					}
				}
			}
			f.close();
		}
		if (isEmpty() || !open)
		{
			result = true;
		}
		return result;
	}
	// Save data of Parking app in file
	void Parking::saveDataFile()
	{
		if (!isEmpty())
		{
			ofstream f(fileName);
			if (f.is_open())
			{
				for (int i = 0; i < noOfSpots; i++)
				{
					if (parkingSpots[i])
					{
						parkingSpots[i]->setCsv(true);
						parkingSpots[i]->write(f);
					}
				}
				f.close();
			}
		}
	}
	// run parking app with number options
	int Parking::run()
	{
		int p_option;
		bool c_check = false;
		bool e_check = false;
		bool result = false;

		if (!isEmpty())
		{
			while (result == false)
			{
				parkingStatus();
				p_option = parkingMenu->run();
				if (p_option == 1)
				{
					parkVehicle();
				}
				if (p_option == 2)
				{
					returnVehicle();
				}
				if (p_option == 3)
				{
					listParkedVehicles();
				}
				if (p_option == 4)
				{
					c_check = closeParking();
					if (c_check)
					{
						result = true;
					}
				}
				if (p_option == 5)
				{
					e_check = exitParkingApp();
					if (e_check)
					{
						result = true;
					}
				}
			}
		}
		return !isEmpty();
	}
}