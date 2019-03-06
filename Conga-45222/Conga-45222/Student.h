#ifndef _STUDENT_HEADER_
#define _STUDENT_HEADER_
#include <iostream>

class Student
{
private:

	char* name;
	char* university;

public:

	Student();
	Student(const char*, const char*);
	Student(const Student&);
	Student& operator=(const Student&);
	~Student();
	const char* getName()const;
	const char* getUniversity()const;
	/*friend std::ostream& operator<<(const Student& student, std::ostream& out)
	{
		out << "(" << student.getName() << "," << student.getUniversity() << ")";
	}*/

private:

	void copyStudent(const Student&);
	void cleanStudent();
};


#endif // _STUDENT_HEADER_INCLUDED