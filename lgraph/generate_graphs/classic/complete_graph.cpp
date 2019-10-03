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

#include <lgraph/generate_graphs/classic/classic.hpp>

// C++ includes
#include <numeric>
using namespace std;

namespace lgraph {
namespace networks {
namespace classic {

namespace _classic {
	inline
	void make_adjacency_matrix(size_t N, vector<neighbourhood>& adj) {
		neighbourhood f0t1(N);
		iota(f0t1.begin(), f0t1.end(), 0);

		for (size_t u = 0; u < N; ++u) {
			adj[u] = f0t1;
			adj[u].remove(0);
		}
	}
}

void complete_graph(size_t N, uugraph& G) {
	vector<neighbourhood> adj(N);
	_classic::make_adjacency_matrix(N, adj);
	G.init(adj, N*(N - 1)/2);
}

void complete_graph(size_t N, udgraph& G) {
	vector<neighbourhood> adj(N);
	_classic::make_adjacency_matrix(N, adj);
	G.init(adj, N*N);
}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
