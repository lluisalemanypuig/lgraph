#include "metrics/distance.hpp"

namespace dsa {
namespace networks {
namespace metrics {
namespace distance {

	size_t max_distance(const graph& G) {
		vector<vector<size_t> > ds;
		G.dist_all_to_all(ds);
		return max_distance(G, ds);
	}

	size_t max_distance(const graph& G, const vector<vector<size_t> >& ds) {
		const size_t N = G.n_nodes();
		size_t D = 0;
		for (size_t i = 0; i < N; ++i) {
			D = accumulate
			(
				ds[i].begin() + i + 1, ds[i].end(), D,
				[](size_t M, size_t d) {
					if (d != utils::inf) {
						M = max(M, d);
					}
					return M;
				}
			);

		}
		return D;
	}

	double mean_distance(const graph& G) {
		vector<vector<size_t> > ds;
		G.dist_all_to_all(ds);
		return mean_distance(G, ds);
	}

	double mean_distance(const graph& G, const vector<vector<size_t> >& ds) {
		const size_t N = G.n_nodes();
		double m = 0;
		for (size_t i = 0; i < N; ++i) {

			// sum values only if they are not infinite
			double li = accumulate
			(
				ds[i].begin(), ds[i].end(), 0.0,
				[](double acc, size_t d) {
					if (d != utils::inf) {
						acc += d;
					}
					return acc;
				}
			);
			// divide by (N - 1) because ds[i][i] = 0
			li /= (N - 1);

			m += li;
		}
		return m/N;
	}
	
	double mcc(const graph& G) {
		vector<double> cc;
		centralities::closeness(G, cc);
		return mcc(G, cc);
	}

	double mcc(const graph& G, const vector<double>& cc) {
		double S = std::accumulate(cc.begin(), cc.end(), 0.0);
		return S/G.n_nodes();
	}
	
} // -- namespace distance
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace dsa

