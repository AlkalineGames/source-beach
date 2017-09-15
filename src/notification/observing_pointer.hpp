#if !defined(BEACH_NOTIFICATION_OBSERVING_POINTER)
#define      BEACH_NOTIFICATION_OBSERVING_POINTER
//----------------------------------------------------------
//  Copyright 2009-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       observing_pointer.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <notification/observable.hpp>
#include <notification/observer.hpp>

namespace notification
{

//--------------------------------------

/// auto-zeroing pointer observing a subject
/**
 *  This encapsulates a pointer to any observable subject
 *  so that the pointer gets zeroed when the subject gets destroyed.
 *
 *  @note   design patterns applied:
 *              - Observer [GoF], [PLoP2], [WF]
 */     
class observing_pointer
    : public observer
{
public:

    observing_pointer( const observable * = 0 );
    observing_pointer( const observing_pointer & );
    virtual ~observing_pointer();

    observing_pointer & operator =( const observing_pointer & rhs )
    {
        set( rhs._subject ); return *this;
    }
    observing_pointer & operator =( const observable * ptr )
    {
        set( ptr ); return *this;
    }
    operator const observable *() const
    {
        return _subject;
    } 
    /// @name dereferencing operators
    /**
     *  !!! clients must not call these if the pointer is null
     */
    //@{
    const observable * operator ->() const { return  _subject; } 
    const observable & operator  *() const { return *_subject; } 
    //@}

    bool operator ==( observable * ptr ) const { return _subject == ptr; } 
    bool operator !=( observable * ptr ) const { return _subject != ptr; } 
    bool operator !()                    const { return _subject == 0; }
    bool null()                          const { return _subject == 0; }
    void nullify() { set( 0 ); }

    void set( const observable * );

    BEACH_NOTIFICATION_OBSERVER_OVERRIDES_REQUIRED

private:

    const observable * _subject;

}; // end of template class observing_pointer

//--------------------------------------

/// type-safe auto-zeroing pointer observing a constant subject
/**
 *  This encapsulates a type-safe pointer to an observable subject
 *  so that the pointer gets zeroed when the subject gets destroyed.
 *
 *  @note   even though this subclass template has all non-virtual
 *          methods that are inlined, GCC still requires template
 *          instantiations for its vtable linkage.
 *
 *  @note   design patterns applied:
 *              - Observer [GoF], [PLoP2], [WF]
 */     
template <class T>
class observing_pointer_typed
    : private observing_pointer
{
public:

    typedef T subject;

    observing_pointer_typed( const subject * ptr = 0 )
      : observing_pointer( ptr )
    {}
    observing_pointer_typed & operator =(
        const observing_pointer & rhs )
    {
        observing_pointer::operator =( rhs );
        return *this;
    }
    observing_pointer_typed & operator =(
        const subject * ptr )
    {
        observing_pointer::operator =( ptr );
        return *this;
    }
    operator const observable *() const
    {
        return observing_pointer::operator const observable*();
    } 
    operator const subject *() const
    {
        return dynamic_cast<const subject*>(
            observing_pointer::operator const observable*());
    } 
    /// @name dereferencing operators
    /**
     *  !!! clients must not call these if the pointer is null
     */
    //@{
    const subject * operator ->() const
    { 
        return dynamic_cast<const subject*>(
            observing_pointer::operator ->());
    } 
    const subject & operator  *() const
    {
        return dynamic_cast<const subject&>(
            observing_pointer::operator *());
    } 
    //@}

    bool operator ==( subject * ptr ) const
    {   
        return observing_pointer::operator ==( ptr );
    }
    bool operator !=( subject * ptr ) const
    {
        return observing_pointer::operator !=( ptr );
    } 
    bool operator !() const
    { 
        return observing_pointer::operator !();
    }
    bool null() const
    { 
        return observing_pointer::null();
    }
    void nullify()
    { 
        observing_pointer::nullify();
    }
    void set( const subject * ptr )
    {
        observing_pointer::set( ptr );
    }

}; // end of template class observing_pointer_typed

//--------------------------------------

/// type-safe auto-zeroing pointer observing a non-constant subject
/**
 *  This encapsulates a type-safe pointer to an observable subject
 *  so that the pointer gets zeroed when the subject gets destroyed.
 *
 *  @note   even though this subclass template has all non-virtual
 *          methods that are inlined, GCC still requires template
 *          instantiations for its vtable linkage.
 *
 *  @note   design patterns applied:
 *              - Observer [GoF], [PLoP2], [WF]
 */     
template <class T>
class observing_pointer_typed_nc
    : public observing_pointer_typed<T>
{
public:

    typedef T subject;

    observing_pointer_typed_nc( subject * ptr = 0 )
      : observing_pointer_typed<T>( ptr )
    {}
    observing_pointer_typed_nc & operator =(
        const observing_pointer & rhs )
    {
        observing_pointer_typed<T>::operator =( rhs );
        return *this;
    }
    observing_pointer_typed_nc & operator =(
        subject * ptr )
    {
        observing_pointer_typed<T>::operator =( ptr );
        return *this;
    }
    operator observable *() const
    {
        return const_cast<observable*>(
            observing_pointer_typed<T>::operator const observable*());
    } 
    operator subject *() const
    {
        return const_cast<subject*>(
            observing_pointer_typed<T>::operator const subject*());
    } 
    /// @name dereferencing operators
    /**
     *  !!! clients must not call these if the pointer is null
     */
    //@{
    subject * operator ->() const
    { 
        return const_cast<subject*>(
            observing_pointer_typed<T>::operator ->());
    } 
    subject & operator  *() const
    {
        return const_cast<subject&>(
            observing_pointer_typed<T>::operator *());
    } 
    //@}

    void set( subject * ptr )
    {
        observing_pointer_typed<T>::set( ptr );
    }

}; // end of template class observing_pointer_typed_nc

//--------------------------------------

}; // end of namespace notification

//----------------------------------------------------------
#endif // BEACH_NOTIFICATION_OBSERVING_POINTER
