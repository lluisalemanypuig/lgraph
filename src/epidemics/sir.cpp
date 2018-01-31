
namespace dsa {
namespace networks {
namespace epidemics {
	
	template<class G, typename cT>
	void SIR
	(
		const graph& net,
		double p0, double beta, double gamma,
		size_t T,
		crandom_generator<> *rg,
		
		vector<size_t>& n_rec,
		vector<size_t>& n_sus,
		vector<size_t>& n_inf
	)
	{
		const size_t N = net.n_nodes();
		
		// sets of infected and susceptible agents
		svector<size_t> infected(N), susceptible(N);
		// easily find recovered and infected agents
		vector<bool> is_susceptible(N, false);
		n_rec = vector<size_t>(T + 1, 0);
		n_sus = vector<size_t>(T + 1, 0);
		n_inf = vector<size_t>(T + 1, 0);
		
		// initialise population with some infected agents
		for (size_t i = 0; i < N; ++i) {
			double r = rg->get_uniform();
			if (r <= p0) {
				// is infected
				infected.add(i);
			}
			else {
				// is susceptible
				susceptible.add(i);
				is_susceptible[i] = true;
			}
		}
		
		// update simulation information
		n_inf[0] = infected.n_elems();
		n_sus[0] = susceptible.n_elems();
		
		// apply all T steps or as many steps to see
		// the infection disappear
		size_t t = 1;
		while (t <= T and infected.n_elems() > 0) {
			
			// step 1: infected agents try to recover
			size_t n_recovered = 0;
			for (size_t i = infected.n_elems(); i >= 1; --i) {
				
				double r = rg->get_uniform();
				if (r <= gamma) {
					// agent recovers
					infected.remove(i - 1);
					is_susceptible[i - 1] = false;
					
					++n_recovered;
				}
			}
			n_rec[t] = n_recovered;
			
			// step 2: infected agents try to infect their neighbours
			// except those already recovered (this is the SIR model)
			
			// branch 1: for each infected agent, try to spread infection
			// to its immediate neighbours.
			size_t current_infected = infected.n_elems();
			for (size_t i = 0; i < current_infected; ++i) {
				
				size_t a = infected[i];
				const neighbourhood& Na = net.get_neighbours(a);
				
				// iterate through the neighbours of agent 'a'
				for (size_t j = 0; j < Na.size(); ++j) {
					size_t a_neigh = Na[j];
					
					// if the neighbour is susceptible and not recovered yet
					// try to infect it
					if (is_susceptible[a_neigh]) {
						
						double r = rg->get_uniform();
						if (r <= beta) {
							size_t neigh_pos;
							susceptible.position(a_neigh, neigh_pos);
							
							infected.add(a_neigh);
							susceptible.remove(neigh_pos);
							
							// update information so that this
							// agent is not revisited later in
							// this step
							is_susceptible[a_neigh] = false;
						}
					}
				}
			}
			
			n_inf[t] = infected.n_elems();
			n_sus[t] = susceptible.n_elems();
			
			++t;
		}
		
	}
	
} // -- namespace epidemics
} // -- namespace networks
} // -- namespace dsa

