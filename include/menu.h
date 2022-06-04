#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "graph.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#define TERMINAL_CLEAR  if(system(CLEAR)){}

using namespace std;

/**
 * Removes empty spaces from the start and end of a string
 * @param str string to be trimmed
 * @return trimmed string
 */
string trimStr(string str);

/**
 * Tests if IOstream buffer is empty
 * @param ios buffer to be tested
 * @return boolean if buffer is empty
 */
bool emptyStream(istream &ios);


/**
 * Simple Menu Terminal GUI
 * prompting user to choose one of the 3 scenarios
 */
class Menu {
public:
    /**
     * Starts the Menu Terminal GUI
     */
    static void start();

    /**
     * Asks user for a number after displaying the message
     */
    static int askInt(const string &message);

    /**
     * It displays the results given to the user in a friendly way
     * @param capacity
     * @param path
     */
    static void displayResults(int capacity, const list<int> &path);

private:

    /**
     * Shows a submenu for the scenario 1
     * and handles user input
     */
    static void submenu1();

    /**
     * Asks information from the user, processes the information
     * according to the scenario, and displays the results.
     * @param option
     */
    static void scenario1(int option);

    /**
     * Shows a submenu for the scenario 2
     * and handles user input
     */
    static void submenu2();

    /**
     * Asks information from the user, processes the information
     * according to the scenario, and displays the results
     * @param option
     */
    static void scenario2(int option);

};


#endif //MENU_H