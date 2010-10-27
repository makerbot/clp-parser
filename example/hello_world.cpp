// Example of simplest usage of CLPP library.
//
// Copyright (C) Denis Shevchenko, 2010.
// shev.denis @ gmail.com

#include <clpp/parser.hpp>

#include <iostream>

void help() {
	std::cout << "Some help info..." << std::endl;
	::exit( 0 );
}

int main( int argc, char* argv[] ) {
	clpp::command_line_parameters_parser parser;
	parser.add_parameter( "-h", "--help", help );
	try {
		parser.parse( argc, argv );
		// If user inputs '-h' or '--help' in command line,
		// function 'help()' will be called.
	} catch ( const std::exception& exc ) {
		std::cerr << exc.what() << std::endl;
	}
	
	return 0;
}
