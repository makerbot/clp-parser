// Command line parameters parser.
// File: parser.hpp
//
// Copyright (C) Denis Shevchenko, 2010.
// shev.denis @ gmail.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see http://www.gnu.org/licenses/lgpl.html
//
// http://clp-parser.sourceforge.net/
//
/////////////////////////////////////////////////////////////////////////////////////////
///
/// \mainpage CLPP
///
/// \section about About
///
/// This document describes <b>'Command line parameters parser'</b> library. It provides parsing 
/// of command line parameters, with callback correspond functions and, if necessary, checking 
/// parameter's value semantic.
///
/// \htmlonly <br/> \endhtmlonly
///
///
///
/// \section download Download
///
/// You can download CLPP source code from \htmlonly<b><a href="http://sourceforge.net/projects/clp-parser">SourceForge</a></b>\endhtmlonly.
/// 
/// \htmlonly <br/> \endhtmlonly
///
/// 
///
/// \section license License
///
/// This library is licensed under \htmlonly<b><a href="http://www.gnu.org/licenses/lgpl-3.0.html">LGPL</a></b>\endhtmlonly, which means that you can use it for commercial and non-commercial purposes. 
///
/// \htmlonly <br/> \endhtmlonly
///
///
///
/// \section motivation Motivation
/// \htmlonly <p style="text-align: right"><strong><em>"Don't invent bicycle"</em></strong></p> \endhtmlonly
///
/// Almost every "console-start" program required some command line parameters, so it handling 
/// is very common task. Actually, this handling add up to two tasks:
/// \li check correctness (in all senses of this word) of inputed parameters,
/// \li some reaction(s) on it.
///
/// CLPP library provides general solution for this tasks. It very simple to use. 
/// 
/// \htmlonly <br/> \endhtmlonly
/// 
///
///
/// \section hello-world-example "Hello world" example
///
/// Simplest example of CLPP using:
///
/// \code
/// namespace {
/// 	void help() {
/// 		std::cout << "My program, version 1.0. Common usage is..." << std::endl;
/// 		// ...
/// 	}
/// }
/// 
/// int main( int argc, char* argv[] ) {
/// 	clp_parser::command_line_parameter_parser parser;
/// 	// Define parameter, without value and without any checking...
/// 	parser.add_parameter( "-h", "--help", help );
/// 	try {
/// 		// If user input '-h' or '--help' in command line, help() will be calling.
/// 		parser.parse( argc, argv );
/// 	} catch ( const std::exception& exc ) {
/// 		std::cerr << exc.what() << std::endl;
/// 	}
/// 	return 0;
/// } 
/// \endcode
///
/// \htmlonly <br/> \endhtmlonly
///
///
///
/// \section features Features
///
/// \li Header-only (not need installing).
/// \li Define parameter with two (in Unix-style) or single name of parameter.
/// \li Call correspond functions, with or without value.
/// \li Common checks of inputed parameters, like duplicate, incorrect, etc.
/// \li Checking of value's type, like integer or real (defines by registered function).
/// \li Checking of value's semantic, like correct path.
/// \li Define parameter's necessity.
/// \li Define parameter's default value.
/// \li Define another "name-value" separator.
///
/// \htmlonly <br/> \endhtmlonly
///
///
///
/// \section changes Changes
///
/// Since <b>1.0rc</b> version removed <tt>check_type()</tt> function (it no need anymore). 
/// See <b>User's guide</b> for more info. 
///
/// \htmlonly <br/> \endhtmlonly
///
///
///
/// \section acknowledgements Acknowledgements
///
/// I'm very grateful to \htmlonly<b><a href="http://www2.research.att.com/~bs/">Bjarne Stroustrup</a></b>\endhtmlonly, who invent so beautiful, so powerful and so dangerous language!
/// 
/// Also I grateful to all authors of \htmlonly<b><a href="http://www.boost.org/">Boost C++ libraries</a></b>\endhtmlonly. Thank you for your work!
/// 
/// \htmlonly <br/> \endhtmlonly
///
///
///
/// \htmlonly <em>Copyright &copy; Denis Shevchenko, 2010</em> \endhtmlonly
///
/////////////////////////////////////////////////////////////////////////////////////////
///
/// \page dependencies External dependencies
///
/// There is only "one" dependency - \htmlonly<b><a href="http://www.boost.org/">Boost C++ libraries</a></b>\endhtmlonly.
/// 
/// Strictly speacking, CLPP used 
/// only following libraries:
/// \li <b>Boost.Any</b>  
/// \li <b>Boost.Signals2</b>
/// \li <b>Boost.Lexical_cast</b>  
/// \li <b>Boost.Bind</b>  
/// \li <b>Boost.Foreach</b>  
/// \li <b>Boost.Ptr_container</b>  
/// \li <b>Boost.Asio</b>
/// \li <b>Boost.Algorithm</b>
/// \li <b>Boost.Unordered</b>
/// \li <b>Boost.Smart_ptr</b>
/// \li <b>Boost.Filesystem</b>  
///
/// Full list of Boost C++ libraries see \htmlonly<b><a href="http://www.boost.org/doc/libs">there</a></b>\endhtmlonly.
///
/// All used libraries are <b>header-only</b>, except <em>Boost.Filesystem</em>, so you must build 
/// <em>Boost.Filesystem</em> library and link it with your programm.
///
/// However, if you using C++ professionally, you (in my humble opinion) <em><b>must</b></em> have 
/// Boost C++ libraries. So just download full package from \htmlonly<b><a href="http://www.boost.org/users/download/">there</a></b>\endhtmlonly, install it and enjoy!
///
/// Note: If you using Windows - see http://www.boostpro.com/download.
///
/////////////////////////////////////////////////////////////////////////////////////////
///
/// \page user_guide User's guide 
///
/// <b>Contents:</b>
///     - \ref introduction
///         - \ref value_or_not_value
/// 		- \ref necessity
/// 		- \ref default_val
///     - \ref common_usage
/// 		- \ref preparing
/// 		- \ref defining_parameter
/// 		- \ref member_functions
/// 		- \ref parsing
///     - \ref advanced_usage
///         - \ref how_to_define_necessity
///         - \ref how_to_define_default_value
/// 		- \ref how_to_define_type_check
/// 		- \ref how_to_define_semantic_check
///         - \ref combine_of_settings
///         - \ref another_value_separator
///
/// \htmlonly <br/> \endhtmlonly
///
/// \htmlonly <hr/> \endhtmlonly
/// 
/// \section introduction Introduction
///
/// Factually, using CLPP library add up to only two tasks:
/// \li <b>defining</b> set of parameters, with specify all required checkings and characteristics,
/// \li <b>parsing</b> inputed parameter(s), with defined checking and calling correspond functions.
/// 
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection value_or_not_value Value or not value?
/// 
/// Command line parameter can have value or haven't.
/// 
/// Example of parameter without value:
/// \code
/// # ./program --help
/// \endcode
/// Parameter <b>'--help'</b> is useful of its own accord, it not need any value.
///
/// Example of parameter with value:
/// \code
/// # ./program --log-dir=/some/path
/// \endcode
/// Parameter <b>'--log-dir'</b> is useless without value.
///
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection necessity Necessity
///
/// Command line parameter can be necessary or optionally.
/// 
/// In examples above parameter <b>'--help'</b> is optionally, because it may missing 
/// (only if user wants to view help info, he input '--help').
/// 
/// But parameter <b>'--log-dir'</b> <em>may be</em> necessary, so user <em>must</em> input it.
///
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection default_val Default value
///
/// Command line parameter can have default value, so not required input it.
/// This option can be useful for some paths, where defined default value:
/// 
/// In example above parameter <b>'--log-dir'</b> may have default value of path, so user can miss it.
/// 
/// \htmlonly <br/> \endhtmlonly
///
/// \htmlonly <hr/> \endhtmlonly
///
/// \section common_usage Common usage
///
/// This section describes common usage of CLPP.
///
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection preparing Preparing
///
/// Copy 'clpp' folder in some place where your compiler searches header files, and after that add:
///
/// \code #include <clpp/parser.hpp> \endcode
///
/// in your program.
///
/// For simplicity, you can also add: 
/// 
/// \code using namespace clp_parser; \endcode
///
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection defining_parameter Defining command line parameter
///
/// Defining of new parameter included three tasks:
/// \li define parameter's name (short and full names, or sungle name),
/// \li register function that will be called if correspond parameter inputed,
/// \li define checks and default value for parameter <em>(optionally)</em>.
///
/// Use for it <b>add_parameter</b> function.
///
/// \code
/// int main( int argc, char* argv[] ) {
/// 	clp_parser::command_line_parameter_parser parser;
/// 	// Define parameter with two names (in Unix-style) and register function help().
/// 	parser.add_parameter( "-h", "--help", help );
/// 	// Define parameter with single name and register function config().
/// 	parser.add_parameter( "--config", config );
/// 	// ...
/// }
/// \endcode
///
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection member_functions Register of functions-members
///
/// You can register not only global functions, but also functions-members.
///
/// \code
/// namespace {
/// 	struct some_parameters_storage {
/// 		static void init() {
/// 			// Some init actions...
/// 		}
/// 		void some_path( const std::string& path ) {
/// 			// Some work with path...
/// 		}
/// 		void some_rnum( double rnumber ) {
/// 			// Some work with rnumber...
/// 		}
/// 	}
/// }
///
/// int main( int argc, char* argv[] ) {
/// 	some_parameters_storage storage;
/// 	
/// 	clp_parser::command_line_parameter_parser parser;
/// 	parser.add_parameter( "-i", "--init", &storage::init ); // Static function can be used as global function.
/// 	parser.add_parameter( "-f", "--file", &storage, &storage::some_path );
/// 	parser.add_parameter( "-rn", "--rnumber", &storage, &storage::some_rnum );
///
/// 	// ...
///
/// 	return 0;
/// }
/// \endcode
///
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection parsing Parsing
///
/// For parsing call <b>parse</b> function.
///
/// \code
/// int main( int argc, char* argv[] ) {
/// 	clp_parser::command_line_parameter_parser parser;
/// 	// ...
/// 	try {
/// 		parser.parse( argc, argv );
/// 	} catch ( const std::exception& exc ) {
/// 		std::cerr << exc.what() << std::endl;
/// 	}
///
/// 	return 0;
/// }
/// \endcode
///
/// This function parse all inputed command line parameters, checks it correctness
/// and callback correspond functions.
///
/// \htmlonly <br/> \endhtmlonly
///
/// \htmlonly <hr/> \endhtmlonly
///
/// \section advanced_usage Advanced usage
///
/// This section describes advanced usage of CLPP.
///
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection how_to_define_necessity Define parameter's necessity
/// 
/// Parameter's necessity defines by calling <b>necessary()</b> function:
/// \code
/// int main( int argc, char* argv[] ) {
/// 	clp_parser::command_line_parameter_parser parser;
/// 	parser.add_parameter( "-c", "--config", config )
/// 		  .necessary();
/// 	// ...
/// }
/// \endcode
/// After that user <b>must</b> input this parameter in command line.
/// 
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection how_to_define_default_value Define parameter's default value
/// 
/// Parameter's default value defines by calling <b>default_value()</b> function:
/// \code
/// int main( int argc, char* argv[] ) {
/// 	clp_parser::command_line_parameter_parser parser;
/// 	parser.add_parameter( "-c", "--config", config )
/// 		  .default_value( "/some/default/path" );
/// 	// ...
/// }
/// \endcode
/// After that user <b>must</b> input this parameter.
///
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection how_to_define_type_check Parameter's value type check
///
/// Since <b>1.0rc</b> version value's type checks automatically. If you register callback function
/// \code
/// void some_num( const double& num );
///
/// int main( int argc, char* argv[] ) {
/// 	clp_parser::command_line_parameter_parser parser;
/// 	parser.add_parameter( "-n", "--number", some_num );
/// 	// ...
/// }
/// \endcode
/// so <tt>number</tt>'s value <b>must</b> be double type (or compatible), if not - exception will throw.
///
///
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection how_to_define_semantic_check Parameter's value semantic check
///
/// Use <b>check_semantic()</b> function.
///
/// \code
/// int main( int argc, char* argv[] ) {
/// 	clp_parser::command_line_parameter_parser parser;
/// 	parser.add_parameter( "-l", "--log-dir", log_dir )
/// 		  .check_semantic( clp_parser::path );
/// 	// ...
/// }
/// \endcode
/// 
/// In this case, value of <b>'--log-dir'</b> <em>must</em> be valid path in current filesystem.
/// If not, correspond std::exception will be throw.
///
/// Supported value's semantic:
/// \li <b>path</b> (check of path correctness, in current filesystem),
/// \li <b>ipv4</b> (check of IP-address validity, exactly IPv4),
/// \li <b>ipv6</b> (check of IP-address validity, exactly IPv6),
/// \li <b>ip</b> (check of IP-address validity, IPv4 or IPv6).
///
/// \htmlonly <br/> \endhtmlonly
///
/// \subsection combine_of_settings Combine of settings
///
/// You can combine settings for parameter, like this:
///
/// \code 
/// int main( int argc, char* argv[] ) {
/// 	clp_parser::command_line_parameter_parser parser;
/// 	parser.add_parameter( "-l", "--log-dir", log_dir )
/// 		  .default_value( "/some/default/path" )
/// 		  .check_semantic( clp_parser::path )
/// 		  ;
/// 	// ...
/// }
/// \endcode
///
/// <b>Note:</b> You cannot combine <em>contradictory</em> settings. For example, if you 
/// write like this:
///
/// \code 
/// int main( int argc, char* argv[] ) {
/// 	clp_parser::command_line_parameter_parser parser;
/// 	parser.add_parameter( "-l", "--log-dir", log_dir )
/// 		  .default_value( "/some/default/path" )
/// 		  .check_semantic( clp_parser::path )
/// 		  .necessary() // Necessary parameter with defined default value? Hmm...
/// 		  ;
/// 	// ...
/// }
/// \endcode
/// 
/// exception will throw.
///
/// \htmlonly <br/> \endhtmlonly
/// 
/// \subsection another_value_separator Another 'name-value' separator
///
/// You can define another 'name-value' separator, instead default <b>'='</b>.
/// 
/// Use <b>set_value_separator()</b> function.
///
/// \code
/// int main( int argc, char* argv[] ) {
/// 	clp_parser::command_line_parameter_parser parser;
/// 	// ...
/// 	parser.set_value_separator( ':' );
/// }
/// \endcode
///
/// In this case, parameters with value <b>must</b> be input as:
///
/// \code 
/// # ./program --log-dir:/some/path
/// \endcode
///
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_LINE_PARAMETERS_PARSER_HPP
#define COMMAND_LINE_PARAMETERS_PARSER_HPP

