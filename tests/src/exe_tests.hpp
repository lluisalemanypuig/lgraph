#pragma once

/* This file contains the definition of the different functions used for
 * testing the library.
 *
 * This file is not to be included by any of the implemented tests, as adding
 * a new function to this file will make ALL the corresponding .cpp files to
 * be compiled again.
 */

// C++ includes
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// custom includes
#include "definitions.hpp"

namespace exe_tests {

err_type ux_path_node_node__single(const string& graph_type, ifstream& fin);
err_type ux_path_node_all__single(const string& graph_type, ifstream& fin);
err_type ux_path_all_all__single(const string& graph_type, ifstream& fin);
err_type ux_path_node_node__all(const string& graph_type, ifstream& fin);
err_type ux_path_node_all__all(const string& graph_type, ifstream& fin);
err_type ux_path_all_all__all(const string& graph_type, ifstream& fin);

err_type ux_distance_node_node__single(const string& graph_type, ifstream& fin);
err_type ux_distance_node_all__single(const string& graph_type, ifstream& fin);
err_type ux_distance_all_all__single(const string& graph_type, ifstream& fin);
err_type ux_distance_node_node__all(const string& graph_type, ifstream& fin);
err_type ux_distance_node_all__all(const string& graph_type, ifstream& fin);
err_type ux_distance_all_all__all(const string& graph_type, ifstream& fin);

err_type wx_path_node_node__single(const string& graph_type, ifstream& fin);
err_type wx_path_node_all__single(const string& graph_type, ifstream& fin);
err_type wx_path_all_all__single(const string& graph_type, ifstream& fin);
err_type wx_path_node_node__all(const string& graph_type, ifstream& fin);
err_type wx_path_node_all__all(const string& graph_type, ifstream& fin);
err_type wx_path_all_all__all(const string& graph_type, ifstream& fin);

err_type wx_distance_node_node__single(const string& graph_type, ifstream& fin);
err_type wx_distance_node_all__single(const string& graph_type, ifstream& fin);
err_type wx_distance_all_all__single(const string& graph_type, ifstream& fin);
err_type wx_distance_node_node__all(const string& graph_type, ifstream& fin);
err_type wx_distance_node_all__all(const string& graph_type, ifstream& fin);
err_type wx_distance_all_all__all(const string& graph_type, ifstream& fin);

} // -- namespace exe_tests
