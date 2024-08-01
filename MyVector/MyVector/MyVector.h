#include <iostream>
#include <initializer_list>
#pragma once
template<typename Typedata>
class MyVector
{
private:
	Typedata* data;
	size_t size;
	size_t capacity;
	
public:

	MyVector();
	MyVector(Typedata First, Typedata Last);
	MyVector(std::initializer_list<Typedata> iniList);
	MyVector(Typedata* data);
	MyVector(MyVector&& other);
	~MyVector();

	size_t MySize() const;
	size_t Capacity() const;
	MyVector<Typedata>& push_back(Typedata data);
	MyVector<Typedata>& pop_back();
	MyVector<Typedata>& erase(Typedata* First, Typedata* Last);
	MyVector<Typedata>& insert(Typedata* pos, const Typedata& value);
	Typedata* find(Typedata value);//ищет элемент и возрощает ссылку элемента
	Typedata& at(size_t index);//возрощает элемент под индексом
	const Typedata& at(size_t index) const;//возрощает элемент под индексом но для const
	Typedata* begin();
	Typedata* end();
	Typedata front();
	const Typedata front() const;
	Typedata back();
	const Typedata back() const;
	Typedata*  getdata();
	const Typedata* getdata() const;
	const Typedata* begin() const;
	const Typedata* end() const;
	Typedata* rbegin(); //{ return data + size - 1; }
	Typedata* rend(); //{ return data - 1; }
	const Typedata* rbegin() const; //{ return data + size - 1; }
	const Typedata* rend() const; //{ return data - 1; }
	void clear();
	void recapacity(size_t newCapacity);
	void resize(size_t newSize);//cheki 
	const void resize(size_t newSize) const;
	void sort(size_t value, Typedata* first, Typedata* last);//Сортирует контейнер value определяет метод сортировки
	const void sort(size_t value, const Typedata* first, const Typedata* last) const;//Сортирует контейнер value определяет метод сортировки но для константы
	void swap(MyVector& other);//обмен содержимого с другим вектором
	void shrink_to_fit();//уменьшение вместимости до текущего размера
	const void shrink_to_fit() const;//уменьшение вместимости для константных контейнеров
	bool empty();

	int& operator [](int index);
	MyVector& operator = (const MyVector& other);

	
};


//Конструкторы и Деструктуры
template<typename Typedata>
inline MyVector<Typedata>::MyVector()
{
	this->data = nullptr;
	this->size = 0;
	this->capacity = 0;
}

template<typename Typedata>
inline MyVector<Typedata>::MyVector(Typedata First, Typedata Last)
{
	if (First < Last || First == Last)
	{
		capacity = size = Last - First + 1;
		data = new Typedata[Last - First + 1];
		int index = 0;
		for (auto i = First; i <= Last; i++)
		{
			data[index++] = i;
			if (true)
			{

			}
		}
	}
	else if (Last < First)
	{
		capacity = size = First - Last + 1;
		data = new Typedata[First - Last + 1];
		size_t index = 0;
		for (auto i = First; i >= Last; i--)
		{
			data[index++] = i;
			if (true)
			{

			}
		}
	}

}

template<typename Typedata>
MyVector<Typedata>::MyVector(std::initializer_list<Typedata> initList)
{
	capacity = size = initList.size();
	data = new Typedata[size];
	size_t i = 0;
	for (const auto& odata : initList)
	{
		data[i++] = odata;
	}
}

template<typename Typedata>
MyVector<Typedata>::MyVector(Typedata* data)
{
	capacity = this->size = size(data);
	data = new Typedata[size];
	for (size_t i = 0; i < this->size; i++)
	{
		this->data[i] = data[i];
	}
}

template<typename Typedata>
MyVector<Typedata>::MyVector(MyVector&& other)
{
	this->data = other.data;
	this->size = other.size;
	this->capacity = other.capacity;
	other.data = nullptr;
}

template<typename Typedata>
MyVector<Typedata>::~MyVector()
{
	delete[] data;
}


//Методы
template<typename Typedata>
size_t MyVector<Typedata>::MySize() const
{
	return size;
}

template<typename Typedata>
inline size_t MyVector<Typedata>::Capacity() const
{
	return capacity;
}

