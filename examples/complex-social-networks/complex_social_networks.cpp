// C includes
#include <string.h>

// C++ includes
#include <iostream>
#include <iomanip>
#include <map>
using namespace std;

// Custom includes
#include <lgraph/data_structures/random_generator.hpp>
#include <lgraph/data_structures/xxgraph.hpp>
#include <lgraph/data_structures/svector.hpp>
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/random_graphs/barabasi_albert.hpp>
#include <lgraph/random_graphs/switching.hpp>
#include <lgraph/metrics/centralities.hpp>
#include <lgraph/metrics/clustering.hpp>
#include <lgraph/metrics/distance.hpp>
#include <lgraph/epidemics/models.hpp>
using namespace lgraph;
using namespace networks;
using namespace utils;

// <Global variables (only used here)>
string model = "none";
string variant = "none";
string from_file = "none";
string to_file = "none";
	
size_t n0 = 10;
size_t m0 = 5;
size_t T = 1;

bool apply_switching = false;
size_t Q = 1;

bool clust_gcc = false;
bool clust_mlcc = false;
bool dist_mgc = false;
bool dist_diam = false;
bool dist_mcc = false;

bool cent_degree = false;
bool cent_closeness = false;
bool cent_betweenness = false;

bool epid_sir = false;
bool epid_sis = false;
double epid_p0 = 0.5;
double epid_gamma = 0.5;
double epid_beta = 0.5;
size_t epid_T = 1;

bool seed = false;

drandom_generator<> *drg;
crandom_generator<> *crg;
// </Global variables>

void print_usage() {
	cout << "Help of this program" << endl;
	cout << "    [-h, --help]: show the usage of this program" << endl;
	cout << "* Reading/writing a network from/to a file:" << endl;
	cout << "    [-i, --input]: reads a network from the specified file. The format must be" << endl;
	cout << "        a list of edges (pairs of vertices spaced)" << endl;
	cout << "    [-o, --output]: stores the generated network in the specified file" << endl;
	cout << endl;
	cout << "* Generating random networks" << endl;
	cout << "    Model selection parameters:" << endl;
	cout << "    --barabasi-albert: generate a Barabasi-Albert model" << endl;
	cout << "        Use one of the following parameters to specify a variant" << endl;
	cout << "        -pa: Generate Barabasi-Albert model with preferential attachment (default)" << endl;
	cout << "        -ra: Generate Barabasi-Albert model with random attachment" << endl;
	cout << "        -ng: Generate Barabasi-Albert model without vertex growth" << endl;
	cout << endl;
	cout << "    Modification of the generated network:" << endl;
	cout << "        -sw: Apply the Switching model on the generated network" << endl;
	cout << endl;
	cout << "    Barabasi-Albert model configuration parameters:" << endl;
	cout << "        --T:  Number of steps of the simulation" << endl;
	cout << "              Default: 1" << endl;
	cout << "        --n0: Initial number of vertices" << endl;
	cout << "              Default: 10" << endl;
	cout << "        --m0: Number of edges added at each step" << endl;
	cout << "              Default: 5" << endl;
	cout << endl;
	cout << "    Switching model configuration parameters:" << endl;
	cout << "        --Q:  The switching model will run for Q*|E| steps." << endl;
	cout << "              Default: 1" << endl;
	cout << endl;
	cout << endl;
	cout << "* Evaluating networks:" << endl;
	cout << "    --gcc: compute Global Clustering Coeficient (Newman 2010)" << endl;
	cout << "    --mlcc: compute Mean Local Clustering Coeficient (Watts & Strogatz 1998)" << endl;
	cout << "    --mgd: mean geodesic distance (average shortest distance between all pairs of nodes)" << endl;
	cout << "    --diam: diameter of the network" << endl;
	cout << "    --mcc: mean closeness centrality" << endl;
	cout << endl;
	cout << endl;
	cout << "* Evaluate importance of nodes:" << endl;
	cout << "    --dc: degree centrality" << endl;
	cout << "    --cc: closeness centrality" << endl;
	cout << "    --bt: betweenness centrality" << endl;
	cout << endl;
	cout << endl;
	cout << "* Simulation of the spread of an infection:" << endl;
	cout << "    --sir: simulate the SIR model over the generated network" << endl;
	cout << "    --sis: simulate the SIS model over the generated network" << endl;
	cout << "    Configuration of the simulation:" << endl;
	cout << "        --p0: initial proportion of infected individuals" << endl;
	cout << "              Default: 0.5" << endl;
	cout << "        --beta: rate of infection" << endl;
	cout << "              Default: 0.5" << endl;
	cout << "        --gamma: rate of recovery" << endl;
	cout << "              Default: 0.5" << endl;
	cout << "        --T-epidemics: number of steps of simulation" << endl;
	cout << "              Default: 1" << endl;
	cout << endl;
	cout << endl;
	cout << "* Other options" << endl;
	cout << "    --seed: Seed the random number generator" << endl;
}

