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

namespace dsa {
namespace utils {

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

} // -- namespace utils
} // -- namespace dsa

#include "node_path.cpp"
