/** 
 * Created July 8, 2020 by
 * Simon Camacho. Vector<T>
 * is a personalized vector class
 * for use in projects by BII.
 * 
 * @version 1.0.0: July 8, 2020
 * Added basic outline of the class,
 * including simplest member functions,
 * including check, [], size, addBack, empty,
 * and remove.
 * 
 * @version 1.0.1: July 9, 2020
 * Added construction with given size, capacity,
 * reserve, reduce, removeBack, merge, front, back,
 * insert, innerVec, and += (for individual values
 * and vectors).
 * 
 * @version 1.0.2: July 12, 2020
 * Added const correct versions of check, [], front, and back. Added
 * const correctness in general to the vector.h file. 
 * Added == and != for vector comparison.
 * 
 * @version 1.0.3: July 14, 2020
 * Added inline to many of the member functions. Added first attempt
 * at foward-iterators and outline of reverse-iterators (iterators 
 * will need to be made into their own class in a different file). Added
 * copy constructor and copy assignment special member functions. Added the
 * + operator for two vectors, as well as for a vector and value_type. Added
 * the stream insertion operator << as well.
 * 
 * @version 1.0.4: July 15, 2020
 * Added move constructor and move operator. Added move versions of addBack
 * and +=. Added non-member swap function. Organized this file and transferred
 * all member and non-member function definitions to the vector.cpp file. Added
 * two exception structs at the bottom of this file –– empty_vector and bad_reserve
 * –– for handling exceptions related to those errors. Added const-cast/static-cast
 * trick to function definitions to minimize code repetition. Made test-harness look
 * much more elegant (added sections, turning tests on and off, etc.). Added first 
 * attempt at vector_iterator class.
 * 
 * @version 1.0.5: July 16, 2020
 * Added some silly stuff to the test harness (mostly practiced with color and bold
 * text escape sequences). Decided that arrays have enough functionality that don't
 * need to overload any operators (they should be random access as is). Implemented
 * basic forward and reverse iterators. The reverse iterators have a high astonishment
 * factor, so probably needs to be changed. Changed insert, innerVec, remove to use iterators
 * instead of size_t indexes.
 * 
 * 
*/
#pragma once
#include <string>
#include <iostream>
#include <exception>
#include <algorithm>
#include <memory>

using std::cout;
using std::endl;
using std::copy;
using std::move;

const int initialCapacity = 10;

template <typename T>
class Vector {
public:

    using iterator = T*;
    using const_iterator = const T*;

    // Constructors/Destructor –––––––––––––––––––––––––––––––
    /** 
     * Default Constructor
     * Sets capacity to initialCapacity
     * Sets size to 0
     * Creates a new vector of size initialCapacity
     */
    Vector();

    /** 
     * Destructor
     * Sets capacity to initialCapacity
     * Sets size to 0
     * Creates a new vector of size initialCapacity
     */
    Vector(const int givenSize);

    /** 
     * Copy Constructor
     * Creates a new vector with the same capacity, size, and elements as the given l-value vector
     */
    Vector(const Vector<T>& given);

    /** 
     * Move Constructor
     * Creates a new vector with the same capacity, size, and elements as the given r-value vector
     */
    Vector(Vector<T>&& given);

    /**
     * Fill Constructor
     * Creates a new vector and fills it with the given value
     */
    Vector(int times, const T val);

    /**
     * Range Constructor
     * Creates a new vector and populates it with the elements of another vector between
     * the given indices of the other vector
     */
    // Vector(const iterator otherBegin, const iterator otherEnd);

    /** 
     * Returns the memory used by the vector
     */
    ~Vector();
    
    // Capacity ––––––––––––––––––––––––––––––––––––––––––––––
    /**
     * Returns the size of the vector
     * O(1) asymptotic complexity
     */
    inline size_t size() const;

    /**
     * Returns true if the vector is empty
     * O(1) asymptotic complexity
     */
    inline bool empty() const;

    /**
     * Returns the current capacity of the vector
     * O(1) asymptotic complexity
     */
    inline size_t capacity() const;

    /**
     * Returns the amount of open space left in the vector
     * O(1) asymptotic complexity
     */ 
    inline size_t open() const;
    
    // Modifiers –––––––––––––––––––––––––––––––––––––––––––––
    /**
     * Adds an l-value element to the back of the vector
     * O(1) asymptotic complexity
     */ 
    Vector<T>& addBack(const T& value);

    /**
     * Adds an r-value element to the back of the vector
     * O(1) asymptotic complexity
     */ 
    Vector<T>& addBack(T&& value);

    /** 
     * Returns and removes the last element in the vector
     * Throws an error if trying to remove an empty element
     * O(1) asymptotic complexity 
     */
    T& removeBack();

    /**
     * Removes the value in the vector at the given index
     * Throws an error for invalid indexes
     * O(N) asymptotic complexity
     */
    void remove(const iterator index);

    /**
     * Inserts a value at a certain index in the vector
     * Throws an error if the index is greater than the size
     * of the vector or if the index is negative
     * O(n) runtime speed
     */
    void insert(const T& value, const iterator index);

    /**
     * Given another vector, adds the elements of 
     * the other vector to the back of the first
     * O(n) runtime speed where n is the size
     * of the other vector
     */
    Vector<T>& merge(const Vector<T>& other);

    // add a version of merge for rvalue references

