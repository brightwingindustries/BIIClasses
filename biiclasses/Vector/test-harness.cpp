/**
 * Created by Simon Camacho
 * on July 8, 2020. Testing harness
 * for the Vector<T> class.
 * 
 */
#include "vector.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

// Color definitions
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define BLINK "\033[5m"
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define BOLDBLUE "\033[1m\033[34m"

// Test Settings
const bool section_A = true; // Constructors/Destructor (6 Methods)
const bool section_B = true; // Capacity (4 Methods)
const bool section_C = true; // Modifiers (8 Methods)
const bool section_D = true; // Element Viewing (6 Methods)
const bool section_E = true; // Memory Handling (3 Methods)
const bool section_F = true; // Operators (7 Methods)
const bool section_G = true; // Iterators (8 Methods)
const bool section_H = true; // Friends (3 Methods)
const bool section_I = true; // Non-Members (4 Methods)

/** 
 * Given two values, returns true if they are equal
 */
template <typename T, typename S>
bool expectEqual(T first, S second) {
    return first == second;
}

/**
 * Macro for testing Vector Constructor/Destructor methods
 */
void testA(const int size, int& numTestsPassed, int& numTestsFailed) {
    // test constructor of vector that dictates initial size
    Vector<int> vec(size);
    if (!expectEqual(vec.capacity(), size)) {
        cout << "Size Initialization Constructor : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Size Initialization Constructor : PASSED" << endl;
        numTestsPassed++;
    }
    
    for (int i = 0; i < size; i++) {
        vec.addBack(i);
    }

    // test copy construction
    Vector<int> copy(vec);
    if (!expectEqual(copy.size(), vec.size())) {
        cout << "Copy Constructor : FAILED" << endl;
        numTestsFailed++;
    } 
    if (!expectEqual(copy.front(), vec.front())) {
        cout << "Copy Constructor : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Copy Constructor : PASSED" << endl;
        numTestsPassed++;
        numTestsPassed++;
    }

    // test fill construction
    int randomVal = (std::rand() % size);
    Vector<std::string> fill(size, "Eva");
    if (!expectEqual(fill.size(), size)) {
        cout << "Fill Constructor (A) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Fill Constructor (A) : PASSED" << endl;
        numTestsPassed++;
    }
    if (!expectEqual(fill[randomVal], "Eva")) {
        cout << "Fill Constructor (B) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Fill Constructor (B) : PASSED" << endl;
        numTestsPassed++;
    }
}

/**
 * Macro for testing Vector Capacity methods
 */
void testB(const int size, int& numTestsPassed, int& numTestsFailed) {
    Vector<int> vec(size);
    if (!expectEqual(vec.capacity(), size)) {
        cout << "Capacity : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Capacity : PASSED" << endl;
        numTestsPassed++;
    }    


    for (int i = 0; i < size; i++) {
        vec.addBack(i);
    }
    
    // test size
    if (!expectEqual(vec.size(), size)) {
        cout << "Size : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Size : PASSED" << endl;
        numTestsPassed++;
    }

    // test empty
    if (vec.empty()) {
        cout << "Empty : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Empty : PASSED" << endl;
        numTestsPassed++;
    }

    Vector<std::string> first(size, "hello");
    if (!expectEqual(first.open(), size)) {
        cout << "Open : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Open : PASSED" << endl;
        numTestsPassed++;
    }
}

/**
 * Macro for testing Vector Modifiers methods
 */
void testC(const int size, int& numTestsPassed, int& numTestsFailed) {
    Vector<int> vec;

    // test addBack
    for (int i = 0; i < size; i++) {
        vec.addBack(i);
    }
    int randomVal = (std::rand() % size);
    if (!expectEqual(randomVal, vec[randomVal])) { 
        cout << "addBack : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "AddBack : PASSED" << endl;
        numTestsPassed++;
    }

    // test remove
    for (int* iter = vec.rbegin(); iter > vec.rend(); iter--) {
        vec.remove(iter);
    }
    if (!expectEqual(vec.size(), 0)) { 
        cout << "Remove : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Remove : PASSED" << endl;
        numTestsPassed++;
    }

    // test merge
    Vector<int> second;
    for (int i = 0; i < size; i++) {
        vec.addBack(i);
        second.addBack(i + 10000);
    }
    vec.merge(second);
    if (!expectEqual(vec.size(), size * 2)) {
        cout << "Merge : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Merge : PASSED" << endl;
        numTestsPassed++;
    }

    // test removeBack
    int currSize = vec.size();
    vec.removeBack();
    if (!expectEqual(currSize, vec.size() + 1)) {
        cout << "RemoveBack : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "RemoveBack : PASSED" << endl;
        numTestsPassed++;
    }

    // test insert
    vec.insert(7, vec.begin());
    if (!expectEqual(vec[0], 7)) {
        cout << "Insert : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Insert : PASSED" << endl;
        numTestsPassed++;
    }

    // test innerVec
    int* start = vec.begin();
    int startInner = size / 5;
    int endInner = size / 2;
    Vector<int> inner = vec.innerVec(start + startInner, start + endInner);
    if (!expectEqual(inner.size(), endInner - startInner)) {
        cout << "InnerVec (A) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "InnerVec (A) : PASSED" << endl;
        numTestsPassed++;
    }
    // if (!expectEqual(inner[endInner], endInner)) {
    //     cout << "InnerVec (B) : FAILED" << endl;
    //     numTestsFailed++;
    // } else {
    //     cout << "InnerVec (B) : PASSED" << endl;
    //     numTestsPassed++;
    // }
}

