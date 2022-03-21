#include <iostream>
#include <string>
#include <vector>
#include <chrono>	// for calculating time
#include <algorithm> // for std::find
class HashTableWithChaining{

	int bucketCount = 20;	// Also default size
	std::vector<std::vector<std::string>> currentHashTable;
	int num_emails;

private:
	unsigned long hash_function(const char* str){
		unsigned long i = 0;
		for (int j = 0; str[j]; j++){
			i += str[j];
		}
		return i % bucketCount;
	}

public:

	HashTableWithChaining(){
		num_emails = 0;
	}

	// -------------------------------------
	//
	// HashTableWithChaining(int)
	// Constructor for the hash table class (this is by default what constructor you should be calling)
	// 
	//
	// 2d vectors are finicky to work with, especially when you don't intend to use all of it, but
	// 	still need to make sure there's a vector(bucket) in each table
	// https://www.techiedelight.com/initialize-two-dimensional-vector-cpp/
	//
	// -----
	// Extra, error checks
	// -----
	// Need to make sure it's properly initialized 
	//  - there's only a rudimentary check for now, and it doesn't do much
	// However, it should be possible that it may have not be initialized properly, as there might not be 
	//	a bucket/vector properly allocated to the table
	//
	// TODO :
 	//  Should run through the entire bucket to check if vector is properly initialized
	//
	// --------------------------------------
	HashTableWithChaining(int emailCount){
		int calculatedSize = emailCount * 90 / 100;

		//currentHashTable.resize(calculatedSize, std::vecotr<std::string>(1, "nothing"));
		currentHashTable.resize(calculatedSize, std::vector<std::string>(0));
		bucketCount = calculatedSize;

		num_emails = 0;

		// Error check, make sure it's properly initialized (assert might be better)
		// However, it should be possible that it may have not be initialized properly, as there might not be 
		//	a bucket/vector properly allocated to the table
		//
		// TODO :
 		//  Should run through the entire bucket to check if it's there
		//
		if (currentHashTable.size() != bucketCount){
			std::err << "Something gone horribly wrong with hash table creation, size doesn't match up" << std::endl;
			std::err << "Note, currentHashTable size is " << currentHashTable.size() << std::endl;
		}
	}

	// ---------------------------------------
	// 
	// insert(std::string)
	// Find the hash function for given string, then use the index given
	//	to find the bucket to put the string into
	// 
	// Note : 	- does not check for duplicates, but it shouldn't matter anyway as it'd be simply mapped
	// 			to the same bucket/location. 
	//			- however, during search operation, it'll only look at the first element 
	//				- it shouldn't affect the operation in any way that might be impactful to performance
	//
	// ---------------------------------------

	void insert(std::string email){
		int v = hash_function(email.c_str());

		currentHashTable[v].push_back(email);
		num_emails++;
		// if (currentHashTable[v][0].compare("nothing")){
		// 	currentHashTable[v][0] = email;
		// }
		// else{
		// 	currentHashTable[v].push_back(email);
		// }
		
	}

	// ------------------------------------------------------------------
	// search(std::string)
	// Return the location of bucket in which the email is located
	//
	// Search for the email in the hash table
	// Find the hash for the given email, then look through the hash table
	// 	- if found, then return the bucket location where the email is found
	//		- this does not check for how deep the email is in specified bucket
	//			- if there's a need to do so, then I would need to return a key value pair somehow, struct might work
	//	- else return -1
	// Finding index from iterators
	// 	- https://stackoverflow.com/questions/2152986/what-is-the-most-effective-way-to-get-the-index-of-an-iterator-of-an-stdvector
	//
	// ------------------------------------------------------------------
	int search(const std::string email){
		int v = hash_function(email.c_str());

		int searchStatus = -1;
		std::vector<std::string>::iterator it_hash_table;

		// for (auto i : currentHashTable)
		for (std::vector<std::string> i : currentHashTable){
			it_hash_table = std::find(i.begin(), i.end(), email);

			if (it_hash_table != i.end()){
				searchStatus = it_hash_table - i.begin();
				break;
			}
		}

		return searchStatus;
	}

