/*
Final Project Milestone - Seneca Valet Application
File : Menu.h
Date : 2020/03/26
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#ifndef _SDDS_MENU_H__
#define _SDDS_NENU_H__
#include <iostream>
using namespace std;
namespace sdds
{
	const int MAX_NO_OF_ITEMS = 10;
	class Menu;
	class MenuItem
	{
		friend class Menu;
		char* m_item;
		MenuItem();
		MenuItem(const char* item);
		MenuItem(const MenuItem& mi) = delete;
		MenuItem& operator=(const MenuItem& item) = delete;
		~MenuItem();
		void setItem(const char* item);
		ostream& display(ostream& os = cout) const;
	};
	class Menu
	{
		char* m_title;
		int m_option = 0;
		int indentation;
		MenuItem* arrayMenuItem[MAX_NO_OF_ITEMS];
	public:
		Menu();
		void setEmpty();
		Menu(const char* title, int indent = 0);
		Menu(const Menu& m);
		Menu& operator=(const Menu& m);
		~Menu();
		void setTitle(const char* title);
		operator bool() const;
		bool isEmpty() const;
		ostream& display(ostream& os = cout) const;
		Menu& operator=(const char* title);
		void add(const char* item);
		int run() const;
		operator int() const;
		Menu& operator<<(const char* item);
	};
}
#endif