#include "detail/checkers.hpp"
#include "detail/parameter.hpp"

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <set>

/// \namespace clp_parser
/// \brief Main namespace of library.
namespace clp_parser {

/// \class command_line_parameter_parser
/// \brief Parser.
///
/// Presents parsing functionality.
class command_line_parameter_parser : boost::noncopyable {
private:
    typedef boost::ptr_vector< cl_param >
            params_storage;
    
    typedef boost::signals2::signal< void ( const std::string& /* value */ ) >
            sig_checker;
    typedef boost::shared_ptr< sig_checker > 
            sig_checker_p;
    typedef boost::unordered_map< value_semantic, sig_checker_p >
            value_semantic_checker;

    /// \enum parameter_part
    /// \brief Parameter's part.
    enum parameter_part { 
    	name 		/*!< Name part. */
    	, value 	/*!< Value part. */
    };
public:
    explicit command_line_parameter_parser() : 
    		m_value_separator( "=" ) {
        // Register checkers of value's semantic.
        m_vs_checker[ path ] = boost::make_shared< sig_checker >();
        m_vs_checker[ path ]->connect( detail::check_path_validity );

        m_vs_checker[ ipv4 ] = boost::make_shared< sig_checker >();
        m_vs_checker[ ipv4 ]->connect( detail::check_ipv4_validity );

        m_vs_checker[ ipv6 ] = boost::make_shared< sig_checker >();
        m_vs_checker[ ipv6 ]->connect( detail::check_ipv6_validity );

        m_vs_checker[ ip ] = boost::make_shared< sig_checker >();
        m_vs_checker[ ip ]->connect( detail::check_ip_validity );
}
private:
	/// \brief Parameter's storage.
    params_storage 	        m_params;
    
