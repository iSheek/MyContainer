#pragma once

template <typename T>
class MyVector
{
private:
	size_t _size;
	size_t _capacity;

	T* _data;
public:
	MyVector() : _size(0), _capacity(4), _data(new T[4]) {}
	MyVector(std::initializer_list<T> l) : _size(l.size()), _capacity(2 * l.size()), _data(new T[2 * l.size()])
	{
		T* it = _data;
		for (const auto& value : l)
		{
			*it = value;
			++it;
		}
	}

	// destructor
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

	T* begin()
	{
		return this->_data;
	}

	T* end()
	{
		return this->_data + this->_size;
	}

	const T* begin() const
	{
		return this->_data;
	}

	const T* end() const
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
			while (it < (pos - this->_data))
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


	// copy constructor
	MyVector(const MyVector<T>& other)
	{
		this->_size = other._size;
		this->_capacity = other._capacity;


		this->_data = new T[other._capacity];

		for (size_t it = 0; it < other._size; ++it)
		{
			this->_data[it] = other._data[it];
		}

	}

	// copy assignment constructor
	MyVector<T>& operator=(const MyVector<T>& other)
	{
		if (this == &other) return *this;



		T* newData = new T[other._capacity];

		this->_size = other._size;
		this->_capacity = other._capacity;

		for (size_t it = 0; it < other._size; ++it)
		{
			newData[it] = other._data[it];
		}

		delete[] this->_data;

		this->_data = newData;

		return *this;

	}

	// move constructor
	MyVector(MyVector<T>&& other) noexcept
	{
		this->_capacity = other._capacity;
		this->_size = other._size;
		this->_data = other._data;

		other._data = nullptr;
		other._capacity = 0;
		other._size = 0;

	}

	// move assignment constructor
	MyVector<T>& operator=(MyVector<T>&& other) noexcept
	{
		if (this == &other) return *this;

		this->_capacity = other._capacity;
		this->_size = other._size;


		delete[] this->_data;
		this->_data = other._data;

		other._capacity = 0;
		other._size = 0;
		other._data = nullptr;

		return *this;
	}

	void pop_back()
	{
		if (this->_size == 0) return;

		this->_data[this->_size - 1].~T();
		--this->_size;
	}

	void clear()
	{
		for (size_t it = 0; it < this->_size; ++it)
		{
			this->_data[it].~T();
		}
		this->_size = 0;
	}

	void erase(T* pos)
	{
		++pos;
		while (pos < this->end())
		{
			*(pos - 1) = *pos++;
		}
		this->_data[this->_size - 1].~T();
		--this->_size;
	}

	T& front()
	{
		return this->_data[0];
	}

	const T& front() const
	{
		return this->_data[0];
	}

	T& back()
	{
		return this->_data[this->_size - 1];
	}

	const T& back() const
	{
		return this->_data[this->_size - 1];
	}

	T* data()
	{
		return this->_data;
	}

	const T* data() const
	{
		return this->_data;
	}

	bool empty() const
	{
		return this->_size == 0;
	}

	void reserve(size_t newCap)
	{
		if (newCap <= this->_capacity) return;



		T* newData = new T[newCap];

		for (size_t it = 0; it < this->_size; ++it)
		{
			newData[it] = this->_data[it];
		}

		delete[] this->_data;
		this->_capacity = newCap;
		this->_data = newData;
	}

	void shrink_to_fit()
	{
		if (this->_capacity <= this->_size) return;

		T* newData = new T[this->_size];

		for (size_t it = 0; it < this->_size; ++it)
		{
			newData[it] = this->_data[it];
		}

		delete[] this->_data;
		this->_capacity = this->_size;
		this->_data = newData;

	}




};