#include <iostream>
#include <vector>
#include <array>

template <typename T>
class MyVector
{
private:
	size_t _size;
	size_t _capacity;

	T* _data;
public:
	MyVector() : _size(0), _capacity(4), _data(new T[4]) {}
	MyVector(std::initializer_list<T> l) : _size(l.size()), _capacity(2 * l.size()), _data(new T[2*l.size()])
	{
		T* it = _data;
		for (const auto& value : l)
		{
			*it = value;
			++it;
		}
	}
	~MyVector()
	{
		delete[] this->_data;
	}

	void push_back(const T& value)
	{
		if (this->_size >= this->_capacity)
		{
			T* newData = new T[2 * _capacity];
			for (size_t it = 0; it < this->_size; ++it)
			{
				newData[it] = this->_data[it];
			}
			delete[] this->_data;
			this->_capacity *= 2;
			this->_data = newData;
		}

		this->_data[this->_size] = value;
		++this->_size;

	}

	T& operator[](size_t index)
	{
		return this->_data[index];
	}

	const T& operator[](size_t index) const
	{
		return this->_data[index];
	}

	T* begin() const
	{
		return this->_data;
	}

	T* end() const
	{
		return this->_data + this->_size;
	}

	size_t size() const
	{
		return this->_size;
	}

	size_t capacity() const
	{
		return this->_capacity;
	}

	template <typename InputIt>
	void insert(T* pos, InputIt first, InputIt last)
	{
		auto elementToAddSize = last - first;

		if (elementToAddSize > (this->_capacity - this->_size))
		{
			
			auto newCapacity = 2 * (this->_capacity + elementToAddSize);
			T* newData = new T[newCapacity];
			size_t it = 0;
			while (it < (pos-this->_data))
			{
				newData[it] = this->_data[it];
				++it;
			}

			auto oldDataIt = it;

			size_t firstIt = 0;
			auto toLoop = it + elementToAddSize;

			while (it < toLoop)
			{
				newData[it++] = first[firstIt++];
			}

			while (oldDataIt < this->size())
			{
				newData[it++] = this->_data[oldDataIt++];
			}
			delete[] this->_data;

			this->_data = newData;
			this->_capacity = newCapacity;
			this->_size += elementToAddSize;

		}
		else
		{
			size_t insertIndex = pos - this->begin();

			for (size_t i = this->_size; i > insertIndex; --i)
			{
				this->_data[i - 1 + elementToAddSize] = this->_data[i - 1];
			}


			while (first < last)
			{
				this->_data[insertIndex++] = *first;
				++first;
			}
			
			this->_size += elementToAddSize;
		}

	}

};




int main()
{

	MyVector<int> vec = { 1, 2, 5, 6 };

	std::array<int, 2> arr = { 1,2 };
	
	vec.insert(vec.begin() + 2, arr.begin(), arr.end());

	for (auto v : vec)
	{
		std::cout << v << std::endl;
	}


	return 0;
}