    /// \brief Value separator.
    /// Default value is '=', in Unix-style.
    std::string 	        m_value_separator;

    /// \brief Checker of parameter's semantic.
    value_semantic_checker  m_vs_checker;
public:
	/// \brief Add new command line parameter.
	/// \param short_name Short name of parameter.
	/// \param full_name Full name of parameter.
	/// \param fn Pointer on function (without value).
	/// \return reference on this parameter;
    cl_param& add_parameter( const std::string& short_name
                        	 , const std::string& full_name
                        	 , void (*fn)() ) {
        detail::check_ptr( fn );
        
        if ( short_name == full_name ) {
            std::string error = "Duplicate names of parameter: '"
                                + short_name + "', '"
                                + full_name + "'! Check your code.";
            throw std::invalid_argument( error );
        } else {}
        
        check_uniq_names( short_name, full_name ); // Is it new names?
        m_params.push_back( new cl_param( std::make_pair( short_name, full_name )
        								  , fn ) );
        return m_params.back();
    }
    
    /// \brief Add new command line parameter.
	/// \param short_name Short name of parameter.
	/// \param full_name Full name of parameter.
	/// \param fn Pointer on function (with value).
	/// \return reference on this parameter;
	template< typename Arg >
    cl_param& add_parameter( const std::string& short_name
                        	 , const std::string& full_name
                        	 , void (*fn)( const Arg& ) ) {
        detail::check_ptr( fn );
        
        if ( short_name == full_name ) {
            std::string error = "Duplicate names of parameter: '"
                                + short_name + "', '"
                                + full_name + "'! Check your code.";
            throw std::invalid_argument( error );
        } else {}
        
        check_uniq_names( short_name, full_name ); // Is it new names?
        m_params.push_back( new cl_param( std::make_pair( short_name, full_name )
        								  , fn ) );
        return m_params.back();
    }
    
