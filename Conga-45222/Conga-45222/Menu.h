#ifndef _MENU_HEADER_
#define _MENU_HEADER_
#include "DancersList.h"
#include "QueueArray.h"


void Menu();
void addDancer(const char*, const char*, int, QueueArray<DancersList<Student>>&);
void removeLastDancer(int, QueueArray<DancersList<Student>>&);
void printQueues(const QueueArray<DancersList<Student>>&);
void mergeQueues(QueueArray<DancersList<Student>>&, int, int);
bool checkStudents(const char*, const char*);
void removeDancer(QueueArray<DancersList<Student>>&, int, const char*);



#endif // _MENU_HEADER_INCLUDED
