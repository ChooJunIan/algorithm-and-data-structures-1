#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <regex>
#include "PriorityQueue_maxHeap.cpp"

// function prototypes for file I/O
void saveEmailsToFile(std::vector<std::string> &emailList, std::string file_name);
void readEmailsFromFile(std::vector<std::string> &emailList, std::string fileName);

// driver program
int main() {
	const std::string datasetFilenames[3] 
		= {"SetA.txt", "SetB.txt", "SetC.txt"}; // filenames for the respective data sets
	std::vector<std::string> emailList; // vector to store the emails to be inserted into the queue
	std::vector<std::string> orderedEmailList; // vector to store the emails that are removed from the queue
	PriorityQueue<std::string> emailPQ; // priority queue that uses a max heap to store the emails

	// loop through each data set to perform the required operations
	for (int i = 0; i < 3; i++) {
		std::cout << "Enqueing and dequeing for emails in " + datasetFilenames[i] 
			<< "..." << std::endl;

		// read all the emails from a data set file
		readEmailsFromFile(emailList, datasetFilenames[i]);

		// insert all emails into the priority queue, display the time taken
		auto startTime = std::chrono::high_resolution_clock::now();
		for(auto e : emailList) {
			emailPQ.enqueue(e);
		}
		auto endTime = std::chrono::high_resolution_clock::now();
		double elapsedTime 
			= std::chrono::duration<double, std::milli>(endTime - startTime).count();
		std::cout << emailPQ.size() <<  " emails enqueued into the priority queue within " 
			<< elapsedTime << " ms" << std::endl;

		// remove 10% of emails from the priority queue, display the time taken
		int dequeAmount = emailPQ.size() / 10; // 10 % to dequeue
		startTime = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < dequeAmount; i++) {
			orderedEmailList.push_back(emailPQ.dequeue());
		}
		endTime = std::chrono::high_resolution_clock::now();
		elapsedTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
		std::cout << dequeAmount <<  " emails dequeued from the priority queue within " 
			<< elapsedTime << " ms\n" << std::endl;

		// save the removed emails to file
		std::string outputFile = datasetFilenames[i] + "_dequeued.txt";
		saveEmailsToFile(orderedEmailList, outputFile);

		// clear the priority queue and email lists
		emailPQ.clear();
		emailList.clear();
		orderedEmailList.clear();
	}
}

// function to store a list of emails into a text file
void saveEmailsToFile(std::vector<std::string> &emailList, std::string file_name){
	std::ofstream out_to_file;
	out_to_file.open(file_name);

	for (auto i : emailList){
		out_to_file << i << std::endl;
	}

	out_to_file.close();
}

// function to read emails from a specified text file
void readEmailsFromFile(std::vector<std::string> &emailList, std::string fileName){
	std::regex emailValidator("[A-Za-z0-9]{4}.[A-Za-z0-9]{4}@[A-Za-z]{5}.(com|net|org)");
	std::ifstream read_file;
	std::string emails_read;

	emailList.clear();
	int emailCount = 0;
	int invalidEmailCount = 0;

	read_file.open(fileName);

	if (!read_file){
		std::cerr << fileName << " not found!" << std::endl;
		return;
	}

	while (read_file >> emails_read){
		// check if the emails match the regex
		if (std::regex_match(emails_read, emailValidator)){
			emailList.push_back(emails_read);
		}
		else{
			invalidEmailCount++;
		}
	}	

	read_file.close();

	std::cout << emailList.size() << " emails successfully read from file. ";
	std::cout << invalidEmailCount << " invalid email(s) found" << std::endl;
}