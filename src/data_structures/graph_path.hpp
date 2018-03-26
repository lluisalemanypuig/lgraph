#pragma once

/// C++ includes
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

/// Custom includes
#include "xxgraph.hpp"
#include "utils/definitions.hpp"
#include "utils/static_bitset.hpp"

namespace dsa {
namespace utils {

/// NODE PATH

// A path in a graph seen as a list of nodes
template<class T = _new_>
class node_path {
	private:
		T path_length;
		vector<node> nodes;

	public:
		node_path();
		node_path(node n); // start path at node 'n'
		~node_path();

		// Empties this path
		void empty();

		/// OPERATORS

		inline friend
		ostream& operator<< (ostream& os, const node_path<T>& np) {
			if (np.size() > 0) {
				os << np[0];
				for (size_t i = 1; i < np.size(); ++i) {
					os << " " << np[i];
				}
				os << " -> " << np.path_length;
			}
			return os;
		}

		// access i-th node in this path
		node operator[] (size_t i) const;
		node& operator[] (size_t i);

		bool operator< (const node_path<T>& p) const;
		bool operator> (const node_path<T>& p) const;

		node_path<T>& operator= (const node_path<T>& np);

		/// MODIFIERS

		// Adds the path p at the end of this path (without the first one).
		// This path's last node and the first node of p must be the same.
		void concatenate(const node_path& p);

		// Adds a node to the path
		void add_node(node u);

		// Accumulates to the length of this path the value 'l'
		void add_length(const T& l);

		// Sets this path length to 'l'
		void set_length(const T& l);

		// Reverses the nodes in the path
		void reverse();

		// Removes the last node in the path
		void delete_last();

		/// GETTERS

		// Returns the number of nodes in this path
		size_t size() const;

		// Returns the length of this path
		T get_length() const;

		// Returns the last node in this path
		size_t last_node() const;
};

template<class T = _new_>
using node_path_set = vector<node_path<T> >;

/// BOOLEAN PATH

// A path in a graph seen as a list of Boolean values.
// The i-th position of this path is 1 if, and only if, the i-th vertex is in the path.
// This is intended to be used ONLY for shortest paths.
//
// Therefore: any boolean_path can be converted into a node_path under the following conditions:
// - no vertex in the path has three neighbours in it
// - if p(u) is the position of vertex 'u' in the node path then:
//    * if u has only one neighbour 'v' then either p(v) < p(u) or p(u) < p(v)
//    * if u has two neighbours 'v', 'w' then either p(v) < p(u) < p(w) or p(w) < p(u) < p(v)
// Any other boolean path not following the previous two conventions is not guaranteed to be
// able to be converted into an object of type 'node_path'.
template<class T = _new_>
class boolean_path {
	private:
		static_bitset nodes_in_path;
		size_t n_nodes;
		T path_length;

	public:
		boolean_path(size_t n = 0);
		~boolean_path();

		/// INITIALISERS

		// initialises the path to an empty path of n nodes
		void init(size_t n);

		// initialises the path to a path of n nodes
		// with the nodes in vp
		void init(size_t n, const node_path<T>& vp);

		// clears the path. Init has to be called to be
		// able to use it again.
		void clear();

		/// MODIFIERS

		// Adds a node to the path
		void add_node(node u);

		// Accumulates to the current length of the the path the value l
		void add_length(const T& l);

		// Sets the current length of the the path the value l
		void set_length(const T& l);

		// Adds to this paths all nodes from bp
		void concatenate(const boolean_path<T>& bp);

		/// OPERATORS

		inline friend
		ostream& operator<< (ostream& os, const boolean_path<T>& bp) {
			os << bp.to_string() << " -> " << bp.path_length;
			return os;
		}

		// Check if the i-th node is in the path
		bool operator[] (size_t i) const;

		boolean_path& operator= (const boolean_path<T>& bp);

		/// GETTERS

		// Returns the number of nodes in the path
		size_t size() const;
		// Returns the sum of the distances between
		// the nodes in the path
		T get_length() const;

		// Returns the maximum number of nodes that
		// could be in the path. The size used to initialise it.
		size_t potential_length() const;

		// Returns the node next to 'u' in the path (which is
		// different from prev). If the only neighbour of 'u'
		// in the path is 'prev' then the function returns 'u'.
		// If 'u' is the first node in the path, set 'prev' to '-1'
		node next(const xxgraph<T> *G, node prev, node u) const;

		/// CONVERSIONS

		// Converts this boolean path into a node_path. The path
		// is assumed to start at s.
		node_path<T> to_node_path(const xxgraph<T> *G, node s) const;
		void to_node_path(const xxgraph<T> *G, node s, node_path<T>& np) const;

		// If the path has some node in it, converts this boolean path into a
		// formatted string
		string pretty_string() const;
		void pretty_string(string& s) const;
		// simple string
		string to_string() const;
		void to_string(string& s) const;
};

template<class T = size_t>
using boolean_path_set = vector<boolean_path<T> >;

} // -- namespace utils
} // -- namespace dsa

#include "graph_path.cpp"
