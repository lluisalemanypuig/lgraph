#include <lgraph/generate_graphs/classic/classic.hpp>

namespace lgraph {
namespace networks {
namespace classic {

	void one_regular(size_t n, uugraph& G) {
		assert(n >= 2);

		if ( (n & 0x1) == 1) {
			// if n is odd, decrease it by one
			// to make it even
			--n;
		}

		G.init(n);
		for (node u = 0; u < n; u += 2) {
			G.add_edge(u, u + 1);
		}
	}

	void one_regular(size_t n, udgraph& G, uint8_t d) {
		assert(n >= 2);

		if ( (n & 0x1) == 1) {
			// if n is odd, decrease it by one
			// to make it even
			--n;
		}

		G.init(n);
		for (node u = 0; u < n; u += 2) {

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
