#pragma once

#include <string>
#include <vector>

// Useful macros
#define ALL(v) (v).begin(), (v).end()
#define foreach(v, it) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); it++)

// This constant can be used to represent null/empty fields
const std::string NULL_FIELD_LABEL = "null";

// System dependent special key codes
#ifdef __linux__
// linux system
const char BACKSPACE_CODE = 127;
const char ENTER_CODE = 10;
const char ESC_CODE = 27;
#elif _WIN32
// windows system
const char BACKSPACE_CODE = 8;
const char ENTER_CODE = 13;
const char ESC_CODE = 27;
#endif

/**
 * Returns true if the received char is valid.
 *
 * @param c The char to be analyzed.
 * @return True if c is valid, false otherwise.
 */
bool isValid(char c);

/**
 * Returns a lower case version of the received string.
 *
 * @param str The string to be lower cased.
 * @return The lower cased input string.
 */
std::string toLower(std::string str);

/**
 * Returns an upper case version of the received string.
 *
 * @param str The string to be upper cased.
 * @return The upper cased input string.
 */
std::string toUpper(std::string str);

/**
 * Returns true if the specified field is null.
 * A null field is identified by the NULL_FIELD_LABEL constant
 *
 * @param field The string of the field to be tested.
 * @return True if the string matches the NULL_FIELD_LABEL.
 */
bool fieldIsNull(std::string field);

/**
 * Returns a vector of strings containing all the tokens in str
 * separated by the specified string separator.
 *
 * @param str The string to separate in tokens.
 * @param separator The string that represents the tokens separator.
 * @return A vector of strings which contains the tokens.
 */
std::vector<std::string> getTokens(std::string str, std::string separator);

void clearScreen();

void clearStdIn();

void pressEnterToContinue();

void clearStdInAndPressEnterToContinue();
