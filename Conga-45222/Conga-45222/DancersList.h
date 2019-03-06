#ifndef _DANCERS_LIST_
#define _DANCERS_LIST_
#include <assert.h>
#include "Student.h"

// Студентът на позиция last е първият в конга опашката, a този на позиция first е последният в конга опашката.
// Затова при извеждане ги извеждаме от last към first.
//Поради същата причина е реализирана и reverse версия на функцията appendDancers
template <typename T>
class DancersList
{
private:


	class Box
	{
	public:

		T data;
		Box* next;
		Box* prev;

	public:

		Box(const Student& data, Box* nextBox = nullptr, Box* prevBox = nullptr) : data(data), next(nextBox), prev(prevBox) {}
		//bool hasNext() const;

	};

private:

	Box* first;
	Box* last;
	int size;


public:

	DancersList()
	{
		Initialize();
	}

	DancersList(const DancersList& dancers)
	{
		Initialize();
		appendDancers(dancers);
	}

	DancersList& operator=(const DancersList& dancers)
	{
		if (this != &dancers)
		{
			destroyDancersChain(first);
			Initialize();
			appendDancers(dancers);
		}
		return *this;
	}

	~DancersList()
	{
		destroyDancersChain(first);
		Initialize();
	}

	bool isEmpty()const
	{
		return size == 0;
	}

	const T& getFirst()const
	{
		return first->data;
	}

	const T& getLast()const
	{
		return last->data;
	}

	int getSize()const
	{
		return size;
	}

	bool appendDancers(const DancersList& dancers)
	{
		if (dancers.isEmpty())
		{
			return true;
		}

		Box* newStart;
		Box* newEnd;
		copyDancersChain(dancers.first, newStart, newEnd);

		if (first == nullptr)
		{
			first = newStart;
			first->prev = nullptr;
		}
		else
		{
			last->next = newStart;
			newStart->prev = last;
		}
		last = newEnd;
		last->next = nullptr;

		size += dancers.size;

		return newStart != nullptr;
	}

	bool checkStudents(const T& frontStudent, const T& backStudent)
	{
		if (frontStudent.getUniversity()!= nullptr && backStudent.getUniversity() != nullptr)
		{
			if (strcmp(frontStudent.getUniversity(), "fmi") == 0)
			{
				return ((strcmp(backStudent.getUniversity(), "fmi") == 0) || (strcmp(backStudent.getUniversity(), "tu") == 0));
			}
			else if (strcmp(frontStudent.getUniversity(), "tu") == 0)
			{
				return (strcmp(backStudent.getUniversity(), "tu") == 0 || strcmp(backStudent.getUniversity(), "unss") == 0);
			}
			else if (strcmp(frontStudent.getUniversity(), "unss") == 0)
			{
				return (strcmp(backStudent.getUniversity(), "unss") == 0 || strcmp(backStudent.getUniversity(), "fmi") == 0);
			}
		}
		return false;
	}



	bool reversedAppendDancers(const DancersList& dancers)
	{
		if (dancers.isEmpty())
		{
			return true;
		}

		Box* newStart;
		Box* newEnd;
		copyDancersChain(dancers.first, newStart, newEnd);

		newEnd->next = first;
		first->prev = newEnd;
		first = newStart;
		size += dancers.size;

		return newStart != nullptr;
	}

	void removeFirst()
	{
		if (!isEmpty())
		{
			Box* tempOld = first;
			first = first->next;
			if (first != nullptr)
			{
				first->prev = nullptr;
			}
			if (first == nullptr)
			{
				last = nullptr;
			}
			--size;
			delete tempOld;
		}

	}

	void removeLast()
	{
		if (!isEmpty())
		{
			Box* deleteBox = last;
			last = deleteBox->prev;
			if (last != nullptr)
			{
				last->next = nullptr;
			}
			if (last == nullptr)
			{
				first = nullptr;
			}
			--size;
			delete deleteBox;
		}

	}

	void removeAt(int index)
	{
		if (index >= size)
		{
			throw std::out_of_range("The number of elements is less than the index!");
		}

		if (index == 0)
		{
			removeFirst();
		}

		else
		{
			Box* deleteBox = findBoxAtIndex(index);
			assert(previousBox != nullptr);
			Box* previousBox = deleteBox->prev;
			Box* nextBox = deleteBox->next;
			if (index == size - 1)
			{
				last = previousBox;
			}
			previousBox->next = nextBox;
			if (index != size - 1)
			{
				nextBox->prev = previousBox;
			}
			delete deleteBox;
			--size;
		}
	}

