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


#ifndef _FILTERDLL_H_INC_
#define _FILTERDLL_H_INC_

#include "libbasedefs.h"


#define FILTER_INTERFACE_VERSION 1

namespace _DSHOWLIB_NAMESPACE
{
	class IFrameFilter;
	struct FilterInfo;

	/**
	 *	Abstract base class for a filter factory. An implementation of this
	 *	interface has to be created by <link>getFilterFactory</link>.
	 *	
	 *	IFilterFactory has methods for enumeration, creation and removal of
	 *	Frame-/Update-Transform-filters
	 */
	class IFilterFactory
	{
	public:
		virtual bool enumFilters( unsigned int index, FilterInfo* pFilterInfo ) = 0;

		virtual IFrameFilter*		createFilter( const wchar_t* name ) = 0;
		
		virtual int	getVersion() = 0;
	};
}

#define FILTERDLL_BEGIN_EXPORT() \
	extern "C" __declspec(dllexport) _DSHOWLIB_NAMESPACE::IFilterFactory*	getFilterFactory() \
	{ \
		static bool init = false; \
		static _DSHOWLIB_NAMESPACE::CFilterFactory fac; \
		if( !init ) \
		{

#define FILTERDLL_REGISTER_FILTER(CFilter) \
			fac.registerFilter( (CFilter*) 0 );

#define FILTERDLL_END_EXPORT() \
			init = true; \
		} \
		return &fac; \
	}

#endif