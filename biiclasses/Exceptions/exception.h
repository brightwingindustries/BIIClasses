/** 
 * Created by Simon Camacho on 
 * July 9, 2020. Exception.h is an
 * exception struct for use by BII
 * classes and projects
*/
#include <iostream>
#include <exception>
#include <typeinfo>


/**
 * Exception handler for attempts to access
 * an empty container
 */
template <typename T>
struct empty_container : public std::exception {
    const char* name = typeid(T).name();
    const char* prefix = 'Trying to acces an empty';

    const char * what () const throw () {
        return prefix + name;
    }
};