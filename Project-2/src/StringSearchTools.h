#pragma once

#include <string>

/**
 * Returns the distance between two strings.
 * If the distance returned is equal to 0 (zero), the strings are the same.
 * The greater the distance, the least is the similarity between the strings.
 *
 * getEditDistanceOPT - Space complexity: O(|P|.|T|)
 * getEditDistanceOT  - Space complexity: O(|T|)
 *
 * @param needle The string to be searched.
 * @param haystack The string where to search the needle.
 * @return The distance between the inputed strings.
 */
int getEditDistanceOPT(std::string needle, std::string haystack);
int getEditDistanceOT(std::string needle, std::string haystack);
