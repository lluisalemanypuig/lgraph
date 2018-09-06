#include <lgraph/generate_graphs/classic/classic.hpp>

namespace lgraph {
namespace networks {
namespace classic {

	void linear_tree(size_t N, uugraph& G) {
		assert(N > 0);

		G.init(N);
		if (N == 1) {
			return;
		}

		for (node u = 0; u < N - 1; ++u) {
			G.add_edge(u, u + 1);
		}
	}

	void linear_tree(size_t N, udgraph& G, uint8_t d) {
		assert(N > 0);
		assert(1 <= d and d <= 3);

		G.init(N);
		if (N == 1) {
			return;
		}
		for (node u = 0; u < N - 1; ++u) {
			if ( (d & 0x01) == 0x01 ) {
				// clockwise
				G.add_edge(u, u + 1);
			}
			if ( (d & 0x02) == 0x02 ) {
				// counter-clockwise
				G.add_edge(u + 1, u);
			}
		}
	}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
