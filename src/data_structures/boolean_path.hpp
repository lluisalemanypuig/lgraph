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
#include "utils/logger.hpp"
#include "node_path.hpp"

namespace lgraph {
namespace utils {

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

		// initialises the path to an empty path within a graph of n nodes
		void init(size_t n);

		// initialises the path to a path within a graph of n nodes
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

		// Stores in 'next' the closest next node to 'u' in the path
		// (which must be different from 'prev'). If the only neighbour of 'u'
		// in the path is 'prev' then the stores returns 'u' and returns false.
		// If 'u' is the first node in the path, set 'prev' to '-1'
		// or any other invalid value
		bool closest_next(const xxgraph<T> *G, node prev, node current, node& next) const;
		// Same as before but in this case the function wil not return
		// any node marked with true in 'prev'
		bool closest_next(const xxgraph<T> *G, const vector<bool>& prev, node current, node& next) const;

		/// CONVERSIONS

		// Converts this boolean path into a node_path. The path
		// is assumed to start at s and to represent a 'shortest'
		// path within the graph G
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

	// Conversion from a node path set to a boolean
	// path set in a graph of N nodes
	template<class T>
	void from_nps_to_bps(const node_path_set<T>& nps, boolean_path_set<T>& bps);

} // -- namespace utils
} // -- namespace lgraph

#include "boolean_path.cpp"
