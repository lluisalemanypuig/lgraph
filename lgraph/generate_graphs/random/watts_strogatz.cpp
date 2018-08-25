#include <lgraph/generate_graphs/random/watts_strogatz.hpp>

namespace lgraph {
using namespace utils;

namespace networks {
namespace random {


	template<class G, typename cT, typename dT>
	void watts_strogatz(
		crandom_generator<G,cT> *crg,
		drandom_generator<G,dT> *drg,
		size_t N, size_t k, float p,
		uugraph& Gs
	)
	{
		assert(2 <= k and k <= N - 1);

		// initialise coninuous RNG
		crg->init_uniform(0, 1.0);

		if (k == N - 1) {
			// make complete graph and finish
			classic::complete_graph(N, Gs);
			return;
		}

		// -- step 1: make ring topology

		// make initial ring (2 neighbours per node)
		classic::cycle_graph(N, Gs);

		// decrease by 1 'k' if it is odd
		if (k%2 == 1) {
			--k;
		}
		// Number of remaining neighbours clockwise.
		// The (k - 2) stands for: each node has
		// already two neighbours
		size_t n = (k - 2)/2;
		// make final ring (k neighbours per node)
		for (node u = 0; u < N; ++u) {
			// Add half the neighbours (u,v) with u < v.
			// The other half will be added later.
			for (size_t i = 0; i < n; ++i) {
				Gs.add_edge(u, (u + 2 + i)%N);
			}
		}

		// -- step 2: rewiring of edges

		// actual number of neighbours clockwise.
		n = k/2;

		// rewiring...
		for (node u = 0; u < N; ++u) {			
			// nothing to do if the node has as neighbours
			// the other nodes of the graph: no possible
			// rewiring
			if (Gs.degree(u) == N - 1) {
				continue;
			}

			// -- make the list of the N-k non-neighbours of node u

			// initialise candidate list
			svector<node> candidates(N);
			for (node u = 0; u < N; ++u) {
				candidates[u] = u;
			}
			// the node itself is not a candidate for non-neighbours
			candidates.remove(u);

			for (node v = N - 2; v > 0; --v) {
				if (Gs.has_edge(u,candidates[v])) {
					candidates.remove(v);
				}
			}
			if (Gs.has_edge(u,candidates[0])) {
				candidates.remove(0);
			}

			neighbourhood Nu = Gs.get_neighbours(u);
			for (node v : Nu) {
				/* Make sure we are trying to rewire an old
				 * edge, that is, an edge that was not rewired,
				 * or we did not try to rewire in a previous
				 * iteration.
				 *
				 * In case we did not use this 'if' we might
				 * try rewiring the same edge twice. Therefore,
				 * the rewiring probability is no longer 'p'.
				 */
				if (not (u < v)) {
					continue;
				}

				// edge (u,v) from the ring created in step 1

				if (crg->get_uniform() < p) {
					// about to rewire
					drg->init_uniform(0, candidates.size() - 1);

					// choose new node
					size_t wp = drg->get_uniform();
					node w = candidates[wp];
					candidates.remove(wp);

					// remove old edge, add new edge
					Gs.remove_edge(u,v);
					Gs.add_edge(u,w);
				}
			}
		}
	}

} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

