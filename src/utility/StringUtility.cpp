/*
 * StringUtility.cpp
 *
 *  Created on: Aug 14, 2015
 *      Author: Daniel Cotter
 */

#include "headers/StringUtility.h"

unsigned int StringUtility::findOccurrences(string data, string token) {
	unsigned int occurrences = 0;

	for (unsigned int i = 0; i < data.length(); i++) {
		i = data.find(token, i);

		if (i >= data.length())
			break;

		occurrences++;
	}

	return occurrences;
}

list<string> StringUtility::explode(string data, string token) {
	list<string> tokenized;

	for (unsigned int i = 0, end = 0; end < data.length(); i++) {
		end = data.find(token, i);

		if (end > data.length())
			end = data.length();

		tokenized.push_back(data.substr(i, (end - i)));
		i = end + (token.length() - 1);
	}

	return tokenized;
}

string StringUtility::trim(string data) {
	unsigned int final = data.length();

	for (unsigned int i = data.length() - 1; i > 0; i--) {
		if (data[i] == '\n' || data[i] == '\r' || data[i] == ' ')
			final--;
		else
			break;
	}

	return data.substr(0, final);
}