	// ---------------------------------------------
	// search_from_emailList(std::vector<std::string)
	// Given emailList passed onto the parameter, calculate the time taken
	// to search for the emails
	//
	// - Display the amount of emails to lookup/search, num emails found and not found
	// - Display the time
	// 
	// Calculating time
	// https://stackoverflow.com/a/50208531
	//
	// --------------------------------------------
	void search_from_emailList(const std::vector<std::string> &emailList){
		// Now everything is ready, time to start measuring the time to generate the emails
		// https://stackoverflow.com/a/50208531
		auto t_start = std::chrono::high_resolution_clock::now();
		int searchStatus = -1;
		int emailFound = 0;
		int emailNotFound = 0;
		for (auto i : emailList){
			searchStatus = search(i);
			if (searchStatus != -1){
				emailFound++;
			}
			else{
				emailNotFound++;
			}
		}


		auto t_end = std::chrono::high_resolution_clock::now();
		double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();

		std::cout << "From " << emailList.size() << " searched, " << emailFound << " email found and " << emailNotFound << " can't be found from the hash table" << std::endl;
		std::cout << emailList.size() << " emails takes " << elapsed_time_ms << " ms to search" << std::endl; 
		std::cout << std::endl;
	}

	// ---------------------------------------------
	// insert_from_emailList(std::vector<std::string)
	// Given emailList passed onto the parameter, calculate the time taken
	// to search for the emails
	//
	// - Display the amount of emails to lookup/search, num emails found and not found
	// - Display the time
	// 
	// Calculating time
	// https://stackoverflow.com/a/50208531
	//
	// --------------------------------------------
	void insert_from_emailList(const std::vector<std::string> &emailList){

		// Now everything is ready, time to start measuring the time to generate the emails
		// https://stackoverflow.com/a/50208531
		auto t_start = std::chrono::high_resolution_clock::now();

		for (auto i : emailList){
			insert(i);
		}

		// End time here
		auto t_end = std::chrono::high_resolution_clock::now();
		double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
		std::cout << emailList.size() << " successfully inserted within " << elapsed_time_ms << " ms" << std::endl;
		std::cout << std::endl;
	}

	// // Note that this is a bit dangerous to do, albeit an option
	// // Remaps the current item in the hash table to the newly resized hash table

	// // Will do later probably
	// void resize_hash_table(int size){
	// 	std::cout << "Function : resize_hash_table - Currently does not do anything, go away" << std::endl;
	// }

	int size(){
		return num_emails;
	}

	double getLoadFactor(){
		int n_table_occupied = 0;
		for (auto i : currentHashTable){
			for (auto j : i){
				if (j.size() != 0)
					n_table_occupied++;
			}
		}

		return n_table_occupied / bucketCount;
	}

	// ------------------------------------
	//
	// printHashTable()
	// Print the hash table
	// 	- it'll be printed according to their 
	// Adding int to string (apparently not as easy as java)
	// 	- https://stackoverflow.com/questions/64782/how-do-you-append-an-int-to-a-string-in-c/64815
	// ------------------------------------
	void printHashTable(){
		// for (int i = 0; i < bucketCount; i++){
		// 	std::string currentBucket;

		// 	currentBucket.append(i + ": [");
		// 	std::cout << "Append string";
		// 	for (auto j : currentHashTable[i]){
		// 		std::cout << "It goes in here" << std::endl;
		// 		currentBucket.append(j + " ");

		// 	}

		// 	currentBucket[currentBucket.size() - 1] = ']';

		// 	std::cout << currentBucket << std::endl;
		// }
		// for (int i = 0; i < bucketCount; i++){
		// 	std::cout << " size" << currentHashTable[i].size() << std::endl;
		// }

		int count = 0;
		for (auto i : currentHashTable){
			//std::cout << "Going through hash table" << std::endl;
			std::string currentBucket;
			currentBucket.append(std::to_string(count));
			currentBucket.append(": [");
			count++;

			for (std::string j : i){
				//std::cout << "Am here";
				currentBucket.append(j + " ");
				// std::cout << j;
			}

			if (currentBucket[currentBucket.size() - 1] == '['){
				currentBucket.append("]");
			}
			else {
				currentBucket[currentBucket.size() - 1] = ']';
			}

			std::cout << currentBucket << std::endl;
			//std::cout << std::endl;
		}
	}
};