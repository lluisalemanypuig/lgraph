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

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the stack,
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using dfs_terminate = function<bool (const xxgraph<T> *, node, const vector<bool>&)>;

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the queue,
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using dfs_process_current = function<void (const xxgraph<T> *, node, const vector<bool>&)>;

	/* parameters:
	 *	- input graph,
	 *	- node at the front of the queue,
	 *	- neighbour of node at the top of the stack,
	 *	- set of visited nodes
	 */
	template<class T = size_t>
	using dfs_process_neighbour = function<void (const xxgraph<T> *, node, node, const vector<bool>&)>;

	template<class T>
	void DFS
	(
		const xxgraph<T> *G,
		node source,
		dfs_terminate<T> term =					[](const xxgraph<T> *, node, const vector<bool>&) -> bool { return false; },
		dfs_process_current<T> proc_curr =		[](const xxgraph<T> *, node, const vector<bool>&) -> void {},
		dfs_process_neighbour<T> proc_neig =	[](const xxgraph<T> *, node, node, const vector<bool>&) -> void {}
	);

} // -- namespace traversal
} // -- namespace lgraph

#include "dfs.cpp"