    /// \brief Add new command line parameter.
    /// Used for POD-type argument (int, double, etc).
	/// \param short_name Short name of parameter.
	/// \param full_name Full name of parameter.
	/// \param fn Pointer on function (with value).
	/// \return reference on this parameter;
	template< typename Arg >
    cl_param& add_parameter( const std::string& short_name
                        	 , const std::string& full_name
                        	 , void (*fn)( Arg ) ) {
        detail::check_ptr( fn );
        
        if ( short_name == full_name ) {
            std::string error = "Duplicate names of parameter: '"
                                + short_name + "', '"
                                + full_name + "'! Check your code.";
            throw std::invalid_argument( error );
        } else {}
        
        check_uniq_names( short_name, full_name ); // Is it new names?
        m_params.push_back( new cl_param( std::make_pair( short_name, full_name )
        								  , fn ) );
        return m_params.back();
    }
    
    /// \brief Add new command line parameter.
	/// \param single_name Single name of parameter.
	/// \param fn Pointer on function (without value).
	/// \return reference on this parameter;
    cl_param& add_parameter( const std::string& single_name
                        	 , void (*fn)() ) {
        detail::check_ptr( fn );
        
        check_uniq_names( single_name ); // Is it new name?
        m_params.push_back( new cl_param( std::make_pair( single_name, "" )
        								  , fn ) );
        return m_params.back();
    }
    
