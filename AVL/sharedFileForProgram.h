#ifndef SHARED_FILE_FOR_PROGRAM
#define SHARED_FILE_FOR_PROGRAM

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <regex>
#include <ctime>
#include <fstream>
// ==================================================
// 
// This functions listed is for generating email list 
//	(including reading and saving those emails to/from files)
// 
// ==================================================

// --------------------------------------
//
// readGeneratedEmailFromFile(vector<string>, string)
// - reads from text file (reads by one token at a time) and puts it to the given <vector> object
//  (from here, you should be able to just dump the vector to your data structure)
// - it makes sure the email read from file satisfies the regex 
//		[A-Za-z0-9]{4}\.[A-Za-z0-9]{4}@[A-Za-z]{5}\.(com|net|org)
// - Note that invalid tokens () would be counted as invalid email, even if they're just bunch of random character 
// 		(separated by spaces!)
// - Does not check for duplicates(!)
// http://www.cplusplus.com/doc/tutorial/basic_io/
// Output 

// On the side note, using iostream::eof() is a bad way to determine whether last line is reached or not
// chances are you'll read the last line twice
// 
// --------------------------------------
void readGeneratedEmailFromFile(std::vector<std::string> &emailList, std::string fileName);


// ---------------------------------------
//
// generateEmail(&vector<string>, int)
// Generate (count) number of emails and put it to emailList vector (arraylist equivalent)
//
// Note : 	The string vector would be cleared out, then a newly generated one will be add to the vector
//			This does not check for duplicates (should it?)
// In this generator, the regex would be strictly defined as 
//		- [A-Za-z0-9]{4}\.[A-Za-z0-9]{4}@[A-Za-z]{5}\.(com|net|org)

// Generating random email
// 1. 	First define a string of specific length for given alphabet [A-Za-z0-9] and [com|met|org]
//			- this done by specifying a string with all the given characters for specific part
// 2. 	Then assign a random number generator(RNG) in which would give a value between 0 and 
//		length of string as defined above
//			- in this function, we're using merseen twister randomizer function as defined by std::random 
//			from <random> (honestly the type of randomizer usen shouldn't matter)
// 3. 	With that, generate parts of the email and append it to email string
// 4.	After the process is done, check if it pass the regex, 
//			- if so, add it to the vector
//			- if not, dumps it, report to console and generate a new one 
//				(honestly, it shouldn't do this, but doesn't hurt to test)
// 5.	Repeat until specified amount of email is successfully generated
//			- again, this does not check for duplicates in the list
// Reference from https://inversepalindrome.com/blog/how-to-create-a-random-string-in-cpp
// Also, this kinda helps in formulating the function (but kinda talks about how to inteprate and generate random string
//		from regex in general) which we thankfully doesn't have to deal with
// https://salesforce.stackexchange.com/questions/54483/how-to-generate-a-random-string-value-based-on-regex-pattern
//
// ---------------------------------------
void generateEmail(std::vector<std::string> &emailList, int count);


// --------------------------------------------------
//
// generateEmailToFile(int, std::string)
// Generate specified amount of emails using generateEmails
//
// By default those emails will be separated line by lines
//
// ---------------------------------------------------
void generateEmailToFile(int count, std::string file_name);
#endif