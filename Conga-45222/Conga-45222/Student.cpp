#include "Student.h"
#include <iostream>
#include <assert.h>

Student::Student() : name(nullptr), university(nullptr) {}

Student::Student(const char* sName, const char* sUniversity) : name(nullptr), university(nullptr)
{
	int lenName = strlen(sName) + 1;
	int lenUniversity = strlen(sUniversity) + 1;
	try
	{
		name = new char[lenName];
		strcpy_s(name, lenName, sName);
		university = new char[lenUniversity];
		strcpy_s(university, lenUniversity, sUniversity);

	}
	catch (std::bad_alloc& e)
	{
		cleanStudent();
		std::cerr << "Not enough memory for name/university\n";
		throw;
	}
}

Student::Student(const Student& s) : name(nullptr), university(nullptr)
{
	try
	{
		copyStudent(s);
	}
	catch (std::bad_alloc& e)
	{
		cleanStudent();
		throw;
	}
}


Student::~Student()
{
	cleanStudent();
}

const char* Student::getName() const
{
	return name;
}

const char* Student::getUniversity() const
{
	return university;
}

void Student::copyStudent(const Student& s)
{
	int lenName = strlen(s.name) + 1;
	int lenUniversity = strlen(s.university) + 1;

	name = new(std::nothrow) char[lenName];
	if (!name)
	{
		std::cerr << "Not enough memory for the name\n";
		throw std::bad_alloc();
	}
	strcpy_s(name, lenName, s.name);
	university = new (std::nothrow) char[lenUniversity];
	if (!university)
	{
		std::cerr << "Not enough memory for the university\n";
		throw std::bad_alloc();
	}
	strcpy_s(university, lenUniversity, s.university);

}

Student& Student::operator=(const Student& s)
{
	if (this != &s)
	{
		cleanStudent();
		copyStudent(s);
	}
	return *this;
}

void Student::cleanStudent()
{
	delete[] name;
	delete[] university;
	name = university = nullptr;
}

