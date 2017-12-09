/***********************************************************************
 * Header:
 *    VECTOR
 * Summary:
 *    This will contain the class definition of:
 *        Vector         : A class that represents a Vector
 *        VectorIterator : An interator through Vector
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

// forward declaration for VectorConstIterator
template <class T>
class VectorConstIterator;

/*****************************************
 * VECTOR
 * Just like the std :: vector <T> class
 ****************************************/
template <class T>
class Vector
{
   public:
      // default constructor: no space allocated
      Vector() : data(NULL), num(0), max(0) {}

      // non-default constructor: set the capacity initially
      Vector(int capacity) throw (const char *) : data(NULL), num(0), max(0)
      {
         if (capacity > 0)
            resize(capacity);
      }
   
      // non-default constructor: set the capacity initially
      Vector(int capacity, const T & t) throw (const char *) :
               data(NULL), num(0), max(0)
      {
         if (capacity > 0)
            resize(capacity, t);
      }

      // copy-constructor: copy over the data from the right-and-side
      Vector (const Vector <T> & rhs) throw (const char *) :
                  data(NULL), num(0), max(0)
      {
         if (!rhs.empty())
            *this = rhs; // call the assignment operator
      }
   
      // delete the data as necessary
      ~Vector()
      {
         if (max != 0)
            delete [] data;
      }
   
      // add to the end of the list, reallocating as necesary
      void push_back(const T & t) throw (const char *);
   
      // read-write access with bounds checking
      T & operator [] (int index) throw (const char *)
      {
         // sanity check
         if (index < 0 || index >= max)
            throw "ERROR: Invalid index";
         return data[index];    // return-by-reference
      }
   
      // read-write access with bounds checking
      T operator [] (int index) const throw (const char *)
      {
         // sanity check
         if (index < 0 || index >= max)
            throw "ERROR: Invalid index";
         return data[index];    // return-by-reference
      }
   
      // read-only access with bounds checking
      T operator () (int index) const throw (const char *)
      {
         // sanity check
         if (index < 0 || index >= max)
            throw "ERROR: Invalid index";
         return data[index];    // return-by-value
      }
   
      // copy one Vector <T> into another
      Vector <T> & operator = (const Vector <T> & rhs) throw (const char *);
   
      // fetch the size
      int size()              const { return num;      }
   
      // fetch the capacity
      int capacity()          const { return max;      }

      // is it empty?
      bool empty()            const { return num == 0; }

      // forget about all the elements
      void clear()                  { num = 0;         } 

      // the various iterator methods
      VectorIterator <T> begin()  { return VectorIterator <T> (data);         }
      VectorIterator <T> end()    { return VectorIterator <T> (data + num);   }

      VectorConstIterator <T> cbegin() const
      {
         return VectorConstIterator <T> (data);
      }
      VectorConstIterator <T> cend() const
      {
         return VectorConstIterator <T> (data + num);
      }

   private:
      T *  data;                 // user data, a dynamically-allocated array
      int  max;                  // the capacity of the array
      int  num;                  // the number of items currently used
      void resize(int newCapacity, const T & t = T()) throw (const char *);
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through Vector.  You only need to
 * support the following:
 *   1. Constructors (default and copy)
 *   2. Not equals operator
 *   3. Increment (prefix and postfix)
 *   4. Dereference
 * This particular iterator is a bi-directional meaning
 * that ++ and -- both work.  Not all iterators are that way.
 *************************************************/
template <class T>
class VectorIterator
{
public:
   // default constructor
   VectorIterator()      : p(NULL) {}

   // initialize to direct p to some item
   VectorIterator(T * p) : p(p)          {}

   // copy constructor
   VectorIterator(const VectorIterator & rhs) { *this = rhs; }

   // assignment operator
   VectorIterator <T> & operator = (const VectorIterator <T> & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorIterator <T> & rhs) const
   {
      return rhs.p != this->p;
   }

