#include "parse_keywords.hpp"

// C++ includes
#include <iostream>
using namespace std;

// custom includes
#include "exe_tests.hpp"

namespace exe_tests {

void mark_wrong_keyword
(const vector<string>& keywords,
 const vector<size_t>& k, const string& tab)
{
	cerr << tab;
	// sure 'keywords' has at least one keyword
	for (size_t i = 0; i < keywords.size(); ++i) {
		cerr << keywords[i] << " ";
	}
	cerr << endl;

	// display the /\ where needed
	size_t it = 0;
	cerr << tab;
	for (size_t i = 0; i < keywords.size(); ++i) {
		size_t l = keywords[i].length();
		if (it < k.size()) {
			if (k[it] != i) {
				cerr << string(l, ' ') << " ";
			}
			else {
				cerr << "/\\";
				cerr << string(l - 2, ' ') << " ";
				++it;
			}
		}
	}
	cerr << endl;
}

err_type call_main(const vector<string>& keywords, ifstream& fin) {
	const string& key = keywords[0];
	if (key == "unweighted") {
		return call_ux(keywords, fin);
	}
	if (key == "weighted") {
		return call_wx(keywords, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_main") << endl;
	cerr << "    Unhandled keyword at 0: '" << key << "'." << endl;
	mark_wrong_keyword(keywords, {0}, "    ");
	return err_type::wrong_keyword;
}

/* ---------- */
/* UNDIRECTED */
/* ---------- */

err_type call_ux(const vector<string>& keywords, ifstream& fin) {
	const string& graph_type = keywords[1];
	if (graph_type != "undirected" and graph_type != "directed") {
		cerr << ERROR("parse_keywords.cpp", "call_ux") << endl;
		cerr << "    Wrong keyword at 1: '" << graph_type << "'." << endl;
		mark_wrong_keyword(keywords, {1}, "    ");
		return err_type::wrong_keyword;
	}

	const string& task = keywords[2];
	if (task == "path") {
		return call_ux_path(keywords, graph_type, fin);
	}
	if (task == "distance") {
		return call_ux_distance(keywords, graph_type, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_ux") << endl;
	cerr << "    Unhandled keyword at 2: '" << task << "'." << endl;
	mark_wrong_keyword(keywords, {2}, "    ");
	return err_type::wrong_keyword;
}

err_type call_ux_path
(const vector<string>& keywords, const string& graph_type, ifstream& fin)
{
	string key3 = keywords[3];
	string key4 = keywords[4];
	string key5 = keywords[5];

	if (key3 == "node" and key4 == "node") {
		return ux_path_node_node(graph_type, key5, fin);
	}
	else if (key3 == "node" and key4 == "all") {
		return ux_path_node_all(graph_type, key5, fin);
	}
	else if (key3 == "all" and key4 == "all") {
		return ux_path_all_all(graph_type, key5, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_ux_path") << endl;
	cerr << "    Wrong combination of the keywords at 3,4,5:" << endl;
	vector<size_t> wrong;
	if (key3 != "node" and key3 != "all") { wrong.push_back(3); }
	if (key4 != "node" and key4 != "all") { wrong.push_back(4); }
	if (key5 != "single" and key5 != "all") { wrong.push_back(5); }
	mark_wrong_keyword(keywords, wrong, "    ");
	return err_type::wrong_keyword;
}

err_type call_ux_distance
(const vector<string>& keywords, const string& graph_type, ifstream& fin)
{
	string key3 = keywords[3];
	string key4 = keywords[4];
	string key5 = keywords[5];

	if (key3 == "node" and key4 == "node") {
		return ux_distance_node_node(graph_type, key5, fin);
	}
	else if (key3 == "node" and key4 == "all") {
		return ux_distance_node_all(graph_type, key5, fin);
	}
	else if (key3 == "all" and key4 == "all") {
		return ux_distance_all_all(graph_type, key5, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_ux_distance") << endl;
	cerr << "    Wrong combination of the keywords at 3,4,5:" << endl;
	vector<size_t> wrong;
	if (key3 != "node" and key3 != "all") { wrong.push_back(3); }
	if (key4 != "node" and key4 != "all") { wrong.push_back(4); }
	if (key5 != "single" and key5 != "all") { wrong.push_back(5); }
	mark_wrong_keyword(keywords, wrong, "    ");
	return err_type::wrong_keyword;
}

/* -------- */
/* DIRECTED */
/* -------- */

err_type call_wx(const vector<string>& keywords, ifstream& fin) {
	const string& graph_type = keywords[1];
	if (graph_type != "undirected" and graph_type != "directed") {
		cerr << ERROR("parse_keywords.cpp", "call_wx") << endl;
		cerr << "    Wrong keyword at 1: '" << graph_type << "'." << endl;
		mark_wrong_keyword(keywords, {1}, "    ");
		return err_type::wrong_keyword;
	}

	const string& task = keywords[2];
	if (task == "path") {
		return call_wx_path(keywords, graph_type, fin);
	}
	if (task == "distance") {
		return call_wx_distance(keywords, graph_type, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_wx") << endl;
	cerr << "    Unhandled keyword at 2: '" << task << "'." << endl;
	mark_wrong_keyword(keywords, {2}, "    ");
	return err_type::wrong_keyword;
}

err_type call_wx_path
(const vector<string>& keywords, const string& graph_type, ifstream& fin)
{
	string key3 = keywords[3];
	string key4 = keywords[4];
	string key5 = keywords[5];

	if (key3 == "node" and key4 == "node") {
		return wx_path_node_node(graph_type, key5, fin);
	}
	else if (key3 == "node" and key4 == "all") {
		return wx_path_node_all(graph_type, key5, fin);
	}
	else if (key3 == "all" and key4 == "all") {
		return wx_path_all_all(graph_type, key5, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_wx_path") << endl;
	cerr << "    Wrong combination of the keywords at 3,4,5:" << endl;
	vector<size_t> wrong;
	if (key3 != "node" and key3 != "all") { wrong.push_back(3); }
	if (key4 != "node" and key4 != "all") { wrong.push_back(4); }
	if (key5 != "single" and key5 != "all") { wrong.push_back(5); }
	mark_wrong_keyword(keywords, wrong, "    ");
	return err_type::wrong_keyword;
}

err_type call_wx_distance
(const vector<string>& keywords, const string& graph_type, ifstream& fin)
{
	string key3 = keywords[3];
	string key4 = keywords[4];
	string key5 = keywords[5];

	if (key3 == "node" and key4 == "node") {
		return wx_distance_node_node(graph_type, key5, fin);
	}
	else if (key3 == "node" and key4 == "all") {
		return wx_distance_node_all(graph_type, key5, fin);
	}
	else if (key3 == "all" and key4 == "all") {
		return wx_distance_all_all(graph_type, key5, fin);
	}

	cerr << ERROR("parse_keywords.cpp", "call_wx_distance") << endl;
	cerr << "    Wrong combination of the keywords at 3,4,5:" << endl;
	vector<size_t> wrong;
	if (key3 != "node" and key3 != "all") { wrong.push_back(3); }
	if (key4 != "node" and key4 != "all") { wrong.push_back(4); }
	if (key5 != "single" and key5 != "all") { wrong.push_back(5); }
	mark_wrong_keyword(keywords, wrong, "    ");
	return err_type::wrong_keyword;
}

} // -- namespace exe_tests
