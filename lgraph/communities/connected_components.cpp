#include <lgraph/communities/communities.hpp>

namespace lgraph {
namespace networks {
namespace communities {

	size_t connected_components(const uugraph& g, vector<size_t>& comps) {
		comps = vector<size_t>(g.n_nodes(), g.n_nodes());

		return 0;
	}

	size_t connected_components(const udgraph& g, vector<size_t>& comps) {
		comps = vector<size_t>(g.n_nodes(), g.n_nodes());

		return 0;
	}

} // -- namespace communities
} // -- namespace networks
} // -- namespace lgraph
