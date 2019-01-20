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

err_type uu_path_node_node__single(ifstream& fin);
err_type uu_path_node_all__single(ifstream& fin);
err_type uu_path_all_all__single(ifstream& fin);
err_type uu_path_node_node__all(ifstream& fin);
err_type uu_path_node_all__all(ifstream& fin);
err_type uu_path_all_all__all(ifstream& fin);

err_type ud_path_node_node__single(ifstream& fin);
err_type ud_path_node_all__single(ifstream& fin);
err_type ud_path_all_all__single(ifstream& fin);
err_type ud_path_node_node__all(ifstream& fin);
err_type ud_path_node_all__all(ifstream& fin);
err_type ud_path_all_all__all(ifstream& fin);

} // -- namespace exe_tests
