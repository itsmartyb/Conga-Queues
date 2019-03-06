#include "Menu.h"
#include <iostream>
#include "DancersList.h"
#include "QueueArray.h"

const int MAX_LENGTH = 24; //Максимална дължина на команда/име на студент
// Понеже first е последният студент в конга опашката, а last е първият,
// при премахване на последният, викаме removeFirst(), а при премахване на първият - removeLast()
// Съответно при добавяне на нов студент, го добавяме в края на опашката, което означава first за структурата.
//По същия начин става и сливането чрез reverse версията на appendDancers, за да се спази логиката first да е последният, а last да е първият.

bool checkStudents(const char* firstUni, const char* secondUni)
{
	if (firstUni != nullptr && secondUni != nullptr)
	{
		if (strcmp(firstUni, "fmi") == 0)
		{
			return ((strcmp(secondUni, "fmi") == 0) || (strcmp(secondUni, "tu") == 0));
		}
		else if (strcmp(firstUni, "tu") == 0)
		{
			return (strcmp(secondUni, "tu") == 0 || strcmp(secondUni, "unss") == 0);
		}
		else if (strcmp(firstUni, "unss") == 0)
		{
			return (strcmp(secondUni, "unss") == 0 || strcmp(secondUni, "fmi") == 0);
		}
	}
	return false;
}

void addDancer(const char* name, const char* university, int index, QueueArray<DancersList<Student>>& dancerQueues)
{
	if (name != nullptr && university != nullptr)
	{
		if (checkStudents(university, dancerQueues.getAt(index).getFirst().getUniversity()))
		{
			Student newStudent(name, university);
			dancerQueues.getAt(index).addHead(newStudent);
			std::cout << "Successfully added " << "(" << newStudent.getName() << ", "
					  << newStudent.getUniversity() << 
				 ") " << "to Line:" << index << "\n";
		}
		else
		{
			std::cout << "Incompatible people!\n";
		}
	}
}

void removeLastDancer(int index, QueueArray<DancersList<Student>>& dancerQueues)
{
	dancerQueues.getAt(index).removeFirst();
	if (dancerQueues.getAt(index).isEmpty())
	{
		dancerQueues.getAt(index) = dancerQueues.getAt(dancerQueues.getSize() - 1);
		dancerQueues.removeAt(dancerQueues.getSize() - 1);
	}
	std::cout << "Successfully removed last student from line " << index << std::endl;
}

void removeFirstDancer(int index, QueueArray<DancersList<Student>>& dancerQueues)
{
	dancerQueues.getAt(index).removeLast();
	if (dancerQueues.getAt(index).isEmpty())
	{	
		dancerQueues.getAt(index) = dancerQueues.getAt(dancerQueues.getSize() - 1);
		dancerQueues.removeAt(dancerQueues.getSize() - 1);
	}
	std::cout << "Successfully removed first student from line " << index << std::endl;
}

void mergeQueues(QueueArray<DancersList<Student>>& dancerQueues, int firstIndexQueue, int secondIndexQueue)
{
	if (checkStudents(dancerQueues.getAt(secondIndexQueue).getLast().getUniversity(),
		dancerQueues.getAt(firstIndexQueue).getFirst().getUniversity()))
	{	
		dancerQueues.getAt(firstIndexQueue).reversedAppendDancers(dancerQueues.getAt(secondIndexQueue));
		dancerQueues.getAt(secondIndexQueue) = dancerQueues.getAt(dancerQueues.getSize() - 1);
		dancerQueues.removeAt(dancerQueues.getSize() - 1);
		std::cout << "Successfully chained queues in positions " << firstIndexQueue << " and " << secondIndexQueue << "\n";
	}
	else
	{
		std::cout << "Incompatible people\n";
	}

}

void removeDancer(QueueArray<DancersList<Student>>& dancerQueues, int queueIndex, const char* studentName)
{
	DancersList<Student>* newQueue = dancerQueues.getAt(queueIndex).removeStudent(studentName);
	if (newQueue != nullptr)
	{
		dancerQueues.pushBack(*newQueue);
	}
	delete newQueue;
	std::cout << "Successfully removed student " << studentName << " from line " << queueIndex << std::endl;
}

void Menu()

{
	QueueArray<DancersList<Student>> dancerQueues(5);
	DancersList<Student> dancers;
	Student integralcho("Integralcho", "fmi");
	dancers.addHead(integralcho);
	dancerQueues.pushBack(dancers);
	do
	{

		std::cout << "Choose a command: ";
		std::cout << "append/removeLast/removeFirst/merge/removeStudent/print\n";
		char buffer[MAX_LENGTH];
		std::cin.getline(buffer, MAX_LENGTH);
		if (strcmp(buffer, "append") == 0)
		{
			char studentName[MAX_LENGTH];
			std::cout << "Name:";
			std::cin.getline(studentName, MAX_LENGTH);
			char universityName[MAX_LENGTH];
			std::cout << "University:";
			std::cin.getline(universityName, MAX_LENGTH);
			int queueIndex;
			std::cout << "Lineindex:";
			std::cin >> queueIndex;
			addDancer(studentName, universityName, queueIndex, dancerQueues);
			std::cin.ignore();
		}
		else if (strcmp(buffer, "removeLast") == 0)
		{
			int queueIndex;
			std::cout << "Lineindex:";
			std::cin >> queueIndex;
			removeLastDancer(queueIndex, dancerQueues);
			std::cin.ignore();
		}
		else if (strcmp(buffer, "removeFirst") == 0)
		{
			int queueIndex;
			std::cout << "Lineindex:";
			std::cin >> queueIndex;
			removeFirstDancer(queueIndex, dancerQueues);
			std::cin.ignore();
		}
		else if (strcmp(buffer, "merge") == 0)
		{
			int firstQueueIndex, secondQueueIndex;
			std::cout << "Lineindex1:";
			std::cin >> firstQueueIndex;
			std::cout << "Lineindex2:";
			std::cin >> secondQueueIndex;
			mergeQueues(dancerQueues, firstQueueIndex, secondQueueIndex);
			std::cin.ignore();
		}
		else if (strcmp(buffer, "removeStudent") == 0)
		{
			char name[MAX_LENGTH];
			std::cout << "Name:";
			std::cin.getline(name, MAX_LENGTH);
			int queueIndex;
			std::cout << "Lineindex:";
			std::cin >> queueIndex;
			removeDancer(dancerQueues, queueIndex, name);
			std::cin.ignore();
		}
		else if (strcmp(buffer, "print") == 0)
		{
			dancerQueues.printElems();
		}
		else if (strcmp(buffer, "quit") == 0)
		{
			break;
		}
	} while (true);
}