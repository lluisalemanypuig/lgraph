#pragma once

/// C++ includes
#include <sstream>
#include <vector>
using namespace std;

/// Custom includes
#include "graph.hpp"
#include "utils/definitions.hpp"

namespace dsa {
namespace utils {

/// NODE PATH

// A path in a graph seen as a list of nodes
class node_path : public vector<node> {
	private:
	public:
		node_path();
		node_path(size_t n);
		node_path(size_t n, node u);

		inline friend
		ostream& operator<< (ostream& os, const node_path& np) {
			if (np.size() > 0) {
				os << np[0];
				for (size_t i = 1; i < np.size(); ++i) {
					os << " " << np[i];
				}
			}
			return os;
		}

		// Adds the path p at the end of this path (without the first one).
		// This path's last node and the first node of p must be the same.
		void concatenate(const node_path& p);
};

typedef vector<node_path> node_path_set;

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
class boolean_path {
	private:
		vector<bool> nodes_in_path;
		size_t n_nodes;

	public:
		boolean_path(size_t n = 0);
		~boolean_path();

		/// INITIALISERS

		// initialises the path to an empty path of n nodes
		void init(size_t n);

		// initialises the path to a path of n nodes
		// with the nodes in vp
		void init(size_t n, const node_path& vp);

		// clears the path. Init has to be called to be
		// able to use it again.
		void clear();

		/// MODIFIERS

		// adds/remove a node from the path
		void add_node(node u);
		void remove_node(node u);

		// Adds to this paths all nodes from bp
		void concatenate(const boolean_path& bp);

		/// OPERATORS

		inline friend
		ostream& operator<< (ostream& os, const boolean_path& bp) {
			os << bp.to_string();
			return os;
		}

		// Check if the i-th node is in the path
		bool operator[] (size_t i) const;

		boolean_path& operator= (const boolean_path& bp);

		/// GETTERS

		// Returns the number of nodes in the path
		size_t size() const;

		// Returns the maximum number of nodes that
		// could be in the path. The size used to initialise it.
		size_t potential_length() const;

		// Returns the node next to 'u' in the path (which is
		// different from prev). If the only neighbour of 'u'
		// in the path is 'prev' then the function returns 'u'.
		// If 'u' is the first node in the path, set 'prev' to '-1'
		node next(const graph& G, node prev, node u) const;

		/// CONVERSIONS

		// Converts this boolean path into a node_path. The path
		// is assumed to start at s.
		node_path to_node_path(const graph& G, node s) const;
		void to_node_path(const graph& G, node s, node_path& np) const;

		// If the path has some node in it, converts this boolean path into a
		// formatted string
		string pretty_string() const;
		void pretty_string(string& s) const;
		// simple string
		string to_string() const;
		void to_string(string& s) const;
};

typedef vector<boolean_path> boolean_path_set;

} // -- namespace utils
} // -- namespace dsa
