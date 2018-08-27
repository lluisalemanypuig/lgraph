#include <lgraph/generate_graphs/random/watts_strogatz.hpp>

namespace lgraph {
using namespace utils;

namespace networks {
namespace random {

	namespace _ws {
		inline
		void get_non_neighbours(const uugraph& Gs, node u, svector<node>& non_neighbours) {
			size_t N = Gs.n_nodes();

			// initialise non-neighbours node list with all nodes
			for (node v = 0; v < N; ++v) {
				non_neighbours[v] = v;
			}
			// a node is not a neighbour of itself
			non_neighbours.remove(u);

			// filter neighbours from non-neighbours list
			// (delete them from the list)
			for (node v : Gs.get_neighbours(u)) {
				non_neighbours.find_remove(v);
			}
		}
	}

	template<class G, typename cT, typename dT>
	void Watts_Strogatz(
		crandom_generator<G,cT> *crg,
		drandom_generator<G,dT> *drg,
		size_t N, size_t k, cT p,
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

		for (node u = 0; u < N; ++u) {			
			// nothing to do if the node has as neighbours
			// the other nodes of the graph: rewiring an edge
			// would be superfluous
			if (Gs.degree(u) == N - 1) {
				continue;
			}

			// -- make the list of the N-k non-neighbours of node u

			// initialise non-neighbours node list
			svector<node> nn(N);
			_ws::get_non_neighbours(Gs, u, nn);

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
					drg->init_uniform(0, nn.size() - 1);

					// choose new node
					size_t wp = drg->get_uniform();
					node w = nn[wp];

					// node 'w' is now a neighbour
					nn.remove(wp);
					// node 'v' is no longer a neighbour
					nn.add(v);

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

