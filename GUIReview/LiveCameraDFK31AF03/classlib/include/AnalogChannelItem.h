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

// AnalogChannelItem.h: interface for the AnalogChannelItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALOGCHANNELITEM_H__31CEA1C4_246E_411C_800F_CF94EE0DBE8D__INCLUDED_)
#define AFX_ANALOGCHANNELITEM_H__31CEA1C4_246E_411C_800F_CF94EE0DBE8D__INCLUDED_

#pragma once

#include <string>
#include "udshl_defs.h"

#include "simplectypes.h"

namespace _DSHOWLIB_NAMESPACE
{
	class Grabber;

	/** Represents an input of a video capture device. **/
	class _UDSHL_EXP_API AnalogChannelItem
	{
		friend Grabber;
	public:
		///< constructs an invalid AnalogChannelItem()
		AnalogChannelItem();
        /** copies an analog channel item.
         * @param op item to copy
         **/
        AnalogChannelItem( const AnalogChannelItem& op );

		/** dtor */
		virtual ~AnalogChannelItem();

		/** assignment operator
		 * @param op2
		 * @return this
		 */
		AnalogChannelItem&	operator=( const AnalogChannelItem& op2 );

		/** return internal PhysicalConnectorType
		 * @return internal PhysicalConnectorType, which is valid only if isValid() returns true
		 **/
		PhysicalConnectorType getPhysicalConnectorType() const { return m_PhysicalConnectorType; };

		/** return index of input
		 * @return index of input or -1, which is valid only if isValid() returns true
		 **/
		int getIndex() const { return m_Index; };

		/** test if the input is valid
		 * @return true, if the input is valid, else false
		 **/
		bool isValid() const;

		/** get a string representation of the input
		 * @return a pointer to the string representation of the input
		 **/
		operator const char* () const;


		/** get a string representation of the input
		 * @return a pointer to the string representation of the input
		 **/
		const char*		c_str() const;

		/** returns the result of a lexicographical compare of the index
		 * @return true, if this is before op
		 * @param op the VideoNormItem to compare with
		 **/
		bool operator < (const AnalogChannelItem& op) const;

		/** test if two channels are equal
		 * @param op channel to compare to this
		 * @return true if this and op are equal, else false
		 **/
		bool			operator==( const AnalogChannelItem& op ) const;

		/** test if two channels are not equal
		 * @param op channel to compare to this
		 * @return false if this and op are equal, else true
		 **/
		bool			operator!=( const AnalogChannelItem& op ) const;

		/** test if two items are equal
		 * @param op item to compare to this
		 * @return true if this and op are equal, else false
		 **/
		bool			operator==( const std::string& op ) const;
		bool			operator==( const std::wstring& op ) const;

		/** generates an invalid item
		 * @return an invalid item
		 * @see isValid()
		 **/
		static AnalogChannelItem createInvalid();

		/** Creates a textual representation for this AnalogChannelItem
		 * @return The textual representation.
		 */
		std::string		toString() const;
		std::wstring	toStringW() const;
	private:
		/** constructs an AnalogChannelItem */
		AnalogChannelItem( int index, PhysicalConnectorType type );

		/** the PhysicalConnectorType of the wrapped type */
		PhysicalConnectorType m_PhysicalConnectorType;
		/** the index of this Channel */
		int				m_Index;
#pragma _DLL_EXPORT_WARNING_DISABLE
		std::string		m_String;
        std::wstring	m_StringW;
#pragma _DLL_EXPORT_WARNING_ENABLE

        void			initStringMember();
	};

};
#endif // !defined(AFX_ANALOGCHANNELITEM_H__31CEA1C4_246E_411C_800F_CF94EE0DBE8D__INCLUDED_)