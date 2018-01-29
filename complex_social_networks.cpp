/// C includes
#include <string.h>

/// C++ includes
#include <iostream>
#include <map>
using namespace std;

/// Custom includes
#include "src/random_graphs/barabasi_albert.hpp"
#include "src/random_graphs/switching.hpp"
#include "src/metrics/centralities.hpp"
#include "src/metrics/clustering.hpp"
#include "src/epidemics/models.hpp"
#include "src/random_generator.hpp"
#include "src/graph.hpp"
using namespace dsa;
using namespace networks;
using namespace utils;

/// </Global variables (only used here)>
string model = "none";
	
size_t n0 = 10;
size_t m0 = 5;
size_t T = 7;

bool apply_switching = false;
size_t Q = 1;

bool clust_gcc = false;
bool clust_mlcc = false;

bool cent_degree = false;

bool epid_sir = false;
bool epid_sis = false;
double epid_p0, epid_gamma, epid_beta;

bool seed = false;
/// <Global variables>

void print_usage() {
	cout << "Help of this program" << endl;
	cout << "    [-h, --help]: show the usage of this program" << endl;
	cout << "* Generating random networks" << endl;
	cout << "    Model selection parameters:" << endl;
	cout << "        -pa: Generate Barabasi-Albert model with preferential attachment" << endl;
	cout << "        -ra: Generate Barabasi-Albert model with random attachment" << endl;
	cout << "        -ng: Generate Barabasi-Albert model without vertex growth" << endl;
	cout << endl;
	cout << "    Modification of the generated network:" << endl;
	cout << "        -sw: Apply the Switching model on the generated network" << endl;
	cout << endl;
	cout << "    Barabasi-Albert model configuration parameters:" << endl;
	cout << "        --T:  Number of steps of the simulation" << endl;
	cout << "        --n0: Initial number of vertices" << endl;
	cout << "        --m0: Number of edges added at each step" << endl;
	cout << endl;
	cout << "    Switching model configuration parameters:" << endl;
	cout << "        --Q:   The switching model will run for Q*|E| steps." << endl;
	cout << "              Its default value is 1" << endl;
	cout << endl;
	cout << endl;
	cout << "* Evaluating networks:" << endl;
	cout << "    --gcc: compute Global Clustering Coeficient (Newman 2010)" << endl;
	cout << "    --mlcc: compute Mean Local Clustering Coeficient (Watts & Strogatz 1998)" << endl;
	cout << endl;
	cout << endl;
	cout << "* Evaluate importance of nodes:" << endl;
	cout << "    --dc: degree centrality" << endl;
	cout << endl;
	cout << endl;
	cout << "* Simulation of the spread of an infection:" << endl;
	cout << "    --sir: simulate the SIR model over the generated network" << endl;
	cout << "    --sis: simulate the SIS model over the generated network" << endl;
	cout << "    Configuration of the simulation:" << endl;
	cout << "        --p0: initial proportion of infected individuals" << endl;
	cout << "        --beta: rate of infection" << endl;
	cout << "        --gamma: rate of recovery" << endl;
	cout << "        --T: number of steps of simulation" << endl;
	cout << endl;
	cout << endl;
	cout << "* Other options" << endl;
	cout << "    --seed: Seed the random number generator" << endl;
}

void print_metrics(const graph& Gs) {
	if (clust_gcc or clust_mlcc) {
		cout << "Metrics:" << endl;
		if (clust_gcc) {
			cout << "    Global clustering coefficient:     " << networks::metrics::clustering::gcc(Gs) << endl;
		}
		if (clust_mlcc) {
			cout << "    Mean local clustering coefficient: " << networks::metrics::clustering::mlcc(Gs) << endl;
		}
		cout << endl;
	}
}

void print_degree_centrality(const graph& Gs) {
	cout << "    Degree centrality:" << endl;
	
	vector<double> deg_cen;
	networks::metrics::centralities::degree(Gs, deg_cen);
	for (size_t u = 0; u < deg_cen.size(); ++u) {
		cout << "    Node " << u << ": " << deg_cen[u] << endl;
	}
	
	cout << endl;
}

void execute_epidemic_models(const graph& Gs) {
	
	crandom_generator<> *rg = new crandom_generator<>();
	vector<size_t> res;
	
	if (epid_sir) {
		networks::epidemics::SIR(Gs, epid_p0, epid_beta, epid_gamma, T, rg, res);
	}
	
	if (epid_sis) {
		networks::epidemics::SIS(Gs, epid_p0, epid_beta, epid_gamma, T, rg, res);
	}
	
	delete rg;
}

int parse_options(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-h") == 0 or strcmp(argv[i], "--help") == 0) {
			print_usage();
			return 1;
		}
		else if (strcmp(argv[i], "-pa") == 0) {
			model = "preferential";
		}
		else if (strcmp(argv[i], "-ra") == 0) {
			model = "random";
		}
		else if (strcmp(argv[i], "-ng") == 0) {
			model = "no-growth";
		}
		else if (strcmp(argv[i], "-sw") == 0) {
			apply_switching = true;
		}
		else if (strcmp(argv[i], "--Q") == 0) {
			Q = atoi(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--T") == 0) {
			T = atoi(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--n0") == 0) {
			n0 = atoi(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--m0") == 0) {
			m0 = atoi(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--p0") == 0) {
			epid_p0 = atof(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--beta") == 0) {
			epid_beta = atof(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--gamma") == 0) {
			epid_gamma = atof(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--seed") == 0) {
			seed = true;
		}
		else if (strcmp(argv[i], "--gcc") == 0) {
			clust_gcc = true;
		}
		else if (strcmp(argv[i], "--mlcc") == 0) {
			clust_mlcc = true;
		}
		else if (strcmp(argv[i], "--dc") == 0) {
			cent_degree = true;
		}
		else if (strcmp(argv[i], "--sir") == 0) {
			epid_sir = true;
		}
		else if (strcmp(argv[i], "--sis") == 0) {
			epid_sis = true;
		}
		else {
			cerr << "Warning: option '" << string(argv[i]) << "' not recognized" << endl;
			cerr << "    See usage with [-h, --help]" << endl;
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	int r = parse_options(argc, argv);
	if (r == 1) {
		// an error occurred or --help was used
		return 1;
	}
	
	
	if (model == "none") {
		cerr << "Error: no model selected." << endl;
		cerr << "    Use [-h, --help] to see the usage" << endl;
		return 1;
	}
	
	drandom_generator<> *rg = new drandom_generator<>();
	if (seed) rg->seed_random_engine();
	
	graph Gs;
	
	if (model == "preferential") {
		networks::random::Barabasi_Albert::preferential_attachment(n0, m0, T, rg, Gs);
	}
	else if (model == "random") {
		networks::random::Barabasi_Albert::random_attachment(n0, m0, T, rg, Gs);
	}
	else if (model == "no-growth") {
		networks::random::Barabasi_Albert::no_vertex_growth(n0, m0, T, rg, Gs);
	}
	
	if (apply_switching) {
		networks::random::switching::switching_model(Q, rg, Gs);
	}
	
	cout << "Resulting network:" << endl;
	cout << Gs << endl;
	cout << endl;
	
	print_metrics(Gs);
	
	if (cent_degree) {
		cout << "Centralities:" << endl;
		if (cent_degree) {
			print_degree_centrality(Gs);
		}
	}
	
	if (epid_sir or epid_sis) {
		execute_epidemic_models(Gs);
	}
	
	// free memory
	delete rg;
}

