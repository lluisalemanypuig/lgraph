#include <lgraph/generate_graphs/classic/classic.hpp>

namespace lgraph {
namespace networks {
namespace classic {

namespace _classic {
	inline
	void make_adjacency_matrix(size_t N, std::vector<neighbourhood>& adj) {
		neighbourhood f0t1(N);
		std::iota(f0t1.begin(), f0t1.end(), 0);

		for (size_t u = 0; u < N; ++u) {
			adj[u] = f0t1;
			adj[u].remove(0);
		}
	}
}

void complete_graph(size_t N, uugraph& G) {
	std::vector<neighbourhood> adj(N);
	_classic::make_adjacency_matrix(N, adj);
	G.init(adj, N*(N - 1)/2);
}

void complete_graph(size_t N, udgraph& G) {
	std::vector<neighbourhood> adj(N);
	_classic::make_adjacency_matrix(N, adj);
	G.init(adj, N*N);
}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
