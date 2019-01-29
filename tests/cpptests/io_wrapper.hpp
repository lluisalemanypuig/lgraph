#pragma once

// C++ includes
#include <iostream>
#include <string>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/udgraph.hpp>
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/wdgraph.hpp>
#include <lgraph/io/io.hpp>

// custom includes
#include "definitions.hpp"

namespace io_wrapper {

err_type read_graph(const string& file, const string& format, lgraph::uxgraph *G);

template<typename T>
err_type read_graph(const string& file, const string& format, lgraph::wxgraph<T> *G) {
	if (format == "edge-list") {
		bool r = lgraph::io::edge_list::read(file, G);
		return (r ? err_type::no_error : err_type::io_error);
	}

	return err_type::graph_format_error;
}

} // -- namespace io_wrapper
