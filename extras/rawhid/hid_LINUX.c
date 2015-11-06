/* Simple Raw HID functions for Linux - for use with Teensy RawHID example
 * http://www.pjrc.com/teensy/rawhid.html
 * Copyright (c) 2009 PJRC.COM, LLC
 *
 *  rawhid_open - open 1 or more devices
 *  rawhid_recv - receive a packet
 *  rawhid_send - send a packet
 *  rawhid_close - close a device
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above description, website URL and copyright notice and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Version 1.0: Initial Release
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <usb.h>

#include "hid.h"


// On Linux there are several options to access HID devices.
//
// libusb 0.1 - the only way that works well on all distributions
// libusb 1.0 - someday will become standard on most distributions
// hidraw driver - relatively new, not supported on many distributions (yet)
// hiddev driver - old, ubuntu, fedora, others dropping support
// usbfs - low level usb API: http://www.kernel.org/doc/htmldocs/usb.html#usbfs
//
// This code uses libusb 0.1, which is well supported on all linux distributions
// and very stable and widely used by many programs.  libusb 0.1 only provides a
// simple synchronous interface, basically the same as this code needs.  However,
// if you want non-blocking I/O, libusb 0.1 simply does not provide that.  There
// is also no kernel-level buffering, so performance is poor.
//
// UPDATE: As of November 2011, hidraw support seems to be working well in all
// major linux distributions.  Embedded and "small" distros, used on ARM boards,
// routers and embedded hardware stil seem to omit the hidraw driver.
//
// The hidraw driver is a great solution.  However, it has only been supported
// by relatively recent (in 2009) kernels.  Here is a quick survey of the status
// of hidraw support in various distributions as of Sept 2009:
//
// Fedora 11: works, kernel 2.6.29.4
// Mandiva 2009.1: works, kernel 2.6.29.1
// Ubuntu 9.10-alpha6: works, kernel 2.6.31
// Ubuntu 9.04: sysfs attrs chain broken (hidraw root only), 2.6.28 kernel
// openSUSE 11.1: sysfs attrs chain broken (hidraw root only), 2.6.27.7 kernel
// Debian Live, Lenny 5.0.2: sysfs attrs chain broken (hidraw root only), 2.6.26
// SimplyMEPIS 8.0.10: sysfs attrs chain broken (hidraw root only), 2.6.27
// Mint 7: sysfs attrs chain broken (hidraw root only), 2.6.28 kernel
// Gentoo 2008.0-r1: sysfs attrs chain broken (hidraw root only), 2.6.24 kernel
// Centos 5: no hidraw or hiddev devices, 2.6.18 kernel
// Slitaz 2.0: no hidraw devices (has hiddev), 2.6.25.5 kernel
// Puppy 4.3: no hidraw devices (has hiddev), 2.6.30.5 kernel
// Damn Small 4.4.10: (would not boot)
// Gentoo 10.0-test20090926: (would not boot)
// PCLinuxOS 2009.2: (would not boot) 
// Slackware: (no live cd available?  www.slackware-live.org dead)



#define printf(...)  // comment this out for lots of info


// a list of all opened HID devices, so the caller can
// simply refer to them by number
typedef struct hid_struct hid_t;
static hid_t *first_hid = NULL;
static hid_t *last_hid = NULL;
struct hid_struct {
	usb_dev_handle *usb;
	int open;
	int iface;
	int ep_in;
	int ep_out;
	struct hid_struct *prev;
	struct hid_struct *next;
};


// private functions, not intended to be used from outside this file
static void add_hid(hid_t *h);
static hid_t * get_hid(int num);
static void free_all_hid(void);
static void hid_close(hid_t *hid);
static int hid_parse_item(uint32_t *val, uint8_t **data, const uint8_t *end);


//  rawhid_recv - receive a packet
//    Inputs:
//	num = device to receive from (zero based)
//	buf = buffer to receive packet
//	len = buffer's size
//	timeout = time to wait, in milliseconds
//    Output:
//	number of bytes received, or -1 on error
//
int rawhid_recv(int num, void *buf, int len, int timeout)
{
	hid_t *hid;
	int r;

	hid = get_hid(num);
	if (!hid || !hid->open) return -1;
	r = usb_interrupt_read(hid->usb, hid->ep_in, buf, len, timeout);
	if (r >= 0) return r;
	if (r == -110) return 0;  // timeout
	return -1;
}

//  rawhid_send - send a packet
//    Inputs:
//	num = device to transmit to (zero based)
//	buf = buffer containing packet to send
//	len = number of bytes to transmit
//	timeout = time to wait, in milliseconds
//    Output:
//	number of bytes sent, or -1 on error
//
int rawhid_send(int num, void *buf, int len, int timeout)
{
	hid_t *hid;

	hid = get_hid(num);
	if (!hid || !hid->open) return -1;
	if (hid->ep_out) {
		return usb_interrupt_write(hid->usb, hid->ep_out, buf, len, timeout);
	} else {
		return usb_control_msg(hid->usb, 0x21, 9, 0, hid->iface, buf, len, timeout);
	}
}

//  rawhid_open - open 1 or more devices
//
//    Inputs:
//	max = maximum number of devices to open
//	vid = Vendor ID, or -1 if any
//	pid = Product ID, or -1 if any
//	usage_page = top level usage page, or -1 if any
//	usage = top level usage number, or -1 if any
//    Output:
//	actual number of devices opened
//
int rawhid_open(int max, int vid, int pid, int usage_page, int usage)
{
	struct usb_bus *bus;
	struct usb_device *dev;
	struct usb_interface *iface;
	struct usb_interface_descriptor *desc;
	struct usb_endpoint_descriptor *ep;
	usb_dev_handle *u;
	uint8_t buf[1024], *p;
	int i, n, len, tag, ep_in, ep_out, count=0, claimed;
	uint32_t val=0, parsed_usage, parsed_usage_page;
	hid_t *hid;

	if (first_hid) free_all_hid();
	printf("rawhid_open, max=%d\n", max);
	if (max < 1) return 0;
	usb_init();
	usb_find_busses();
	usb_find_devices();
	for (bus = usb_get_busses(); bus; bus = bus->next) {
		for (dev = bus->devices; dev; dev = dev->next) {
			if (vid > 0 && dev->descriptor.idVendor != vid) continue;
			if (pid > 0 && dev->descriptor.idProduct != pid) continue;
			if (!dev->config) continue;
			if (dev->config->bNumInterfaces < 1) continue;
			printf("device: vid=%04X, pic=%04X, with %d iface\n",
				dev->descriptor.idVendor,
				dev->descriptor.idProduct,
				dev->config->bNumInterfaces);
			iface = dev->config->interface;
			u = NULL;
			claimed = 0;
			for (i=0; i<dev->config->bNumInterfaces && iface; i++, iface++) {
				desc = iface->altsetting;
				if (!desc) continue;
				printf("  type %d, %d, %d\n", desc->bInterfaceClass,
					desc->bInterfaceSubClass, desc->bInterfaceProtocol);
				if (desc->bInterfaceClass != 3) continue;
				if (desc->bInterfaceSubClass != 0) continue;
				if (desc->bInterfaceProtocol != 0) continue;
				ep = desc->endpoint;
				ep_in = ep_out = 0;
				for (n = 0; n < desc->bNumEndpoints; n++, ep++) {
					if (ep->bEndpointAddress & 0x80) {
						if (!ep_in) ep_in = ep->bEndpointAddress & 0x7F;
						printf("    IN endpoint %d\n", ep_in);
					} else {
						if (!ep_out) ep_out = ep->bEndpointAddress;
						printf("    OUT endpoint %d\n", ep_out);
					}
				}
				if (!ep_in) continue;
				if (!u) {
					u = usb_open(dev);
					if (!u) {
						printf("  unable to open device\n");
						break;
					}
				}
				printf("  hid interface (generic)\n");
				if (usb_get_driver_np(u, i, (char *)buf, sizeof(buf)) >= 0) {
					printf("  in use by driver \"%s\"\n", buf);
					if (usb_detach_kernel_driver_np(u, i) < 0) {
						printf("  unable to detach from kernel\n");
						continue;
					}
				}
				if (usb_claim_interface(u, i) < 0) {
					printf("  unable claim interface %d\n", i);
					continue;
				}
				len = usb_control_msg(u, 0x81, 6, 0x2200, i, (char *)buf, sizeof(buf), 250);
					printf("  descriptor, len=%d\n", len);
				if (len < 2) {
					usb_release_interface(u, i);
					continue;
				}
				p = buf;
				parsed_usage_page = parsed_usage = 0;
				while ((tag = hid_parse_item(&val, &p, buf + len)) >= 0) {
					printf("  tag: %X, val %X\n", tag, val);
					if (tag == 4) parsed_usage_page = val;
					if (tag == 8) parsed_usage = val;
					if (parsed_usage_page && parsed_usage) break;
				}
				if ((!parsed_usage_page) || (!parsed_usage) ||
				  (usage_page > 0 && parsed_usage_page != usage_page) || 
				  (usage > 0 && parsed_usage != usage)) {
					usb_release_interface(u, i);
					continue;
				}
				hid = (struct hid_struct *)malloc(sizeof(struct hid_struct));
				if (!hid) {
					usb_release_interface(u, i);
					continue;
				}
				hid->usb = u;
				hid->iface = i;
				hid->ep_in = ep_in;
				hid->ep_out = ep_out;
				hid->open = 1;
				add_hid(hid);
				claimed++;
				count++;
				if (count >= max) return count;
			}
			if (u && !claimed) usb_close(u);
		}
	}
	return count;
}


//  rawhid_close - close a device
//
//    Inputs:
//	num = device to close (zero based)
//    Output
//	(nothing)
//
void rawhid_close(int num)
{
	hid_t *hid;

	hid = get_hid(num);
	if (!hid || !hid->open) return;
	hid_close(hid);
}

// Chuck Robey wrote a real HID report parser
// (chuckr@telenix.org) chuckr@chuckr.org
// http://people.freebsd.org/~chuckr/code/python/uhidParser-0.2.tbz
// this tiny thing only needs to extract the top-level usage page
// and usage, and even then is may not be truly correct, but it does
// work with the Teensy Raw HID example.
static int hid_parse_item(uint32_t *val, uint8_t **data, const uint8_t *end)
{
	const uint8_t *p = *data;
	uint8_t tag;
	int table[4] = {0, 1, 2, 4};
	int len;

	if (p >= end) return -1;
	if (p[0] == 0xFE) {
		// long item, HID 1.11, 6.2.2.3, page 27
		if (p + 5 >= end || p + p[1] >= end) return -1;
		tag = p[2];
		*val = 0;
		len = p[1] + 5;
	} else {
		// short item, HID 1.11, 6.2.2.2, page 26
		tag = p[0] & 0xFC;
		len = table[p[0] & 0x03];
		if (p + len + 1 >= end) return -1;
		switch (p[0] & 0x03) {
		  case 3: *val = p[1] | (p[2] << 8) | (p[3] << 16) | (p[4] << 24); break;
		  case 2: *val = p[1] | (p[2] << 8); break;
		  case 1: *val = p[1]; break;
		  case 0: *val = 0; break;
		}
	}
	*data += len + 1;
	return tag;
}


static void add_hid(hid_t *h)
{
	if (!first_hid || !last_hid) {
		first_hid = last_hid = h;
		h->next = h->prev = NULL;
		return;
	}
	last_hid->next = h;
	h->prev = last_hid;
	h->next = NULL;
	last_hid = h;
}


static hid_t * get_hid(int num)
{
	hid_t *p;
	for (p = first_hid; p && num > 0; p = p->next, num--) ;
	return p;
}


static void free_all_hid(void)
{
	hid_t *p, *q;

	for (p = first_hid; p; p = p->next) {
		hid_close(p);
	}
	p = first_hid;
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
	first_hid = last_hid = NULL;
}


static void hid_close(hid_t *hid)
{
	hid_t *p;
	int others=0;

	usb_release_interface(hid->usb, hid->iface);
	for (p = first_hid; p; p = p->next) {
		if (p->open && p->usb == hid->usb) others++;
	}
	if (!others) usb_close(hid->usb);
	hid->usb = NULL;
}



