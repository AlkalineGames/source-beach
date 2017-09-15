#if !defined(BEACH_SERIALIZATION_SERIALIZABLE)
#define      BEACH_SERIALIZATION_SERIALIZABLE

//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/context.hpp>
#include <atoms/primitives.hpp>
#include <serialization/selector.hpp>

//--------------------------------------

/// Beach Serialization Framework
/**
 *	A framework that provides mechanisms for externalizing
 *  an object's state. Several classes in the framework are
 *  based on an enhanced variation of the Serializer design
 *  pattern documented in the book Pattern Languages of
 *  Program Design, Volume III [PLoP3].
 */
namespace serialization
{
    class reader;
    class serializable_source;
    class serializable_spec;
    class writer;
    using atoms::boolean;
    using chain::context;
    using atoms::whole;

//--------------------------------------

/// interface for serializable objects
/**
 *  This class is implemented as an abstract superclass
 *  rather than a pure interface so that subclasses do not
 *  have to override every operation. Subclass methods
 *  should not call any of these methods as they will do
 *  nothing or return null results. 
 *
 *  Use of selectors is the most significant variation to
 *  the original Serializer design pattern.
 *
 *  @note   design patterns applied:
 *              - Serializer [PLoP3]
 */ 
class serializable
{
public:

    /// @note Each subclass should declare its own copy of this enum
    enum selector_index
    {
        selector_all,       ///< combination of all selectors
        selector_identity,  ///< combination of all identiny selectors

        //  ------------------------------------------------------------
        //  Subclasses should insert their own attribute selectors here:
        //  ------------------------------------------------------------
        //  selector_...,

        selector_count
    };

    //@}

    /// @name selector operations
    virtual const selector & get_selector_all(); ///< polymorphic (all for the instance)

//  ------------------------------------------------------------------
//  Each subclass should declare the following members and operations:
//  ------------------------------------------------------------------
//
//  static selector __selectors[selector_count];
//
//  static const selector & get_selector( whole in_index )
//  {
//      if ( in_index < selector_count )    { return __selectors[in_index];     }
//      else                                { return __selectors[selector_all]; }
//  }
//  static void register_selectors();
    //@}

    virtual void populate_spec( serializable_spec & ) const; ///< this level does nothing
    
    /// @name old Serializer operations, this level delegates to new
    //@{
    virtual boolean read_from( reader & ); ///< this method returns true
    virtual void    write_to(  writer &, const selector * = 0 );
    //@}

    /// @name new Serializer operations, this level delegates to old
    //@{
    virtual boolean read_from( context &, reader & ); ///< this method returns true
    virtual void    write_to(  context &, writer &, const selector * = 0 );
    //@}

    serializable_source *   get_serializable_source()   { return _source; }
    void                    set_serializable_source(
        serializable_source * in_source )               { _source = in_source; }

protected:

    serializable();
    virtual ~serializable();

private:

    serializable_source * _source;
     
}; // end of class serializable

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
// $Log: serializable.hpp,v $
// Revision 1.7  2009/05/12 22:02:27  cat
// read_from/write_to(...) old methods delegate to new methods and vice-versa
//
// Revision 1.6  2009/05/11 16:02:21  cat
// [encapsulated] context supported with overloaded methods
//
// Revision 1.5  2005/08/30 04:41:22  cat
// renamed sanddune to beach
//
// Revision 1.4  2005/06/22 14:56:33  cat
// added popultate_spec(...)
//
// Revision 1.3  2004/07/10 21:28:30  cat
// renamed Serializable to serializable; added serializable_source association
//
// Revision 1.2  2003/07/27 10:11:58  def
// removed old deprecated tag serialization methods
//
// Revision 1.1.1.1  2002/07/14 20:16:50  cat
// first import
//----------------------------------------------------------

#endif // BEACH_SERIALIZATION_SERIALIZABLE
