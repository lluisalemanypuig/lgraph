#include <lgraph/generate_graphs/classic/classic.hpp>

namespace lgraph {
namespace networks {
namespace classic {

	void cycle_graph(size_t N, uugraph& G) {
		assert(N >= 3);

		linear_tree(N, G);

		// last edge
		if (N > 2) {
			G.add_edge(0, N - 1);
		}
	}

	void cycle_graph(size_t N, udgraph& G, uint8_t d) {
		assert(N >= 3);
		assert(1 <= d and d <= 3);

		linear_tree(N, G, d);

		if (N > 2) {
			if ( (d & 0x01) == 0x01 ) {
				// clockwise
				G.add_edge(N - 1, 0);
			}
			if ( (d & 0x02) == 0x02 ) {
				// counter-clockwise
				G.add_edge(0, N - 1);
			}
		}
	}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
