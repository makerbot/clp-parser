// Command line parameters parser.
// File: parameter.hpp
//
// Copyright (C) Denis Shevchenko, 2010.
// shev.denis@gmail.com
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

#ifndef DETAIL__PARAMETER_HPP
#define DETAIL__PARAMETER_HPP

#include <boost/algorithm/string.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/any.hpp>

#include <string>
#include <vector>

/// \namespace clp_parser
/// \brief Main namespace of library.
namespace clp_parser {

/// \enum value_semantic 
/// \brief Value semantic types (for checking).
enum value_semantic {
	no_semantic			/*!< Default value. */
	, path				/*!< Path semantic checking. */
	, ipv4				/*!< IPv4 semantic checking. */
    , ipv6              /*!< IPv6 semantic checking. */
    , ip                /*!< IP semantic checking. */
};

/// \namespace clp_parser::detail
/// \brief Details of realization.
namespace detail {

typedef std::vector< std::string > 
		str_storage;

/// \struct arg_holder
/// \brief Hold objects needed for parameters with value.
template< typename Arg >
struct arg_holder {
	typedef boost::signals2::signal< void ( const Arg& /* value */ ) >
            sig_with_value_type;
public:
	/// \brief Overloaded ctor for register global function with argument.
	/// \param fn Pointer on function.
	explicit arg_holder( void (*fn)( const Arg& ) ) {
		sig_with_value.connect( fn );
	}
	
	/// \brief Overloaded ctor for register member-function with argument.
	/// \param obj Pointer on object.
	/// \param fn Pointer on member-function.
	template< typename Object >
	explicit arg_holder( Object* obj
						 , void (Object::*fn)( const Arg& ) ) {
		sig_with_value.connect( boost::bind( fn, obj, _1 ) );
	}
	
	/// \brief Signal for callback correspond function.
	/// Must be used for parameters with value.
    sig_with_value_type sig_with_value;
    
    /// \brief Default parameter's value.
    Arg 				def_value;
};

typedef boost::shared_ptr< arg_holder< int > > 				i_arg_holder_p;
typedef boost::shared_ptr< arg_holder< unsigned int > > 	ui_arg_holder_p;
typedef boost::shared_ptr< arg_holder< double > > 			d_arg_holder_p;
typedef boost::shared_ptr< arg_holder< std::string > > 		s_arg_holder_p;

/// \struct parameter
/// \brief Command line parameter.
///
/// Presents one command line parameter
/// with necessary options.
struct parameter : boost::noncopyable {
    typedef boost::signals2::signal< void () >
    		sig_type;
    typedef std::pair
    			< 
    				std::string /* short_name */
    				, std::string /* full_name */ 
    			>
            parameter_name;
public:
	/// \brief Overloaded ctor, for callable functions without values.
	/// \param nm Parameter's name.
	/// \param fn Pointer on function.
    explicit parameter( const parameter_name& nm 
      					, void (*fn)() ) :
            name( nm )
            , is_necessary( false )
            , has_def_value( false )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
        sig.connect( fn );
    }
    
   	/// \brief Overloaded ctor, for callable functions with values.
   	/// \param nm Parameter's name.
   	/// \param fn Pointer on function.
    template< typename Arg >
    explicit parameter( const parameter_name& nm
      					, void (*fn)( const Arg& ) ) :
            name( nm )
            , for_arg( boost::make_shared< arg_holder<Arg> >( fn ) )
            , is_necessary( false )
            , has_def_value( false )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
    }
    
    /// \brief Overloaded ctor, for callable object's function without values.
   	/// \param nm Parameter's name.
   	/// \param obj Pointer on object.
   	/// \param fn Pointer on object's function.
    template< typename T >
    explicit parameter( const parameter_name& nm 
      					, T* 				  obj
      					, void (T::*fn)() ) :
            name( nm )
            , is_necessary( false )
            , has_def_value( false )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
        sig.connect( boost::bind( fn, obj ) );
    }
    
    /// \brief Overloaded ctor, for callable object's function with values.
   	/// \param nm Parameter's name.
   	/// \param obj Pointer on object.
   	/// \param fn Pointer on object's function.
    template
    	< 
    		typename T
    		, typename Arg 
    	>
    explicit parameter( const parameter_name& nm 
      					, T* 				  obj
      					, void (T::*fn)( const Arg& ) ) :
            name( nm )
            , for_arg( boost::make_shared< arg_holder<Arg> >( obj, fn ) )
            , is_necessary( false )
            , has_def_value( false )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
    }
