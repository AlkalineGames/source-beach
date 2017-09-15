#if !defined(BEACH_LIFECYCLE_POLYMORPHIC_POLYMORPHIC_COUNTED_HANDLE)
#define      BEACH_LIFECYCLE_POLYMORPHIC_POLYMORPHIC_COUNTED_HANDLE

//----------------------------------------------------------
// Copyright 1997-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       polymorphic_counted_handle.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

namespace lifecycle
{

//--------------------------------------

/**
 *  Define a mechanism that implements the
 *  Counted Body pattern / Counted Pointer idiom for C++.
 *
 *  Actual code is based on Scott Meyers book:
 *  More Effective C++, Item 29: Reference Counting.
 *
 *  @note       design patterns applied:
 *                  - Counted Body    [PLOP4]
 *                  - Counted Pointer [POSA1]
 */      
template <class B, class T> ///< T must be a subclass of counted_body
class polymorphic_counted_handle
    : public counted_handle<B>
{
public:

    typedef counted_handle<B> base_handle;
    typedef B                 base_body;
    typedef T                 body;

    polymorphic_handle( base_handle & bh )
      : _body = dynamic_cast<body*>(&(*bh))
    {}

    polymorphic_handle(              const polymorphic_handle & );
    polymorphic_handle & operator =( const polymorphic_handle & );
    ~polymorphic_handle();

    body * operator ->() const;
    body & operator  *() const;
    
private:

    void init();

    body * _body;

}; // end of template class polymorphic_counted_handle

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// $Log: polymorphic_counted_handle.hpp,v $
// Revision 1.2  2005/08/30 05:11:03  cat
// renamed sanddune to beach
//
// Revision 1.1.1.1  2002/07/14 20:16:52  cat
// first import
//----------------------------------------------------------

#endif // BEACH_LIFECYCLE_POLYMORPHIC_COUNTED_HANDLE
