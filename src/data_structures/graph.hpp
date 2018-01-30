#pragma once

/// C++ includes
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
using namespace std;

namespace dsa {
namespace networks {

typedef size_t node;
typedef vector<node> neighbourhood;
typedef neighbourhood::const_iterator lcit;
typedef neighbourhood::iterator lit;
typedef pair<node, node> edge;

/*
Implementation of directed graphs as adjacency lists
*/
class graph {
	private:
		vector<neighbourhood> adjacency_list;
		size_t num_edges;
		
		// Returns a constant iterator to node u in the neighbourhood n
		// of some node in the graph.
		lcit cget_neighbour_position(const neighbourhood& n, node u) const;
		
		// Returns an iterator to node u in the neighbourhood n of some
		// node in the graph.
		lit get_neighbour_position(neighbourhood& n, node u);
		
	public:
		graph();
		graph(size_t n); // n: number of nodes
		~graph();
		
		// Clears the graph and initializes it
		// with an empty graph of 'n' nodes
		void init(size_t n);
		
		/// OPERATORS
		
		inline friend
		ostream& operator<< (ostream& os, const graph& d) {
			for (size_t i = 0; i < d.adjacency_list.size(); ++i) {
				os << i << ":";
				lcit begin = d.adjacency_list[i].begin();
				lcit end = d.adjacency_list[i].end();
				for (lcit it = begin; it != end; ++it) os << " " << *it;
				if (i < d.adjacency_list.size() - 1) os << endl;
			}
			return os;
		}
		
		graph& operator= (const graph& g);
		
		/// SETTERS
		
		// Adds one node to the graph. Returns the index of the new node.
		size_t add_node();
		
		// Adds n nodes to the graph. Returns the index of the last node.
		size_t add_n_nodes(size_t n);
		
		// Adds a directed edge between nodes u and v assuming it does
		// not exist.
		void add_edge(const edge& e);
		void add_edge(node u, node v);
		
		// Removes the edge (u, v) from the graph.
		void remove_edge(const edge& e);
		void remove_edge(node u, node v);
		
		// Deletes all edges and nodes from the graph
		void clear();
		
		/// GETTERS
		
		// Returns true if node 'u' is in this graph.
		bool has_node(node u) const;
		
		// Returns true if there is an undirected edge between nodes u and v
		bool has_edge(node u, node v) const;
		
		// Returns the number of ndoes
		size_t n_nodes() const;
		
		// Returns the number of edges
		size_t n_edges() const;
		
		// Returns all nodes (as integers)
		void nodes(vector<node>& all_nodes) const;
		
		// Returns all edges as pairs of nodes
		void edges(vector<edge>& e) const;
		
		// Returns the neighbourhood of node u
		const neighbourhood& get_neighbours(node u) const;
		
		// Returns the number of neighbours of u
		size_t degree(node u) const;
		
		// Returns the degree sequence of the graph
		// pairs: degree, amount
		void get_degree_sequence(map<node, node>& ds) const;
		
		// Returns the number of triangles in this graph
		size_t n_triangles() const;
};

} // -- namespace networks
} // -- namespace dsa

