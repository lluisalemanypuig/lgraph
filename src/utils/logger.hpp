#pragma once

/// C++ includes
#include <iostream>
#include <fstream>
using namespace std;

template<class out_stream = std::ofstream>
class null_stream {
	public:
		null_stream() { }
		~null_stream() { }
		
		void open(const char *s, const ios_base::openmode& m = ios_base::out) { }
		
		template<typename t_printable>
		inline friend
		out_stream& operator<< (out_stream& ns, const t_printable& t) {
			return ns;
		}
};

template<class out_stream = ofstream>
class logger {
	private:
		out_stream fout;
		
		logger() { }
		
	public:
		out_stream& log() {
			return fout;
		}
		
		static logger& get_logger() {
			static logger<out_stream> L;
			L.fout.open("log", ios_base::app);
			return L;
		}
		
		logger (const logger& L)			= delete;
		void operator= (const logger& L)	= delete;
};


