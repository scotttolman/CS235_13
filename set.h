/***********************************************************************
 * Header File
 *    This is the header file for a "set" container
 * Summary:
 *     This will contain the class definition of:
 *		Set         : A class that represents a set
 * Author:
 *    Mark Baldwin and Scott Tolman
 ************************************************************************/

#pragma once

#include <cassert> // For Assert


template <class T>
    class set
{
    public:

    //Constructors and Destructor
    set <T>() { numElements = 0; numCapacity = 0; data = NULL; };        // Default Constructor
    set <T>(int num) throw (const char *);								 // Non-Default Constructor
    set <T>(const set & rhs) throw (const char *);						 // Copy Constructor
    ~set() { if (data != NULL) delete[] data; }                          // Destructor
    set<T>& operator= (const set<T>& rhs) throw (const char *);          // Operator =
    set<T>& operator|| (const set<T>& rhs) throw(const char *);	 // Operator || for Union 
    set<T>& operator&& (set<T>& rhs) throw(const char *);	 // Operator && for Intersection


    //General  Methods
    bool empty() const;
    int size() const;
    void clear();
		
    //Iterator methods
    class iterator;
    iterator begin() { return iterator(data); }
    iterator  end();
    iterator find(T userValue);
    void erase(iterator toErase);
    void insert( T userInput) throw (const char *);








	class const_iterator;
	const_iterator cbegin() { return const_iterator(data); }
	const_iterator  cend();









    private:

    T * data;					

    int numCapacity;
    int capacity;
    int numElements;
		
    // Private methods
    void resize(int newCapacity) throw (const char *);
    void slideRight(int indexPostition);
    void slideLeft(int indexPostition);
};











	/**************************************************
	* SET ITERATOR
	* An const_iterator through set
	*************************************************/
	template <class T>
	class set <T> ::const_iterator
	{
	public:
		// constructors, destructors, and assignment operator
		const_iterator() : p(NULL) {              }
		const_iterator(T * p) : p(p) {              }
		const_iterator(const const_iterator & rhs) { *this = rhs; }
		const_iterator & operator = (const const_iterator & rhs)
		{
			this->p = rhs.p;
			return *this;
		}

		// equals, not equals operator
		bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
		bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

		// dereference operator
		T & operator * () { return *p; }
		const T & operator * () const { return *p; }

		// prefix increment
		const_iterator & operator ++ ()
		{
			p++;
			return *this;
		}

		// postfix increment
		const_iterator operator ++ (int postfix)
		{
			const_iterator tmp(*this);
			p++;
			return tmp;
		}

	private:
		T * p;
	};

	/********************************************
	* SET :: END
	* Note that you have to use "typename" before
	* the return value type
	********************************************/
	template <class T>
	typename set <T>::const_iterator set <T>::cend()
	{
		return const_iterator(data + numElements);
	}









/**************************************************
* SET ITERATOR
* An iterator through set
*************************************************/
template <class T>
    class set <T> ::iterator
{
    public:
    // constructors, destructors, and assignment operator
    iterator() : p(NULL) {              }
    iterator(T * p) : p(p) {              }
    iterator(const iterator & rhs) { *this = rhs; }
    iterator & operator = (const iterator & rhs)
        {
        this->p = rhs.p;
        return *this;
        }

    // equals, not equals operator
    bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
    bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

    // dereference operator
    T & operator * () { return *p; }
    const T & operator * () const { return *p; }

    // prefix increment
    iterator & operator ++ ()
    {
        p++;
        return *this;
    }

    // postfix increment
    iterator operator ++ (int postfix)
    {
        iterator tmp(*this);
        p++;
        return tmp;
    }

    private:
    T * p;
};

/********************************************
* SET :: END
* Note that you have to use "typename" before
* the return value type
********************************************/
template <class T>
    typename set <T>::iterator set <T>::end()
{
    return iterator(data + numElements);
}

/********************************************
* SET :: FIND
* Note that you have to use "typename" before
* the return value type
********************************************/
template<class T>
    typename set<T>::iterator set<T>::find(T userValue)
{
    for (set<T> ::iterator it = begin(); it != end(); ++it)
    {
        if (userValue == *it)
        return it;
    }

    return end();
}

/********************************************
* SET :: ERASE
* Note that you have to use "typename" before
* the return value type
********************************************/
template<class T>
    void set<T>::erase(iterator toErase)
{
    int index = 0;

    for (set<T> ::iterator it = begin(); it != end(); ++it)
    {
        if (*toErase == *it)
        break;
        else
        index++;
    }

    slideLeft(index);
    this->numElements--;
}

