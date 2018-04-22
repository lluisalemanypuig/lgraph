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
#include "uxgraph.hpp"
#include "utils/definitions.hpp"

namespace lgraph {
namespace utils {

/*
Implementation of undirected unweighted graphs with adjacency lists
*/
class uugraph : public uxgraph<_new_> {
	private:

		/// GETTERS

		void get_unique_edges(set<edge>& edges) const;

	private:

		/// MODIFIERS

		// Initialise the list of weights, if necessary
		void initialise_weights(size_t n);

		// Clear the list of weights, if necessary
		void clear_weights();

		// Adds the weight w to the specified node's list
		void add_weight(node u, _new_ w);

		// Removes the weight from the position 'p'
		// of list of neighbours of node u
		void remove_weight(node u, nit p);

	public:
		uugraph();
		uugraph(size_t n); // n: number of nodes
		~uugraph();

		/// OPERATORS
		
		inline friend
		ostream& operator<< (ostream& os, const uugraph& g) {
			for (size_t i = 0; i < g.adjacency_list.size(); ++i) {
				os << i << ":";
				ncit begin = g.adjacency_list[i].begin();
				ncit end = g.adjacency_list[i].end();
				for (ncit it = begin; it != end; ++it) os << " " << *it;
				if (i < g.adjacency_list.size() - 1) os << endl;
			}
			return os;
		}

		uugraph& operator= (const uugraph& g);
		
		/// MODIFIERS

		void add_edges(const vector<edge>& edge_list, const vector<_new_>& ws = vector<_new_>());

		/// GETTERS

		// Returns all unique edges of this graph
		void edges(vector<edge>& all_edges) const;

		// Returns true if there is an undirected edge between nodes u and v
		bool has_edge(node u, node v) const;

		// Returns the weight of the existing edge (u,v)
		_new_ edge_weight(node u, node v) const;

		// Returns the weights to all neighbours of node u
		// Returns a list of degree-many 1's
		void get_weights(node u, vector<_new_>& ws) const;

		/// I/O

		bool read_from_file(const string& filename);
		bool read_from_file(const char *filename);
		bool store_in_file(const string& filename);
		bool store_in_file(const char *filename);
};

} // -- namespace utils
} // -- namespace dsa

