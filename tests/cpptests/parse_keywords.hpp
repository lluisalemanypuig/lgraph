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

// {unweighted/weighted}

err_type call_x
(const vector<string>& keywords, size_t i, ifstream& fin);

// {unweighted/weighted} + {undirected/directed}

err_type call_xx
(const vector<string>& keywords, size_t i, ifstream& fin);

err_type call_xx_metric
(const vector<string>& keywords, size_t i, ifstream& fin);

// {unweighted/weighted} + undirected

err_type call_xu
(const vector<string>& keywords, size_t i, ifstream& fin);
err_type call_xu_metric
(const vector<string>& keywords, size_t i, ifstream& fin);

// unweighted + {undirected/directed}

err_type call_ux
(const vector<string>& keywords, size_t i, ifstream& fin);
err_type call_ux_path
(const vector<string>& keywords, size_t i, const string& graph_type, ifstream& fin);
err_type call_ux_distance
(const vector<string>& keywords, size_t i, const string& graph_type, ifstream& fin);
err_type call_ux_metric
(const vector<string>& keywords, size_t i, const string& graph_type, ifstream& fin);

// weighted + {undirected/directed}

err_type call_wx
(const vector<string>& keywords, size_t i, ifstream& fin);
err_type call_wx_path
(const vector<string>& keywords, size_t i, const string& graph_type, ifstream& fin);
err_type call_wx_distance
(const vector<string>& keywords, size_t i, const string& graph_type, ifstream& fin);
err_type call_wx_metric
(const vector<string>& keywords, size_t i, const string& graph_type, ifstream& fin);

} // -- namespace exe_tests