/**
 * Macro for testing Vector Element Viewing methods
 */
void testD(const int size, int& numTestsPassed, int& numTestsFailed) {
    Vector<int> vec;
    for (int i = 0; i < size; i++) {
        vec.addBack(i);
    }
    
    // test non-const check
    int checking = vec.check(0);
    if (!expectEqual(checking, 0)) { 
        cout << "Check (non-const) (A) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Check (non-const) (A) : PASSED" << endl;
        numTestsPassed++;
    }
    vec.check(0) = 20;
    if (!expectEqual(vec.check(0), 20)) { 
        cout << "Check (non-const) (B) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Check (non-const) (B) : PASSED" << endl;
        numTestsPassed++;
    }

    // test front and const front
    if (!expectEqual(vec.front(), 20)) {
        cout << "Front (non-const) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Front (non-const) : PASSED" << endl;
        numTestsPassed++;
    }
    vec.front() = 200;
    const Vector<int> copy = vec;
    if (!expectEqual(copy.front(), 200)) {
        cout << "Front (const) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Front (const) : PASSED" << endl;
        numTestsPassed++;
    }
}

/**
 * Macro for testing Vector Memory Handling methods
 */
void testE(const int size, int& numTestsPassed, int& numTestsFailed) {
    Vector<int> vec;
    
    // test reserve
    vec.reserve(size * 2);
    if (!expectEqual(vec.capacity(), (size * 2) + 10)) {
        cout << "Reserve : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Reserve : PASSED" << endl;
        numTestsPassed++;
    }

    for (int i = 0; i < size; i++) {
        vec.addBack(i);
    }

    // test reduce
    vec.reduce();
    if (!expectEqual(vec.capacity(), vec.size())) {
        cout << "Reduce : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Reduce : PASSED" << endl;
        numTestsPassed++;
    }
}

/**
 * Macro for testing Vector Operator methods
 */
void testF(const int size, int& numTestsPassed, int& numTestsFailed) {
    Vector<int> vec;
    
    // test += operator for single values
    vec += 25;
    if (!expectEqual(vec[0], 25)) {
        cout << "Operator+= (element) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Operator+= (element) : PASSED" << endl;
        numTestsPassed++;
    }
    vec.removeBack();

    // test += operator for two vectors
    Vector<int> helper;
    for (int i = 0; i < size; i++) {
        helper.addBack(i);
    }
    vec += helper;
    if (!expectEqual(vec.size(), size)) {
        cout << "Operator+= (vector) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Operator+= (vector) : PASSED" << endl;
        numTestsPassed++;
    }
}

/**
 * Macro for testing Vector Iterator methods
 */
void testG(const int size, int& numTestsPassed, int& numTestsFailed) {
    Vector<std::string> vec(size, "Hello, World!");
    
    // test regular foward iterator
    int randomVal = (std::rand() % size);
    std::string* iter = vec.begin();
    iter += randomVal;
    if (!expectEqual(*iter, "Hello, World!")) {
        cout << "Forward Iterator : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Forward Iterator : PASSED" << endl;
        numTestsPassed++;
    }

    Vector<std::string> other(size, "Hello, World!");
    
    // test regular reverse iterator
    std::string* riter = vec.rbegin();
    riter -= randomVal;
    if (!expectEqual(*iter, "Hello, World!")) {
        cout << "Reverse Iterator : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Reverse Iterator : PASSED" << endl;
        numTestsPassed++;
    }
}

/**
 * Macro for testing Vector Friend methods
 */
void testH(const int size, int& numTestsPassed, int& numTestsFailed) {
    Vector<int> first;
    Vector<int> second;
    Vector<int> third;
    for (int i = 0; i < size; i++) {
        first.addBack(i);
        second.addBack(i);
        third.addBack(i + 10);
    }
    
    // test == operator for two vectors
    if (first == second) {
        cout << "Operator== (vector) : PASSED" << endl;
        numTestsPassed++;
    } else {
        cout << "Operator== (vector) : FAILED" << endl;
        numTestsFailed++;
    }

    // test != operator for two vectors
    if (first != third) {
        cout << "Operator!= (vector) : PASSED" << endl;
        numTestsPassed++;
    } else {
        cout << "Operator!= (vector) : FAILED" << endl;
        numTestsFailed++;
    }

    // test << operator
    // Vector<int> almost;
    // for (int i = 0; i < 10; i++) {
    //     almost.addBack(i);
    // }
    // cout << almost;
}

/**
 * Macro for testing Vector Non-Member methods
 */