template<typename Typedata>
inline MyVector<Typedata>& MyVector<Typedata>::push_back(Typedata data)
{
	int newSize = this->size + 1;
	Typedata* newData = new Typedata[newSize];
	for (size_t i = 0; i < newSize; i++)
	{
		newData[i] = this->data[i];
		if (i == newSize - 1)
		{
			newData[i] = data;
		}
	}
	delete[] this->data;
	this->size = newSize;
	this->data = newData;
	this->capacity = newSize;
	return *this;
}

template<typename Typedata>
inline MyVector<Typedata>& MyVector<Typedata>::pop_back()
{
	int newSize = this->size - 1;
	Typedata* newData = new Typedata[newSize];
	for (size_t i = 0; i < newSize; i++)
	{
		newData[i] = this->data[i];
	}
	delete[] this->data;
	this->data = newData;
	this->size = newSize;
	this->capacity = newSize;
	return *this;
}

template<typename Typedata>
inline MyVector<Typedata>& MyVector<Typedata>::erase(Typedata* First, Typedata* Last)
{
	if (First == Last) return *this;

	size_t eraseCount = Last - First;
	for (Typedata* p = First; p != data + size - eraseCount; ++p) //выполняет функцию сдвига элементов массива влево, чтобы заполнить пробел, оставленный удаленными элементами
	{
		*p = *(p + eraseCount);
	}
	size -= eraseCount;

	return *this;
}

template<typename Typedata>
inline MyVector<Typedata>& MyVector<Typedata>::insert(Typedata* pos, const Typedata& value)
{
	if (size == capacity) {
		capacity = (capacity == 0) ? 1 : capacity + 1;
		Typedata* newData = new Typedata[capacity];
		size_t index = 0;
		for (Typedata* p = data; p != pos; ++p, ++index)
		{
			newData[index] = *p;
		}
		newData[index++] = value;
		for (Typedata* p = pos; p != data + size; ++p, ++index)
		{
			newData[index] = *p;
		}
		delete[] data;
		data = newData;
		++size;
	}
	else {
		for (Typedata* p = data + size; p != pos; --p) {
			*p = *(p - 1);
		}
		*pos = value;
		++size;
	}

	return *this;
}

template<typename Typedata>
inline void MyVector<Typedata>::resize(size_t newSize)
{
	if (newSize <= size)
	{
		return;
	}

	if (newSize >= capacity)
	{
		Typedata* newData;
		newData = new Typedata[newSize];
		capacity = newSize;
		for (size_t i = 0; i < size; i++)
		{
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		size = newSize;
	}
	else if (newSize < capacity)
	{
		Typedata* newData;
		newData = new Typedata[capacity];
		for (size_t i = 0; i < size; i++)
		{
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		size = newSize;
	}

}

template<typename Typedata>
inline const void MyVector<Typedata>::resize(size_t newSize) const
{
	if (newSize <= size)
	{
		return;
	}
	Typedata* newData;
	if (newSize >= capacity)
	{
		newData = new Typedata[newSize];
		capacity = newSize;
	}
	else if (newSize < capacity)
	{
		newData = new Typedata[capacity];
	}
	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	size = newSize;
}

template<typename Typedata>
inline void MyVector<Typedata>::recapacity(size_t newCapacity)
{
	if (newCapacity <= capacity)
	{
		return;
	}
	Typedata* newData = new Typedata[newCapacity];
	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	capacity = newCapacity;

}

template<typename Typedata>
inline void MyVector<Typedata>::shrink_to_fit()
{
	if (size >= capacity)
	{
		return;
	}
	Typedata* newData = new Typedata[size];
	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	capacity = size;
}

template<typename Typedata>
inline const void MyVector<Typedata>::shrink_to_fit() const
{
	if (size >= capacity)
	{
		return;
	}
	Typedata* newData = new Typedata[size];
	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	capacity = size;
}

template<typename Typedata>
inline void MyVector<Typedata>::swap(MyVector& other)
{
	if (this->capacity < other.szie || other.capacity < other.size)
	{
		return;
	}
	else
	{
		Typedata* temp = new Typedata[this->size];
		for (size_t i = 0; i < this->size; i++)
		{
			temp[i] = this->data[i];
		}
		this->size = other.size;
		for (size_t i = 0; i < other.size; i++)
		{
			this->data[i] = other.data[i];
		}
		other.size = temp.size;
		for (size_t i = 0; i < temp.size; i++)
		{
			other.data[i] = temp.data[i];
		}
		delete[] temp;
	}
}

template<typename Typedata>
inline Typedata* MyVector<Typedata>::find(Typedata value)
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == value)
		{
			return data[i];
		}
	}
	return;
}

