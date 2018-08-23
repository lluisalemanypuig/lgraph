#include <lgraph/generate_graphs/classic/random/erdos_renyi.hpp>

namespace lgraph {
namespace networks {
namespace random {
namespace Erdos_Renyi {

	template<class G, typename cT>
	void erdos_renyi(crandom_generator<G,cT> *rg, size_t N, double p, uugraph& Gs) {
		Gs.init(N);
		rg->init_uniform(0, 1);

		size_t v = 1;
		int w = -1;

		while (v < N) {

			cT r = rg->get_uniform();
			w = w + 1 + (log(1 - r)/log(1 - p));
			while (w >= int(v) and v < N) {
				w = w - int(v);
				++v;
			}

			if (v < N) {
				Gs.add_edge(node(v),node(w));
			}
		}
	}


} // -- namespace Erdos_Renyi
} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

