/*********************************************************************
 * lgraph
 * Copyright (C) 2018-2019 Lluís Alemany Puig
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Contact: Lluís Alemany Puig (lluis.alemany.puig@gmail.com)
 * 
 ********************************************************************/

#include <lgraph/graph_traversal/traversal_ux.hpp>

// C++ includes
#include <queue>
using namespace std;

// lgraph includes
#include <lgraph/graph_traversal/bfs.hpp>

namespace lgraph {
namespace traversal {
using namespace std;
using namespace bfs;

/* VERTEX-VERTEX */

_new_ uxdistance(const uxgraph *G, node source, node target) {
	// distances from source to nodes
	queue<_new_> distances;
	distances.push(0);

	// current distance from source to u
	_new_ current_dist;

	// distance from source to target. Set to infinite
	// for those targets not reachable from source.
	_new_ st_dist = inf_t<_new_>();

	// DO terminate when target node is found. BFS guarantees that when this happens
	// the shortest distance was found
	bfs_terminate terminate =
	[&target](const uxgraph *, node u, const vector<bool>&)
	{
		return u == target;
	};

	bfs_process_current process_current =
	[&distances, &current_dist, &target, &st_dist]
	(const uxgraph *, node u, const vector<bool>&)
	{
		current_dist = distances.front();
		distances.pop();
		if (u == target) {
			st_dist = current_dist;
		}
	};

	// function to compute the shortest distance from source to node v
	bfs_process_neighbour process_neighbour =
	[&distances, &current_dist]
	(const uxgraph *, node, node v, const vector<bool>& vis)
	{
		if (not vis[v]) {
			distances.push(current_dist + 1);
		}
	};

	BFS(G, source, terminate, process_current, process_neighbour);

	return st_dist;
}

_new_ uxdistance(const uxgraph *G, node source, node target, size_t& n_paths) {
	vector<_new_> distances;
	vector<size_t> paths;
	uxdistance(G, source, distances, paths);
	n_paths = paths[target];
	return distances[target];
}

/* VERTEX-ALL */

void uxdistance(const uxgraph *G, node source, std::vector<_new_>& ds) {
	const size_t N = G->n_nodes();

	// distance from source to all nodes
	ds = vector<_new_>(N, inf_t<_new_>());
	ds[source] = 0;

	// do NOT terminate: iterate through all nodes
	bfs_terminate terminate =
	[](const uxgraph *, node, const vector<bool>&)
	{ return false; };

	// don't need to process the currently visited node
	bfs_process_current process_current =
	[](const uxgraph *, node, const vector<bool>&) { };

	// function to compute the shortest distance from source to node v
	bfs_process_neighbour process_neighbour =
	[&ds](const uxgraph *, node u, node v, const vector<bool>&)
	{
		_new_ d = ds[u] + 1;
		if (d < ds[v]) {
			ds[v] = d;
		}
	};

	BFS(G, source, terminate, process_current, process_neighbour);
}

void uxdistance
(const uxgraph *G, node source, std::vector<_new_>& ds, std::vector<size_t>& n_paths)
{
	const size_t N = G->n_nodes();

	// distance from source to all nodes
	ds = vector<_new_>(N, inf_t<_new_>());
	ds[source] = 0;
	// number of paths between each pair of nodes
	n_paths = vector<size_t>(N, 0);
	n_paths[source] = 1;

	// do NOT terminate: iterate through all nodes
	bfs_terminate terminate =
	[](const uxgraph *, node, const vector<bool>&)
	{
		return false;
	};

	// don't need to process the currently visited node
	bfs_process_current process_current =
	[](const uxgraph *, node, const vector<bool>&) { };

	// function to compute the shortest distance from source to node v
	bfs_process_neighbour process_neighbour =
	[&ds, &n_paths](const uxgraph *, node u, node v, const vector<bool>&)
	{
		_new_ d = ds[u] + 1;
		if (d < ds[v]) {
			ds[v] = d;
			n_paths[v] = n_paths[u];
		}
		else if (d == ds[v]) {
			++n_paths[v];
		}
	};

	BFS(G, source, terminate, process_current, process_neighbour);
}

/* ALL-ALL */

void uxdistances(const uxgraph *G, std::vector<std::vector<_new_> >& dist) {
	const size_t N = G->n_nodes();

	// initialise data
	dist = vector<vector<_new_> >(N, vector<_new_>(N, inf_t<_new_>()));

	// initialise with edge weights (here always 1)
	for (size_t u = 0; u < N; ++u) {
		const neighbourhood& Nu = G->get_neighbours(u);
		for (size_t v : Nu) {
			dist[u][v] = 1;
		}
	}

	// find the all-to-all distance (N^3)
	for (size_t w = 0; w < N; ++w) {
		// distance from a vertex to itself is 0
		dist[w][w] = 0;

		for (size_t u = 0; u < N; ++u) {
			for (size_t v = 0; v < N; ++v) {

				// ignore the cases where:
				// the path is not moving
				if (u == v) {
					continue;
				}
				// the distances are infinite
				if (dist[u][w] == inf_t<_new_>()) {
					continue;
				}
				if (dist[w][v] == inf_t<_new_>()) {
					continue;
				}

				size_t d = dist[u][w] + dist[w][v];
				if (d < dist[u][v]) {
					dist[u][v] = dist[u][w] + dist[w][v];
				}
			}
		}
	}
}

void uxdistances(
	const uxgraph *G,
	std::vector<std::vector<_new_> >& dist,
	std::vector<std::vector<size_t> >& n_paths
)
{
	const size_t N = G->n_nodes();

	// initialise data
	dist = vector<vector<_new_> >(N, vector<_new_>(N, inf_t<_new_>()));
	n_paths = vector<vector<size_t> >(N, vector<size_t>(N, 0));

	// initialise with edge weights (here always 1) the distance and the
	// number of shortest-paths from u to all its neighbours
	for (size_t u = 0; u < N; ++u) {
		const neighbourhood& Nu = G->get_neighbours(u);
		for (size_t v : Nu) {
			dist[u][v] = 1;
			n_paths[u][v] = 1;
		}
	}

	// find the all-to-all distance (N^3)
	for (size_t w = 0; w < N; ++w) {
		// distance from a vertex to itself is 0
		dist[w][w] = 0;
		n_paths[w][w] = 1;

		for (size_t u = 0; u < N; ++u) {
			for (size_t v = 0; v < N; ++v) {

				// ignore the cases where:
				// the path is not moving
				if (u == v) {
					continue;
				}
				// the distances are infinite
				if (dist[u][w] == inf_t<_new_>()) {
					continue;
				}
				if (dist[w][v] == inf_t<_new_>()) {
					continue;
				}

				size_t d = dist[u][w] + dist[w][v];
				if (d < dist[u][v]) {
					// this is a shorter path than the shortest found so far
					dist[u][v] = dist[u][w] + dist[w][v];

					if (u != w and w != v) {
						n_paths[u][v] = n_paths[u][w]*n_paths[w][v];
					}
				}
				else if (d == dist[u][v]) {
					// this is a path as short as the shortest found so far
					if (u != w and w != v) {
						n_paths[u][v] += n_paths[u][w]*n_paths[w][v];
					}
				}
			}
		}
	}
}

} // -- namespace traversal
} // -- namespace lgraph

