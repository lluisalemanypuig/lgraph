#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

// Custom includes
#include <lgraph/utils/definitions.hpp>
#include <lgraph/data_structures/uxgraph.hpp>

namespace lgraph {
namespace utils {

/**
 * @brief Unweighted undirected (ux) graphs.
 *
 * This class implements the unweighted undirected graph data structure
 * based on adjacency lists.
 */
class uugraph : public uxgraph {
	protected:

		// Unique edges of this graph in a set
		void get_unique_edges(set<edge>& edges) const;

	public:
		/// Constructor
		uugraph();
		/// Destructor
		~uugraph();

		// MODIFIERS

		void add_edge(const edge& e);
		void add_edge(node u, node v);

		void remove_edge(const edge& e);
		void remove_edge(node u, node v);

		// GETTERS

		bool has_edge(node u, node v) const;

};

} // -- namespace utils
} // -- namespace lgraph
