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


#if !defined(__EPIX_XCLIBVER_DEFINED)
#define __EPIX_XCLIBVER_DEFINED

#if defined(C_GNU64)|defined(C_MSC64)
  #if defined(PIXCI_CLSER)
    #if PIXCI_CLSER==10
      #define XCLIB_IDN       "PIXCI(R) CameraLink API V1.0"
    #elif PIXCI_CLSER==11
      #define XCLIB_IDN       "PIXCI(R) CameraLink API V1.1"
    #else
      #define XCLIB_IDN       "PIXCI(R) CameraLink API V?.?"
    #endif
  #elif defined(PIXCI_LITE)
    #define XCLIB_IDN	    "PIXCI(R) 64 Bit Library Lite"
  #elif defined(PIXCI_VIRTUAL)
    #define XCLIB_IDN	    "PIXCI(R) 64 Bit Virtual Library"
  #else
    #define XCLIB_IDN	    "PIXCI(R) 64 Bit Library"
  #endif
#else
  #if defined(PIXCI_CLSER)
    #if PIXCI_CLSER==10
      #define XCLIB_IDN       "PIXCI(R) CameraLink API V1.0"
    #elif PIXCI_CLSER==11
      #define XCLIB_IDN       "PIXCI(R) CameraLink API V1.1"
    #else
      #define XCLIB_IDN       "PIXCI(R) CameraLink API V?.?"
    #endif
  #elif defined(PIXCI_LITE)
    #define XCLIB_IDN	    "PIXCI(R) 32 Bit Library Lite"
  #elif defined(PIXCI_VIRTUAL)
    #define XCLIB_IDN	    "PIXCI(R) 32 Bit Virtual Library"
  #else
    #define XCLIB_IDN	    "PIXCI(R) 32 Bit Library"
  #endif
#endif
/*
 * XCLIB_IDR is machine generated.
 */
#define XCLIB_IDV	"3.07.00"
#define XCLIB_IDV0	3
#define XCLIB_IDV1	07
#define XCLIB_IDV2	00
#define XCLIB_IDR       "[11.03.08]"
#define XCLIB_IDNVR	XCLIB_IDN " " XCLIB_IDV " " XCLIB_IDR


#endif				/* !defined(__EPIX_XCLIBVER_DEFINED) */