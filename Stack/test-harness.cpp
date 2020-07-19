#include "stack.h"
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
const bool section_A = true; // Constructors/Destructor (4 Methods)
const bool section_B = true; // Capacity (2 Methods)
const bool section_C = true; // Modifiers (2 Methods)
const bool section_D = true; // Element Viewing (2 Methods)
const bool section_E = true; // Operators (4 Methods)
const bool section_F = true; // Friends (2 Methods)
const bool section_G = true; // Non-Members (3 Methods)

/** 
 * Given two values, returns true if they are equal
 */
template <typename T, typename S>
bool expectEqual(T first, S second) {
    return first == second;
}

/**
 * Macro for testing Stack Constructor/Destructor methods
 */
void testA(const int size, int& numTestsPassed, int& numTestsFailed) {
    cout << "Hello from testA!" << endl;
}

/**
 * Macro for testing Stack Capacity methods
 */
void testB(const int size, int& numTestsPassed, int& numTestsFailed) {
    Stack<int> stk;
    for (int i = 0; i < size; i++) {
        stk.push(i);
    }
    
    // test size
    if (!expectEqual(stk.size(), size)) {
        cout << "Size : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Size : PASSED" << endl;
        numTestsPassed++;
    }

    // test empty
    if (stk.empty()) {
        cout << "Empty : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Empty : PASSED" << endl;
        numTestsPassed++;
    }

}

/**
 * Macro for testing Stack Modifier methods
 */
void testC(const int size, int& numTestsPassed, int& numTestsFailed) {
    Stack<std::string> stk;

    // test push    
    for (int i = 0; i < size; i++) {
        stk.push("Eva");
    }
    if (!expectEqual(stk.size(), size)) {
        cout << "Push : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Push : PASSED" << endl;
        numTestsPassed++;
    }
    
    // test pull
    for (int i = size; i > 0; i--) {
        stk.pull();
    }
    if (!stk.empty()) {
        cout << "Pull : FAILED" << endl;
        numTestsFailed++;
    } else {
        cout << "Pull : PASSED" << endl;
        numTestsPassed++;
    }

}

/**
 * Macro for testing Stack Element Viewing methods
 */
void testD(const int size, int& numTestsPassed, int& numTestsFailed) {
    Stack<std::string> stk;

    stk.push("Some kind of general message, I suppose");

    // test non-const top
    if (!expectEqual(stk.top(), "Some kind of general message, I suppose")) {
        cout << "Top (non-const) : FAILED" << endl;
        numTestsFailed++;
    }
    stk.top() = "Camp Lejeune";
    std::string top = stk.pull();
    if (!expectEqual(top, "Camp Lejeune")) {
        cout << "Top (non-const) : FAILED" << endl;
    } else {
        cout << "Top (non-const) : PASSED" << endl;
        numTestsPassed++;
    }
}

/**
 * Macro for testing Stack Operator methods
 */
void testE(const int size, int& numTestsPassed, int& numTestsFailed) {
    cout << "Hello from testE!" << endl;
}

/**
 * Macro for testing Stack Friend methods
 */
void testF(const int size, int& numTestsPassed, int& numTestsFailed) {
    cout << "Hello from testF!" << endl;
}

/**
 * Macro for testing Stack Non-Member methods
 */
void testG(const int size, int& numTestsPassed, int& numTestsFailed) {
    cout << "Hello from testG!" << endl;
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
    cout << BOLD << "Beginning Stack Tests..." << RESET << endl;
    cout << endl;

    cout << BOLD << "Section Key" << RESET << endl;
    cout << "Section A : Constructors/Destructor" << endl;
    cout << "Section B : Capacity" << endl;
    cout << "Section C : Modifiers" << endl;
    cout << "Section D : Element Viewing" << endl;
    cout << "Section E : Operators" << endl;
    cout << "Section F : Friends" << endl;
    cout << "Section G : Non-Members" << endl;
    cout << endl;

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