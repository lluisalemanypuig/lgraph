#pragma once

// C++ includes
#include <vector>

// lgraph includes
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/utils/random_generator.hpp>

namespace lgraph {
namespace networks {
namespace epidemics {

/* SIR */

/**
 * @brief SIR (Susceptible, Infected, Recovered) epidemic model.
 *
 * @param[in] net The network the epidemic model is applied on
 * @param[in] p0 Initial proportion of infected individuals. Used as a probability
 * of being infected at the beginning of the simulation, applied to each individual.
 * @param[in] beta Rate of infection of an individual with a single neighbour
 * @param[in] gamma Rate of recovery of an individual
 * @param[in] T Maximum number of steps of the simulation. The steps performed have index 1,2,...,@e T
 * @param[in] drg The discrete random generator used for algorithm optimisation
 * @param[in] crg The continuous random generator used to generate numbers between 0 and 1
 *
 * @param[out] n_rec n_rec[i] contains the amount of recoverd agents after the i-th step is completed.
 *		@e n_rec[0] always has a zero and is not a valid value. Its size at the end of the simulation @e T + 1.
 *
 * @param[out] n_sus n_sus[i] contains the amount of susceptible agents after the i-th step is completed.
 *		@e n_sus[0] contains the amount of agents susceptible of infection after infecting a
 *		proportion @e of p0 agents of the population. Its size at the end of the simulation is @e T + 1.
 *
 * @param[out] n_inf n_inf[i] contains the amount of infected agents after the i-th step is completed.
 *		n_inf[0] contains the amount of agents susceptible of infection after infecting a
 *		proportion of @e p0 agents of the population. Its size at the end of the simulation @e T + 1.
 */
template<
	class G = std::default_random_engine,
	typename dT = size_t,
	typename cT = double
>
void SIR
(
	const uugraph& net,
	double p0, double beta, double gamma,
	size_t T,
	utils::drandom_generator<G,dT>& drg,
	utils::crandom_generator<G,cT>& crg,

	std::vector<size_t>& n_rec,
	std::vector<size_t>& n_sus,
	std::vector<size_t>& n_inf
);

/**
 * @brief SIR (Susceptible, Infected, Recovered) epidemic model with immunities.
 *
 * The immune nodes are not considered for infection.
 *
 * @param[in] net The network the epidemic model is applied on
 * @param[in] p0 Initial proportion of infected individuals. Used as a probability
 * of being infected at the beginning of the simulation, applied to each individual.
 * @param[in] beta Rate of infection of an individual with a single neighbour.
 * @param[in] gamma Rate of recovery of an individual.
 * @param[in] T Maximum number of steps of the simulation. The steps performed have index 1,2,...,@e T
 * @param[in] immune The individuals of the net immune to infection.
 * @param[in] drg The discrete random generator used for algorithm optimisation.
 * @param[in] crg The continuous random generator used to generate numbers between 0 and 1.
 *
 * @param[out] n_rec n_rec[i] contains the amount of recoverd agents after the i-th step is completed.
 *		@e n_rec[0] always has a zero and is not a valid value. Its size at the end of the simulation @e T + 1.
 *
 * @param[out] n_sus n_sus[i] contains the amount of susceptible agents after the i-th step is completed.
 *		@e n_sus[0] contains the amount of agents susceptible of infection after infecting a
 *		proportion @e of p0 agents of the population. Its size at the end of the simulation is @e T + 1.
 *
 * @param[out] n_inf n_inf[i] contains the amount of infected agents after the i-th step is completed.
 *		n_inf[0] contains the amount of agents susceptible of infection after infecting a
 *		proportion of @e p0 agents of the population. Its size at the end of the simulation @e T + 1.
 */
template<
	class G = std::default_random_engine,
	typename dT = size_t,
	typename cT = double
>
void SIR
(
	const uugraph& net,
	double p0, double beta, double gamma,
	size_t T,
	const std::vector<bool>& immune,
	utils::drandom_generator<G,dT>& drg,
	utils::crandom_generator<G,cT>& crg,

	std::vector<size_t>& n_rec,
	std::vector<size_t>& n_sus,
	std::vector<size_t>& n_inf
);

/* SIS */

/**
 * @brief SIS (Susceptible, Infected, Susceptible) epidemic model.
 *
 * @param[in] net The network the epidemic model is applied on.
 * @param[in] p0 Initial proportion of infected individuals. Used as a probability
 * of being infected at the beginning of the simulation, applied to each individual.
 * @param[in] beta Rate of infection of an individual with a single neighbour.
 * @param[in] gamma Rate of recovery of an individual.
 * @param[in] T Maximum number of steps of the simulation. The steps performed have index 1,2,...,@e T.
 * @param[in] drg The discrete random generator used for algorithm optimisation.
 * @param[in] crg The continuous random generator used to generate numbers between 0 and 1.
 *
 * @param[out] n_rec n_rec[i] contains the amount of recoverd agents after the i-th step is completed.
 *		@e n_rec[0] always has a zero and is not a valid value. Its size at the end of the simulation @e T + 1.
 *
 * @param[out] n_sus n_sus[i] contains the amount of susceptible agents after the i-th step is completed.
 *		@e n_sus[0] contains the amount of agents susceptible of infection after infecting a
 *		proportion @e of p0 agents of the population. Its size at the end of the simulation is @e T + 1.
 *
 * @param[out] n_inf n_inf[i] contains the amount of infected agents after the i-th step is completed.
 *		n_inf[0] contains the amount of agents susceptible of infection after infecting a
 *		proportion of @e p0 agents of the population. Its size at the end of the simulation @e T + 1.
 */
template<
	class G = std::default_random_engine,
	typename dT = size_t,
	typename cT = double
>
void SIS
(
	const uugraph& net,
	double p0, double beta, double gamma,
	size_t T,
	utils::drandom_generator<G,dT>& drg,
	utils::crandom_generator<G,cT>& crg,

	std::vector<size_t>& n_rec,
	std::vector<size_t>& n_sus,
	std::vector<size_t>& n_inf
);

/**
 * @brief SIS (Susceptible, Infected, Susceptible) epidemic model with immunities.
 *
 * @param[in] net The network the epidemic model is applied on.
 * @param[in] p0 Initial proportion of infected individuals. Used as a probability
 * of being infected at the beginning of the simulation, applied to each individual.
 * @param[in] beta Rate of infection of an individual with a single neighbour.
 * @param[in] gamma Rate of recovery of an individual.
 * @param[in] T Maximum number of steps of the simulation. The steps performed have index 1,2,...,@e T.
 * @param[in] immune The individuals of the net immune to infection.
 * @param[in] drg The discrete random generator used for algorithm optimisation.
 * @param[in] crg The continuous random generator used to generate numbers between 0 and 1.
 *
 * @param[out] n_rec n_rec[i] contains the amount of recoverd agents after the i-th step is completed.
 *		@e n_rec[0] always has a zero and is not a valid value. Its size at the end of the simulation @e T + 1.
 *
 * @param[out] n_sus n_sus[i] contains the amount of susceptible agents after the i-th step is completed.
 *		@e n_sus[0] contains the amount of agents susceptible of infection after infecting a
 *		proportion @e of p0 agents of the population. Its size at the end of the simulation is @e T + 1.
 *
 * @param[out] n_inf n_inf[i] contains the amount of infected agents after the i-th step is completed.
 *		n_inf[0] contains the amount of agents susceptible of infection after infecting a
 *		proportion of @e p0 agents of the population. Its size at the end of the simulation @e T + 1.
 */
template<
	class G = std::default_random_engine,
	typename dT = size_t,
	typename cT = double
>
void SIS
(
	const uugraph& net,
	double p0, double beta, double gamma,
	size_t T,
	const std::vector<bool>& immune,
	utils::drandom_generator<G,dT>& drg,
	utils::crandom_generator<G,cT>& crg,

	std::vector<size_t>& n_rec,
	std::vector<size_t>& n_sus,
	std::vector<size_t>& n_inf
);

} // -- namespace epidemics
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/epidemics/sir.cpp>
#include <lgraph/epidemics/sir_immune.cpp>
#include <lgraph/epidemics/sis.cpp>
#include <lgraph/epidemics/sis_immune.cpp>