/********************************************
* SET :: INSERT
* Note that you have to use "typename" before
* the return value type
********************************************/
template<class T>
    void set<T>::insert(T userInput)
    throw (const char *)
{

    int index = 0;

    for (set<T> ::iterator it = begin(); it != end(); ++it)
    {
        if (userInput == *it)
        return;
        else if (userInput < *it)
        break;
        else
        index++;
    }
		
    resize(numElements + 1);
		
    if (index < numElements)
        slideRight(index);
		
    this->data[index] = userInput;
    this->numElements++;
		
}



/**********************************************
* SET : NON-DEFAULT CONSTRUCTOR
* Preallocate the set to "capacity"
**********************************************/
template <class T>
    set <T> ::set(int num) throw (const char *)
{
    assert(num >= 0);

    this->numElements = 0;
    // do nothing if there is nothing to do.
    // since we can't grow an array, this is kinda pointless
    if (num == 0)
    {
        this->numCapacity = 0;
        this->data = NULL;
        return;
    }

    // attempt to allocate
    try
    {
        data = new T[num];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }


    // copy over the stuff
    this->numCapacity = num;
}




/*******************************************
* SET :: COPY CONSTRUCTOR
*******************************************/
template <class T>
    set <T> ::set(const set <T> & rhs) throw (const char *)
{
    assert(rhs.numElements >= 0);

    // do nothing if there is nothing to do
    if (rhs.numElements == 0)
    {
        numElements = 0;
        data = NULL;
        return;
    }

    // attempt to allocate
    try
    {
        data = new T[rhs.numElements];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }


    // copy over the capacity
    numElements = rhs.numElements;
    numCapacity = numElements;

    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < numElements; i++)
        data[i] = rhs.data[i];

}

/**********************************************
* SET : ASSIGNMENT OPERATOR =
* Copy one set into another
**********************************************/
template <class T>
    set<T>& set<T> :: operator= (const set<T>& rhs)
    throw (const char *)
    {
        this->resize(rhs.size());
        for (int i = 0; i < rhs.size(); i++)
        data[i] = rhs.data[i];

        this->numElements = rhs.size();

        return *this;
    }

/**********************************************
* SET : ASSIGNMENT OPERATOR ||
* Copy one set into another
**********************************************/
template <class T>
    set<T>& set<T> :: operator|| (const set<T>& rhs) 
    throw (const char *)
{

    set<T> *s = new set<T>(*this);

    for (int i = 0; i < rhs.numElements; i++)
    {
        // insert all elements that are in rhs that are different
        s->insert(rhs.data[i]);
    }
		
    return *s;
}

/**********************************************
* SET : ASSIGNMENT OPERATOR &&
* Copy one set into another
**********************************************/
template <class T>
    set<T>& set<T> :: operator&& (set<T>& rhs) 
    throw (const char *)
{
		
    set<T> *s = new set<T>();

    iterator lhsIT = this->begin();
    iterator rhsIT = rhs.begin();

    while (lhsIT != this->end() && rhsIT != rhs.end())
    {
        if (*lhsIT == *rhsIT)
        {
        s->insert(*lhsIT);
        lhsIT++;
        rhsIT++;
        }
        else if (*lhsIT < *rhsIT)
        lhsIT++;
        else if (*lhsIT > *rhsIT)
        rhsIT++;
    }
			
    return *s;
}



/**********************************************
* SET : RESIZE
* Resize set to new capacity
**********************************************/
template<class T>
    void set<T>::resize(int newCapacity) throw(const char *)
{
    T * temp;
    try
    {
        temp = new T[newCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for set";
    }
		
    for (int i = 0; i < size(); i++)
        temp[i] = data[i];
    if (data != NULL)
        delete[] data;
		
    data = temp;
    //iBack = size() - 1;
    //iFront = 0;
    capacity = newCapacity;
}

/**********************************************
* SET : SLIDE RIGHT
* Move all elements to the right one space
**********************************************/
template<class T>
    inline void set<T>::slideRight(int indexPostition)
{
    for (int i = numElements; i > indexPostition; i--)
        data[i] = data[i - 1];
}

/**********************************************
* SET : SLIDE LEFT
* Move all elements to the left one space
**********************************************/
template<class T>
    inline void set<T>::slideLeft(int indexPostition)
{
    for (int i = indexPostition; i < numElements - 1; i++)
        data[i] = data[i + 1];
}


/**********************************************
* SET : EMPTY
* Return true if empty
**********************************************/
template<class T>
    bool set<T>::empty() const
{
    return size() == 0;
}

/**********************************************
* SET : SIZE
* Return the size of the set
**********************************************/
template<class T>
    int set<T>::size() const
{
    return this->numElements;
}

/**********************************************
* SET : CLEAR
* Set numElements to 0
**********************************************/
template<class T>
    void set<T>::clear()
{
    numElements = 0;
}

