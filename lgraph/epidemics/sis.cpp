#include <lgraph/epidemics/models.hpp>

namespace lgraph {
namespace networks {
namespace epidemics {
	
	template<class G, typename dT, typename cT>
	void SIS
	(
		const uugraph& net,
		double p0, double beta, double gamma,
		size_t T,
		drandom_generator<G,dT> *drg,
		crandom_generator<G,cT> *crg,
		
		vector<size_t>& n_rec,
		vector<size_t>& n_sus,
		vector<size_t>& n_inf
	)
	{
		logger<null_stream>& LOG = logger<null_stream>::get_logger();
		
		const size_t N = net.n_nodes();
		
		// easiliy iterate through susceptible and infected agents
		svector<size_t> infected(N), susceptible(N);
		
		// easily find susceptible and infected agents
		vector<bool> is_susceptible(N, false);
		vector<bool> is_infected(N, false);
		
		n_rec = vector<size_t>(T + 1, 0);
		n_sus = vector<size_t>(T + 1, 0);
		n_inf = vector<size_t>(T + 1, 0);
		
		// initialise population with some infected agents
		for (size_t i = 0; i < N; ++i) {
			double r = crg->get_uniform();
			if (r <= p0) {
				// is infected
				infected.add(i);
				is_infected[i] = true;
			}
			else {
				// is susceptible
				susceptible.add(i);
				is_susceptible[i] = true;
			}
		}
		
		LOG.log() << "Population after initialisation" << endl;
		LOG.log() << "    Susceptible: " << susceptible << endl;
		LOG.log() << "    Infected:    " << infected << endl;
		
		// update simulation information
		n_inf[0] = infected.size();
		n_sus[0] = susceptible.size();
		
		// apply all T steps or as many steps to see
		// the infection disappear
		size_t t = 1;
		while (t <= T and infected.size() > 0) {
			
			LOG.log() << "Step: " << t << endl;
			
			LOG.log() << "-------------------------------" << endl;
			LOG.log() << "|   Population:" << endl;
			LOG.log() << "|       Susceptible: " << susceptible << endl;
			LOG.log() << "|       Infected:    " << infected << endl;
			LOG.log() << "-------------------------------" << endl;
			
			LOG.log() << "    Phase 1:" << endl;
			
			// phase 1: infected agents try to recover
			size_t n_recovered = 0;
			for (size_t i = infected.size(); i >= 1; --i) {
				
				size_t iA = infected[i - 1];
				LOG.log() << "        Agent " << iA << " recovers? ";
				
				double r = crg->get_uniform();
				if (r <= gamma) {
					LOG.log() << "Yes" << endl;
					
					// agent recovers
					infected.remove(i - 1);
					susceptible.add(iA);
					is_susceptible[iA] = true;
					is_infected[iA] = false;
					
					++n_recovered;
				}
				else {
					LOG.log() << "No" << endl;
				}
			}
			n_rec[t] = n_recovered;
			
			LOG.log() << "-------------------------------" << endl;
			LOG.log() << "|   Population:" << endl;
			LOG.log() << "|       Susceptible: " << susceptible << endl;
			LOG.log() << "|       Infected:    " << infected << endl;
			LOG.log() << "-------------------------------" << endl;
		
			// phase 2: infected agents try to infect their neighbours
			// except those already recovered (this is the SIR model)
			
			size_t current_infected = infected.size();
			
			LOG.log() << "    Phase 2:" << endl;
			LOG.log() << "        # susceptible= " << susceptible.size() << endl;
			LOG.log() << "        # infected=    " << current_infected << endl;
			
			if (current_infected < susceptible.size()) {
				LOG.log() << "        Branch 1" << endl;
				
				// branch 1 (trivial approach): for each infected agent,
				// try to spread infection to its immediate neighbours.
				
				for (size_t a : infected) {

					LOG.log() << "            Looking at agent " << a << endl;
					
					const neighbourhood& Na = net.get_neighbours(a);
					
					// iterate through the neighbours of agent 'a'
					for (node w : Na) {

						LOG.log() << "                Agent tries to infect neighbour " << w << endl;
						
						// if the neighbour is susceptible try to infect it
						if (is_susceptible[w]) {
							
							double r = crg->get_uniform();
							if (r <= beta) {
								
								LOG.log() << "                ... and succeeds" << endl;
								
								// neighbour becomes infected
								susceptible.find_remove(w);
								infected.add(w);
								
								is_susceptible[w] = false;
								is_infected[w] = true;
							}
						}
						else {
							LOG.log() << "                ... but fails because it is not susceptible" << endl;
						}
					}
				}
			}
			else {
				LOG.log() << "        Branch 2" << endl;
				
				/*
				branch 2: for each susceptible agent, count how many
				infeced neighours it has. If agent i has k infected
				neighbours then agent i receives k attemps of infection
				and becomes infected if any of the attempts generates a
				uniform random number 'r' smaller or equal than beta. Any
				attemp will succeed with probability beta, and fail with
				probability 1 - beta. Agent i becomes infected if at least
				one attempt succeeds.
				
				Prob[at least one succeeds] = 1 - Prob[all fail] = 1 - (1 - beta)^k
				
				Deciding whether a susceptible agent i with k infected
				neighbours becomes infected or not comes down to generating
				a binomially distributed random number B(k, beta). If
				the value generated 'r' is 0, then the agent remains
				healthy. The agent becomes infected if otherwise.
				
				Therefore:
				
				for each susceptible agent:
				    1. compute the amount of infected neighbours
				    2. generate random binomial number r
				    3. if r >= 1 then agent becomes infected
				*/
				
				// for each susceptible agent:
				for (size_t i = susceptible.size(); i >= 1; --i) {
					size_t sA = susceptible[i - 1];
					
					size_t infected_neighs = 0;
					const neighbourhood& Ni = net.get_neighbours(sA);
					
					// 1. compute the amount of infected neighbours
					for (node w : Ni) {
						if (is_infected[w]) {
							++infected_neighs;
						}
					}
					
					LOG.log() << "            Susceptible agent " << sA
						 << " is surrounded by " << infected_neighs
						 << " infected agents" << endl;
					
					// do more work only if the agent has some infected
					// neighbour
					if (infected_neighs > 0) {
						// 2. generate random binomial number r
						drg->init_binomial(infected_neighs, beta);
						dT binom_val = drg->get_binomial();
						
						// 3. if r >= 1 then agent becomes infected
						if (binom_val >= 1) {
							LOG.log() << "            ... and it became infected" << endl;
							
							// agent becomes infected
							
							is_susceptible[sA] = false;
							susceptible.remove(i - 1);
							
							is_infected[sA] = true;
							infected.add(sA);
						}
						else {
							LOG.log() << "            ... and survives the attempt" << endl;
						}
					}
					else {
						LOG.log() << "            ... and survives the attempt" << endl;
					}
				}
				
			}
			
			n_inf[t] = infected.size();
			n_sus[t] = susceptible.size();
			
			++t;
		}
	}
	
} // -- namespace epidemics
} // -- namespace networks
} // -- namespace lgraph

