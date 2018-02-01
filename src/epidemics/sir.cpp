
namespace dsa {
namespace networks {
namespace epidemics {
	
	template<class G, typename dT, typename cT>
	void SIR
	(
		const graph& net,
		double p0, double beta, double gamma,
		size_t T,
		drandom_generator<G,dT> *drg,
		crandom_generator<G,cT> *crg,
		
		vector<size_t>& n_rec,
		vector<size_t>& n_sus,
		vector<size_t>& n_inf
	)
	{
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
		
		cout << "Population after initialisation" << endl;
		cout << "    Susceptible: " << susceptible << endl;
		cout << "    Infected:    " << infected << endl;
		
		// update simulation information
		n_inf[0] = infected.n_elems();
		n_sus[0] = susceptible.n_elems();
		
		// apply all T steps or as many steps to see
		// the infection disappear
		size_t t = 1;
		while (t <= T and infected.n_elems() > 0) {
			
			cout << "Step: " << t << endl;
			cout << "    Phase 1:" << endl;
			
			// phase 1: infected agents try to recover
			size_t n_recovered = 0;
			for (size_t i = infected.n_elems(); i >= 1; --i) {
				
				size_t iA = infected[i - 1];
				cout << "        Agent " << iA << " recovers? ";
				
				double r = crg->get_uniform();
				if (r <= gamma) {
					cout << "Yes" << endl;
					
					// agent recovers
					infected.remove(i - 1);
					is_susceptible[iA] = false;
					is_infected[iA] = false;
					
					++n_recovered;
				}
				else {
					cout << "No" << endl;
				}
			}
			n_rec[t] = n_recovered;
			
			cout << "-------------" << endl;
			cout << "    Population:" << endl;
			cout << "        Susceptible: " << susceptible << endl;
			cout << "        Infected:    " << infected << endl;
			cout << "-------------" << endl;
			
			// phase 2: infected agents try to infect their neighbours
			// except those already recovered (this is the SIR model)
			
			size_t current_infected = infected.n_elems();
			
			cout << "    Phase 2:" << endl;
			cout << "        susceptible= " << susceptible.size() << endl;
			cout << "        infected=    " << current_infected << endl;
			
			if (current_infected < susceptible.n_elems()) {
				cout << "        Branch 1" << endl;
				
				// branch 1 (trivial approach): for each infected agent,
				// try to spread infection to its immediate neighbours.
				
				for (size_t i = 0; i < current_infected; ++i) {
					
					size_t a = infected[i];
					cout << "            Looking at agent " << a << endl;
					
					const neighbourhood& Na = net.get_neighbours(a);
					
					// iterate through the neighbours of agent 'a'
					for (size_t w : Na) {
						cout << "                Agent tries to infect neighbour " << w << endl;
						
						// if the neighbour is susceptible and not recovered yet
						// try to infect it
						if (is_susceptible[w]) {
							
							double r = crg->get_uniform();
							if (r <= beta) {
								
								cout << "                ... and succeeds" << endl;
								
								// neighbour becomes infected
								
								size_t neigh_pos;
								susceptible.position(w, neigh_pos);
								susceptible.remove(neigh_pos);
								
								infected.add(w);
								
								// update information so that this agent
								// is not revisited later in this step
								is_susceptible[w] = false;
								is_infected[w] = true;
							}
						}
						else {
							cout << "                ... but fails because it is not susceptible" << endl;
						}
					}
				}
			}
			else {
				cout << "        Branch 2" << endl;
				
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
				for (size_t i = susceptible.n_elems(); i >= 1; --i) {
					size_t sA = susceptible[i - 1];
					
					size_t infected_neighs = 0;
					const neighbourhood& N_i = net.get_neighbours(sA);
					
					// 1. compute the amount of infected neighbours
					for (size_t w : N_i) {
						if (is_infected[w]) {
							++infected_neighs;
						}
					}
					
					cout << "            Susceptible agent " << sA
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
							cout << "            ... and it became infected" << endl;
							
							// agent becomes infected
							
							// update information so that this agent is not
							// revisited later in this step
							is_susceptible[i - 1] = false;
							susceptible.remove(i - 1);
							
							is_infected[i - 1] = true;
							infected.add(sA);
						}
						else {
							cout << "            ... and survives the attempt" << endl;
						}
					}
				}
				
			}
			
			cout << "    Population:" << endl;
			cout << "        Susceptible: " << susceptible << endl;
			cout << "        Infected:    " << infected << endl;
			
			n_inf[t] = infected.n_elems();
			n_sus[t] = susceptible.n_elems();
			
			++t;
		}
		
	}
	
} // -- namespace epidemics
} // -- namespace networks
} // -- namespace dsa

