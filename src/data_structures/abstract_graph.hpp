#pragma once

/// C++ includes
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

namespace dsa {
namespace utils {

typedef size_t node;
typedef vector<node> neighbourhood;
typedef neighbourhood::const_iterator ncit;
typedef neighbourhood::iterator nit;
typedef pair<node, node> edge;

/*
Generic interface of the adjacency list implementation of
a graph, with a series of methods common to all of them.
*/
template<class T = size_t>
class abstract_graph {
	protected:
		vector<neighbourhood> adjacency_list;
		size_t num_edges;

		// Returns a constant iterator to node u in the neighbourhood n
		// of some node in the graph.
		ncit cget_neighbour_position(const neighbourhood& n, node u) const;

		// Returns an iterator to node u in the neighbourhood n of some
		// node in the graph.
		nit get_neighbour_position(neighbourhood& n, node u);

	public:
		abstract_graph();
		abstract_graph(size_t n);
		virtual ~abstract_graph();

		// Clears the graph and initializes it
		// with an empty graph of 'n' nodes
		virtual void init(size_t n) = 0;

		/// OPERATORS

		/// MODIFIERS

		// Adds one node to the graph. Returns the index of the new node.
		size_t add_node();

		// Adds n nodes to the graph. Returns the index of the last node.
		size_t add_n_nodes(size_t n);

		// Adds a directed edge between nodes u and v assuming it does
		// not exist.
		virtual void add_edge(const edge& e, T w) = 0;
		virtual void add_edges(const vector<edge>& edge_list, const vector<T>& ws) = 0;
		virtual void add_edge(node u, node v, T w) = 0;

		// Removes the edge (u, v) from the graph.
		virtual void remove_edge(const edge& e) = 0;
		virtual void remove_edges(const vector<edge>& edge_list) = 0;
		virtual void remove_edge(node u, node v) = 0;

		// Deletes all memory used by the graph
		virtual void clear() = 0;

		/// GETTERS

		// Returns true if node 'u' is in this graph.
		bool has_node(node u) const;

		// Returns true if there is an undirected edge between nodes u and v
		virtual bool has_edge(node u, node v) const = 0;

		// Returns the number of ndoes
		size_t n_nodes() const;

		// Returns the number of edges
		size_t n_edges() const;

		// Returns all nodes (as integers)
		void nodes(vector<node>& all_nodes) const;

		// Returns the neighbourhood of node u
		const neighbourhood& get_neighbours(node u) const;

		// Returns the number of neighbours of u
		size_t degree(node u) const;

		// Returns the weight of the existing edge (u,v)
		virtual T edge_weight(node u, node v) const = 0;

		/// I/O

		// Reads/writes the graph from/into the file with name 'filename'
		virtual bool read_from_file(const string& filename) = 0;
		virtual bool read_from_file(const char *filename) = 0;
		virtual bool store_in_file(const string& filename) = 0;
		virtual bool store_in_file(const char *filename) = 0;

		/// GRAPH FEATURES

		// Returns the adjacency matrix of this graph
		void get_adjacency_matrix(vector<vector<bool> >& adj_mat) const;

		// Returns the degree sequence of the graph
		// pairs: degree, amount
		void get_degree_sequence(map<node, node>& ds) const;

		// Returns the number of triangles in this graph
		size_t n_triangles() const;
};

} // -- namespace utils
} // -- namespace dsa

#include "abstract_graph.cpp"