public:
	/// \brief Parameter's name.
	parameter_name  name;
	
	/// \brief Necessity flag.
	/// If it true, this parameter _must_
	/// be in command line.
	bool 			is_necessary;
	
	/// \brief Default value flag.
	/// If it true, this parameter can be missing.
	bool 			has_def_value;
	
	/// \brief arg_holder for parameters with value;
	boost::any		for_arg;

	/// \brief Signal for callback correspond function.
	/// Must be used for parameters without value.
    sig_type		sig;
    
	/// \brief Value's semantis label.
	value_semantic 	value_s;
public:
	/// \brief Define parameter with semantic's checked value.
	/// \param vs Value's semantic field.
	/// \return *this
	parameter& check_semantic( const value_semantic& vs ) {
		value_s = vs;
		return *this;
	}
	
	/// \brief Define parameter as necessary.
	/// \return *this
	parameter& necessary() {
		if ( has_def_value ) {
			std::string error = "Option '" + name.first 
			                    + "' already have default value, it cannot be necessary!"; 
			throw std::logic_error( error );
		} else {}
		is_necessary = true;
		return *this;
	}
	
	/// \brief Define parameter's default value.
	/// \param value Default value.
	/// \return *this
	parameter& default_value( const boost::any& value ) {
		if ( is_necessary ) {
			std::string error = "Option '" + name.first 
			                    + "' already define in necessary mode, it cannot have default value!"; 
			throw std::logic_error( error );
		} else {}
		
		has_def_value = true;
		
		if ( value.type() == typeid( std::string ) ) {
			if ( boost::contains( boost::any_cast< std::string >( value ), " " ) ) {
        		std::string error = "Invalid default parameter's value '" 
        							+ name.first 
        							+ "': it shouldn't contains space(s)!";
        		throw std::invalid_argument( error );
			}
        } else {}
		
		if 		  ( typeid( i_arg_holder_p ) == for_arg.type() ) {
			i_arg_holder_p p = boost::any_cast< i_arg_holder_p >( for_arg );
			// Type checking...
			if ( typeid( p->def_value ) == value.type() ) {
				p->def_value = boost::any_cast< int >( value );
			} else {
				std::string error = "Default value's type for parameter '" 
									+ name.first 
									+ "' must be <int>";
				throw std::invalid_argument( error );
			}
		} else if ( typeid( ui_arg_holder_p ) == for_arg.type() ) {
			ui_arg_holder_p p = boost::any_cast< ui_arg_holder_p >( for_arg );
			// Type checking...
			if ( typeid( p->def_value ) == value.type() ) {
				p->def_value = boost::any_cast< unsigned int >( value );
			} else {
				std::string error = "Default value's type for parameter '" 
									+ name.first 
									+ "' must be <unsigned int>";
				throw std::invalid_argument( error );
			}
		} else if ( typeid( d_arg_holder_p ) == for_arg.type() ) {
			d_arg_holder_p p = boost::any_cast< d_arg_holder_p >( for_arg );
			// Type checking. Note that value with type 'double'
			// can be initialized by integer value;
			if ( typeid( p->def_value ) == value.type() ) {
				p->def_value = boost::any_cast< double >( value );
			} else if ( typeid( int ) == value.type() ) {
				p->def_value = boost::any_cast< int >( value );
			} else if ( typeid( unsigned int ) == value.type() ) {
				p->def_value = boost::any_cast< unsigned int >( value );
			} else if ( typeid( float ) == value.type() ) {
				p->def_value = boost::any_cast< float >( value );
			} else {
				std::string error = "Default value's type for parameter '" 
									+ name.first 
									+ "' must be <double>";
				throw std::invalid_argument( error );
			}
		} else if ( typeid( s_arg_holder_p ) == for_arg.type() ) {
			s_arg_holder_p p = boost::any_cast< s_arg_holder_p >( for_arg );
			// Type checking...
			if ( typeid( p->def_value ) == value.type() ) {
				p->def_value = boost::any_cast< std::string >( value );
			} else {
				std::string error = "Default value's type for parameter '" 
									+ name.first 
									+ "' must be <std::string>";
				throw std::invalid_argument( error );
			}
		}

		return *this;
	}
};

} // namespace detail

typedef detail::parameter cl_param;

} // namespace clp_parser

#endif // DETAIL__PARAMETER_HPP
