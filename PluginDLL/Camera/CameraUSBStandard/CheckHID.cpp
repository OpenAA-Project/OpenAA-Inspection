/*
 * Copyright (C) 2020
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

#include "libusb.h"



int	CheckEnum(int VendorID[] ,int VendorIDNumb)
{
	libusb_device **devs;

	int	r = libusb_init(NULL);
	if (r < 0)
		return 0;

	ssize_t cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
		return 0;
	int	Counter=0;
	for(int i=0;i<cnt;i++){
		struct libusb_device_descriptor desc;
		int	ret = libusb_get_device_descriptor(devs[i], &desc);
		if (ret < 0) {
			return Counter;
		}
		//if(desc.idVendor==VendorID
		//&& desc.idProduct==ProductID){
		for(int j=0;j<VendorIDNumb;j++){
			if(desc.idVendor==VendorID[j]){
				Counter++;
				break;
			}
		}
	}

	return Counter;
}