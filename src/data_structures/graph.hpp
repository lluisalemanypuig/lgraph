#pragma once

/// C++ includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
using namespace std;

/// Custom includes
#include "abstract_graph.hpp"
#include "utils/definitions.hpp"
#include "utils/logger.hpp"

namespace dsa {
namespace utils {

/*
Implementation of undirected unweighted graphs with adjacency lists
*/
class uugraph : public abstract_graph<> {
	private:

		void __add_edge(const edge& e);
		void __add_edges(const vector<edge>& edge_list);
		void __add_edge(node u, node v);

		void get_unique_edges(set<edge>& edges) const;

	public:
		uugraph();
		uugraph(size_t n); // n: number of nodes
		~uugraph();

		void init(size_t n);

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

		// Adds a directed edge between nodes u and v assuming it does
		// not exist. The weight, if provided, is ignored.
		void add_edge(const edge& e, char w = 0);
		void add_edges(const vector<edge>& edge_list, const vector<char>& ws = vector<char>());
		void add_edge(node u, node v, char w = 0);
		
		// Removes the edge (u, v) from the graph.
		void remove_edge(const edge& e);
		void remove_edges(const vector<edge>& edge_list);
		void remove_edge(node u, node v);
		
		// Deletes all edges and nodes from the graph
		void clear();
		
		/// GETTERS

		// Returns all unique edges of this graph
		void edges(vector<edge>& all_edges) const;

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