    /// \brief Add new command line parameter.
	/// \param single_name Single name of parameter.
	/// \param fn Pointer on function (with value).
	/// \return reference on this parameter;
	template< typename Arg >
    cl_param& add_parameter( const std::string& single_name
                        	 , void (*fn)( const Arg& ) ) {
        detail::check_ptr( fn );
        
        check_uniq_names( single_name ); // Is it new name?
        m_params.push_back( new cl_param( std::make_pair( single_name, "" )
        								  , fn ) );
        return m_params.back();
    }
    
    /// \brief Add new command line parameter.
    /// Used for POD-type argument (int, double, etc).
	/// \param single_name Single name of parameter.
	/// \param fn Pointer on function (with value).
	/// \return reference on this parameter;
	template< typename Arg >
    cl_param& add_parameter( const std::string& single_name
                        	 , void (*fn)( Arg ) ) {
        detail::check_ptr( fn );
        
        check_uniq_names( single_name ); // Is it new name?
        m_params.push_back( new cl_param( std::make_pair( single_name, "" )
        								  , fn ) );
        return m_params.back();
    }
    
    /// \brief Add new command line parameter.
	/// \param short_name Short name of parameter.
	/// \param full_name Full name of parameter.
	/// \param obj Pointer to object.
	/// \param fn Pointer on object's function (without value).
	/// \return reference on this parameter;
    template
    	< 
    		typename Object
    		, typename Arg
    	> 
	cl_param& add_parameter( const std::string& short_name, 
                        	 const std::string& full_name, 
                        	 Object* 			obj,
                        	 void (Object::*fn)() ) {
        detail::check_ptr( obj, fn );
        
        if ( short_name == full_name ) {
            std::string error = "Duplicate names of parameter: '"
                                + short_name + "', '"
                                + full_name + "'! Check your code.";
            throw std::invalid_argument( error );
        } else {}
        
        check_uniq_names( short_name, full_name ); // Is it new names?
        m_params.push_back( new cl_param( std::make_pair( short_name, full_name )
        								  , obj
        								  , fn ) );
        return m_params.back();
    }
    
    /// \brief Add new command line parameter.
	/// \param short_name Short name of parameter.
	/// \param full_name Full name of parameter.
	/// \param obj Pointer to object.
	/// \param fn Pointer on object's function (with value).
	/// \return reference on this parameter;
    template
    	< 
    		typename Object
    		, typename Arg
    	> 
	cl_param& add_parameter( const std::string& short_name, 
                        	 const std::string& full_name, 
                        	 Object* 			obj,
                        	 void (Object::*fn)( const Arg& ) ) {  
        detail::check_ptr( obj, fn );
        
        if ( short_name == full_name ) {
            std::string error = "Duplicate names of parameter: '"
                                + short_name + "', '"
                                + full_name + "'! Check your code.";
            throw std::invalid_argument( error );
        } else {}
        
        check_uniq_names( short_name, full_name ); // Is it new names?
        m_params.push_back( new cl_param( std::make_pair( short_name, full_name )
        								  , obj
        								  , fn ) );
        return m_params.back();
    }
     
    /// \brief Add new command line parameter.
    /// Used for POD-type argument (int, double, etc).
	/// \param short_name Short name of parameter.
	/// \param full_name Full name of parameter.
	/// \param obj Pointer to object.
	/// \param fn Pointer on object's function (with value).
	/// \return reference on this parameter;
    template
    	< 
    		typename Object
    		, typename Arg
    	> 
	cl_param& add_parameter( const std::string& short_name, 
                        	 const std::string& full_name, 
                        	 Object* 			obj,
                        	 void (Object::*fn)( Arg ) ) {  
        detail::check_ptr( obj, fn );
        
        if ( short_name == full_name ) {
            std::string error = "Duplicate names of parameter: '"
                                + short_name + "', '"
                                + full_name + "'! Check your code.";
            throw std::invalid_argument( error );
        } else {}
        
        check_uniq_names( short_name, full_name ); // Is it new names?
        m_params.push_back( new cl_param( std::make_pair( short_name, full_name )
        								  , obj
        								  , fn ) );
        return m_params.back();
    }
    
    /// \brief Add new command line parameter.
	/// \param single_name Single name of parameter.
	/// \param obj Pointer to object.
	/// \param fn Pointer on object's function (without value).
	/// \return reference on this parameter;
    template< typename Object > 
	cl_param& add_parameter( const std::string& single_name,
                        	 Object* 			obj,
                        	 void (Object::*fn)() ) {  
        detail::check_ptr( obj, fn );
        
        check_uniq_names( single_name ); // Is it new name?
        m_params.push_back( new cl_param( std::make_pair( single_name, "" )
        								  , obj
        								  , fn ) );
        return m_params.back();
    }
    
    /// \brief Add new command line parameter.
	/// \param single_name Single name of parameter.
	/// \param obj Pointer to object.
	/// \param fn Pointer on object's function (with value).
	/// \return reference on this parameter;
    template
    	< 
    		typename Object
    		, typename Arg
    	> 
	cl_param& add_parameter( const std::string& single_name,
                        	 Object* 			obj,
                        	 void (Object::*fn)( const Arg& ) ) {  
        detail::check_ptr( obj, fn );
        
        check_uniq_names( single_name ); // Is it new name?
        m_params.push_back( new cl_param( std::make_pair( single_name, "" )
        								  , obj
        								  , fn ) );
        return m_params.back();
    }
    
