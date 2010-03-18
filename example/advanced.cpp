// Example of advanced usage of CLPP 1.0rc.
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
	
	void version() {
		std::cout << "Version 1.0.0" << std::endl;
		::exit( 0 );
	}
	
	void config_file( const std::string& path ) {
		// ...
	}
	
	// Supports since 0.9.3 version.
	class Log {
		// Some_storage m_storage;
	public:
		void log_file( const std::string& path ) {
			std::cout << "path: " << path << std::endl;
			// m_storage.store_path( path );
		}
		void log_num( const std::string& number ) {
			std::cout << "number: " << number << std::endl;
			// m_storage.store_num( boost::lexical_cast< int >( number ) );
		}
		void log_some() {
			std::cout << "some... " << std::endl;
			// some action...
		}
		static void log_init() {
			std::cout << "init... " << std::endl;
			// some action...
		}
	};
	
	// Supports since 1.0rc version.
	/*
	class Optimizer {
		// Some_storage m_storage;
	public:
		void level( const int& lev ) {
			std::cout << "level: " << lev << std::endl;
			// No need boost::lexical_cast< int >( lev ) anymore!
			// m_storage.store_level( lev );
		}
	};
	*/
}

int main( int argc, char* argv[] ) {
	Log log;
	Optimizer optimizer;
	{
	clp_parser::command_line_parameter_parser parser;
	
	parser.add_parameter( "-h", "--help", help );
	parser.add_parameter( "--version", version );
	parser.add_parameter( "-c", "--config", config_file )
		  .default_value( "/home/" ) // Default value of path to config file.
		  .check_semantic( clp_parser::path ) // Check existence of path in current filesystem.
		  ;
	parser.add_parameter( "-lf", "--log-file", &log, &Log::log_file )
		  .necessary()
		  .check_semantic( clp_parser::path )  
		  ;
	parser.add_parameter( "-ln", "--log-num", &log, &Log::log_num )
		  .default_value( 1 )
		  .check_type( clp_parser::unsigned_integer )  
		  ;
	parser.add_parameter( "-ls", "--log-some", &log, &Log::log_some );
	// static member-function using as global function.
	parser.add_parameter( "-li", "--log-init", &Log::log_init ); 
	
	// 1.0rc version.
	// parser.add_parameter( "-o", "--optimize", &optimizer, &Optimizer::level );
	
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
