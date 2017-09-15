//----------------------------------------------------------
//  Copyright 2010-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       ref_iterator_counted_imp.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/ref_iterator_counted_imp.hpp>

namespace lifecycle
{

//--------------------------------------
//  public methods
//--------------------------------------

template <class T, class C, class I>
ref_iterator_counted_imp<T,C,I>::ref_iterator_counted_imp(
    collection & in_collection )
  :
    _collection(            in_collection ),
    _collection_iterator(   in_collection.begin() )
{}

//--------------------------------------

template <class T, class C, class I>
// virtual
ref_iterator_counted_imp<T,C,I>::~ref_iterator_counted_imp()
{}

//--------------------------------------

template <class T, class C, class I>
// virtual
void
ref_iterator_counted_imp<T,C,I>::first()
{
    _collection_iterator = _collection.begin();
}

//--------------------------------------

template <class T, class C, class I>
// virtual
void
ref_iterator_counted_imp<T,C,I>::next()
{
    _collection_iterator++;
}

//--------------------------------------

template <class T, class C, class I>
// virtual
boolean
ref_iterator_counted_imp<T,C,I>::is_valid() const
{
    _collection_iterator != _collection.end();
}

//--------------------------------------

template <class T, class C, class I>
// virtual
T &
ref_iterator_counted_imp<T,C,I>::retrieve() const
{
#if 0
    static const text this_method_name[]
        = "id_iterator_imp::retrieve()";

    if ( _map_iterator == _collection_imp._id_map.end() )
    {
        logger::acquire_default_instance().log_error(
            this_class_name, this_method_name,
            text_error_invalid_iterator );
        // !!! RETURN IS BOGUS BUT WE HAVE TO RETURN SOMETHING
        return *static_cast<ptr>(0);
    }
#endif
    return *_collection_iterator;
}

//--------------------------------------

template <class T, class C, class I>
// virtual
size_type
ref_iterator_counted_imp<T,C,I>::get_index() const ///< may be meaningless
{
#if 0
    static const text this_method_name[]
        = "id_iterator_imp::get_index()";

    logger::acquire_default_instance().log_error(
        this_class_name, this_method_name,
        text_error_not_supported );
#endif
    return 0;
}

//--------------------------------------

template <class T, class C, class I>
// virtual
void
ref_iterator_counted_imp<T,C,I>::insert(
    ref in_ref )
{
    // !!! we could use the iterator as a hint, but we won't bother
    _collection.add( in_ref );
}

//--------------------------------------

template <class T, class C, class I>
// virtual
void
ref_iterator_counted_imp<T,C,I>::remove() ///< no-op if ! is_valid()
{
    if ( ! is_valid() )
    {
        return;
    }
    _collection_iterator = _collection.erase( _collection_iterator );
#if 0
    persistent_object * object = _map_iterator->second;
//  @@@ current C++ Standard library map::erase(...)
//  @@@ is not returning the next iterator, in line with c++0x
//    _map_iterator = _collection_imp._id_map.erase( _map_iterator );
//  @@@ SO I HOPE THIS WORKS   
    id_map::iterator itererase( _map_iterator );
    _map_iterator++;
    _collection_imp._id_map.erase( itererase );
    _collection_imp.erase_from_name_map( *object );
    _collection_imp.erase_from_priority_map( *object );
#endif
}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// (end of file)
