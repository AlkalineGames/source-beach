#if !defined(BEACH_SERIALIZATION_SERIALIZABLE_CHANGE)
#define      BEACH_SERIALIZATION_SERIALIZABLE_CHANGE
//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       serializable_change.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/enumerations.hpp>
#include <atoms/primitives.hpp>
#include <chain/extension.hpp>
#include <serialization/selector.hpp>
#include <lifecycle/object_identifier.hpp>

namespace serialization
{

//--------------------------------------

/// a record of change in a serializable object's state

class serializable_change
{
public:

    typedef atoms::change_basis                 basis;
    typedef atoms::whole16                      selector_index;
    typedef atoms::whole64                      time_mark;
    typedef chain::extension::class_identity    extension_id;
    typedef lifecycle::object_identifier        object_id;

    BEACH_ALLOCATION_OPERATORS

    serializable_change(
        time_mark           in_time_mark,
        basis               in_basis,
        extension_id        in_extension_id,
        selector_index      in_selector_index,
        object_id           in_object_id )
      :
        _time_mark(         in_time_mark ),
        _basis(             in_basis ),
        _extension_id(      in_extension_id ),
        _selector_index(    in_selector_index ),
        _object_id(         in_object_id )
    {}

    serializable_change( atoms::no_init_type )
    {}

    time_mark       get_time_mark()         const { return _time_mark;      }
    basis           get_basis()             const { return _basis;          }
    extension_id    get_extension_id()      const { return _extension_id;   }
    selector_index  get_selector_index()    const { return _selector_index; }
    object_id       get_object_id()         const { return _object_id; }

private:

    time_mark       _time_mark;
    basis           _basis;
    extension_id    _extension_id;
    selector_index  _selector_index;
    object_id       _object_id;

}; // end of class serializable_change

//--------------------------------------

}; // end of namespace serialization

//----------------------------------------------------------
#endif // BEACH_SERIALIZATION_SERIALIZABLE_CHANGE
