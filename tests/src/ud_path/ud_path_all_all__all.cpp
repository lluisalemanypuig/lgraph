// C++ inlcudes
#include <iostream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/node_path.hpp>
#include <lgraph/graph_traversal/traversal.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "src/definitions.hpp"
#include "src/io_wrapper.hpp"
#include "src/test_utils.hpp"

namespace exe_tests {

err_type ud_path_all_all__all(ifstream& fin) {
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("ud_path_all_all__all.cpp", "ud_path_all_all__all") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("ud_path_all_all__all.cpp", "ud_path_all_all__all") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("ud_path_all_all__all.cpp", "ud_path_all_all__all") << endl;
		cerr << "    Expected field 'BODY'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}

	udgraph G;
	err_type r = io_wrapper::read_graph(input_graph, format, &G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("ud_path_all_all__all.cpp", "ud_path_all_all__all") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("ud_path_all_all__all.cpp", "ud_path_all_all__all") << endl;
			cerr << "    Format '" << format << "' not supported." << endl;
		}
		return r;
	}

	// this test needs no BODY

	vector<vector< node_path_set<_new_> > > uv_paths;
	traversal::uxpaths(&G, uv_paths);
	for (node u = 0; u < G.n_nodes(); ++u) {
		for (node v = 0; v < G.n_nodes(); ++v) {
			sort(uv_paths[u][v].begin(), uv_paths[u][v].end(),
				 test_utils::comp_ux_paths);

			cout << "(" << u << ", " << v << "): ";
			if (uv_paths[u][v].size() == 0) {
				cout << "No paths" << endl;
			}
			else {
				for (const node_path<_new_>& p : uv_paths[u][v]) {
					if (p.size()== 0) {
						cout << "No path" << endl;
					}
					else {
						cout << "(" << u << ", " << v << "): "
							 << p.to_string() << "; " << p.get_length() << endl;
					}
				}
			}
		}
	}

	return err_type::no_error;
}

}