void print_metrics(const uugraph& Gs) {
	if (clust_gcc or clust_mlcc or dist_mgc or dist_diam or dist_mcc) {
		cout << "Metrics:" << endl;
		if (clust_gcc) {
			cout << "    Global clustering coefficient:     " << networks::metrics::clustering::gcc(Gs) << endl;
		}
		if (clust_mlcc) {
			cout << "    Mean local clustering coefficient: " << networks::metrics::clustering::mlcc(Gs) << endl;
		}
		if (dist_mgc) {
			cout << "    Mean geodesic distance: " << networks::metrics::distance::mean_distance(Gs) << endl;
		}
		if (dist_diam) {
			cout << "    Maximum geodesic distance: " << networks::metrics::distance::max_distance(Gs) << endl;
		}
		if (dist_mcc) {
			cout << "    Mean closeness centrality: " << networks::metrics::distance::mcc(Gs) << endl;
		}
		cout << endl;
	}
}

void print_degree_centrality(const uugraph& Gs) {
	cout << "    Degree centrality:" << endl;
	
	vector<double> deg_cen;
	networks::metrics::centralities::degree(Gs, deg_cen);
	for (size_t u = 0; u < deg_cen.size(); ++u) {
		cout << "    Node " << u << ": " << deg_cen[u] << endl;
	}
	
	cout << endl;
}

void print_closeness_centrality(const uugraph& Gs) {
	cout << "    Closeness centrality:" << endl;

	vector<double> close_cen;
	networks::metrics::centralities::closeness(Gs, close_cen);
	for (size_t u = 0; u < close_cen.size(); ++u) {
		cout << "    Node " << u << ": " << close_cen[u] << endl;
	}

	cout << endl;
}

void print_betweenness_centrality(const uugraph& Gs) {
	cout << "    Betweenness centrality:" << endl;

	vector<double> bt_cen;
	networks::metrics::centralities::betweenness(Gs, bt_cen);
	for (size_t u = 0; u < bt_cen.size(); ++u) {
		cout << "    Node " << u << ": " << bt_cen[u] << endl;
	}

	cout << endl;
}

void print_centralities(const uugraph& Gs) {
	if (cent_degree or cent_closeness or cent_betweenness) {
		cout << "Centralities:" << endl;
		if (cent_degree) {
			print_degree_centrality(Gs);
		}
		if (cent_closeness) {
			print_closeness_centrality(Gs);
		}
		if (cent_betweenness) {
			print_betweenness_centrality(Gs);
		}
	}
}

void display_epid_information
(
	const vector<size_t>& rec,
	const vector<size_t>& sus,
	const vector<size_t>& inf
)
{
	size_t max_rec, max_sus, max_inf;
	max_rec = max_sus = max_inf = 0;
	
	for (size_t i = 0; i < rec.size(); ++i) {
		max_rec = max(max_rec, rec[i]);
		max_sus = max(max_sus, sus[i]);
		max_inf = max(max_inf, inf[i]);
	}
	
	size_t len_step = max(size_t(4), std::to_string(rec.size()).length());
	size_t len_rec  = max(size_t(3), std::to_string(max_rec).length());
	size_t len_sus  = max(size_t(3), std::to_string(max_sus).length());
	size_t len_inf  = max(size_t(3), std::to_string(max_inf).length());
	
	cout << setw(len_step) << "Step" << "\t"
		 << setw(len_rec) << "Rec" << "\t"
		 << setw(len_sus) << "Sus" << "\t"
		 << setw(len_inf) << "Inf" << endl;
	
	cout << setw(len_step) << 0 << "\t"
		 << setw(len_rec) << " " << "\t"
		 << setw(len_sus) << sus[0] << "\t"
		 << setw(len_inf) << inf[0] << endl;
	
	for (size_t t = 1; t < inf.size(); ++t) {
		cout << setw(len_step) << t << "\t"
			 << setw(len_rec) << rec[t] << "\t"
			 << setw(len_sus) << sus[t] << "\t"
			 << setw(len_inf) << inf[t] << endl;
	}
}

