#include "classic.hpp"

namespace lgraph {
namespace networks {
namespace classic {

	void linear_tree(size_t N, uugraph& Gs) {
		assert(N > 0);

		Gs.init(N);
		if (N == 1) {
			return;
		}

		for (node u = 0; u < N - 1; ++u) {
			Gs.add_edge(u, u + 1);
		}
	}

	void linear_tree(size_t N, udgraph& Gs, uint8_t d) {
		assert(N > 0);
		assert(1 <= d and d <= 3);

		Gs.init(N);
		if (N == 1) {
			return;
		}
		for (node u = 0; u < N - 1; ++u) {
			if ( (d & 0x01) == 0x01 ) {
				// clockwise
				Gs.add_edge(u, u + 1);
			}
			if ( (d & 0x02) == 0x02 ) {
				// counter-clockwise
				Gs.add_edge(u + 1, u);
			}
		}
	}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
