#if !defined(BEACH_NOTIFICATION_OBSERVABLE_LIST)
#define      BEACH_NOTIFICATION_OBSERVABLE_LIST
//----------------------------------------------------------
//  Copyright 2006-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observable_list.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/enumerations.hpp>
#include <collection/ref_vector.hpp>
#include <notification/observable_imp.hpp>

namespace notification
{
    using atoms::ownership;

//--------------------------------------

/// class template adapter for lists that notify observers
/**
 *  @note   design patterns applied:
 *              - Adapter  [GoF]
 *              - Observer [GoF] [PLoP2] [cat]
 */     
template <class T>
class observable_list
    : public virtual observable_imp
{
public:

    typedef T element;
    typedef collection::ref_vector<T> list; ///< vector for indexing

    enum observer_flag /// bitwise lists can be combined
    { 
        observe_element_added       = observable::next_observer_flag,
        observe_element_changed     = observe_element_added     << 1,
        observe_element_removing    = observe_element_changed   << 1,
        next_observer_flag          = observe_element_removing  << 1
    };
    observable_list();              ///< leaves ownership
    observable_list( ownership );   ///< takes ownership, regardless of passed value
    virtual ~observable_list();

    const list & get_list_const() const { return _list; }

    /// @name mutators; notify observers
    //@{
    void add(       element & );
    void change(    element &, const element & in_new_value ); ///< assigns
    void remove(    element & );
    //@}

protected:

    list _list;

private:

    /// @name copy operations not supported
    //@{
    observable_list(              const observable_list & );
    observable_list & operator =( const observable_list & );
    //@}

}; // end of template class observable_list

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_OBSERVABLE_LIST
