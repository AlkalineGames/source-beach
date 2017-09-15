//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_trigger.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <invocation/command_trigger.hpp> // this header

#include <invocation/command.hpp>

namespace invocation
{

//--------------------------------------
//  public methods
//--------------------------------------

command_trigger::command_trigger()
  :
    _state( OffState ),
    _soloOffCommand( 0 ),
    _soloOnCommand( 0 ),
    _soloEdgeCommand( 0 ),
    _combinedTriggers()
{}

//--------------------------------------

command_trigger::~command_trigger()
{
    // destroy our associations
    for ( CombinedTriggersType::wrapped_iterator
          i( _combinedTriggers ); i.is_valid(); i.next() )
    {
        delete & i.retrieve();
    }
}

//--------------------------------------

void command_trigger::combine(
    command_trigger &   inOtherTrigger, 
    command *           inOffCommand,
    command *           inOnCommand,
    boolean             isBidirectional )
{
    // locate existing combination if already defined
    CombinedTrigger * theCombinedTrigger;
    CombinedTriggersType::wrapped_iterator i( _combinedTriggers );
    for ( ; i.is_valid(); i.next() )
    {
        theCombinedTrigger = &i.retrieve();
        if (    theCombinedTrigger->otherTrigger
             == &inOtherTrigger )
        {
            break;
        }
    }
    if ( ! i.is_valid() ) // create new combination
    {
        theCombinedTrigger = new CombinedTrigger;
        _combinedTriggers.add( * theCombinedTrigger );
    }
    // initialize the combination
    theCombinedTrigger->otherTrigger = &inOtherTrigger;
    theCombinedTrigger->offCommand   = inOffCommand;  
    theCombinedTrigger->onCommand    = inOnCommand;   

    if ( isBidirectional ) // make combination work both ways
    {
        inOtherTrigger.combine(
            *this, inOffCommand, inOnCommand, false );
    }
}

//--------------------------------------

boolean 
command_trigger::isSolo() const
{
    // solo if no combined other triggers are On
    for ( CombinedTriggersType::wrapped_iterator
          i( const_cast<command_trigger*>(this)->_combinedTriggers );
          i.is_valid(); i.next() )
    {
        if ( i.retrieve().otherTrigger->state() == OnState )
        {
            return false;
        }
    }
    return true;
}

//--------------------------------------

void
command_trigger::signal(
    StateType inState )
{
    // Edge is always a solo command
    if ( inState == EdgeState )
    {
        if ( _soloEdgeCommand != 0 )
        {
            _soloEdgeCommand->execute();
        }
        _state = inState;
        return;
    }
    if (   (inState != OnState)
        && (inState != OffState) )
    {
        return;
    }
    // On or Off: check for combinations
    boolean isCombination = false;
    for ( CombinedTriggersType::wrapped_iterator
          i( _combinedTriggers ); i.is_valid(); i.next() )
    {
        CombinedTrigger & theCombinedTrigger = i.retrieve();
        const command_trigger & theOtherTrigger
            = * theCombinedTrigger.otherTrigger;

        if ( theOtherTrigger.state() == OnState )
        {
            if ( inState == OnState )
            {
                if (    theOtherTrigger.isSolo()
                    && (theOtherTrigger._soloOffCommand != 0) )
                {
                    theOtherTrigger._soloOffCommand->execute();
                }
                if ( theCombinedTrigger.onCommand != 0 )
                {
                     theCombinedTrigger.onCommand->execute();
                }
            }
            else // Off
            {
                if ( theCombinedTrigger.offCommand != 0 )
                {
                     theCombinedTrigger.offCommand->execute();
                }
                // update state before checking isSolo
                _state = inState;

                if (    theOtherTrigger.isSolo()
                    && (theOtherTrigger._soloOnCommand != 0) )
                {
                    theOtherTrigger._soloOnCommand->execute();
                }
            }
            isCombination = true;
        }
    }
    if ( ! isCombination ) // solo command
    {
        if (   (inState == OnState)
            && (_soloOnCommand != 0) )
        {
            _soloOnCommand->execute();
        }
        else if (   (inState == OffState)
                 && (_soloOffCommand != 0) )
        {
            _soloOffCommand->execute();
        }
    }
    _state = inState;
}

//--------------------------------------

void
command_trigger::toggle() // reverses state: Off-->On, On-->Off, Edge-->Edge
{
    switch ( state() )
    {
        case OffState  : signalOn();   break;
        case OnState   : signalOff();  break;
        case EdgeState : signalEdge(); break;
    }
}

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
// (end of file)
