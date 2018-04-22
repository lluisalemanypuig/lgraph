#pragma once

/// C includes
#include <assert.h>

/// C++ includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
using namespace std;

/// Custom includes
#include "xxgraph.hpp"
#include "utils/definitions.hpp"

namespace lgraph {
namespace utils {

template<class T>
class uxgraph : public xxgraph<T> {
	protected:

		/// MODIFIERS

		// Initialise the adjacency list
		void initialise_adjacency_list(size_t n);

		// Clear the adjacency list
		void clear_adjacency_list();

		// Adds the weight w to the specified node's list
		virtual void add_weight(node u, T w) = 0;

		// Removes the weight from the position 'p'
		// of list of neighbours of node u
		virtual void remove_weight(node u, nit it) = 0;

	public:
		uxgraph();
		virtual ~uxgraph();

		/// OPERATORS

		/// MODIFIERS

		// Adds an edge between nodes u and v assuming it does not exist.
		void add_edge(const edge& e, T w = 0);
		void add_edge(node u, node v, T w = 0);

		// Removes the edge (u, v) from the graph.
		void remove_edge(const edge& e);
		void remove_edges(const vector<edge>& edge_list);
		void remove_edge(node u, node v);

		/// GETTERS

		// Returns true if there is an undirected edge between nodes u and v
		bool has_edge(node u, node v) const;
};

} // -- namespace utils
} // -- namespace dsa

#include "uxgraph.cpp"