    /// \brief Add new command line parameter.
    /// Used for POD-type argument (int, double, etc).
	/// \param single_name Single name of parameter.
	/// \param obj Pointer to object.
	/// \param fn Pointer on object's function (with value).
	/// \return reference on this parameter;
    template
    	< 
    		typename Object
    		, typename Arg
    	> 
	cl_param& add_parameter( const std::string& single_name,
                        	 Object* 			obj,
                        	 void (Object::*fn)( Arg ) ) {  
        detail::check_ptr( obj, fn );
        
        check_uniq_names( single_name ); // Is it new name?
        m_params.push_back( new cl_param( std::make_pair( single_name, "" )
        								  , obj
        								  , fn ) );
        return m_params.back();
    }
public:
 	/// \brief Set another value separator, instead default '='.
 	/// \param sep Separator.
 	/// \throw std::invalid_argument If separator is space symbol.
    void set_value_separator( char sep ) {
    	if ( ' ' == sep ) { 
    		throw std::invalid_argument( "Space symbol cannot be value separator!" );
    	} else {}
        m_value_separator = sep;
    }
private:
	/// \brief Check uniq names.
	/// \param short_name Short name of parameter.
	/// \param full_name Full name of parameter.
	/// \throw std::invalid_argument If short or full name already used.
    void check_uniq_names( const std::string& short_name, const std::string& full_name = "" ) {
        BOOST_FOREACH ( const cl_param& param, m_params ) {
            if ( !full_name.empty() ) {
                if ( corresponds( param, short_name )
                     || corresponds( param, full_name ) ) {
                    std::string error = "Parameter's names '"
                                        + short_name 
                                        + "' and/or '"
                                        + full_name + "' not uniq! Check your code.";
                    throw std::invalid_argument( error );
                } else {}
            } else {
                if ( corresponds( param, short_name ) ) {
                    std::string error = "Parameter's name '"
                                        + short_name + "' not uniq! Check your code.";
                    throw std::invalid_argument( error );
                } else {}
            }
        }
    }
    
    /// \brief Check redundancy of parameters.
    /// \param fact_params_quantity Quantity of inputed parameters.
    /// \throw std::runtime_error If quantity of inputed parameters more than defined.
    void check_params_redundancy( size_t fact_params_quantity ) {
        if ( fact_params_quantity > m_params.size() ) {
            std::string error = "Too much parameters, defined only " 
                                + boost::lexical_cast< std::string >( m_params.size() )
                                + ".";
            throw std::runtime_error( error );
        } else {}
    }
    
    /// \brief Check incorrect parameters.
    /// Incorrect parameters not allowed.
    /// \param fact_params Container of inputed parameters.
    /// \throw std::runtime_error If incorrect parameter(s) exists.
    void check_incorrect_params( const detail::str_storage& fact_params ) {
        BOOST_FOREACH ( const std::string& fact_param, fact_params ) {
            std::string check_fact_param = retrieve( name, fact_param );
            
            BOOST_FOREACH ( const cl_param& param, m_params ) {
                if ( corresponds( param, check_fact_param ) ) {
                    check_fact_param.clear();
                    break;
                } else {}
            }
            
            if ( !check_fact_param.empty() ) {
                std::string error = "Incorrect parameter '" + check_fact_param + "'!";
                std::string maybe = " Check defined parameter(s) or correction of value separator.";
                throw std::runtime_error( error + maybe );
            } else {}
        }
    }
    
    /// \brief Check existence of all parameters which defined as necessary.
    /// \param fact_params Container of inputed parameters.
    /// \throw std::runtime_error If some necessary parameter(s) missing.
    void check_necessary_params( const detail::str_storage& fact_params ) {
    	detail::str_storage names;
    	
    	BOOST_FOREACH ( const cl_param& param, m_params ) {
            if ( param.is_necessary ) {
            	names.push_back( param.name.first );
            } else {}
        }
        
        BOOST_FOREACH ( const std::string& fact_param, fact_params ) {
        	std::string check_fact_param = retrieve( name, fact_param );
            names.erase( std::remove( names.begin() 
            						  , names.end()
            						  , check_fact_param ) 
            			 , names.end() );
        }
        
        if ( !names.empty() ) {
        	std::string error = "Parameter(s): ";
        	BOOST_FOREACH ( const std::string& name, names ) {
        		error += "'" + name + "', ";
        	}
        	boost::erase_last( error, ", " );
        	error += " are defined as necessary, but it missing!";
        	throw std::runtime_error( error );
        } else {}
    }
    
