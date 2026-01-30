/*
 * Copyright (C) 2023
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

#if	!defined(XDATABASETYPE_H)
#define	XDATABASETYPE_H

enum	FieldType{
	ftUnknown
	,ftInteger
	,ftWord
	,ftSmallint
	,ftFixedChar
	,ftDateTime
	,ftFloat
	,ftVarBytes
	,ftString
	,ftBlob
};

enum TriggerAction{
	_TA_BeforeInsert   =1
	,_TA_AfterInsert    =2
	,_TA_BeforeUpdate   =3
	,_TA_AfterUpdate    =4
	,_TA_BeforeDelete   =5
	,_TA_AfterDelete    =6
};

#endif