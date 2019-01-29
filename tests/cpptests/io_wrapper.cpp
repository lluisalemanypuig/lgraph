#include "io_wrapper.hpp"

// lgraph includes
using namespace lgraph;

namespace io_wrapper {

err_type read_graph(const string& file, const string& format, uxgraph *G) {
	if (format == "edge-list") {
		bool r = lgraph::io::edge_list::read(file, G);
		return (r ? err_type::no_error : err_type::io_error);
	}

	return err_type::graph_format_error;
}

} // -- namespace io_wrapper
