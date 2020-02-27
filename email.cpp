#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

enum charType {upper_letter, lower_letter, at, underscore, dot, hyphen, unrecognized};
struct Email {string name = ""; bool at = false; bool domain = false; bool dot = false; bool extension = false;};
// enum state {empty, on_name, read_underscore, }

 

int main () {
	cout << "Give input and type 'Done' when finished:" << endl;

	string line_in;
	vector<string> output;

	while (cin >> line_in) {
		size_t line_len = line_in.size();
		string line = line_in;

		if (line == "Done") {
			break;
		}
		
		Email email;

		// first pass: convert _at_ and _dot_
		for (int i = 0; i < line_len; i++) {
			char c = line[i];
			charType type;


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
			else {
				type = unrecognized;
				// throw error: unrecognized character
			}

			// use substring to check for _at_ and _dot_
			// while (true) {

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

				if (!found_at && !found_dot) break;

			// }

			

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