/**
 * Created by Simon Camacho on July 16, 2020. 
 * Stack<T> is a personalized stack class
 * for use in projects by BII.
 * 
 * @version 1.0.0: July 16, 2020
 * Added some basic member functions,
 * constructors etc.
 * 
 * @version 1.0.1: July 17, 2020
 * Added the stackNode struct, size,
 * push, top, pull. Tried to work on
 * move and copy constructors but unsuccessful
 * so far
 * 
 * @version 1.0.2: July 18, 2020
 * Added the empty_stack exception struct. Added
 * empty. Organized this file and the stack.cpp
 * file. Added some initial work on operators by
 * adding +=, some work on +, some work on =, and
 * == and !=.
 * 
 * 
 */
#pragma once
#include <iostream>
// #include "../exceptions/exception.h"

using std::cout;
using std::endl;
using std::move;
using std::copy;

template <typename T>
class Stack {
public:

    // Constructors/Destructor –––––––––––––––––––––––––––––––
    /** 
     * Default Constructor
     */
    Stack();

    /**
     * Copy Constructor
     */
    Stack(Stack<T>& other);

    /**
     * Move Constructor
     */
    Stack(Stack<T>&& other);

    /** 
     * Destructor
     * O(N) asymptotic complexity (N is the size of the stack)
     */
    ~Stack();

    // Capacity ––––––––––––––––––––––––––––––––––––––––––––––
    /**
     * Returns the number of nodes in the stack
     * O(1) asymptotic complexity
     */
    inline size_t size() const;

    /**
     * Returns true if the stack is empty
     * O(1) asymptotic complexity
     */
    inline bool empty() const;

    // Modifiers –––––––––––––––––––––––––––––––––––––––––––––
    /**
     * Adds an element to the top of the stack
     * O(1) asymptotic complexity
     */
    Stack<T>& push(const T& element);

    // rvalue version of push?
    // Stack<T>& push(const T&& element);

    /**
     * Removes an element from the top of the stack
     * O(1) asymptotic complexity
     */
    T& pull();

    // Element Viewing –––––––––––––––––––––––––––––––––––––––
    /**
     * Views the element on the top of the stack
     * without removing it (non-const)
     * O(1) asymptotic complexity
     */
    T& top();

    /**
     * Views the element on the top of the stack
     * without removing it (const)
     * O(1) asymptotic complexity
     */
    const T& top() const;

    // Operators –––––––––––––––––––––––––––––––––––––––––––––
    /**
     * Adds the given element to the top of the stack
     * O(1) asymptotic complexity
     */
    Stack<T>& operator+=(const T& element);

    // rvalue version of +=?
    // Stack<T>& operator+=(const T&& element);
    // version where you add another stack to the top
    // and an rvalue version of that

    /**
     * Adds the given stack to the top of the stack
     * O(N) asymptotic complexity
     */
    Stack<T>& operator+=(const Stack<T>& other);

    /**
     * Copy Assignment
     */
    Stack<T>& operator=(const Stack<T>& assign);

    /**
     * Move Assignment
     */
    Stack<T>& operator=(const Stack<T>&& assign);

    // Friends –––––––––––––––––––––––––––––––––––––––––––––––
    /**
     * Given two stacks, returns true if they have
     * the same elements in the same order
     */
    template <typename T_>
    friend bool operator==(const Stack<T_>& left, const Stack<T_>& right);

    /**
     * Given two stacks, returns true if they have
     * don't have the same elements in the same order
     */
    template <typename T_>
    friend bool operator!=(const Stack<T_>& left, const Stack<T_>& right);

    // Non-Members (Not Declared) ––––––––––––––––––––––––––––
    // Stack<T> operator+(const T& left, const Stack<T>& right);
    // Stack<T> operator+(const Stack<T>& left, const T& right);
    // Stack<T> operator+(const Stack<T>& left, const Stack<T>& right);

private:

    /** Individual nodes on the stack */
    struct stackNode {
        /** Current node value */
        T element;
        /** Address of the previous node */
        stackNode* previous;
        /** Address of the next node */
        stackNode* next;
        /** stackNode constructor */
        stackNode(const T& element, stackNode* previous, stackNode* next) :
            element(element), previous(previous), next(next) { }

        /** 
         * Overloaded the << operator to be able to print out
         * individual stackNodes
         */
        friend std::ostream& operator<<(std::ostream& out, stackNode node) {
            out << node->element;
            return out;
        }
    };

    /** Pointer to the top of the stack */
    stackNode* _head;

    /** The number of nodes in the stack */
    int _size;

    // maybe declare a temp pointer for use
    // throughout the class defs... kinda annoying to keep declaring... i dunno
};

/**
 * Exception handler for attempts to access
 * an empty stack
 */
struct empty_stack : public std::exception {
    const char * what () const throw () {
        return "Trying to access an empty stack";
    }
};

#include "stack.cpp"
