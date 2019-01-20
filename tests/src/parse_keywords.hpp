#pragma once

// C++ includes
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// custom includes
#include "definitions.hpp"

namespace exe_tests {

/* FUNCTIONS FOR KEYWORD PARSING */

// parses the first keyword and calls the appropriate main type function
err_type call_main(const vector<string>& keywords, ifstream& fin);

err_type call_ux(const vector<string>& keywords, ifstream& fin);
err_type call_uu(const vector<string>& keywords, ifstream& fin);
err_type call_uu_path(const vector<string>& keywords, ifstream& fin);
err_type call_ud(const vector<string>& keywords, ifstream& fin);
err_type call_ud_path(const vector<string>& keywords, ifstream& fin);

} // -- namespace exe_tests
