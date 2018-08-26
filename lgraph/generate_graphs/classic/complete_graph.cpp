#include <lgraph/generate_graphs/classic/classic.hpp>

namespace lgraph {
namespace networks {
namespace classic {

	inline
	void make_adjacency_matrix(size_t N, vector<neighbourhood>& adj) {
		for (size_t u = 0; u < N; ++u) {
			size_t i = 0;
			adj[u] = neighbourhood(N - 1);
			for (size_t v = 0; v < N; ++v) {
				if (u != v) {
					adj[u][i] = v;
					++i;
				}
			}
		}
	}

	void complete_graph(size_t N, uugraph& Gs) {
		vector<neighbourhood> adj(N);
		make_adjacency_matrix(N, adj);
		Gs = uugraph(adj);
	}

	void complete_graph(size_t N, udgraph& Gs) {
		vector<neighbourhood> adj(N);
		make_adjacency_matrix(N, adj);
		Gs = udgraph(adj);
	}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
