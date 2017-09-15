#if !defined(BEACH_INVOCATION_COMMAND_TRIGGER)
#define      BEACH_INVOCATION_COMMAND_TRIGGER
//----------------------------------------------------------
//  Copyright 1997-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       command_trigger.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/allocation.hpp>
#include <collection/ref_vector.hpp>

namespace invocation
{
    using atoms::boolean;
    class command;

//--------------------------------------

/// mechanism to execute commands from one or more triggered states
/**
 *  @note   design patterns applied:
 *              - Command   [GoF]
 *              - Prototype [GoF]
 */
class command_trigger
{
public:

    enum StateType { OffState, OnState, EdgeState, StateCount };
    struct CombinedTrigger
    {
        const command_trigger * otherTrigger;
        command *               offCommand;
        command *               onCommand;
    };
    typedef collection::ref_vector<CombinedTrigger>
        CombinedTriggersType;

    BEACH_ALLOCATION_OPERATORS

    command_trigger();
    ~command_trigger();

    void soloCommands( command * inOffCommand,
                       command * inOnCommand,
                       command * inEdgeCommand )
    {
        _soloOffCommand     = inOffCommand;
        _soloOnCommand      = inOnCommand;
        _soloEdgeCommand    = inEdgeCommand;
    }
    CombinedTriggersType::wrapped_iterator_const combinedTriggers() const
    {   return _combinedTriggers; }
    
    void combine( command_trigger &, 
                  command * inOffCommand,
                  command * inOnCommand,
                  boolean   isBidirectional = true );

    StateType state()  const { return _state; }
    boolean   isSolo() const;
        ///< solo if no combined other triggers are On

    /// @name actions
    //@{
    void signalOff()    { signal( OffState  ); } ///< (handles combinations)
    void signalOn()     { signal( OnState   ); } ///< (handles combinations)
    void signalEdge()   { signal( EdgeState ); } ///< (ignores combinations)
    void signal( StateType );
    void toggle(); ///< reverses state: Off-->On, On-->Off, Edge-->Edge
    //@}
    
private:

    /// @name copy operations not implemented
    //@{
    command_trigger(              const command_trigger & );
    command_trigger & operator =( const command_trigger & );
    //@}
    
    StateType               _state;
    command *               _soloOffCommand;
    command *               _soloOnCommand;
    command *               _soloEdgeCommand;
    CombinedTriggersType    _combinedTriggers;

}; // class command_trigger

//--------------------------------------

}; // end of namespace invocation

//----------------------------------------------------------
#endif // BEACH_INVOCATION_COMMAND_TRIGGER
