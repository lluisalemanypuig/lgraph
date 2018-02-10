#pragma once

/// C++ includes
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <queue>
using namespace std;

/// Custom includes
#include "data_structures/graph.hpp"

namespace dsa {
using namespace utils;

namespace traversal {

	void BFS
	(
		const graph& G,
		node source,
		function<bool (const graph&, node, const vector<bool>&)> terminate				 = [](const graph&, node, const vector<bool>&) -> bool { return false; },
		function<void (const graph&, node, const vector<bool>&)> process_current		 = [](const graph&, node, const vector<bool>&) -> void {},
		function<void (const graph&, node, node, const vector<bool>&)> process_neighbour = [](const graph&, node, node, const vector<bool>&) -> void {}
	);


	/* Functions that compute the distances:
	 * - vertex-to-vertex	(BFS)
	 * - vertex-to-all		(BFS)
	 * - all-to-all			(Floyd-Warshall)
	 */
	size_t distance(const graph& G, node source, node target);
	void distance(const graph& G, node source, vector<size_t>& distances);
	void distances(const graph& G, vector<vector<size_t> >& ds);


} // -- namespace traversal
} // -- namespace dsa
