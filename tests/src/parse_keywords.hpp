#pragma once

// C++ includes
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// custom includes
#include "definitions.hpp"

namespace exe_tests {

void mark_wrong_keyword
(const vector<string>& keywords, const vector<size_t>& k, const string& tab = "");

/* FUNCTIONS FOR KEYWORD PARSING */

// parses the first keyword and calls the appropriate main type function
err_type call_main(const vector<string>& keywords, ifstream& fin);

err_type call_ux(const vector<string>& keywords, ifstream& fin);
err_type call_ux_path
(const vector<string>& keywords, const string& graph_type, ifstream& fin);
err_type call_ux_distance
(const vector<string>& keywords, const string& graph_type, ifstream& fin);

err_type call_wx(const vector<string>& keywords, ifstream& fin);
err_type call_wx_path
(const vector<string>& keywords, const string& graph_type, ifstream& fin);
err_type call_wx_distance
(const vector<string>& keywords, const string& graph_type, ifstream& fin);

} // -- namespace exe_tests
