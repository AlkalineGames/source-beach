#if !defined(BEACH_LIFECYCLE_COUNTED_REF)
#define      BEACH_LIFECYCLE_COUNTED_REF

//----------------------------------------------------------
//  Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       counted_ref.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

namespace lifecycle
{
        
//--------------------------------------

// reference-like "handle" template to a reference counted object
/**
 *  A template for the "handle" participant of a
 *  a mechanism that implements the Counted Pointer
 *  design pattern idiom for C++.
 *
 *  This object has the semantics of a reference;
 *  clients can safely assume that the reference
 *  is never null.
 *
 *  Actual code is based on Scott Meyers book:
 *  More Effective C++, Item 29: Reference Counting.
 *
 *  @note   design patterns applied:
 *              - Counted Pointer [POSA1]
 */
template <class T> // T must be a subclass of counted_object
class counted_ref
{
public:

    typedef T object;

    counted_ref( object & obj )
      :
        _object( &obj )
    {
        add_reference_count();
    }
    counted_ref( const counted_ref & rhs )
      :
        _object( rhs._object )
    {
        add_reference_count();
    }
    ~counted_ref()
    {
        remove_reference_count();
    }
    bool operator ==( const counted_ref & rhs ) const
    {
        return _object == rhs._object;
    }
    bool operator !=( const counted_ref & rhs ) const
    {
        return _object != rhs._object;
    }
    counted_ref & operator =(
        const counted_ref & rhs )
    {
        if ( &rhs != this )
        {
            if ( _object != rhs._object )
            {
                remove_reference_count();
                _object = rhs._object;
                add_reference_count();
            }                    
        }                
        return *this;
    }
    counted_ref & operator =(
        object & in_object )
    {
        if ( _object != &in_object )
        {
            remove_reference_count();
            _object = &in_object;
            add_reference_count();
        }                
        return *this;
    }
    void assign_without_deref(  ///< !!! only to be used in special cases
        object & in_object )
    {
        if ( _object != &in_object )
        {
            // remove_reference_count(); !!! no dereference
            _object = &in_object;
            add_reference_count();
        }                
    }
    void assign_without_ref(  ///< !!! only to be used in special cases
        object & in_object )
    {
        if ( _object != &in_object )
        {
            // remove_reference_count(); !!! no dereference
            _object = &in_object;
            // add_reference_count(); !!! no reference
        }                
    }

          object * ptr()            const { return  _object; }
    const object * ptr_const()      const { return  _object; }
          object & ref()            const { return *_object; }
    const object & ref_const()      const { return *_object; }
          object * operator ->()    const { return  _object; }
          object & operator  *()    const { return *_object; }
    operator object *()             const { return  _object; }
    operator object &()             const { return *_object; }
    
private:

    void add_reference_count()
    {
        _object->add_reference();
    }
    void remove_reference_count()
    {
        object::remove_reference_to_object(
        //  static_cast<counted_object&>(*_object) );
            *_object );
    }

    object * _object;

}; // end of template class counted_ref

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_COUNTED_REF
