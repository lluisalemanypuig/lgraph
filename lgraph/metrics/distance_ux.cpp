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

#include <lgraph/metrics/distance_ux.hpp>

// C++ includes
#include <numeric>
using namespace std;

// lgraph includes
#include <lgraph/graph_traversal/traversal_ux.hpp>
#include <lgraph/metrics/centralities_ux.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace distance {

_new_ max_distance(const uxgraph *G) {
	std::vector<std::vector<_new_> > ds;
	traversal::uxdistances(G, ds);
	return max_distance(G, ds);
}

_new_ max_distance(const uxgraph *G, const std::vector<std::vector<_new_> >& ds) {
	const size_t N = G->n_nodes();
	_new_ D = 0;
	for (size_t i = 0; i < N; ++i) {
		D = accumulate
		(
			ds[i].begin() + i + 1, ds[i].end(), D,
			[](_new_ M, _new_ d) {
				if (d != inf_t<_new_>()) {
					M = std::max(M, d);
				}
				return M;
			}
		);
	}
	return D;
}

double mean_distance(const uxgraph *G) {
	std::vector<std::vector<_new_> > ds;
	traversal::uxdistances(G, ds);
	return mean_distance(G, ds);
}

double mean_distance(const uxgraph *G, const std::vector<std::vector<_new_> >& ds) {
	const size_t N = G->n_nodes();
	double m = 0;
	for (size_t i = 0; i < N; ++i) {

		// sum values only if they are not infinite
		double li = accumulate
		(
			ds[i].begin(), ds[i].end(), 0.0,
			[](double acc, _new_ d) {
				if (d != inf_t<_new_>()) {
					acc += d;
				}
				return acc;
			}
		);
		// divide by (N - 1) because ds[i][i] = 0
		li /= (N - 1);

		m += li;
	}
	return m/N;
}

} // -- namespace distance
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph

