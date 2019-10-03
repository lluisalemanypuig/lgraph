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

namespace lgraph {
namespace traversal {
using namespace std;

/* VERTEX-VERTEX */

// one path
void uxpath(const uxgraph *G, node source, node target, boolean_path<_new_>& p) {
	node_path<_new_> path;
	uxpath(G, source, target, path);
	p.init(G->n_nodes(), path);
}

// all paths
void uxpaths(const uxgraph *G, node source, node target, boolean_path_set<_new_>& ps) {
	node_path_set<_new_> node_all_paths;
	uxpaths(G, source, target, node_all_paths);
	from_nps_to_bps(node_all_paths, G->n_nodes(), ps);
}

/* VERTEX-ALL */

// one path
void uxpath(const uxgraph *G, node source, std::vector<boolean_path<_new_> >& ps) {
	vector<node_path<_new_> > nps;
	uxpath(G, source, nps);
	for (const node_path<_new_>& p : nps) {
		ps.push_back(boolean_path<_new_>());
		ps.back().init(G->n_nodes(), p);
	}
}

// all paths
void uxpaths(const uxgraph *G, node source, std::vector<boolean_path_set<_new_> >& ps) {
	const size_t N = G->n_nodes();

	vector<node_path_set<_new_> > node_ps;
	uxpaths(G, source, node_ps);

	ps = vector<boolean_path_set<_new_> >(N);
	for (size_t i = 0; i < N; ++i) {
		from_nps_to_bps(node_ps[i], N, ps[i]);
	}
}

/* ALL-ALL */

// one path
void uxpath
(const uxgraph *G, std::vector<std::vector<boolean_path<_new_> > >& all_all_paths)
{
	const size_t N = G->n_nodes();

	vector<node_path_set<_new_> > node_ps;
	uxpath(G, node_ps);

	all_all_paths = vector<boolean_path_set<_new_> >(N);
	for (size_t i = 0; i < N; ++i) {
		from_nps_to_bps(node_ps[i], N, all_all_paths[i]);
	}
}

// all paths
void uxpaths
(const uxgraph *G, std::vector<std::vector<boolean_path_set<_new_> > >& all_all_paths)
{
	const size_t N = G->n_nodes();

	vector<vector<node_path_set<_new_> > > all_all_node_paths;
	uxpaths(G, all_all_node_paths);

	all_all_paths =
		vector<vector<boolean_path_set<_new_> > >
		(N, vector<boolean_path_set<_new_> >(N));

	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < N; ++j) {
			from_nps_to_bps(all_all_node_paths[i][j], N, all_all_paths[i][j]);
		}
	}
}

} // -- namespace traversal
} // -- namespace lgraph
