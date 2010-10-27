// Example of advanced usage of CLPP library.
//
// Copyright (C) Denis Shevchenko, 2010.
// shev.denis @ gmail.com

#include <clpp/parser.hpp>

#include <iostream>

void help() {
	std::cout << "Some help info..." << std::endl;
	::exit( 0 );
}
	
void version() {
	std::cout << "Version 1.0.0" << std::endl;
	::exit( 0 );
}
	
class Log {
public:
	void log_file( const std::string& path ) {
		std::cout << "path: " << path << std::endl;
	}
		
	void log_num( int number ) const {
		std::cout << "number: " << number << std::endl;
	}
		
    void log_some() {
		std::cout << "some... " << std::endl;
	}
};

int main( int argc, char* argv[] ) {
	Log log;
	
	clpp::command_line_parameters_parser parser;
	
    try {
	    parser.add_parameter( "-h", "--help", help );
	    parser.add_parameter( "--version", version );
	    parser.add_parameter( "-lf", "--log-file", &log, &Log::log_file )
		      .necessary()
		      .check_semantic( clpp::path )  
		      ;
	    parser.add_parameter( "-ln", "--log-num", &log, &Log::log_num )
		      .default_value( 1 )
		      ;
	    parser.add_parameter( "-ls", "--log-some", &log, &Log::log_some );

		parser.parse( argc, argv );
	} catch ( const std::exception& exc ) {
		std::cerr << exc.what() << std::endl;
	}
	
	return 0;
}
