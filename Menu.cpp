/*
Final Project Milestone - Seneca Valet Application
File : Menu.cpp
Date : 2020/03/26
Name : Solip Kim
Email : skim428@myseneca.ca
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
using namespace std;
namespace sdds
{
	// MenuItem constructor
	MenuItem::MenuItem()
	{
		m_item = nullptr;
	}
	// Menuitem constructor (const char*)
	MenuItem::MenuItem(const char* item)
	{
		m_item = nullptr;
		if (item && item[0] != '\0')
		{
			setItem(item);
		}
	}
	// Set m_item
	void MenuItem::setItem(const char* item)
	{
		int len = strlen(item);
		m_item = new char[len + 1];
		strcpy(m_item, item);
	}
	// Menuitem destructor
	MenuItem::~MenuItem()
	{
		delete[] m_item;
		m_item = nullptr;
	}
	// Display m_item
	ostream& MenuItem::display(ostream& os) const
	{
		if (m_item && m_item[0] != '\0')
		{
			os << m_item << endl;
		}
		return os;
	}
	// Menu constructor
	Menu::Menu()
	{
		setEmpty();
	}
	// Set Menu class empty;
	void Menu::setEmpty()
	{
		m_title = nullptr;
		for (int i = 0; i < m_option; i++)
		{
			arrayMenuItem[i] = nullptr;
		}
		m_option = 0;
		indentation = 0;
	}
	// Menu constructor (const Menu&)
	Menu::Menu(const Menu& m)
	{
		setEmpty();
		*this = m;
	}
	// Menu constructor (const char*, int)
	Menu::Menu(const char* title, int indent)
	{
		setEmpty();
		if (title && title[0] != '\0')
		{
			*this = title;
			if (indent > 0)
			{
				indentation = indent;
			}
		}
	}
	// Set m_title
	void Menu::setTitle(const char* title)
	{
		int len = strlen(title);
		m_title = new char[len + 1];
		strcpy(m_title, title);
	}
	// Copy Menu 'm' to this
	Menu& Menu::operator=(const Menu& m)
	{
		if (this != &m)
		{
			if (isEmpty())
			{
				if (!m.isEmpty())
				{
					setTitle(m.m_title);
					indentation = m.indentation;
					m_option = m.m_option;
					if (m_option > 0)
					{
						for (int i = 0; i < m_option; i++)
						{
							arrayMenuItem[i] = new MenuItem(m.arrayMenuItem[i]->m_item);
						}
					}
				}
			}
			else
			{
				delete[] m_title;
				if (m_option > 0)
				{
					for (int i = 0; i < m_option; i++)
						delete arrayMenuItem[i];
				}
				setEmpty();
				if (!m.isEmpty())
				{
					setTitle(m.m_title);
					indentation = m.indentation;
					m_option = m.m_option;
					if (m_option > 0)
					{
						for (int i = 0; i < m_option; i++)
						{
							arrayMenuItem[i] = new MenuItem(m.arrayMenuItem[i]->m_item);
						}
					}
				}
			}
		}
		return *this;
	}
	// Menu destructor
	Menu::~Menu()
	{
		delete[] m_title;
		m_title = nullptr;
		for (int i = 0; i < m_option; i++)
		{
			delete arrayMenuItem[i];
			arrayMenuItem[i] = nullptr;
		}
	}
	// bool operator / true = class is not empty
	Menu::operator bool() const
	{
		return !isEmpty();
	}
	// Check if Menu is empty or not / true = empty
	bool Menu::isEmpty() const
	{
		return m_title == nullptr || m_title[0] == '\0';
	}
	// Display Menu
	ostream& Menu::display(ostream& os) const
	{
		if (isEmpty()) os << "Invalid Menu!" << endl;
		else
		{
			string indent = "";
			if (indentation > 0)
			{
				for (int i = 0; i < indentation * 4; i++) indent += " ";
			}
			os << indent << m_title << endl;
			if (m_option == 0) os << "No Items to display!" << endl;
			else
			{
				for (int j = 0; j < m_option; j++)
				{
					os << indent << j + 1 << "- " << arrayMenuItem[j]->m_item << endl;
				}
				os << indent << "> ";
			}
		}
		return os;
	}
	// Copy title
	Menu& Menu::operator=(const char* title)
	{
		if (title && title[0] != '\0')
		{
			if (!isEmpty())
			{
				delete[] m_title;
				m_title = nullptr;
			}
			setTitle(title);
		}
		else
		{
			setEmpty();
		}
		return *this;
	}
	// Add item in menu
	void Menu::add(const char* item)
	{
		if (item && item[0] != '\0')
		{
			if (m_option < MAX_NO_OF_ITEMS)
			{
				arrayMenuItem[m_option] = new MenuItem(item);
				m_option++;
			}
		}
		else
		{
			delete[] m_title;
			for (int i = 0; i < m_option; i++)
			{
				delete arrayMenuItem[i];
			}
			setEmpty();
		}
	}
	// Run Menu
	int Menu::run() const
	{
		display();
		int option;
		bool check;
		if (m_option == 0 || isEmpty())
		{
			option = 0;
			return option;
		}
		do
		{
			cin >> option;
			check = cin.fail();
			cin.clear();
			cin.ignore(1000, '\n');
			if (check)
			{
				cout << "Invalid Integer, try again: ";
			}
			else if (option <= 0 || option > m_option)
			{
				cout << "Invalid selection, try again: ";
			}
		} while (check || option <= 0 || option > m_option);
		return option;
	}
	Menu::operator int() const
	{
		return this->run();
	}
	// Add item in Menu uisng operator<<
	Menu& Menu::operator<<(const char* item)
	{
		add(item);
		return *this;
	}
}
