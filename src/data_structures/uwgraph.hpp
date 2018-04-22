#pragma once

/// C includes
#include <assert.h>

/// C++ includes
#include <fstream>
#include <utility>
#include <vector>
using namespace std;

/// Custom includes
#include "uxgraph.hpp"
#include "utils/definitions.hpp"

namespace lgraph {
namespace utils {

/*
Implementation of undirected weighted graphs with adjacency lists
*/

template<class T>
class uwgraph : public uxgraph<T> {
	private:
		vector<vector<T> > weights;

		/// GETTERS

		void get_unique_edges(set<pair<edge, T> >& edges) const;

	private:

		/// MODIFIERS

		// Initialise the list of weights
		void initialise_weights(size_t n);

		// Clear the list of weights
		void clear_weights();

		// Adds the weight w to the specified node's list
		void add_weight(node u, T w);

		// Removes the weight from the position 'p'
		// of list of neighbours of node u
		void remove_weight(node u, nit p);

	public:
		uwgraph();
		uwgraph(size_t n);
		~uwgraph();

		/// OPERATORS

		inline friend
		ostream& operator<< (ostream& os, const uwgraph<T>& g) {
			for (size_t i = 0; i < g.adjacency_list.size(); ++i) {
				os << i << ":";
				ncit begin = g.adjacency_list[i].begin();
				ncit end = g.adjacency_list[i].end();
				auto weights_it = g.weights[i].begin();

				for (ncit it = begin; it != end; ++it, ++weights_it) {
					os << " " << *it;
					os << "(";
					os << *weights_it;
					os << ")";
				}

				if (i < g.adjacency_list.size() - 1) os << endl;
			}
			return os;
		}

		uwgraph& operator= (const uwgraph& g);

		/// MODIFIERS

		void add_edges(const vector<edge>& edge_list, const vector<T>& ws = vector<T>());

		/// GETTERS

		// Returns the weight of the existing edge (u,v)
		T edge_weight(node u, node v) const;

		// Returns the weights to all neighbours of node u
		void get_weights(node u, vector<T>& ws) const;
		const vector<T>& get_weights(node u) const;

		/// I/O

		bool read_from_file(const string& filename);
		bool read_from_file(const char *filename);
		bool store_in_file(const string& filename);
		bool store_in_file(const char *filename);
};

} // -- namespace utils
} // -- namespace dsa

#include "uwgraph.cpp"
