/***********************************************************************
* Header:
*    QUEUE
* Summary:
*    This will contain the class definition of:
*        Queue         : A class that represents a queue
* Author
*    Scott Tolman
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

//#include <cassert>

namespace custom
{

	/*****************************************
	* QUEUE
	* Just like the std :: queue <T> class
	****************************************/
	template <class T>
	class queue
	{
	public:
		queue()
		{
			data = NULL;
			capacity = 0;
			numPop = 0;
			numPush = -1;
		}
		queue(int capacity) : data(NULL), capacity(0), numPop(0), numPush(-1)
		{
			if (capacity > 0)
				resize(capacity);
		}
		queue(queue & rhs) : data(NULL), capacity(0), numPop(0), numPush(-1)
		{
			if (rhs.capacity > 0)
			{
				resize(rhs.capacity);
				*this = rhs;
			}
		}
		~queue() { if (size() != 0) delete[] data; }
		void 		push(const T & t) throw (const char *);
		void 		pop();
		T & 		front() throw (const char *);
		T 			front() const throw (const char *);
		T &         back() throw (const char *);
		T           back() const throw (const char *);
		queue <T> & operator = (const queue <T> & rhs) throw (const char *);
		int 		size() const { return numPush - numPop + 1; }
		bool 		empty() const { return size() == 0; }
		void 		clear() { numPop = 0; numPush = -1; }
	private:
		void        resize(int newCapacity) throw(const char *);
		int         iHead() const { return numPop % capacity; }
		int         iTail() const { return numPush % capacity; }

		T * data;
		int capacity;
		int numPop;
		int numPush;
	};
	template<class T>
	void queue<T>		  ::push(const T & t) throw(const char *)
	{
		if (capacity == 0)
		{
			resize(1);
		}
		else if (capacity == size())
			resize(capacity * 2);
		numPush++;
		data[iTail()] = t;
	}
	template<class T>
	void queue<T>		  ::pop()
	{
		if (size() > 0)
		{
			numPop++;
		}
	}
	template<class T>
	T & queue<T>		  ::front() throw(const char *)
	{
		if (size() < 1)
			throw "ERROR: attempting to access an element in an empty queue";
		return data[iHead()];

	}
	template<class T>
	T queue<T>			  ::front() const throw(const char *)
	{
		if (size() < 1)
			throw "ERROR: attempting to access an element in an empty queue";
		return data[iHead()];
	}
	template<class T>
	T & queue<T>		  ::back() throw(const char *)
	{
		if (size() < 1)
			throw "ERROR: attempting to access an element in an empty queue";
		return data[iTail()];
	}
	template<class T>
	T queue<T>			  ::back() const throw(const char *)
	{
		if (size() < 1)
			throw "ERROR: attempting to access an element in an empty queue";
		return data[iTail()];
	}
	template<class T>
	queue<T>& queue<T>	  ::operator= (const queue<T>& rhs) throw(const char *)
	{
		numPush = -1;
		numPop = 0;
		if (capacity < rhs.size())
			resize(rhs.size());
		for (int i = 0; i < rhs.size(); i++)
			push(rhs.data[(rhs.iHead() + i) % rhs.capacity]);
		return *this;
	}
	template<class T>
	void queue<T>::resize(int newCapacity) throw(const char *)
	{
		T * temp;
		try
		{
			temp = new T[newCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for queue";
		}
		for (int i = 0; i < size(); i++)
			temp[i] = data[(iHead() + i) % capacity];
		if (data != NULL)
			delete [] data;
		data = temp;
		numPush = size() - 1;
		numPop = 0;
		capacity = newCapacity;
	}
}

#endif //QUEUE_H