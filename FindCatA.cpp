// FindCatA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <cctype>

#include <algorithm>

using namespace std;


void show_match_options() {
	cout << "Select options" << endl;
	cout << "1) Word (exact matches only)" << endl;
	cout << "2) Pattern (exact matches + part of a larger word)" << endl;
	cout << "Your choice: ";
}

int count_word_from_file(istream& file, string word) {
	string word_from_file;
	int countwords = 0;
	while (file >> word_from_file) // for each candidate word read from the file 
	{
		// this removes , ! . and any other special characters
		word_from_file.erase(std::remove_if(word_from_file.begin(), word_from_file.end(),
			[](auto const& c) -> bool { return !std::isalnum(c); }), word_from_file.end());

		if (word == word_from_file) ++countwords;

	}
	return countwords;
}



int count_pattern_from_file(istream& file, string word) {
	string line;
	int countwords = 0;
	while (getline(file, line)) {
		int found = line.find(word);
		while (found != string::npos) {
			++countwords;
			found = line.find(word, found + 1);
		}
	}
	return countwords;
}

int count_pattern_from_console(string word) {

	cout << "Enter the text below. type ESC to exit press Enter key twice" << endl;
	string line;
	int countwords = 0, found;
	do {
		getline(cin, line);
		found = line.find(word);
		while (found != string::npos) {
			++countwords;
			found = line.find(word, found + 1);
		}
	} while (line != "ESC");

	return countwords;
}

int count_word_from_console(string word) {
	cout << "Enter the text below. type ESC to stop" << endl;
	string line, word_input;
	int countwords = 0;

	do // for each candidate word read from the file 
	{
		// this removes , ! . and any other special characters
		word_input.erase(std::remove_if(word_input.begin(), word_input.end(),
			[](auto const& c) -> bool { return !std::isalnum(c); }), word_input.end());

		if (word == word_input) ++countwords;
		cin >> word_input;


	} while (word_input != "ESC");
	return countwords;
}


int main()
{
	int file_choice, countwords, exitcode = 1, match_choice, dummy;
	string word, line, input, path = "", oldpath;
	while (exitcode) {
		cout << "1) From File" << endl;
		cout << "2) From Console \n" << endl;
		cout << "your choice: ";
		cin >> file_choice;
		if (file_choice == 1) {
			cout << "Write the path of the file\n";
			oldpath = path;
			if (path == "") {
				cin >> path;
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "The default will be the previous path you opened" << endl;

				getline(cin, path);
				if (path.empty()) {
					path = oldpath;
				}

			}

			ifstream file(path.c_str());

			if (!file.is_open())
			{
				cerr << "Error! File not found!\nTry again\n";
				continue;
			}

			cout << "File '" << path << "' opened.\n";

			cout << "Write the word you're searching for\n";
			cin >> word;
			show_match_options();
			cin >> match_choice;
			if (match_choice == 1) {
				countwords = count_word_from_file(file, word);
			}
			else {
				countwords = count_pattern_from_file(file, word);
			}

		}



		else if (file_choice == 2) {
			cout << "Write the word you're searching for\n";
			cin >> word;
			show_match_options();
			cin >> match_choice;

			cout << "Now, write the text to search from" << endl;
			if (match_choice == 1) {
				countwords = count_word_from_console(word);
			}
			else {
				countwords = count_pattern_from_console(word);
			}


		}
		else {
			cout << "Please Enter a correct choice.\n" << endl;
			continue;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "The word '" << word << "' has been found " << countwords << " times.\n";
		cout << endl;
		cout << "\nPress 0 to exit \nPress any number to search again: \n";
		cin >> exitcode;
	}

	return 0;

}