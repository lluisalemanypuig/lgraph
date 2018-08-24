#include <lgraph/generate_graphs/classic/classic.hpp>

namespace lgraph {
namespace networks {
namespace classic {

	void complete_graph(size_t N, uugraph& Gs) {
		Gs.init(N);

		for (node u = 0; u < N; ++u) {
			for (node v = u + 1; v < N; ++v) {
				Gs.add_edge(u,v);
			}
		}
	}

	void complete_graph(size_t N, udgraph& Gs) {
		Gs.init(N);

		for (node u = 0; u < N; ++u) {
			for (node v = 0; v < N; ++v) {
				if (u != v) {
					// self-loops are not allowed
					Gs.add_edge(u,v);
				}
			}
		}
	}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
