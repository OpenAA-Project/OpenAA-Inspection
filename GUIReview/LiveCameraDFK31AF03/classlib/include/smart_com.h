/*
 * Copyright (C) 2012
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef SMART_COM_H_INC_
#define SMART_COM_H_INC_

template<class TComObj>
class smart_com
{
public:
	typedef TComObj			value_type;
	typedef TComObj*		pointer;
	typedef const TComObj*	const_pointer;
	typedef TComObj&		reference;
	typedef const TComObj&	const_reference;
public:
	/** ctor to empty object */
	/** assign pointer and increment reference */
	smart_com( TComObj* p = 0 ) : m_pComPtr(p)					{ if( m_pComPtr ) m_pComPtr->AddRef(); }
	// if bAttach == true then the pointer is attached to this object but not addref'ed in the ctor
	explicit smart_com( TComObj* p, bool bAttach )
		: m_pComPtr( p )	{ if( !bAttach && m_pComPtr ) m_pComPtr->AddRef(); }
	/** copy constructor */
	template<class TType>
	explicit smart_com( const smart_com<TType>& op2 ) : m_pComPtr( op2.get() )	{ if( m_pComPtr ) m_pComPtr->AddRef(); }

	smart_com( const smart_com& op2 ) : m_pComPtr( op2.m_pComPtr )	{ if( m_pComPtr ) m_pComPtr->AddRef(); }
	/** dtor */
	~smart_com()													{ destroy(); }

	smart_com&		operator=( smart_com op2 )
	{
		std::swap( m_pComPtr, op2.m_pComPtr );
		return *this;
	}
	smart_com&		operator=( pointer op2 )
	{
		if ( op2 != m_pComPtr )
		{
			destroy();
			m_pComPtr = op2;
			if( m_pComPtr )
				m_pComPtr->AddRef();
		}
		return *this;
	}
	
	void			attach( pointer p )									{ destroy(); m_pComPtr = p; }
	pointer			detach()											{ pointer p = 0; std::swap( m_pComPtr, p ); return p; }

	bool			operator<( const smart_com<TComObj>& op2 ) const	{ return m_pComPtr < op2.m_pComPtr; }
	bool			operator==( const smart_com<TComObj>& op2 ) const	{ return m_pComPtr == op2.m_pComPtr; }
	bool			operator!=( const smart_com<TComObj>& op2 ) const	{ return m_pComPtr != op2.m_pComPtr; }
	bool			operator==( void* p ) const							{ return get() == p; }
	bool			operator!=( void* p ) const							{ return get() != p; }
	friend bool		operator==( void* p, const smart_com<TComObj>& op2 );
	friend bool		operator!=( void* p, const smart_com<TComObj>& op2 );

	reference		operator*()											{ return *m_pComPtr; }
	const_reference operator*()	const									{ return *m_pComPtr; }
	pointer			operator->()										{ return m_pComPtr; }
	const_pointer	operator->() const									{ return m_pComPtr; }

	static GUID		getIID()											{ return __uuidof( value_type ); }

	// this operator provides a shortcut for QueryInterface
	//operator void**()	{ return reinterpret_cast<void**>( &m_pComPtr ); }


	pointer&		get()		{ return m_pComPtr; }
	/** needed for CreateInstance, QueryInterface, ... */
	pointer&		getImpl()	{ return m_pComPtr; }
	/** return just a copy of the pointer */
	pointer			get() const { return m_pComPtr; }

	/**	return an addref'ed interface pointer. Needed when you want to pass an AddRef'ed pointer by value. */
	pointer			getReference() const { if( get() != 0 ) { get()->AddRef(); } return get(); }

	/** release the current reference, set this to 0, return the pointer to the interface */
	pointer			release()	{ TComObj* p = m_pComPtr; destroy(); return p; }

	/** release reference and set this to 0 */
	void			destroy()	{ if ( m_pComPtr ) { m_pComPtr->Release(); m_pComPtr = 0; } }
private:
	/** internal pointer to the COM interface */
	pointer			m_pComPtr;
};

template<class TPtr>
const smart_com<TPtr>& smart_comAddRef( const smart_com<TPtr>& p )
{
	smart_com<TPtr> tmp( p );
	tmp->AddRef();
	return p;
}

/** attaches the interface to a smart_com object.
 * this is useful for things like :
 *	{
 *		TItf* p = pSth;				// pSth has a ref-count of 1
 *		smart_com<IItf> pObj( p );	// adds 1 to the reference count
 *	}	// this would leave an reference count of 1
 * better use :
 *	{
 *		TItf* p = pSth;										// pSth has a ref-count of 1
 *		smart_com<IItf> pObj( attach_to_smart_com( p ) );	// this does not add a reference count
 *	} // here the reference count would be 0
 */
template<class TItf>
smart_com<TItf>	attach_to_smart_com( TItf* pObj )
{
	return smart_com<TItf>( pObj, true );
}

template<class TComObj>
inline bool	operator==( void* p, const smart_com<TComObj>& op2 )
{
	return op2.get() == p;
}

template<class TComObj>
inline bool	operator!=( void* p, const smart_com<TComObj>& op2 )
{
	return op2.get() != p;
}

#endif //SMART_COM_H_INC_