    /**
     * Returns a new vector that is a subset of the old vector between
     * the two given indexes, inclusive.
     * Throws an error if the vector is empty or if the indexes are invalid
     */
    Vector<T> innerVec(const iterator first, const iterator second);

    /**
     * Given two indices, swaps the elements at the given
     * indices
     */
    Vector<T>& swap(const iterator first, const iterator second);
    
    // Element Viewing –––––––––––––––––––––––––––––––––––––––
    /**
     * Returns a reference to the value at a given index
     * Throws an error for invalid indexes
     */
    T& check(const size_t index);

    /**
     * Returns the value at a given index
     * Throws an error for invalid indexes
     */
    const T& check(const size_t index) const;

    /**
     * Return a reference to the first element in the vector
     * Throws an error if the vector is empty
     * O(1) runtime speed
     */
    inline T& front();

    /**
     * Return the value of the first element in the vector
     * Throws an error if the vector is empty
     * O(1) runtime speed
     */
    inline const T& front() const;

    /**
     * Return a reference to the last element in the vector
     * Throws an error if the vector is empty 
     * O(1) runtime speed
     */
    inline T& back();

    /**
     * Return the value of the last element in the vector
     * Throws an error if the vector is empty 
     * O(1) runtime speed
     */
    inline const T& back() const;

    // Memory Handling –––––––––––––––––––––––––––––––––––––––
    /**
     * Clears the existing vector and resets capacity to 
     * initialCapacity
     */
    Vector<T>& clear();

    /**
     * Enlarges the vector by a given length on top
     * of its existing size
     * Throws an error if the length is less than or
     * equal to 0 
     */
    void reserve(const size_t length);

    /**
     * Reduces the capacity of the current vector to
     * match its size
     */
    void reduce();
    
    // Operators –––––––––––––––––––––––––––––––––––––––––––––
    /**
     * Returns a reference to the value at a given index
     */
    T& operator[](const size_t index);

    /**
     * Returns a the value at a given index
     */
    const T& operator[](const size_t index) const;

    /**
     * Adds an lvalue element to the back of the vector
     * O(1) runtime speed
     */ 
    Vector<T>& operator+=(const T& value);

    /**
     * Adds an rvalue element to the back of the vector
     * O(1) runtime speed
     */ 
    Vector<T>& operator+=(T&& value);

    /**
     * Adds the elements of the other vector to the back
     * of the vector
     * O(n) runtime speed where n is the size of the other
     * vector
     */ 
    Vector<T>& operator+=(const Vector<T>& other);

    /**
     * Copy Assignment
     */
    Vector<T>& operator=(const Vector<T>& assign);

    /**
     * Move Assignment
     */
    Vector<T>& operator=(Vector<T>&& assign);
    
    // Iterators –––––––––––––––––––––––––––––––––––––––––––––
    /**
     * Iterator with initial position at front of the vector
     */
    iterator begin();

    /**
     * Iterator with initial position at back of the vector
     */
    iterator end();

    /**
     * Const iterator with initial position at front of the vector
     */
    const_iterator begin() const;

    /**
     * Const iterator with initial position at back of the vector
     */
    const_iterator end() const;

    /**
     * Reverse iterator with initial position at back of the vector
     */
    iterator rbegin();

    /**
     * Reverse iterator with initial position at front of the vector
     */
    iterator rend();

    /**
     * Const reverse iterator with initial position at back of the vector
     */
    const_iterator rbegin() const;

    /**
     * Const reverse iterator with initial position at front of the vector
     */
    const_iterator rend() const;
    
    // Friends –––––––––––––––––––––––––––––––––––––––––––––––
    /**
     * Given two vectors, returns true if they have the same elements
     * in the same order
     * O(n) runtime speed
     */
    template <typename T_>
    friend bool operator==(const Vector<T_>& first, const Vector<T_>& second);

    /**
     * Given two vectors, returns true if they don't have the same elements
     * in the same order
     * O(n) runtime speed
     */
    template <typename T_>
    friend bool operator!=(const Vector<T_>& first, const Vector<T_>& second);

    /**
     * Given an output stream and a vector, prints the elements of the vector
     * to the console
     * O(n) runtime speed
     */
    template <typename T_>
    friend std::ostream& operator<<(std::ostream& out, const Vector<T_>& vec);
    
    // Non-Members (Not Declared) ––––––––––––––––––––––––––––
    // Vector<T> operator+(const Vector<T>& lhs, const T& rhs);
    // Vector<T> operator+(const T& lhs, const Vector<T>& rhs);
    // Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs);
    // void swap(Vector<T>& first, Vector<T>& second);
    
    // Functions to Implement ––––––––––––––––––––––––––––––––
    // void operator{}(const T& elements);
    // Vector{const T& element};

private:
    /* the underlying array */
    T* _elements;

    /* the current number of elements in the vector */
    int _size;

    /* the maximum capacity of the current vector */
    int _capacity;

    /** 
     * Enlarges the size of the underlying array by the 
     * given amount
     */
    void expand(int amount);
};


/**
 * Exception handler for attempts to access
 * an empty vector
 */
struct empty_vector : public std::exception {
    const char * what () const throw () {
        return "Trying to access an empty vector";
    }
};

/**
 * Exception handler for reserving invalid
 * amounts of memory
 */
struct bad_reserve : public std::exception {
    const char * what () const throw () {
        return "Trying to reserve an invalid length";
    }
};

#include "vector.cpp"
