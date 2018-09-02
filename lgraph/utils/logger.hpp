#pragma once

// C++ includes
#include <iostream>
#include <fstream>

namespace lgraph {
namespace utils {

/**
 * @brief A class for a null stream.
 *
 * The operator '<<' for any suitable type does not have
 * any effect on it (nothing is displayed). The 'endl' modifier
 * is also redefined to have no effect on the stream.
 */
class null_stream {
	public:
		/// Open an empty stream for null messages.
		void open(const char *, const std::ios_base::openmode& ) { }
		
		/// This is the type of std::cout.
		typedef std::basic_ostream<char, std::char_traits<char> > cout_type;

		/// This is the function signature of std::endl.
		typedef cout_type& (*standard_endl)(cout_type&);

		/// Define an operator<< to take in std::endl.
		null_stream& operator<< (const standard_endl&)
		{ return *this; }
		
		/// operator<< for any printable type.
		template<class t_printable>
		null_stream& operator<< (const t_printable&)
		{ return *this; }
};

/**
 * @brief A class for the cout stream.
 *
 * A wrapper over the ostrem object cout.
 */
class cout_stream {
	public:
		/// Open an empty stream for standard output messages.
		void open(const char *, const std::ios_base::openmode& ) { }

		/// This is the type of std::cout.
		typedef std::basic_ostream<char, std::char_traits<char> > cout_type;

		/// This is the function signature of std::endl.
		typedef cout_type& (*standard_endl)(cout_type&);

		/// Define an operator<< to take in std::endl.
		cout_stream& operator<< (const standard_endl&) {
			std::cout << std::endl;
			return *this;
		}

		/// operator<< for any printable type.
		template<class t_printable>
		cout_stream& operator<< (const t_printable& t) {
			std::cout << t;
			return *this;
		}
};

/**
 * @brief A class for the cerr stream.
 *
 * A wrapper over the ostrem object cerr.
 */
class cerr_stream {
	public:
		/// Open an empty stream for error messages.
		void open(const char *, const std::ios_base::openmode& ) { }

		/// This is the type of std::cout.
		typedef std::basic_ostream<char, std::char_traits<char> > cerr_type;

		/// This is the function signature of std::endl.
		typedef cerr_type& (*standard_endl)(cerr_type&);

		/// Define an operator<< to take in std::endl.
		cerr_stream& operator<< (const standard_endl&) {
			std::cerr << std::endl;
			return *this;
		}

		/// operator<< for any printable type.
		template<class t_printable>
		cerr_stream& operator<< (const t_printable& t) {
			std::cerr << t;
			return *this;
		}
};

/**
 * @brief Class for message display.
 *
 * Singleton class to centralise the displaying of messages either
 * to the standard or error output, or to a file. For example, during
 * development it is useful to have "couts" to display the values of
 * variables, to show the progress of algorithms, ...
 *
 * Once the development is complete, one may want to get rid of these
 * couts by deleting them. This may be a bad idea since bugs may be
 * discovered later in the development of the project. To avoid their
 * deletion/comment-out, the logger can be used in the following way:
 *
 *		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();	// declare the object\n
 *		LOG.log() << "message 1" << endl;	// Use it	\n
 *		LOG.log() << "message 2" << endl;				\n\n
 *
 * Once we are not interested in displaying messages anymore, change
 * the declaration of the object to:
 *
 *		logger<null_stream>& LOG = logger<null_stream>::get_logger();
 *
 * The other calls displaying "message *" will have no effect. There
 * is only one instance of this class for a cout_stream, one for a
 * cerr_stream, one for a null_stream, and another for a stream to
 * a file.
 *
 * @param out_stream The ofstream type or the @ref null_stream.
 * @ref cout_stream, @ref cerr_stream.
 */
template<class out_stream = std::ofstream>
class logger {
	private:
		/// The stream object to output the strings to.
		out_stream fout;
		/// In case of an stream to a file, is it opened?.
		bool opened;
		
		/**
		 * @brief Empty constructor.
		 *
		 * Made private to make this class a singleton.
		 */
		logger() {
			opened = false;
		}
		
	public:
		/**
		 * @brief Returns the stream to output information to.
		 *
		 * This works exactly like the 'cout' and 'cerr' ostream
		 * classes. All objects passed to this using '<<' must
		 * implement this operator.
		 */
		out_stream& log() {
			return fout;
		}
		
		/**
		 * @brief Returns the only instance of this class.
		 * @param o In case of using a stream to a file (ofstream),
		 * indicate the name of the file.
		 * @return Returns the only instance of this class of the
		 * indicated type in the template parameter.
		 */
		static logger& get_logger(const std::string& o = "log.txt") {
			static logger<out_stream> L;
			
			if (not L.opened) {
				L.fout.open(o.c_str(), std::ios_base::app);
				L.opened = true;
			}
			
			return L;
		}
		
		/// Deleted copy-constructor.
		logger (const logger& L)			= delete;
		/// Deleted assignation operator.
		void operator= (const logger& L)	= delete;
};

} // -- namespace utils
} // -- namespace lgraph

