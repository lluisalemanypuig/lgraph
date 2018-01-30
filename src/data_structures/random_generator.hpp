#pragma once

/// C++ includes
#include <random>
using namespace std;

namespace dsa {
namespace utils {

/*
Simple class that implements a pseudo-random number generator.
It uses some of the C++11 utilities available in the header <random>
to generate random numbers following different distributions, e.g.
uniform distribution, geometric, Bernoulli, binomial, ...
*/

template<
	class G = default_random_engine,	// class used for the random engine
	typename T = size_t				// type of the distribution
										// int, double, unsigned int, size_t, ...
>
class random_generator {
	protected:
		G gen;
		
	public:
		random_generator();
		virtual ~random_generator();
		
		// Initialises the random engine.
		virtual void seed_random_engine();
		
		/* Initialisers of the distributions */
		
		virtual void init_uniform(T a, T b) = 0;
		
		/* Get pseudo-random numbers */
		
		virtual T get_uniform() = 0;
		
}; // -- class random_generator

///
/// DISCRETE RANDOM GENERATOR

template<
	class G = default_random_engine,	// class used for the random engine
	typename dT = size_t				// type of the discrete distributions
										// int, char, unsigned int, size_t, ...
>
class drandom_generator : public random_generator<G,dT> {
	private:
		uniform_int_distribution<dT> U;
		
	public:
		drandom_generator();
		~drandom_generator();
		
		/* Initialisers of the distributions */
		
		void init_uniform(dT a, dT b);
		
		/* Get pseudo-random numbers */
		
		dT get_uniform();
		
}; // -- class drandom_generator

///
/// CONTINUOUS RANDOM GENERATOR

template<
	class G = default_random_engine,	// class used for the random engine
	typename cT = float				// type of the continuous distributions
										// float, double
>
class crandom_generator : public random_generator<G,cT> {
	private:
		uniform_real_distribution<cT> U;
		
	public:
		crandom_generator();
		~crandom_generator();
		
		/* Initialisers of the distributions */
		
		void init_uniform(cT a, cT b);
		
		/* Get pseudo-random numbers */
		
		cT get_uniform();
		
}; // -- class crandom_generator

} // -- namespace utils
} // -- namespace dsa

#include "random_generator.cpp"
#include "drandom_generator.cpp"
#include "crandom_generator.cpp"
