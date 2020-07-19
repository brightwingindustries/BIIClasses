/**
 * Created by Simon Camacho on July 15, 2020
 * 
 * Function declarations for the BII
 * Vector class
 */
#pragma once
#include <string>
#include <iostream>
#include <exception>
#include <algorithm>
#include <memory>
#include "vector.h"

using std::cout;
using std::endl;
using std::copy;
using std::move;

// Private Functions –––––––––––––––––––––––––––––––––––––

template <typename T>
void Vector<T>::expand(int amount) {
    /**
     * The creation of 'newArray' may not be RAII compliant, so may
     * need to change to using smart pointers:
     * std::unique_ptr<T[]> newArray = std::make_unique<T[amount]>();
     */
    T* newArray = new T[amount];
    for (int i = 0; i < _size; i++) {
        newArray[i] = _elements[i];
    }
    delete [] _elements;
    _elements = newArray;
    _capacity = amount;
}

// Constructors/Destructor –––––––––––––––––––––––––––––––

template <typename T> 
Vector<T>::Vector() : 
    _size(0), 
    _capacity(initialCapacity), 
    _elements(new T[initialCapacity]) { }

template <typename T> 
Vector<T>::Vector(const int givenSize) : 
    _size(0), 
    _capacity(givenSize), 
    _elements(new T[givenSize]) { }

template <typename T>
Vector<T>::Vector(const Vector<T>& given) : 
    _size(given._size), 
    _capacity(given._capacity), 
    _elements(new T[given._capacity]) { 
    copy(given._elements, given._elements + given._size, _elements);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& given) : 
    _size(move(given._size)), 
    _capacity(move(given._capacity)), 
    _elements(move(given._elements)) { 
    given._elements = nullptr;
}

template <typename T>
Vector<T>::Vector(int times, const T val) :
    _size(times),
    _capacity(times * 2),
    _elements(new T[times * 2]) { 
    for (int i = 0; i < times; i++) {
        _elements[i] = val;
    }
}

// template <typename T>
// Vector<T>::Vector(const iterator otherBegin, const iterator otherEnd) : 
//     _size(0),
//     _capacity(),
//     _elements(new T[times * 2]) { 
//     for (iterator iter = otherBegin; iter < otherEnd; iter++) {
//         addBack(*iter);
//     }
// }

template <typename T>
Vector<T>::~Vector() {
    delete [] _elements;
}

// Capacity ––––––––––––––––––––––––––––––––––––––––––––––

template <typename T>
inline size_t Vector<T>::size() const {
    return _size;
}

template <typename T>
inline bool Vector<T>::empty() const {
    return _size == 0;
}

template <typename T>
inline size_t Vector<T>::capacity() const {
    return _capacity;
}

template <typename T>
inline size_t Vector<T>::open() const {
    return _capacity - _size;
}

// Modifiers –––––––––––––––––––––––––––––––––––––––––––––