void execute_epidemic_models(const uugraph& Gs) {
	vector<size_t> n_rec, n_sus, n_inf;
	
	cout << "-- EPIDEMIC SIMULATION --" << endl;
	cout << "p0= " << epid_p0 << endl;
	cout << "beta= " << epid_beta << endl;
	cout << "gamma= " << epid_gamma << endl;
	
	if (epid_sir) {
		networks::epidemics::SIR
		(
			Gs,
			epid_p0, epid_beta, epid_gamma, epid_T,
			drg, crg,
			n_rec, n_sus, n_inf
		);
		
		cout << "SIR:" << endl;
		display_epid_information(n_rec, n_sus, n_inf);
	}
	
	if (epid_sis) {
		networks::epidemics::SIS
		(
			Gs,
			epid_p0, epid_beta, epid_gamma, epid_T,
			drg, crg,
			n_rec, n_sus, n_inf
		);
		
		cout << "SIS:" << endl;
		display_epid_information(n_rec, n_sus, n_inf);
	}
}

int parse_options(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-h") == 0 or strcmp(argv[i], "--help") == 0) {
			print_usage();
			return 1;
		}
		else if (strcmp(argv[i], "-i") == 0 or strcmp(argv[i], "--input") == 0) {
			from_file = string(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "-o") == 0 or strcmp(argv[i], "--output") == 0) {
			to_file = string(argv[i + 1]);
			++i;
		}
		else if (strcmp(argv[i], "--barabasi-albert") == 0) {
			model = "barabasi-albert";
		}
		else if (strcmp(argv[i], "-pa") == 0) {
			variant = "preferential";
		}
		else if (strcmp(argv[i], "-ra") == 0) {
			variant = "random";
		}
		else if (strcmp(argv[i], "-ng") == 0) {
			variant = "no-growth";
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
		else if (strcmp(argv[i], "--T-epidemics") == 0) {
			epid_T = atoi(argv[i + 1]);
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
		else if (strcmp(argv[i], "--mgd") == 0) {
			dist_mgc = true;
		}
		else if (strcmp(argv[i], "--diam") == 0) {
			dist_diam = true;
		}
		else if (strcmp(argv[i], "--mcc") == 0) {
			dist_mcc = true;
		}
		else if (strcmp(argv[i], "--dc") == 0) {
			cent_degree = true;
		}
		else if (strcmp(argv[i], "--cc") == 0) {
			cent_closeness = true;
		}
		else if (strcmp(argv[i], "--bt") == 0) {
			cent_betweenness = true;
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
	
	if (model == "none" and from_file == "none") {
		cerr << "Error: no model selected nor a file was specified." << endl;
		cerr << "    Use [-h, --help] to see the usage" << endl;
		return 1;
	}
	if (model != "none" and from_file != "none") {
		cerr << "Error: both model and file were specified. Choose only one." << endl;
		cerr << "    Use [-h, --help] to see the usage" << endl;
		return 1;
	}

	drg = new drandom_generator<>();
	crg = new crandom_generator<>();
	if (seed) {
		drg->seed_random_engine();
		crg->seed_random_engine();
	}
	
	uugraph Gs;

	if (from_file != "none") {
		// read uugraph from file
		Gs.read_from_file(from_file);
	}
	else if (model == "barabasi-albert") {
		if (variant == "preferential") {
			networks::random::Barabasi_Albert::preferential_attachment(n0, m0, T, drg, Gs);
		}
		else if (variant == "random") {
			networks::random::Barabasi_Albert::random_attachment(n0, m0, T, drg, Gs);
		}
		else if (variant == "no-growth") {
			networks::random::Barabasi_Albert::no_vertex_growth(n0, m0, T, drg, Gs);
		}
	}
	
	if (apply_switching) {
		networks::random::switching::switching_model(Q, drg, Gs);
	}

	cout << "Resulting network:" << endl;
	cout << Gs << endl;
	cout << endl;
	
	print_metrics(Gs);
	
	print_centralities(Gs);
	
	if (epid_sir or epid_sis) {
		execute_epidemic_models(Gs);
	}
	
	if (to_file != "none") {
		Gs.store_in_file(to_file);
	}
	
	// free memory
	delete drg;
	delete crg;
}