template<typename Typedata>
inline Typedata& MyVector<Typedata>::at(size_t index)
{
	if (index >= size)
	{
		return;
	}
	else
	{
		return data[index];
	}
}

template<typename Typedata>
inline const Typedata& MyVector<Typedata>::at(size_t index) const
{
	if (index >= size)
	{
		return;
	}
	else
	{
		return data[index];
	}
}

template<typename Typedata>
inline Typedata* MyVector<Typedata>::begin()
{
	return data;
}

template<typename Typedata>
inline Typedata* MyVector<Typedata>::end()
{
	return data + size;
}

template<typename Typedata>
inline Typedata MyVector<Typedata>::front()
{
	return this->data[0];
}

template<typename Typedata>
inline const Typedata MyVector<Typedata>::front() const
{
	return this->data[0];
}

template<typename Typedata>
inline Typedata MyVector<Typedata>::back()
{
	return this->data[this->size - 1];
}

template<typename Typedata>
inline const Typedata MyVector<Typedata>::back() const
{
	return this->data[this->size - 1];
}

template<typename Typedata>
inline Typedata* MyVector<Typedata>::getdata()
{
	return data;
}

template<typename Typedata>
inline const Typedata* MyVector<Typedata>::getdata() const
{
	return data;
}

template<typename Typedata>
inline const Typedata* MyVector<Typedata>::begin() const
{
	return data;
}

template<typename Typedata>
inline const Typedata* MyVector<Typedata>::end() const
{
	return data + size;
}

template<typename Typedata>
inline Typedata* MyVector<Typedata>::rbegin()
{
	return data + size - 1;;
}

template<typename Typedata>
inline Typedata* MyVector<Typedata>::rend()
{
	return data - 1;
}

template<typename Typedata>
inline const Typedata* MyVector<Typedata>::rbegin() const
{
	return data + size - 1;
}

template<typename Typedata>
inline const Typedata* MyVector<Typedata>::rend() const
{
	return data - 1;
}

template<typename Typedata>
inline void MyVector<Typedata>::clear()
{
	delete[] this->data;
}

template<typename Typedata>
inline void MyVector<Typedata>::sort(size_t value, Typedata* first, Typedata* last)
{
	if (value == 0)
	{
		while (true)
		{
			bool swapped = false;
			for (Typedata* i = first; i < last - 1; i++)
			{
				Typedata second = *(i + 1);
				if (*i > second)
				{
					Typedata temp;
					temp = *i;
					*i = *(i + 1);
					*(i + 1) = temp;
					swapped = true;
				}
			}
			if (swapped == false)
			{
				break;
			}
		}
	}
	else if (value == 1)
	{
		while (true)
		{
			bool swapped = false;
			for (Typedata* i = first; i < last - 1; i++)
			{
				if (*i < *(i + 1))
				{
					Typedata temp;
					temp = *i;
					*i = *(i + 1);
					*(i + 1) = temp;
					swapped = true;
				}
			}
			if (swapped == false)
			{
				break;
			}
		}
	}
	else if (value == 2)
	{
		srand(time(0));
		for (Typedata* i = first; i < last - 1; ++i)
			std::swap(*i, *(first + std::rand() % size));
	}
}

template<typename Typedata>
inline bool MyVector<Typedata>::empty()
{
	return this->data == nullptr;
}


//Перегрузка Операторов
template<typename Typedata>
int& MyVector<Typedata>::operator [] (int index)
{
	return data[index];
}

template<typename Typedata>
MyVector<Typedata>& MyVector<Typedata>::operator = (const MyVector& other)
{
	this->size = other.size;
	this->capacity = other.capacity;
	if (this == &other)
	{
		return *this;
	}
	else if (this->data != nullptr)
	{
		delete[] data;
	}
	this->data = new Typedata[size];
	for (size_t i = 0; i < this->size; i++)
	{
		this->data[i] = other.data[i];
	}
	return *this;
}