template <typename T>
Vector<T>& Vector<T>::addBack(const T& value) {
    if (_size == _capacity) {
        expand(_capacity * 2);
    }
    _elements[_size] = value;
    _size++;
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::addBack(T&& value) {
    if (_size == _capacity) {
        expand(_capacity * 2);
    }
    _elements[_size] = move(value);
    _size++;
    return *this;
}

template <typename T>
T& Vector<T>::removeBack() {
    if (empty()) {
        cout << "removeBack failed\n";
        throw empty_vector();
    }
    _size--;
    return _elements[_size];
}

template <typename T>
void Vector<T>::remove(const iterator index) {
    if (index >= end() || index < begin()) {
        cout << "remove failed\n";
        throw std::out_of_range("Trying to access index outside of vector");
    }
    iterator counter = index;
    while (counter < end()) {
        *counter = *(counter + 1);
        counter++;
    }
    _size--;
}

template <typename T>
Vector<T>& Vector<T>::merge(const Vector<T>& other) {
    if (other._size > open()) {
        reserve(other._size - open());
    }
    for (int i = 0; i < other._size; i++) {
        addBack(other._elements[i]);
    }
    return *this;
}

template <typename T>
void Vector<T>::insert(const T& value, const iterator index) {
    if (index < begin() || index >= end()) {
        cout << "Insert failed\n";
        throw std::out_of_range("Trying to access index outside of vector");
    }
    if (_size == _capacity) {
        expand(_capacity * 2);
    }
    for (iterator iter = end(); iter > index; iter--) {
        *iter = *(iter - 1);
    }
    *index = value;
    _size++;
}

template <typename T>
Vector<T> Vector<T>::innerVec(const iterator first, const iterator second) {
    if (empty()) {
        cout << "innerVec failed\n";
        throw empty_vector();
    }
    if (first < begin() || first > end()) {
        cout << "innerVec failed\n";
        throw std::out_of_range("Trying to access index outside of vector");
    }
    if (second < begin() || second > end()) {
        cout << "innerVec failed\n";
        throw std::out_of_range("Trying to access index outside of vector");
    }
    if (first > second) {
        cout << "innerVec failed\n";
        throw std::out_of_range("Given indices not in proper order");
    }

    Vector<T> inner;
    for (iterator iter = first; iter < second; iter++) {
        inner.addBack(*iter);
    }
    return inner;
}

template <typename T>
Vector<T>& Vector<T>::swap(const iterator first, const iterator second) {
    T element = move(*first);
    *first = move(*second);
    *second = element;
    return *this;
}

// Elements Viewing ––––––––––––––––––––––––––––––––––––––

template <typename T>
T& Vector<T>::check(const size_t index)  {
    return const_cast<T&>(static_cast<const Vector<T>*>(this)->check(index));
}

template <typename T>
const T& Vector<T>::check(const size_t index) const {
    if (index >= _size || index < 0) {
        cout << "Check failed\n";
        throw std::out_of_range("Trying to access index outside of vector");
    }
    return *(begin() + index);
}

template <typename T>
inline T& Vector<T>::front() {
    return const_cast<T&>(static_cast<const Vector<T>*>(this)->front());
}

template <typename T>
inline const T& Vector<T>::front() const {
    if (empty()) {
        cout << "front failed\n";
        throw empty_vector();
    }
    return _elements[0];
}

template <typename T>
inline T& Vector<T>::back() {
    return const_cast<T&>(static_cast<const Vector<T>*>(this)->back());
}

template <typename T>
inline const T& Vector<T>::back() const {
    if (empty()) {
        cout << "back failed\n";
        throw empty_vector();
    }
    return _elements[_size - 1];
}

// Memory Handling –––––––––––––––––––––––––––––––––––––––

template <typename T>
void Vector<T>::reserve(const size_t length) {
    if (length <= 0) {
        cout << "reserve failed\n";
        throw bad_reserve();
    }
    expand(_capacity + length);
}

template <typename T>
void Vector<T>::reduce() {
    expand(_size);
}

template <typename T>
Vector<T>& Vector<T>::clear() {
    expand(initialCapacity);
    _size = 0;
    return *this;
}

// Operators –––––––––––––––––––––––––––––––––––––––––––––

template <typename T>
T& Vector<T>::operator[](const size_t index) {
    return check(index);
}

template <typename T>
const T& Vector<T>::operator[](const size_t index) const {
    return check(index);
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const T& value) {
    addBack(value);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(T&& value) {
    addBack(value);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    merge(other);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& assign) {
    if (&assign == this) return *this;
    _size = assign._size;
    _capacity = assign._capacity;
    T* newArray = new T[assign._capacity];
    copy(assign._elements, assign._elements + assign._size, newArray);
    delete [] _elements;
    _elements = newArray;
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& assign) {
    if (&assign == this) return *this;
    _size = move(assign._size);
    _capacity = move(assign._capacity);
    delete [] _elements;
    _elements = move(assign._elements);
    assign._elements = nullptr;
    return *this;
}

// Iterators –––––––––––––––––––––––––––––––––––––––––––––

template <typename T>
T* Vector<T>::begin() {
    return const_cast<T*>(static_cast<const Vector<T>*>(this)->begin());
}

template <typename T>
T* Vector<T>::end() {
    return const_cast<T*>(static_cast<const Vector<T>*>(this)->end());
}

template <typename T>
const T* Vector<T>::begin() const {
    return _elements;
}

template <typename T>
const T* Vector<T>::end() const {
    return _elements + size();
}

// ADD REVERSE ITERATORS
template <typename T>
T* Vector<T>::rbegin() {
    return const_cast<T*>(static_cast<const Vector<T>*>(this)->rbegin());
}

template <typename T>
T* Vector<T>::rend() {
    return const_cast<T*>(static_cast<const Vector<T>*>(this)->rend());
}

template <typename T>
const T* Vector<T>::rbegin() const {
    return _elements + size() - 1;
}

template <typename T>
const T* Vector<T>::rend() const {
    return _elements - 1;
}

// Friends –––––––––––––––––––––––––––––––––––––––––––––––

template <typename T>
bool operator==(const Vector<T>& first, const Vector<T>& second) {
    if (first._size != second._size) {
        return false;
    }
    for (int i = 0; i < first._size; i++) {
        if (first._elements[i] != second._elements[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const Vector<T>& first, const Vector<T>& second) {
    return !(first == second);
}

// maybe doesn't need to be a friend!
template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& vec) {
    out << '{';
    for (const T* iter = vec.begin(); iter < vec.end(); iter++) {
        out << *iter;
        if (iter + 1 == vec.end()) break;
        out << ", ";
    }
    out << '}' << endl;
    return out;
}

// Non-Members –––––––––––––––––––––––––––––––––––––––––––
/**
 * Returns a new vector with the given element added to the 
 * given element
 */
template <typename T>
Vector<T> operator+(const Vector<T>& lhs, const T& rhs) {
    Vector<T> copy = lhs;
    copy += rhs;
    return copy;
}

/**
 * Returns a new vector with the given element added to the 
 * given element
 */
template <typename T>
Vector<T> operator+(const T& lhs, const Vector<T>& rhs) {
    Vector<T> copy = rhs;
    copy += lhs;
    return copy;
}

/**
 * Returns a new vector with the two given vectors added to each
 * other
 */
template <typename T>
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
    Vector<T> copy = lhs;
    for (const T* iter = rhs.begin(); iter < rhs.end(); iter++) {
        copy += *iter;
    }
    return copy;
}

/**
 * Swaps the contents of the two given vectors
 */
template <typename T>
void swap(Vector<T>& first, Vector<T>& second) {
    Vector<T> lvalue = move(first);
    first = move(second);
    second = move(lvalue);
}
