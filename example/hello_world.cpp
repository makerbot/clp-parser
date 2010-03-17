// Example of simplest usage of CLPP 0.9.3. 
//
// Copyright (C) Denis Shevchenko, 2010.
// shev.denis @ gmail.com

#include <clpp/parser.hpp>

#include <iostream>

namespace {
	void help() {
		std::cout << "Help info..." << std::endl;
		::exit( 0 );
	}
}

int main( int argc, char* argv[] ) {
	{
	clp_parser::command_line_parameter_parser parser;
	parser.add_parameter( "-h", "--help", help );
	try {
		parser.parse( argc, argv );
	} catch ( const std::exception& exc ) {
		std::cerr << exc.what() << std::endl;
	}
	} // At exit from scope parser will destroy, because it no need anymore.
	  // All obtained resources will be free.
	
	// ...
	
	return 0;
}
