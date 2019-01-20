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
	if (key == "undirected") {
		return call_uu(keywords, fin);
	}
	if (key == "directed") {
		return call_ud(keywords, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_ux") << endl;
	cerr << "    Unknow keyword at 1: '" << key << "'." << endl;
	return err_type::wrong_keyword;
}

err_type call_uu(const vector<string>& keywords, ifstream& fin) {
	const string& key = keywords[2];
	if (key == "path") {
		return call_uu_path(keywords, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_uu") << endl;
	cerr << "    Unknow keyword at 2: '" << key << "'." << endl;
	return err_type::wrong_keyword;
}

err_type call_uu_path(const vector<string>& keywords, ifstream& fin) {
	string key1 = keywords[3];
	string key2 = keywords[4];
	string key3 = keywords[5];

	if (key1 == "node" and key2 == "node") {
		if (key3 == "single") {
			return uu_path_node_node__single(fin);
		}
		if (key3 == "all") {
			return uu_path_node_node__all(fin);
		}
	}
	else if (key1 == "node" and key2 == "all") {
		if (key3 == "single") {
			return uu_path_node_all__single(fin);
		}
		if (key3 == "all") {
			return uu_path_node_all__all(fin);
		}
	}
	else if (key1 == "all" and key2 == "all") {
		if (key3 == "single") {
			return uu_path_all_all__single(fin);
		}
		if (key3 == "all") {
			return uu_path_all_all__all(fin);
		}
	}

	cerr << ERROR("parse_keywords.cpp", "call_uu_path") << endl;
	cerr << "    Wrong combination of the keywords at 3,4,5:" << endl;
	cerr << "        " << key1 << "  --  " << key2 << "  --  " << key3 << endl;
	cerr << "   ";
	for (const string& s : keywords) {
		cerr << " " << s;
	}
	cerr << endl;
	return err_type::wrong_keyword;
}

err_type call_ud(const vector<string>& keywords, ifstream& fin) {
	const string& key = keywords[2];
	if (key == "path") {
		return call_ud_path(keywords, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_ud") << endl;
	cerr << "    Unknow keyword at 2: '" << key << "'." << endl;
	return err_type::wrong_keyword;
}

err_type call_ud_path(const vector<string>& keywords, ifstream& fin) {
	string key1 = keywords[3];
	string key2 = keywords[4];
	string key3 = (keywords.size() > 5 ? keywords[5] : "");

	if (key1 == "node" and key2 == "node") {
		if (key3 == "all") {
			return ud_path_node_node__all(fin);
		}
		return ud_path_node_node__single(fin);
	}
	else if (key1 == "node" and key2 == "all") {
		if (key3 == "all") {
			return ud_path_node_all__all(fin);
		}
		return ud_path_node_all__single(fin);
	}
	else if (key1 == "all" and key2 == "all") {
		if (key3 == "all") {
			return ud_path_all_all__all(fin);
		}
		return ud_path_all_all__single(fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_ud_path") << endl;
	cerr << "    Wrong combination of the keywords at 3,4:" << endl;
	cerr << "        " << key1 << "  --  " << key2 << endl;
	cerr << "   ";
	for (const string& s : keywords) {
		cerr << " " << s;
	}
	cerr << endl;
	return err_type::wrong_keyword;
}

}
