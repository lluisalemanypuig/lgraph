#include "parse_keywords.hpp"

// C++ includes
#include <iostream>
using namespace std;

// custom includes
#include "exe_tests.hpp"

namespace exe_tests {

err_type call_main(const vector<string>& keywords, ifstream& fin) {
	const string& key = keywords[0];
	if (key == "unweighted") {
		return call_ux(keywords, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_main") << endl;
	cerr << "    Unknow keyword at 0: '" << key << "'." << endl;
	return err_type::wrong_keyword;
}

err_type call_ux(const vector<string>& keywords, ifstream& fin) {
	const string& key = keywords[1];
	if (key == "undirected" or key == "directed") {
		return call_ux_path(keywords, key, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_ux") << endl;
	cerr << "    Unknow keyword at 1: '" << key << "'." << endl;
	return err_type::wrong_keyword;
}

err_type call_ux_path
(const vector<string>& keywords, const string& graph_type, ifstream& fin)
{
	string key1 = keywords[3];
	string key2 = keywords[4];
	string key3 = keywords[5];

	if (key1 == "node" and key2 == "node") {
		if (key3 == "single") {
			return ux_path_node_node__single(graph_type, fin);
		}
		if (key3 == "all") {
			return ux_path_node_node__all(graph_type, fin);
		}
	}
	else if (key1 == "node" and key2 == "all") {
		if (key3 == "single") {
			return ux_path_node_all__single(graph_type, fin);
		}
		if (key3 == "all") {
			return ux_path_node_all__all(graph_type, fin);
		}
	}
	else if (key1 == "all" and key2 == "all") {
		if (key3 == "single") {
			return ux_path_all_all__single(graph_type, fin);
		}
		if (key3 == "all") {
			return ux_path_all_all__all(graph_type, fin);
		}
	}

	cerr << ERROR("parse_keywords.cpp", "call_ux_path") << endl;
	cerr << "    Wrong combination of the keywords at 3,4,5:" << endl;
	cerr << "        " << key1 << "  --  " << key2 << "  --  " << key3 << endl;
	cerr << "   ";
	for (const string& s : keywords) {
		cerr << " " << s;
	}
	cerr << endl;
	return err_type::wrong_keyword;
}

}
