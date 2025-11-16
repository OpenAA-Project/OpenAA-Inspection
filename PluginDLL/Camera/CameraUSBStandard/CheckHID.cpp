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