   // equals operator
   bool operator == (const VectorIterator <T> & rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator ++ (int postfix)
   {
      VectorIterator <T> tmp(*this);
      p++;
      return tmp;
   }
   // prefix decrement
   VectorIterator <T> & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   VectorIterator <T> operator -- (int postfix)
   {
      VectorIterator <T> tmp(*this);
      p--;
      return tmp;
   }

private:
   T * p;
};

/**************************************************
 * VECTOR CONSTANT ITERATOR
 * An iterator through Vector where we cannot change
 * the vector with *it
 *
 * The only difference between this and VectorIterator
 * is that the pointer member variable is a const and
 * the dereference operator returns const by-reference
 *************************************************/
template <class T>
class VectorConstIterator
{
public:
   // default constructor
   VectorConstIterator()      : p(NULL) {}

   // initialize to direct p to some item
   VectorConstIterator(T * p) : p(p)          {}

   // copy constructor
   VectorConstIterator(const VectorConstIterator <T> & rhs)
   {
      this->p = rhs.p;
   }

   // assignment operator
   VectorConstIterator <T> & operator = (const VectorConstIterator <T> & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorConstIterator <T> & rhs) const
   {
      return rhs.p != this->p;
   }

   // equals operator
   bool operator == (const VectorConstIterator <T> & rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   const T operator * () const
   {
      return *p; 
   }

   // prefix increment
   VectorConstIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorConstIterator <T> operator ++ (int postfix)
   {
      VectorConstIterator <T> tmp(*this);
      p++;
      return tmp;
   }
   // prefix decrement
   VectorConstIterator <T> & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   VectorConstIterator <T> operator -- (int postfix)
   {
      VectorConstIterator <T> tmp(*this);
      p--;
      return tmp;
   }

private:
   const T * p;
};

/***************************************
 * VECTOR <T> :: RESIZE
 * This method will grow the current buffer
 * to newCapacity.  It will also copy all
 * the data from the old buffer into the new
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 *     THROW  : ERROR: Unable to allocate a new buffer for Vector
 **************************************/
template <class T>
void Vector <T> :: resize(int newCapacity, const T & t) throw (const char *)
{
   assert(newCapacity > 0 && newCapacity > max);

   // allocate the new array
   T * pNew;
   try
   {
      pNew = new T[newCapacity];       // could throw bad_alloc
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Vector";
   }
   
   // copy over the data from the old array
   for (int i = 0; i < num; i++)
      pNew[i] = data[i];
   for (int i = num; i < newCapacity; i++)
      pNew[i] = t;

   // delete the old and assign the new
   if (NULL != data)
      delete [] data;
   data = pNew;
   max  = newCapacity;
}

/***************************************
 * VECTOR <T> :: push_back
 * This method will add the element 't' to the
 * end of the current buffer.  It will also grow
 * the buffer as needed to accomodate the new element
 *     INPUT  : 't' the new element to be added
 *     OUTPUT : *this 
 *     THROW  : "ERROR: Unable to allocate a new buffer for Vector
 **************************************/
template <class T>
void Vector <T> :: push_back (const T & t) throw (const char *)
{
   assert(num <= max);
   
   // grow if necessary
   if (max == 0)
      resize(1);
   else if (num == max)
      resize(max * 2);   // could throw bad_alloc
   assert(num < max);

   // actually add on to the end of the list
   data[num++] = t;
}

/***************************************
 * VECTOR <T> :: assigment operator
 * This operator will copy the contents of the
 * rhs onto *this, growing the buffer as needed
 *     INPUT  : rhs the vector to copy from
 *     OUTPUT : *this
 *     THROW  : "ERROR: Unable to allocate a new buffer for Vector
 **************************************/
template <class T>
Vector <T> & Vector <T> :: operator = (const Vector <T> & rhs)
   throw (const char *)
{
   if (&rhs == this)
      return *this;
   
   // blow away anything that was in this->data previously
   num = 0;

   // make sure we are big enough to handle the new data
   if (rhs.num > max)
      resize(rhs.num);
   assert(max >= rhs.num);

   // copy over the data from the right-hand-side
   num = rhs.num;
   for (int i = 0; i < rhs.num; i++)
      data[i] = rhs.data[i];

   // return self
   return *this;
}

#endif // VECTOR_H
