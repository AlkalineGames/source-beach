#if !defined(BEACH_LIFECYCLE_CLASS_INFO)
#define      BEACH_LIFECYCLE_CLASS_INFO
//----------------------------------------------------------
//  Copyright 2004-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       class_info.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <chain/extension_typed.hpp>
#include <lifecycle/class_identifier.hpp>
#include <lifecycle/object_identifier.hpp>

namespace lifecycle
{
    class class_info;
    using atoms::stringex;
    using atoms::text;

//--------------------------------------

/// abstract superclass for a class_info extension
/**
 *  @note   design patterns applied:
 *              - Extension Object [PLoP3]
 */
class class_info_extension
    : public chain::extension_typed<class_info>
{
public:

    class_info_extension( class_identifier, class_info & in_owner );
    virtual void update_owner_changed() = 0;
};
        
//--------------------------------------

/// dynamic information for static classes
/**
 *  @note   design patterns applied:
 *              - Extension Object  [PLoP3]
 *              - Taxonomy        [POSA1]
 */
class class_info
{
public:

    class_info(
        class_identifier    in_class_id,
        const text *        in_class_name,
        object_identifier   in_last_object_id,
        class_identifier *  inout_static_class_id );

    ~class_info();

    BEACH_ALLOCATION_OPERATORS

    class_identifier    get_class_id()          const { return _class_id; }
    const stringex &    get_class_name()        const { return _class_name; }
    object_identifier   get_last_object_id()    const { return _last_object_id; }
    class_identifier *  get_static_class_id()   const { return _static_class_id; }

    void                set_class_id(           class_identifier    );
    void                set_class_name(         const text *        );
    void                set_last_object_id(     object_identifier   );
    void                set_static_class_id(    class_identifier *  );
    object_identifier   acquire_next_object_id();

    /// @name extension object (degenerate)
    //@{
    const class_info_extension * get_extension_const() const    { return _extension; }
          class_info_extension * get_extension()                { return _extension; }

    void set_extension( class_info_extension * ); ///< destroys existing extension
    //@}

protected: 

    class_identifier        _class_id;
    stringex                _class_name;
    object_identifier       _last_object_id;
    class_identifier *      _static_class_id;
    class_info_extension *  _extension;

private:

    /// @name copy constructor not implemented
    //@{
    class_info( const class_info & );
    //@}

}; // end of class class_info

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_CLASS_INFO
