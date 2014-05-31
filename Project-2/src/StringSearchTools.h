#pragma once

#include <string>

/*
 * Returns the distance between the strings.
 *
 * If the distance returned is equal to 0 (zero) the strings are the same.
 * The greater the distance, the least is the similarity between the strings.
 *
 * OPT - space complexity: O(|P|.|T|)
 * OT - space complexity: O(|T|)
 */
int getEditDistanceOPT(std::string needle, std::string haystack);
int getEditDistanceOT(std::string needle, std::string haystack);
