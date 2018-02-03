#pragma once

/// C++ includes
#include <vector>
using namespace std;

/// Custom includes
#include "data_structures/random_generator.hpp"
#include "data_structures/svector.hpp"
#include "data_structures/graph.hpp"
#include "utils/logger.hpp"

namespace dsa {
using namespace utils;

namespace networks {
namespace epidemics {
	
	/*
	Implementation of algorithms to simulate the spread of an infection
	over a network. We say that a non-infected agent is healhy.
	
	Epidemic models implemented are:
	- SIR: Susceptible -> Infected -> Recovered
	- SIS: Susceptible -> Infected -> Susceptible
	
	
	All methods follow the same convention for their input parameters:
	- G: the network over which the infection spreads
	- p0: initial proportion of infected individuals.
		0 <= p0 <= 1
	- beta: rate of infection of an individual with a single neighbour.
		0 <= beta <= 1
	- gamma: rate of recovery of an individual.
		0 <= gamma <= 1
	- T: maximum number of steps of the simulation. The steps performed
		have index 1,2,...,T.
	- rg: the random generator used to generate real uniform numbers
		between 0 and 1.
	
	Likewise for their output parameters:
	- n_rec: n_rec[i] contains the number of recoverd agents after the
		i-th step is completed. n_rec[0] always has a zero and is not a
		valid value.
		Size at the end of the population T + 1.
	- n_sus: n_sus[i] contains the number of susceptible agents after
		the i-th step is completed. n_sus[0] contains the amount of agents
		susceptible of infection after infecting a proportion of p0 agents
		of the population.
		Size at the end of the population T + 1.
	- n_inf: n_inf[i] contains the number of infected agents after the
		i-th step is completed. n_inf[0] contains the amount of agents
		susceptible of infection after infecting a proportion of p0 agents
		of the population.
		Size at the end of the population T + 1.
	*/
	
	template<
		class G = default_random_engine,
		typename dT = size_t,
		typename cT = double
	>
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
	);
	
	template<
		class G = default_random_engine,
		typename dT = size_t,
		typename cT = double
	>
	void SIS
	(
		const graph& net,
		double p0, double beta, double gamma,
		size_t T,
		drandom_generator<G,dT> *drg,
		crandom_generator<G,cT> *crg,
		
		vector<size_t>& n_rec,
		vector<size_t>& n_sus,
		vector<size_t>& n_inf
	);
	
	
} // -- namespace epidemics
} // -- namespace networks
} // -- namespace dsa

#include "sir.cpp"
#include "sis.cpp"
