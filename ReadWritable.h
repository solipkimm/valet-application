/*
Final Project Milestone - Seneca Valet Application
File : ReadWritable.h
Date : 2020/03/28
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#ifndef _SDDS_READWRITABLE_H__
#define _SDDS_READWRITABLE_H__
#include <iostream>
using namespace std;
namespace sdds
{
	class ReadWritable
	{
		bool flag;
	public:
		ReadWritable();
		virtual ~ReadWritable() = default;
		bool isCsv() const;
		void setCsv(bool value);
		virtual std::istream& read(std::istream& istr = std::cin) = 0;
		virtual std::ostream& write(std::ostream& ostr = std::cout) const = 0;
	};
	std::ostream& operator<<(std::ostream& os, const ReadWritable& r);
	std::istream& operator>>(std::istream& in, ReadWritable& r);
}
#endif
