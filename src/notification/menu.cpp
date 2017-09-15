//----------------------------------------------------------
//  Copyright 1992-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       menu.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/menu.hpp> // this header

#include <invocation/command.hpp>

//--------------------------------------

namespace notification
{

//--------------------------------------
//  public methods
//--------------------------------------

menu::menu(
    const text *            in_name,
    command *               in_command,
    boolean                 in_do_close_on_execute )
  :
    _name(                  in_name ),
    _command(               in_command ),
    _do_close_on_execute(   in_do_close_on_execute ),
    _entries(               atoms::destroyer<menu>() )
{}

//--------------------------------------

// virtual
menu::~menu()
{
    delete _command;
}

//--------------------------------------

void
menu::add_entry(
    menu & in_entry )
{
    _entries.push_back( in_entry );
    notify_observers( observe_entry_added, &in_entry );
}

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
// $Log: menu.cpp,v $
// Revision 1.5  2007/10/30 16:02:18  cat
// ref_vector<> refactored to contain references instead of pointers
//
// Revision 1.4  2006/05/31 00:33:49  cat
// added do_close_on_execute
//
// Revision 1.3  2006/02/06 17:46:13  cat
// refactored from ui framework into a presentation independent abstraction
//
// Revision 1.2  2004/01/06 20:41:23  cat
// renamed and moved all command classes from SandDune notification to invocation
//
// Revision 1.1.1.1  2002/07/14 20:21:31  cat
// first import
//----------------------------------------------------------

// (end of file)