    /// \brief Check repetition of parameter(s).
    /// \param fact_params Container of inputed parameters.
    /// \throw std::runtime_error If some parameter(s) repeating.
    void check_params_repetition( const detail::str_storage& fact_params ) {
        std::set< std::string > uniq_check;
        BOOST_FOREACH ( const std::string& fact_param, fact_params ) {
            std::string check_fact_param = retrieve( name, fact_param );
            BOOST_FOREACH ( const cl_param& param, m_params ) {
                if ( corresponds( param, check_fact_param ) ) {
                    uniq_check.insert( param.name.first );
                    break;
                } else {}
            }
        }
        
        if ( uniq_check.size() != fact_params.size() ) {
            throw std::runtime_error( "Parameter(s) repetition!" );
        } else {}
    }
    
    /// \brief Check correction of parameter's values. 
    /// If parameter defined with value - it value _must_ exists.
    /// If parameter defined without value - no value.
    /// \param fact_params Container of inputed parameters.
    /// \throw std::runtime_error If some parameter(s) incorrect.
    void check_values_correction( const detail::str_storage& fact_params ) {
    	BOOST_FOREACH ( const std::string& fact_param, fact_params ) {
    		std::string param_name = retrieve( name, fact_param );
    		if ( boost::contains( fact_param, m_value_separator ) ) {
    			// Maybe, parameter with value...
    			BOOST_FOREACH ( const cl_param& param, m_params ) {
    				if ( corresponds( param, param_name ) ) {
						// Find!
					    if ( !param.sig.empty() ) {
					    	// Parameter without value, incorrect!
					    	std::string error = "Parameter '" 
					    	                    + param_name 
					    	                    + "' defined without value!";
					    	throw std::runtime_error( error );
					    } else {
					    	// Check factual value existence.
					    	std::string param_value = retrieve( value, fact_param );
					    	if ( param_value.empty() ) {
					    		std::string error = "Parameter '" 
					    		                    + param_name 
					    		                    + "' defined with value, but it missing!";
					    		throw std::runtime_error( error );
					    	} else {}
					    }
					} else {}
    			}
    		} else {
    			// Maybe, parameter without value...
    			BOOST_FOREACH ( const cl_param& param, m_params ) {
    				if ( corresponds( param, param_name ) ) {
						// Find!
					    if ( param.sig.empty() ) {
					    	// Parameter with value, incorrect!
					    	std::string error = "Parameter '" + param_name + "' defined with value!";
					    	throw std::runtime_error( error );
					    } else {}
					} else {}
    			}
    		}
    	}
    }
    
    /// \brief Check parameter's value semantic.
    /// \param fact_params Container of inputed parameters.
    /// \throw std::exception If semantic incorrect.
    void check_values_semantic( const detail::str_storage& fact_params ) {
    	// For parameter's _default_ value semantic checking.
    	detail::str_storage names;
    	
    	BOOST_FOREACH ( const cl_param& param, m_params ) {
    		names.push_back( param.name.first );
    	}
    	
    	BOOST_FOREACH ( const std::string& fact_param, fact_params ) {
    		if ( boost::contains( fact_param, m_value_separator ) ) {
    			std::string param_name = retrieve( name, fact_param );
    			BOOST_FOREACH ( const cl_param& param, m_params ) {
					if ( corresponds( param, param_name )
					     && no_semantic != param.value_s ) {
                        (*m_vs_checker.at( param.value_s ))( retrieve( value, fact_param ) );
                        // Not need anymore...
					    names.erase( std::remove( names.begin()
					    						  , names.end()
					    						  , param.name.first )
					                 , names.end() );
						break; 
					} else {}
				}
    		} else {}
    	}
    	
    	// Check parameter's _default_ value semantic.
    	BOOST_FOREACH ( const cl_param& param, m_params ) {
    		detail::str_storage::iterator it = std::find( names.begin(), 
    		                                              names.end(), 
    		                                              param.name.first );
    		if ( names.end() != it 
    			 && param.has_def_value
    			 && no_semantic != param.value_s ) {
				// Value's semantic checks only for <std::string> values,
				// because numeric values - is just numbers. :-)
				if ( typeid( detail::s_arg_holder_p ) == param.for_arg.type() ) {
					detail::s_arg_holder_p p = boost::any_cast< detail::s_arg_holder_p >( param.for_arg );
					(*m_vs_checker.at( param.value_s ))( p->def_value );
				}
    		} else {}
    	}
    }
    
    /// \brief Retrieve part from parameter.
    /// It can be parameter's name or parameter's value.
    /// \param part_type Part's type.
    /// \param fact_param Parameter.
    /// \return Part.
    std::string retrieve( const parameter_part& part_type
    					  , const std::string& 	fact_param ) const {
    	std::string part( fact_param );
    	if ( boost::contains( part, m_value_separator ) ) { 
            detail::str_storage param_parts;
		    boost::split( param_parts, fact_param, boost::is_any_of( m_value_separator ) );
		    if ( param_parts.size() > 2 ) {
		        std::string error = "Separator repetition in param '" + fact_param + "'!";
		        throw std::runtime_error( error );
		    } else {}
		    if 	    ( part_type == name  ) { part = param_parts.front(); }
		    else if ( part_type == value ) { part = param_parts.back(); }
        } else {}
        return part;
    }
    
