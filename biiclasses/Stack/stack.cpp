/**
 * Created by Simon Camacho
 * on July 18, 2020. Function
 * definitions for the stack.h
 * class
 */

#include "stack.h"
#include <exception>

// Constructors/Destructor –––––––––––––––––––––––––––––––

template <typename T>
Stack<T>::Stack() :
    _head(nullptr), _size(0) { }

template <typename T>
Stack<T>::Stack(Stack<T>& other) :
    _head(nullptr), _size(other._size) { 
    stackNode* temp = _head;
    for (int i = 0; i < other._size; i++) {
        // something about either temp
        // needing to be pushed down the 
        // list or maybe head is and then
        // we bring it back up to temp
        // at the end

    }
}

template <typename T>
Stack<T>::Stack(Stack<T>&& other) :
    _head(move(other._head)), _size(move(other._size)) { 
    other._head = nullptr;
}


// template <typename T>
// Vector<T>::Vector(const Vector<T>& given) : 
//     _size(given._size), 
//     _capacity(given._capacity), 
//     _elements(new T[given._capacity]) { 
//     copy(given._elements, given._elements + given._size, _elements);
// }

// template <typename T>
// Vector<T>::Vector(Vector<T>&& given) : 
//     _size(move(given._size)), 
//     _capacity(move(given._capacity)), 
//     _elements(move(given._elements)) { 
//     given._elements = nullptr;
// }



template <typename T>
Stack<T>::~Stack() {
    stackNode* temp = nullptr;
    while (_head != nullptr) {
        temp = _head;
        _head = _head->next;
        delete temp;
    }
}

// Capacity ––––––––––––––––––––––––––––––––––––––––––––––

template <typename T>
inline size_t Stack<T>::size() const {
    return _size;
}

template <typename T>
inline bool Stack<T>::empty() const {
    return _size == 0;
}

// Modifiers –––––––––––––––––––––––––––––––––––––––––––––

template <typename T>
Stack<T>& Stack<T>::push(const T& element) {
    if (_head == nullptr) {
        _head = new stackNode(element, nullptr, nullptr);
    } else {
        stackNode* temp = new stackNode(element, _head, nullptr);
        _head->previous = temp;
        _head = temp;
    }
    _size++;
    return *this;
}

template <typename T>
T& Stack<T>::pull() {
    if (empty()) {
        cout << "pull failed\n";
        throw empty_stack();
    }
    stackNode* temp = _head;
    
    _head = _head->next;
    cout << "Getttttin here??? " << endl;
    temp->next = nullptr;
    return temp->element;
}

// Element Viewing –––––––––––––––––––––––––––––––––––––––

template <typename T>
T& Stack<T>::top() {
    if (empty()) {
        cout << "top failed\n";
        throw empty_stack();
    }
    return _head->element;
}

template <typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        cout << "top failed\n";
        throw empty_stack();
    }
    return _head->element;
}

// Operators –––––––––––––––––––––––––––––––––––––––––––––

template <typename T>
Stack<T>& Stack<T>::operator+=(const T& element) {
    push(element);
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator+=(const Stack<T>& other) {
    stackNode* temp = other._head;
    // this can be done more efficiently. Maybe add a back pointer?
    while (temp != nullptr) {
        temp = temp->next;
    }
    while (temp != nullptr) {
        push(temp->element);
        temp = temp->previous;
    }
    return *this;
}

//     template <typename T>
// Vector<T>& Vector<T>::operator=(const Vector<T>& assign) {
//     if (&assign == this) return *this;
//     _size = assign._size;
//     _capacity = assign._capacity;
//     T* newArray = new T[assign._capacity];
//     copy(assign._elements, assign._elements + assign._size, newArray);
//     delete [] _elements;
//     _elements = newArray;
//     return *this;
// }

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& assign) {
    if (&assign == this) return *this;
    _size = assign._size;
    for (int i = 0; i < _size; i++) {
        // Something like adding things to the end etc.
    }
}

// Friends –––––––––––––––––––––––––––––––––––––––––––––––
template <typename T>
bool operator==(const Stack<T>& left, const Stack<T>& right) {
    if (left._size != right._size) {
        return false;
    }
    while (left._head != nullptr) {
        if (left._head->element != right._head->element) {
            return false;
        }
        left._head = left._head->next;
        right._head = right._head->next;
    }
    return true;
}

template <typename T>
bool operator!=(const Stack<T>& left, const Stack<T>& right) {
    return !(left == right);
}

// Non-Members –––––––––––––––––––––––––––––––––––––––––––
/**
 * Given an element and a stack,
 * returns a new stack with the 
 * element added to the top
 */
template <typename T>
Stack<T> operator+(const T& left, const Stack<T>& right) {
    Stack<T> copy = right;
    copy += left;
    return copy;
}

/**
 * Given an element and a stack,
 * returns a new stack with the 
 * element added to the top.
 */
template <typename T>
Stack<T> operator+(const Stack<T>& left, const T& right) {
    Stack<T> copy = left;
    copy += right;
    return copy;
}

/**
 * Given two stacks,
 * returns a new stack with the 
 * contents of the right stack added 
 * to the top of the left stack.
 */
template <typename T>
Stack<T> operator+(const Stack<T>& left, const Stack<T>& right) {
    Stack<T> copy = left;
    copy += right;
    return copy;
}
