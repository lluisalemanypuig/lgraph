#include <lgraph/generate_graphs/classic/classic.hpp>

namespace lgraph {
namespace networks {
namespace classic {

	void star_graph(size_t N, uugraph& G) {
		G.init(N);

		for (node u = 1; u < N; ++u) {
			G.add_edge(0,u);
		}
	}

	void star_graph(size_t N, udgraph& G, uint8_t d) {
		G.init(N);

		for (node u = 1; u < N; ++u) {
			if ( (d & 0x01) == 0x01 ) {
				// clockwise
				G.add_edge(0,u);
			}
			if ( (d & 0x02) == 0x02 ) {
				// counter-clockwise
				G.add_edge(u,0);
			}
		}
	}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