    /// \brief Check correspondence of parameter's name and fact name.
    /// \param parameter Parameter.
    /// \param fact_param_name Factual name.
    /// \return true If corresponds.
    bool corresponds( const cl_param& 	 	parameter
    				  , const std::string& 	fact_param_name ) const {
    	return fact_param_name == parameter.name.first
    	       || fact_param_name == parameter.name.second;
    }
public:
	/// \brief Parsing of inputed parameters.
	/// \param argc standard main() arg quantity.
	/// \param argv standard main() arg array.
	/// \throw std::exception If any problems occures.
    void parse( int argc, char** argv ) {
        detail::str_storage fact_params;
        // Begin on 1 element, because 0 is program's name.
        for ( int i = 1; i < argc; ++i ) {
            fact_params.push_back( std::string( argv[i] ) );
        }
        
        // Is any parameters are defined?
        if ( m_params.empty() && !fact_params.empty() ) {
            throw std::runtime_error( "You input some parameters, but no one defined!" );
        } else {}
        
        // Checks.
        check_params_redundancy( fact_params.size() );
        check_incorrect_params( fact_params );
        check_params_repetition( fact_params );
        check_necessary_params( fact_params );
        check_values_correction( fact_params );
        check_values_semantic( fact_params );
        
        // For callbacks for parameters with _default_ values.
    	detail::str_storage names;
    	BOOST_FOREACH ( const cl_param& param, m_params ) {
    		names.push_back( param.name.first );
    	}
        
        // Callbacks.
        BOOST_FOREACH ( const std::string& fact_param, fact_params ) {
            std::string fact_param_name( fact_param );
            std::string fact_param_value;
            if ( boost::contains( fact_param_name, m_value_separator ) ) {
                fact_param_name  = retrieve( name, fact_param );
                fact_param_value = retrieve( value, fact_param );
            } else {}
            BOOST_FOREACH ( cl_param& param, m_params ) {
                if ( corresponds( param, fact_param_name ) ) {
                    if ( !param.sig.empty() ) {
                    	// Parameter without value.
                        param.sig();
                        names.erase( std::remove( names.begin()
                        						  , names.end()
                        						  , param.name.first )
					                 , names.end() );
                        break;
                    } else {
                    	// Parameter with value.                 	
                    	if 		  ( typeid( detail::i_arg_holder_p ) == param.for_arg.type() ) {
							detail::i_arg_holder_p p = boost::any_cast< detail::i_arg_holder_p >( param.for_arg );
							p->sig_with_value( boost::lexical_cast< int >( fact_param_value ) );
						} else if ( typeid( detail::ui_arg_holder_p ) == param.for_arg.type() ) {
							detail::ui_arg_holder_p p = boost::any_cast< detail::ui_arg_holder_p >( param.for_arg );
							p->sig_with_value( boost::lexical_cast< unsigned int >( fact_param_value ) );
						} else if ( typeid( detail::d_arg_holder_p ) == param.for_arg.type() ) {
							detail::d_arg_holder_p p = boost::any_cast< detail::d_arg_holder_p >( param.for_arg );
							p->sig_with_value( boost::lexical_cast< double >( fact_param_value ) );
						} else if ( typeid( detail::s_arg_holder_p ) == param.for_arg.type() ) {
							detail::s_arg_holder_p p = boost::any_cast< detail::s_arg_holder_p >( param.for_arg );
							// Already std::string argument, no need lexical_cast.
							p->sig_with_value( fact_param_value );
						}
                        
                        names.erase( std::remove( names.begin()
                        						  , names.end()
                        						  , param.name.first )
					                 , names.end() );
                        break;
                    }
                } else {}
            }
        }
        
        // Callbacks for parameters with _default_ value.
        BOOST_FOREACH ( cl_param& param, m_params ) {
    		detail::str_storage::iterator it = std::find( names.begin() 
    		                                              , names.end() 
    		                                              , param.name.first );
    		if ( names.end() != it 
    		     && param.sig.empty()
    		     && param.has_def_value ) {
    		    if 		  ( typeid( detail::i_arg_holder_p ) == param.for_arg.type() ) {
					detail::i_arg_holder_p p = boost::any_cast< detail::i_arg_holder_p >( param.for_arg );
					p->sig_with_value( p->def_value );
				} else if ( typeid( detail::ui_arg_holder_p ) == param.for_arg.type() ) {
					detail::ui_arg_holder_p p = boost::any_cast< detail::ui_arg_holder_p >( param.for_arg );
					p->sig_with_value( p->def_value );
				} else if ( typeid( detail::d_arg_holder_p ) == param.for_arg.type() ) {
					detail::d_arg_holder_p p = boost::any_cast< detail::d_arg_holder_p >( param.for_arg );
					p->sig_with_value( p->def_value );
				} else if ( typeid( detail::s_arg_holder_p ) == param.for_arg.type() ) {
					detail::s_arg_holder_p p = boost::any_cast< detail::s_arg_holder_p >( param.for_arg );
					p->sig_with_value( p->def_value );
				}
    		} else {}
    	}
    }
};

} // namespace clp_parser
 
#endif // COMMAND_LINE_PARAMETERS_PARSER_HPP
