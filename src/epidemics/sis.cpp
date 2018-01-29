
namespace dsa {
namespace networks {
namespace epidemics {
	
	template<
		class G = default_random_engine,
		typename cT = float
	>
	void SIS
	(
		const graph& net,
		double p0, double beta, double gamma,
		size_t T,
		crandom_generator<> *rg,
		
		vector<size_t>& n_inf
	)
	{
		
		
		
	}
	
} // -- namespace epidemics
} // -- namespace networks
} // -- namespace dsa

