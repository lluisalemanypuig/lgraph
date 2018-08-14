#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <fstream>
#include <utility>
#include <vector>
using namespace std;

// Custom includes
#include <lgraph/utils/definitions.hpp>
#include <lgraph/data_structures/wxgraph.hpp>

namespace lgraph {
namespace utils {

/**
 * @brief Weighted undirected graphs.
 *
 * This class implements the weighted, undirected graph data structure
 * based on adjacency lists.
 *
 * @param T In case of weighted graphs, this parameter indicates
 * the type of the edge weights
 */
template<class T>
class wugraph : public wxgraph<T> {
	protected:

		// Unique edges of this graph in a set
		void get_unique_edges(set<pair<edge, T> >& edges) const;

	public:
		/// Constructor
		wugraph();
		/// Destructor
		~wugraph();

		// MODIFIERS

		void add_edge(const edge& e, const T& w);
		void add_edge(node u, node v, const T& w);

		void remove_edge(const edge& e);
		void remove_edge(node u, node v);

		// GETTERS

		bool has_edge(node u, node v) const;
		T edge_weight(node u, node v) const;
		bool is_directed() const;

};

} // -- namespace utils
} // -- namespace lgraph

#include "wugraph.cpp"
