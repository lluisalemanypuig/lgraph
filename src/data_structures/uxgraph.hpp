#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
using namespace std;

// Custom includes
#include "xxgraph.hpp"
#include "utils/definitions.hpp"

namespace lgraph {
namespace utils {

/**
 * @brief Abstract class for undirected (ux) graphs.
 *
 * This interface implements a few methods to generalise the concept
 * of undirected graph. It implements a few methods that deal with
 * the adjacency list of each node. Adds two new pure virtual methods:
 * @ref add_weight and @ref remove_weight.
 *
 * @param T In case of weighted graphs, this parameter indicates
 * the type of the edge weights
 */
template<class T>
class uxgraph : public xxgraph<T> {
	protected:

		// MODIFIERS

		// Initialise the adjacency list
		void initialise_adjacency_list(size_t n);

		// Clear the adjacency list
		void clear_adjacency_list();

		/**
		 * @brief Adds a weight to a weight list
		 * @param u The node whose weight list will be modified
		 * @param w The weight to be added
		 */
		virtual void add_weight(node u, T w) = 0;

		/**
		 * @brief Removes the weight at a certain position of a weight list
		 * @param u The node whose weight list will be modified
		 * @param it The weight's position to be deleted
		 */
		virtual void remove_weight(node u, nit it) = 0;

	public:
		uxgraph();
		virtual ~uxgraph();

		// Adds an edge between nodes u and v assuming it does not exist.
		void add_edge(const edge& e, T w = 0);
		void add_edge(node u, node v, T w = 0);

		// Removes the edge (u, v) from the graph.
		void remove_edge(const edge& e);
		void remove_edges(const vector<edge>& edge_list);
		void remove_edge(node u, node v);

		// Returns true if there is an undirected edge between nodes u and v
		bool has_edge(node u, node v) const;
};

} // -- namespace utils
} // -- namespace lgraph

#include "uxgraph.cpp"
