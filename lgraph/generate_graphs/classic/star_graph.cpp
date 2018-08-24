#include "classic.hpp"

namespace lgraph {
namespace networks {
namespace classic {

	void star_graph(size_t N, uugraph& Gs) {
		Gs.init(N);

		for (node u = 1; u < N; ++u) {
			Gs.add_edge(0,u);
		}
	}

	void star_graph(size_t N, udgraph& Gs, uint8_t d) {
		Gs.init(N);

		for (node u = 1; u < N; ++u) {
			if ( (d & 0x01) == 0x01 ) {
				// clockwise
				Gs.add_edge(0,u);
			}
			if ( (d & 0x02) == 0x02 ) {
				// counter-clockwise
				Gs.add_edge(u,0);
			}
		}
	}

} // -- namespace classic
} // -- namespace networks
} // -- namespace lgraph
