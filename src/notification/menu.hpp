#if !defined(BEACH_NOTIFICATION_MENU)
#define      BEACH_NOTIFICATION_MENU
//----------------------------------------------------------
//  Copyright 1992-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       menu.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>
#include <atoms/stringex.hpp>
#include <collection/ref_vector.hpp>
#include <notification/observable_imp.hpp>

namespace invocation
{
    class command;
};

//--------------------------------------

namespace notification
{
    class menu_rep;
    using atoms::stringex;
    using atoms::text;
    using invocation::command;

//--------------------------------------

/// menu of named commands in a tree hierarchy
/**
 *  @note   design patterns applied:
 *              - Composite [GoF]
 *              - Observer  [GoF]
 */
class menu
    : public virtual observable_imp
{
public:
   
    enum observer_flag ///< bitwise values can be combined
    { 
        observe_entry_added = observable::next_observer_flag,   ///< == 0x00000002
        next_observer_flag  = observe_entry_added << 1,         ///< == 0x00000004
    };

    typedef class collection::ref_vector<menu> entries;

    menu(
        const text *    in_name,
        command *       in_command, ///< takes ownership of command
        boolean         in_do_close_on_execute = true );

    virtual ~menu();

    const stringex &    get_name()                  const { return _name; }
    command *           get_command()               const { return _command; }
    boolean             get_do_close_on_execute()   const { return _do_close_on_execute; }
    const entries &     get_entries_const()         const { return _entries; }

    void add_entry( menu & ); ///< takes ownership of entry

private:

    stringex    _name;
    command *   _command;
    boolean     _do_close_on_execute;
    entries     _entries;

}; // end of class stringex

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_MENU
