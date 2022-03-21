#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <regex>
#include "sharedFileForProgram.h"
#include <ctime>
#include <fstream>

#include <chrono>
// =======================================
//
//
//
// =======================================

// --------------------------------------
//
// readGeneratedEmailFromFile(vector<string>, string)
// - reads from text file (reads by one token at a time) and puts it to the given <vector> object
//  (from here, you should be able to just dump the vector to your data structure)
// - makes sure the email read from file satisfies the regex 
//		[A-Za-z0-9]{4}\.[A-Za-z0-9]{4}@[A-Za-z]{5}\.(com|net|org)
// - Note that invalid tokens () would be counted as invalid email, even if they're just bunch of random character 
// 		(separated by spaces!)
// http://www.cplusplus.com/doc/tutorial/basic_io/

// On the side note, using iostream::eof() is a bad way to determine whether last line is reached or not
// chances are you'll read the last line twice
// 
// --------------------------------------
void readGeneratedEmailFromFile(std::vector<std::string> &emailList, std::string fileName){
	//std::cout << "Do nothing me thinks" << std::endl;

	std::regex emailValidator("[A-Za-z0-9]{4}.[A-Za-z0-9]{4}@[A-Za-z]{5}.(com|net|org)");

	std::ifstream read_file;
	std::string emails_read;

	// Make sure you expect that email list is cleared before you pass it into this function
	emailList.clear();
	int emailCount = 0;
	int invalidEmailCount = 0;

	read_file.open(fileName);

	if (!read_file){
		std::cerr << fileName << " not found!" << std::endl;
		return;
	}

	while (read_file >> emails_read){
		

		if (std::regex_match(emails_read, emailValidator)){
			emailList.push_back(emails_read);

		}

		else{
			invalidEmailCount++;
		}
	}	

	read_file.close();

	std::cout << emailList.size() << " emails successfully read from file" << std::endl;
	std::cout << invalidEmailCount << " invalid email found\n" << std::endl;

	// for (auto i : emailList){
	// 	std::cout << i << std::endl;
	// }
}


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
// Reference from https://inversepalindrome.com/blog/how-to-create-a-random-string-in-cpp
// Also, this kinda helps in formulating the function (but kinda talks about how to inteprate and generate random string
//		from regex in general) which we thankfully doesn't have to deal with
// https://salesforce.stackexchange.com/questions/54483/how-to-generate-a-random-string-value-based-on-regex-pattern
// ---------------------------------------
void generateEmail(std::vector<std::string> &emailList, int count){

	std::regex emailValidator("[A-Za-z0-9]{4}.[A-Za-z0-9]{4}@[A-Za-z]{5}.(com|net|org)");
	// [A-za-z0-9]

	// Clear 
	emailList.clear();
	//unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::time_t t;
	const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	const std::string LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	const std::vector<std::string> domainEmail{"com", "net", "org"};
	//std::random_device random_device;
	std::mt19937 generator(std::time(&t));

	// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	// This is for generating a random int for selecting [A-Za-z0-9]
	std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);
	std::uniform_int_distribution<> distribution_letters(0, LETTERS.size() - 1);
	std::uniform_int_distribution<> end_selector(0, 2);

	bool uniqueGeneratedEmail;

	// Now everything is ready, time to start measuring the time to generate the emails
	// https://stackoverflow.com/a/50208531
	auto t_start = std::chrono::high_resolution_clock::now();

	while (emailList.size() < count)
	{
		std::string possible_generated_mail;
	
	
		// First part of the email
		// [A-Za-z0-9]{4}\.[A-Za-z0-9]{4}@[A-Za-z]{5}\.(com|net|org)
		//       ^
		// in which it'll be repeated 4 times, and ends with .
		for (int i = 0; i < 4; i++){
			possible_generated_mail += (CHARACTERS[distribution(generator)]);
		}
	
		possible_generated_mail.append(".");
	
		// Second part of the email
		// [A-Za-z0-9]{4}\.[A-Za-z0-9]{4}@[A-Za-z]{5}\.(com|net|org)
		//                         ^
		// in which it'll be repeated 4 times, and ends with @
	    for (int i = 0; i < 4; i++){
			possible_generated_mail += (CHARACTERS[distribution(generator)]);
		}
		//std::cout << possible_generated_mail << std::endl;
	
		possible_generated_mail.append("@");
	
		// Third part of the email
		// [A-Za-z0-9]{4}\.[A-Za-z0-9]{4}@[A-Za-z]{5}\.(com|net|org)
		//                                      ^
		// in which it'll be repeated 5 times, and ends with another "."
		for (int i = 0; i < 5; i++){
			possible_generated_mail += (LETTERS[distribution_letters(generator)]);
		}
		//std::cout << possible_generated_mail << std::endl;
	
		possible_generated_mail.append(".");
	
	
		// Fourth part of the email
		// [A-Za-z0-9]{4}\.[A-Za-z0-9]{4}@[A-Za-z]{5}\.(com|net|org)
		//                                                  ^
		// It will select either of the 3 selection and appends it to the string
		possible_generated_mail += (domainEmail[end_selector(generator)]);
	
		//std::cout << possible_generated_mail << std::endl;
	

		// Just verifying the regex, though it should match in general
		// Might want to comment this out if speed is of concern, though not particular sure how slow
		// 	this function is
		// Although, it doesn't make use of too much * so it should be relatively fast whatnot
		// Relative speed of regex - https://www.loggly.com/blog/regexes-the-bad-better-best/

		//std::cout << "Email generated : " << possible_generated_mail << std::endl;
		// if (std::regex_match (possible_generated_mail, emailValidator)){
		// 	// emailList.push_back(possible_generated_mail);
		// }
		// else{
		// 	std::cout << "Email " << possible_generated_mail << " is invalid\n" << std::endl;
		// }

		// If not a match, skip the duplicate checker and proceed to the next generator iteration
		if (!(std::regex_match(possible_generated_mail, emailValidator))) {
			std::cout << "Email " << possible_generated_mail << " is invalid\n" << std::endl;
			continue;
		}

		// check for duplicate emails the old fashion way..
		// set 'unique' flag to true at first, then linear search for the newly created email in the existing email list, 
		// setting the flag to false if duplicate found. 
		// (WARNING: runs in n^2 time, 500k emails took under 90 minutes. Comment out if you must, the chances of a duplicate is VERY low)
		uniqueGeneratedEmail = true; 
		for (std::string &email : emailList) {
			if (possible_generated_mail.compare(email) == 0) {
				uniqueGeneratedEmail = false;
				break;
			}
		}

		// if the email is unique, add to the list, otherwise don't and proceed to generate another email
		if (uniqueGeneratedEmail)
			emailList.push_back(possible_generated_mail); // add unique email to the list
		else
			std::cout << "Email " << possible_generated_mail << " is not unique, generating another..." << std::endl;
	}

	// Print 
	// for (auto i : emailList){
	// 	std::cout << i << std::endl;
	// }

	// End time here
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();

	// Can only be accurate up to 1ms apparently
	std::cout << emailList.size() <<  " email successfully generated within " << elapsed_time_ms << " ms" << std::endl;
}

// --------------------------------------------------
//
// generateEmailToFile(int, std::string)
// Generate specified amount of emails using generateEmails
//
// By default those emails will be separated line by lines
//
// ---------------------------------------------------
void generateEmailToFile(int count, std::string file_name){
	std::vector<std::string> emailList;

	generateEmail(emailList, count);

	std::ofstream out_to_file;
	out_to_file.open(file_name);

	for (auto i : emailList){
		out_to_file << i << std::endl;
	}

	out_to_file.close();
}