/*
Final Project Milestone - Seneca Valet Application
File : ReadWritable.cpp
Date : 2020/03/28
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#include <iostream>
#include "ReadWritable.h"
using namespace std;
namespace sdds
{
	// ReadWritable Constructor
	ReadWritable::ReadWritable()
	{
		flag = false;
	}
	// Check if it is comma seperated value / true = comma seperated value
	bool ReadWritable::isCsv() const
	{
		return flag;
	}
	// Set comma seperated value / true = comma seperated value
	void ReadWritable::setCsv(bool value)
	{
		flag = value;
	}
	//
	ostream& operator<<(ostream& os, const ReadWritable& r)
	{
		r.write(os);
		return os;
	}
	//
	istream& operator>>(istream& in, ReadWritable& r)
	{
		r.read(in);
		return in;
	}
}