	DancersList* removeStudent(const char* name)
	{
		if (name != nullptr && !isEmpty())
		{
			if (strcmp(name, first->data.getName()) == 0)
			{
				removeFirst();
				return nullptr;
			}
			else if (strcmp(name, last->data.getName()) == 0)
			{
				removeLast();
				return nullptr;
			}
			else 
			{
				Box* currentBox = first;
				while (currentBox->next != nullptr)
				{
					if (strcmp(currentBox->data.getName(), name) == 0)
					{	
						DancersList* newQueue;
						Box* nextBox = currentBox->next;
						Box* previousBox = currentBox->prev;
						if (checkStudents(previousBox->data, nextBox->data))
						{
							previousBox->next = nextBox;
							nextBox->prev = previousBox;
							--size;
							return nullptr;
						}
						else
						{
							Box* newFirst = first;
							newFirst->prev = nullptr;
							Box* newLast = currentBox->prev;
							newLast->next = nullptr;
							first = currentBox->next;
							first->prev = nullptr;
							size = findSize(first);
							newQueue = new DancersList();
							newQueue->first = newFirst;
							newQueue->last = newLast;
							newQueue->size = findSize(newFirst);
						}
						delete currentBox;
						return newQueue;
					}
					currentBox = currentBox->next;
				}
			}
			return nullptr;
		}
	}

	bool addTail(const T& data)
	{
		Box* newTail = new Box(data);
		if (newTail != nullptr)
		{
			if (isEmpty())
			{
				first = newTail;
				last = newTail;
			}
			else
			{
				last->next = newTail;
				newTail->prev = last;
				last = newTail;
			}
			++size;
		}
		return newTail != nullptr;
	}

	void addHead(const T& data)
	{
		Box* newHead = new Box(data, first);
		if (isEmpty())
		{
			last = newHead;
			first = newHead;
			first->prev = last->next = nullptr;
		}
		else
		{
			first->prev = newHead;
			first = newHead;
			first->prev = nullptr;
		}
		++size;
	}
	
	

	Box* findBoxAtIndex(int idx)
	{
		if (idx < 0 || idx >= size)
		{
			return nullptr;
		}
		Box* itBox = first;

		for (int i = 0; i < idx; ++i)
		{
			itBox = itBox->next;
		}

		return itBox;
	}

	void printDancers() const
	{
		Box* printBox = last;
		while (printBox != nullptr)
		{
			std::cout << "(" << printBox->data.getName() << ", " << printBox->data.getUniversity() << ") ";
			printBox = printBox->prev;
		}
		std::cout << std::endl;
	}

private:

	static void destroyDancersChain(Box* firstBox)
	{
		Box* deleteBox = firstBox;
		Box* currentBox = firstBox;

		while (currentBox != nullptr)
		{
			deleteBox = currentBox;
			currentBox = currentBox->next;
			delete deleteBox;
		}
	}

	int findSize(Box* firstBox)
	{
		Box* itBox = firstBox;
		int tempSize = 0;
		while (itBox != nullptr)
		{
			++tempSize;
			itBox = itBox->next;
		}
		return tempSize;
	}

	static void copyDancersChain(Box* firstBox, Box*& copyStart, Box*& copyEnd)
	{
		copyStart = nullptr;
		copyEnd = nullptr;

		if (firstBox == nullptr)
		{
			return;
		}

		Box* newDancers = nullptr;
		try
		{
			newDancers = new Box(firstBox->data);
			Box* readBox = firstBox->next;
			Box* writeBox = newDancers;
			while (readBox != nullptr)
			{
				writeBox->next = new Box(readBox->data);
				writeBox->next->prev = writeBox;
				writeBox = writeBox->next;
				readBox = readBox->next;
			}

			copyStart = newDancers;
			copyEnd = writeBox;
		}
		catch (std::bad_alloc& e)
		{
			destroyDancersChain(newDancers);
		}
	}

	void Initialize()
	{
		first = last = nullptr;
		size = 0;
	}


	/*static Box* findLastBox(Box* firstBox)
	{
		if (firstBox != nullptr)
		{
			Box* it = firstBox;
			while (it->next != nullptr)
			{
				it = it->next;
			}
			return it;
		}
		return nullptr;
	}*/

};


#endif // _DANCERS_LIST_INCLUDED
