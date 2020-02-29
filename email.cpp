#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define NUM_VALID_DOMAIN_NAMES 6

using namespace std;

enum charType {upper_letter, lower_letter, at, underscore, dot, hyphen, number, unrecognized};
charType getCharType(char c);
bool isValidDomainType(charType type);
string domain_names[] = {"co.nz" , "com.au", "co.ca", "com", "co.us", "co.uk"};

// struct Email {string name = ""; bool at = false; bool domain = false; bool dot = false; bool extension = false;};
// enum state {empty, on_name, read_underscore, }

 

int main () {
	cout << "Give input and type 'Done' when finished:" << endl;

	string line_in;
	vector<string> output;

	while (cin >> line_in) {
		size_t line_len = line_in.size();
		string line = line_in;

		string errorMessage = "";
		size_t num_of_ats = 0;

		if (line == "Done") {
			break;
		}
		
		// Email email;

		// first pass: convert _at_ and _dot_
		for (int i = 0; i < line_len; i++) {
			char c = line[i];
			charType type = getCharType(c);

			if (type == unrecognized) {
				errorMessage = "unrecognized character(s)";
			}

			
			// use substring to check for _at_ and _dot_

			while (true) {

				bool found_at = false, found_dot = false;

				size_t found = line.find("_at_");
				if (found != string::npos) {
					line.replace(found, 4, "@");
					found_at = true;
				}
			
				found = line.find("_dot_");
				if (found != string::npos) {
					line.replace(found, 5, ".");
					found_dot = true;
				}

				if (!found_at && !found_dot) 
				{
					break;
				}

			}
			

			// check final string for correct number of @'s
			size_t num_ats = 0;
			string line_copy = line;
			while (true) {
				size_t found = line_copy.find("@");
				if (found != string::npos) {
					num_ats++;
					line_copy.erase(found, 1);
				}
				else break;
			}
			if (num_ats > 1) {
				errorMessage = "too many '@'s";
			}
			else if (num_ats < 1) {
				errorMessage = "missing @";
			}


			// check that there are valid domain and mailbox names
			if (num_ats == 1) {
				size_t at_pos = line.find("@");
				charType type1 = getCharType(line[at_pos + 1]);
				
				if (!isValidDomainType(type1)) {
					errorMessage = "Invalid domain name";
				}

				charType type2 = getCharType(line[0]);
				if (!isValidDomainType(type2)) {
					errorMessage = "Invalid mailbox name";
				}
			}

			
			// TODO: check for valid domain extension
			bool valid_ext = false;
			for (int i = 0; i < NUM_VALID_DOMAIN_NAMES; i++) {
				string domain_ext = domain_names[i];
				size_t ext_size = domain_ext.size();
				size_t extension_pos = line.find(domain_ext);
				size_t last_pos = line.size() - 1;
				if (extension_pos != string::npos) {
					valid_ext = true;
					if (extension_pos + ext_size != last_pos + 1) {
						valid_ext = false; // not in the last position
					}
					else break;
				}
			}
			if (!valid_ext) {
				errorMessage = "no valid domain extension";
			}



			// convert uppercase to lowercase
			if (type == upper_letter) {
				line[i] += 32;
			}


			// error handling
			if (errorMessage != "") {
				line = line_in + " <-- " + errorMessage;
				break;
			}
			
		}

	output.push_back(line);

	}

	// print output
	reverse(output.begin(), output.end());

	while(!output.empty()) {
		cout << output.back() << endl;
		output.pop_back();
	}

	return 0;
}

charType getCharType(char c) {
	charType type;

	cout << c << endl;

	// determine type of character
	if (c >= 65 && c <= 90) {
		type = upper_letter;
	}
	else if (c >= 97 && c <= 122) {
		type = lower_letter;
	}
	else if (c == 64) {
		type = at;
	}
	else if (c == 95) {
		type = underscore;
	}
	else if (c == 46) {
		type = dot;
	}
	else if (c == 45) {
		type = hyphen;
	}
	else if (c >= 48 && c <= 57) {
		type = number;
	}
	else {
		type = unrecognized;
	}

	return type;
}

bool isValidDomainType(charType type) {
	if (type == lower_letter || type == upper_letter
	|| type == hyphen || type == underscore 
	|| type == number) {
		return true;
	}

	return false;
}