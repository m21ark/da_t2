#ifndef MENU_H
#define MENU_H

#include <iostream>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

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
 * Asks user for a char
 * @return user given char
 */
char askChar();

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

private:

    static void scenario1();

    static void scenario2();

};


#endif //MENU_H