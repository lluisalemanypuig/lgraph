#pragma once

/// C++ includes
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

/// Custom includes
#include "data_structures/xxgraph.hpp"
#include "utils/logger.hpp"

namespace lgraph {
using namespace utils;

namespace traversal {

	template<class T>
	using djka_node = pair<T, node>;

	/* parameters:
	 *	- input graph,
	 *	- first: shortest distance to that node,
	 *	  second: node at the front of the priority queue
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using djka_terminate = function<bool (const xxgraph<T> *, const djka_node<T>&, const vector<bool>&)>;

	/* parameters:
	 *	- input graph,
	 *	- first: shortest distance to that node,
	 *	  second: node at the front of the priority queue
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using djka_process_current = function<void (const xxgraph<T> *, const djka_node<T>&, const vector<bool>&)>;

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the priority queue (u),
	 *	- neighbour of node at the top of the priority queue (v),
	 *	- weight of edge (u,v)
	 *	- set of visited nodes
	 *
	 * Returns true or false n whether the next pair should be added or not
	 */
	template<class T = size_t>
	using djka_process_neighbour = function<bool (const xxgraph<T> *, node, node, const T&, const vector<bool>&)>;

	template<class T>
	void Dijkstra
	(
		const xxgraph<T> *G,
		node source,
		djka_terminate<T> term =				[](const xxgraph<T> *, const djka_node<T>&, const vector<bool>&) -> bool { return false; },
		djka_process_current<T> proc_curr =		[](const xxgraph<T> *, const djka_node<T>&, const vector<bool>&) -> void {},
		djka_process_neighbour<T> proc_neig =	[](const xxgraph<T> *, node, node, const T&, const vector<bool>&) -> bool { return true; }
	);

} // -- namespace traversal
} // -- namespace lgraph

#include "dijkstra.cpp"
