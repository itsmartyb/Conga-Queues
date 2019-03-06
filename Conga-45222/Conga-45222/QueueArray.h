#ifndef _QUEUE_ARRAY_H
#define _QUEUE_ARRAY_H

template <typename T>

class QueueArray {
private:

	T* data;
	int capacity;
	int size;

public:

	QueueArray();
	QueueArray(int);
	~QueueArray();
	QueueArray(const QueueArray&);
	QueueArray<T>& operator=(const QueueArray&);
	void insertAt(int, const T&);
	void removeAt(int);
	void pushBack(const T&);
	void popBack();
	const T& operator[](int) const;
	T& operator[](int);
	int getSize()const;
	int getCapacity()const;
	T& getAt(int);
	//int search(const T&);
	void printElems() const;
	void changeValue(int, const T&);
	void swapQueues(int, int);




private:

	void clean();
	void copy(const QueueArray&);
	void resize(int);
};

template <typename T>
QueueArray<T>::QueueArray() : data(nullptr), capacity(0), size(0) {}

template <typename T>
QueueArray<T>::QueueArray(int capacity) : data(nullptr), size(0), capacity(capacity)
{
	data = new T[capacity];
}

template <typename T>
QueueArray<T>::QueueArray(const QueueArray<T>& other)
{
	copy(other);
}

template <typename T>
QueueArray<T>& QueueArray<T>::operator=(const QueueArray<T>& other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}

	return *this;
}

template <typename T>
QueueArray<T>::~QueueArray()
{
	clean();
}

template <typename T>
void QueueArray<T>::clean()
{
	delete[] data;
	data = nullptr;
	capacity = 0;
	size = 0;

}

template <typename T>
void QueueArray<T>::copy(const QueueArray& other)
{
	data = new T[other.size];
	for (int i = 0; i < other.size; ++i)
	{
		data[i] = other.data[i];
	}
	capacity = other.capacity;
	size = other.size;
}

template <typename T>
void QueueArray<T>::swapQueues(int firstQueue, int secondQueue)
{
	DancersList<Student> temp = data[firstQueue];
	data[firstQueue] = data[secondQueue];
	data[secondQueue] = temp;

}

template <typename T>
void QueueArray<T>::resize(int newCap)
{
	T* temp = data;
	data = new T[newCap];
	for (int i = 0; i < size; ++i)
	{
		data[i] = temp[i];
	}
	capacity = newCap;
	delete[]temp;
}

template <typename T>
void QueueArray<T>::insertAt(int index, const T& elem)
{
	if (index > size)
	{
		return;
	}

	if (size >= capacity)
	{
		int newCap = (capacity == 0 ? 2 : capacity * 2);
		resize(newCap);
	}

	++size;
	for (int i = size - 1; i > index; --i)
	{
		data[i] = data[i - 1];
	}
	changeValue(index, elem);
}

template <typename T>
void QueueArray<T>::changeValue(int index, const T& elem)
{
	if (index >= size)
	{
		return;
	}
	data[index] = elem;
}

template <typename T>
void QueueArray<T>::pushBack(const T& elem)
{
	insertAt(size, elem);
}

template <typename T>
void QueueArray<T>::removeAt(int index)
{
	if (size)
	{
		if (size * 4 < capacity)
		{
			int newCap = (capacity == 0 ? 0 : capacity / 2);
			resize(newCap);
		}
		for (int i = index; i < size - 1; ++i)
		{
			data[i] = data[i + 1];
		}
		--size;
	}
	else
	{
		return;
	}
}

template <typename T>
void QueueArray<T>::popBack()
{
	if (size)
	{
		removeAt(size - 1);
	}
	else
	{
		return;
	}

}

template <typename T>
const T& QueueArray<T>::operator[](int pos) const
{
	return data[pos];
}

template <typename T>
T& QueueArray<T>::operator[](int pos)
{

	return const_cast<T&>(static_cast<const QueueArray&>(*this)[pos]);
}

template <typename T>
T& QueueArray<T>::getAt(int index)
{
	if (index >= size)
	{
		throw std::out_of_range("Index is out of range");
	}
	return data[index];
}


template <typename T>
int QueueArray<T>::getSize()const {

	return size;
}

template <typename T>
int QueueArray<T>::getCapacity()const {

	return capacity;
}

/*template <typename T>
int QueueArray<T>::search(const T& elem)
{
	for (int i = 0; i < size; ++i)
	{
		if (data[i] == elem)
		{
			return i;
		}
	}
	return -1;
}*/

template <typename T>
void QueueArray<T>::printElems()const {

	for (int i = 0; i < size; i++)
	{
		std::cout << "Line" << i << ": ";
		data[i].printDancers();
	}

	std::cout << std::endl;

}


#endif // QUEUE_ARRAY_H_INCLUDED

