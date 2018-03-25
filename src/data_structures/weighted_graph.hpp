#pragma once

/// C includes
#include <assert.h>

/// C++ includes
#include <fstream>
#include <utility>
#include <vector>
using namespace std;

/// Custom includes
#include "abstract_graph.hpp"
#include "utils/definitions.hpp"

namespace dsa {
namespace utils {

template<class T>
class uwgraph : public abstract_graph<T> {
	private:
		vector<vector<T> > weights;

		void get_unique_edges(set<pair<edge, T> >& edges) const;

	public:
		uwgraph<T>();
		uwgraph<T>(size_t n);
		~uwgraph<T>();

		void init(size_t n);

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

		// Adds a directed edge between nodes u and v assuming it does
		// not exist. The weight, if provided, is ignored.
		void add_edge(const edge& e, T w);
		void add_edges(const vector<edge>& edge_list, const vector<T>& ws);
		void add_edge(node u, node v, T w);

		// Removes the edge (u, v) from the graph.
		void remove_edge(const edge& e);
		void remove_edges(const vector<edge>& edge_list);
		void remove_edge(node u, node v);

		// Deletes all edges and nodes from the graph
		void clear();

		// Returns the weight of the existing edge (u,v)
		T weight(node u, node v) const;

		/// GETTERS

		// Returns true if there is an undirected edge between nodes u and v
		bool has_edge(node u, node v) const;

		/// I/O

		bool read_from_file(const string& filename);
		bool read_from_file(const char *filename);
		bool store_in_file(const string& filename);
		bool store_in_file(const char *filename);
};

} // -- namespace utils
} // -- namespace dsa

#include "weighted_graph.cpp"
