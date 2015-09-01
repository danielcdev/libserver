/*
 * StringUtility.h
 *
 *  Created on: Aug 14, 2015
 *      Author: Daniel Cotter
 */

#ifndef UTILITY_STRINGUTILITY_H_
#define UTILITY_STRINGUTILITY_H_

#include <string>
#include <list>

using namespace std;

class StringUtility {

public:
	static unsigned int findOccurrences(string data, string token);
	static list<string> explode(string data, string token);
	static string trim(string data);
};

#endif /* UTILITY_STRINGUTILITY_H_ */