void testI(const int size, int& numTestsPassed, int& numTestsFailed) {
    Vector<int> first;
    for (int i = 0; i < size; i++) {
        first.addBack(i);
    }
    
    // test + operator
    Vector<int> second = first + 4;
    Vector<int> third = 5 + second;
    if (!expectEqual(second.back(), 4)) {
        cout << "Operator+ (element rhs) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Operator+ (element rhs) : PASSED" << endl;
        numTestsPassed++;
    }
    if (!expectEqual(third.back(), 5)) {
        cout << "Operator+ (element lhs) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Operator+ (element) : PASSED" << endl;
        numTestsPassed++;
    }

    Vector<int> testOne;
    Vector<int> testTwo;
    Vector<int> testThree;
    for (int i = 0; i < size; i++) {
        testOne += i;
        testTwo += i;
    }
    testThree = testOne + testTwo;
    if (!expectEqual(testThree.size(), testOne.size() + testTwo.size())) {
        cout << "Operator+ (vectors) : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Operator+ (vectors) : PASSED" << endl;
        numTestsPassed++;
    }
}

/**
 * Given the desired section and the appropriate information, 
 * performs the tests of that section
 */
void doTest(const char section, const bool option, const int size, int& numTestsPassed, int& numTestsFailed, void (*test)(const int, int&, int&)) {
    cout << BOLD << "–––– Section " << section << " Tests ––––" << RESET << endl;
    cout << endl;
    if (option) {
        (*test)(size, numTestsPassed, numTestsFailed);
        cout << endl;
    } else {
        cout << "SKIP" << endl;
        cout << endl;
    }
}

/**
 * Writes a few nifty things to the console for the
 * user's pleasure
 */
void closingSequence() {
    cout << endl;
    cout << "Tests courtesy of " << BOLD << ITALIC << "Brightwing Industries International" << RESET << endl;
    cout << endl;
    cout << BOLDBLUE;
    cout << "BBBBBBBBBBBBB  " << "     " << "IIIIIIIIIIIII " << "     " << "IIIIIIIIIIIII" << endl;
    cout << "B             B" << "     " << "      I       " << "     " << "      I" << endl;
    cout << "B             B" << "     " << "      I       " << "     " << "      I" << endl;
    cout << "B             B" << "     " << "      I       " << "     " << "      I" << endl;
    cout << "B             B" << "     " << "      I       " << "     " << "      I" << endl;
    cout << "BBBBBBBBBBBBBB " << "     " << "      I       " << "     " << "      I" << endl;
    cout << "B             B" << "     " << "      I       " << "     " << "      I" << endl;
    cout << "B             B" << "     " << "      I       " << "     " << "      I" << endl;
    cout << "B             B" << "     " << "      I       " << "     " << "      I" << endl;
    cout << "BBBBBBBBBBBBB  " << "     " << "IIIIIIIIIIIII " << "     " << "IIIIIIIIIIIII" << endl;
    cout << RESET << endl;
}

int main() {
    cout << BOLD << "Beginning Vector Tests..." << RESET << endl;
    cout << endl;

    cout << BOLD << "Section Key" << RESET << endl;
    cout << "Section A : Constructors/Destructor" << endl;
    cout << "Section B : Capacity" << endl;
    cout << "Section C : Modifiers" << endl;
    cout << "Section D : Element Viewing" << endl;
    cout << "Section E : Memory Handling" << endl;
    cout << "Section F : Operators" << endl;
    cout << "Section G : Iterators" << endl;
    cout << "Section H : Friends" << endl;
    cout << "Section I : Non-Members" << endl;
    cout << endl;

    // maybe add a request system to see which sections should be tested

    // get testSize
    int testSize = 0;
    std::string response;
    cout << "What is the desired test size (enter/return for default test size): ";
    std::getline(std::cin, response);
    if (response.empty()) {
        testSize = 1000000;
    } else {
        testSize = stoi(response);
    }
    cout << endl;
    
    // for use in testing
    int numTestsFailed = 0;
    int numTestsPassed = 0;
    
    // maybe decompose this section
    doTest('A', section_A, testSize, numTestsPassed, numTestsFailed, testA);
    doTest('B', section_B, testSize, numTestsPassed, numTestsFailed, testB);
    doTest('C', section_C, testSize, numTestsPassed, numTestsFailed, testC);
    doTest('D', section_D, testSize, numTestsPassed, numTestsFailed, testD);
    doTest('E', section_E, testSize, numTestsPassed, numTestsFailed, testE);
    doTest('F', section_F, testSize, numTestsPassed, numTestsFailed, testF);
    doTest('G', section_G, testSize, numTestsPassed, numTestsFailed, testG);
    doTest('H', section_H, testSize, numTestsPassed, numTestsFailed, testH);
    doTest('I', section_I, testSize, numTestsPassed, numTestsFailed, testI);

    // Inform user as to which tests passed
    if (!numTestsFailed) {
        cout << BOLD << "Passed all " << numTestsPassed << " tests!" << RESET << endl;
    } else {
        cout << "Passed " << BOLD << numTestsPassed << RESET << " out of " << BOLD << numTestsPassed + numTestsFailed << RESET << " tests." << endl;
    }

    // Closing Sequence
    closingSequence();

    return 0;
}