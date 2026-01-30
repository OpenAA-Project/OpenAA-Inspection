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



#if defined(C_MSC32)|defined(C_MSC16)|defined(C_MSC64)
  #pragma pack()
  #pragma warning (disable:4103)    /* packing changes */
  /*
   * The following would be better, but pack warning messages
   * are still generated?
   *
   *   #pragma pack()
   *   #pragma warning (default:4103)	     // packing changes
   */
#elif defined(C_BOR32)|defined(C_BOR16)
  #pragma option -a.		   /* no pop available, restore to command line!! */
#elif defined(C_HIC32)
  #pragma Pop_align_members;
#elif defined(C_WAT32)|defined(C_WAT16)
  #pragma pack()
#elif defined(C_TMSC40)
#elif defined(C_GNU32)|defined(C_GNU64)
#else
  #error "Can't identify compiler."
#endif
/*
 * Check proper usage
 */
#if EPIX_CEXT_HPE!=1
  #error "Bad usage of cext_hp[1248se].h."
#endif
#undef EPIX_CEXT_HPE