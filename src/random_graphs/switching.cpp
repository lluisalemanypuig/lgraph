
namespace dsa {
namespace networks {
namespace random {
namespace switching {

	// Resorts the edges so that all edges that share and enpoint with e1
	// are placed behind max_idx. The edge e1 is also put behind max_idx.
	// Returns true if max_idx >= 0.
	// Returns false if otherwise.
	// The event of 'false' happens when all edges in the set share an
	// endpoint with e1 (think of a star tree)
	bool resort_edges(size_t e_idx, vector<edge>& all_edges, size_t& max_idx) {
		edge e = all_edges[e_idx];

		// place e at the end only if necessary
		if (e_idx != max_idx) {
			swap(all_edges[e_idx], all_edges[max_idx]);
		}
		// reduce the interval:
		//               max_idx
		// [e0, e1, ...,  ek,    e_idx]
		--max_idx;

		size_t i = 0;
		while (i <= max_idx and max_idx > 0) {

			size_t s = all_edges[i].first;
			size_t t = all_edges[i].second;

			if (s == e.first or s == e.second or t == e.first or t == e.second) {
				// the i-th edge and 'e' share an endpoint
				// put the i-th edge at the end, reduce interval

				swap(all_edges[i], all_edges[max_idx]);
				--max_idx;

				// do not increment 'i' so that we can process the
				// edge that was at the end of the interval and now
				// place at the i-th position
			}
			else {
				// the i-th edge and 'e' do not share any endpoint
				// continue to the next edge.
				++i;
			}
		}

		// there may be one more edge to process...
		bool max_idx_0_or_more = true;
		if (max_idx == 0) {
			// ... there is
			size_t s = all_edges[0].first;
			size_t t = all_edges[0].second;
			if (s == e.first or e.second or t == e.first or t == e.second) {
				max_idx_0_or_more = false;
			}
		}

		return max_idx_0_or_more;
	}

	template<class G, typename dT>
	void switching_model(size_t Q, drandom_generator<G,dT> *rg, graph& Gs) {

		vector<edge> all_edges;
		Gs.edges(all_edges);
		size_t max_idx = all_edges.size() - 1;

		size_t T = Q*Gs.n_edges();
		for (size_t i = 1; i <= T; ++i) {

			rg->init_uniform(0, max_idx);
			size_t e1_idx = rg->get_uniform();

			// make sure that the next edge chosen is different
			// from e1, shares no endpoint with it, so that it
			// can be chosen in constant time
			bool r = resort_edges(e1_idx, all_edges, max_idx);

			if (r) {
				rg->init_uniform(0, max_idx);
				size_t e2_idx = rg->get_uniform();

				// delete edges e1 and e2 from the graph and
				// make two new ones, swapping the endpoints
				// of e1 and e2.

				// e1 is always placed at the end
				e1_idx = all_edges.size() - 1;

				// Exchange endpoints:
				// from ((s,t),(u,v)) to ((s,v),(u,t))
				swap(all_edges[e1_idx].second, all_edges[e2_idx].second);
			}

			max_idx = all_edges.size() - 1;
		}

		// clear the current graph and build a new one
		// with the switched edges
		const size_t N = Gs.n_nodes();
		Gs.clear();
		Gs.init(N);
		for (const edge& e : all_edges) {
			Gs.add_edge(e);
		}
	}


} // -- namespace switching
} // -- namespace random
} // -- namespace networks
} // -- namespace dsa

