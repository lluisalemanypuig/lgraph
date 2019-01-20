// C includes
#include <string.h>

// C++ includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// custom includes
#include "definitions.hpp"
#include "parse_keywords.hpp"

err_type get_type_keyword(const string& filename, ifstream& fin, string& type) {
	string field;
	fin >> field;

	if (field != "TYPE") {
		cerr << ERROR("main.cpp", "get_type_keyword") << endl;
		cerr << "    In input test file '" << filename << "'." << endl;
		cerr << "    First field is not 'TYPE'." << endl;
		cerr << "    Field found: '" << field << "'." << endl;
		return err_type::first_no_TYPE;
	}

	fin >> type;
	return err_type::no_error;
}

void get_keywords(const string& type, vector<string>& keywords) {
	bool finish = false;

	size_t dash_pos = 0;
	do {
		size_t new_dash_pos = type.find("-", dash_pos);
		if (new_dash_pos != string::npos) {
			string keyword = type.substr(dash_pos, new_dash_pos - dash_pos);
			keywords.push_back(keyword);
			dash_pos = new_dash_pos + 1;
		}
		else {
			string keyword = type.substr(dash_pos, type.length() - dash_pos);
			keywords.push_back(keyword);
			finish = true;
		}
	}
	while (not finish);
}

int main(int argc, char *argv[]) {
	// error checking
	if (argc == 1) {
		cerr << ERROR("main.cpp", "main") << endl;
		cerr << "    No arguments given. Use" << endl;
		cerr << "        ./tests -i" << endl;
		cerr << "        ./tests --input" << endl;
		cerr << "    to specify an input test file." << endl;
		return 1;
	}
	if (argc > 3) {
		cerr << ERROR("main.cpp", "main") << endl;
		cerr << "    Too many arguments given. Use" << endl;
		cerr << "        ./tests -i" << endl;
		cerr << "        ./tests --input" << endl;
		cerr << "    to specify an input test file." << endl;
		return 1;
	}
	if (strcmp(argv[1], "-i") != 0 and strcmp(argv[1], "--input") != 0) {
		cerr << ERROR("main.cpp", "main") << endl;
		cerr << "    Unrecognised parameter '" << string(argv[1]) << "'. Use" << endl;
		cerr << "        ./tests -i" << endl;
		cerr << "        ./tests --input" << endl;
		cerr << "    to specify an input test file." << endl;
		return 1;
	}

	string input_file(argv[2]);
	ifstream fin;
	fin.open(input_file.c_str());
	if (not fin.is_open()) {
		cerr << ERROR("main.cpp", "main") << endl;
		cerr << "    Could not open input test '" << input_file << "'" << endl;
		return 1;
	}

	string type;
	err_type r = get_type_keyword(input_file, fin, type);

	if (r == err_type::first_no_TYPE) {
		// some error occurred
		return 1;
	}

	vector<string> keywords_type;
	get_keywords(type, keywords_type);

	r = exe_tests::call_main(keywords_type, fin);
	return (r == err_type::no_error ? 0 : 1);
}

