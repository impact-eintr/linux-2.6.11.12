#ifndef __LINUX_USB_H
#define __LINUX_USB_H

#include <linux/mod_devicetable.h>
#include <linux/usb_ch9.h>

#define USB_MAJOR			180


#ifdef __KERNEL__

#include <linux/config.h>
#include <linux/errno.h>        /* for -ENODEV */
#include <linux/delay.h>	/* for mdelay() */
#include <linux/interrupt.h>	/* for in_interrupt() */
#include <linux/list.h>		/* for struct list_head */
#include <linux/kref.h>		/* for struct kref */
#include <linux/device.h>	/* for struct device */
#include <linux/fs.h>		/* for struct file_operations */
#include <linux/completion.h>	/* for struct completion */
#include <linux/sched.h>	/* for current && schedule_timeout */

struct usb_device;
struct usb_driver;

/*-------------------------------------------------------------------------*/

/*
 * Host-side wrappers for standard USB descriptors ... these are parsed
 * from the data provided by devices.  Parsing turns them from a flat
 * sequence of descriptors into a hierarchy:
 *
 *  - devices have one (usually) or more configs;
 *  - configs have one (often) or more interfaces;
 *  - interfaces have one (usually) or more settings;
 *  - each interface setting has zero or (usually) more endpoints.
 *
 * And there might be other descriptors mixed in with those.
 *
 * Devices may also have class-specific or vendor-specific descriptors.
 */

/**
 * struct usb_host_endpoint - host-side endpoint descriptor and queue
 * @desc: descriptor for this endpoint, wMaxPacketSize in native byteorder
 * @urb_list: urbs queued to this endpoint; maintained by usbcore
 * @hcpriv: for use by HCD; typically holds hardware dma queue head (QH)
 *	with one or more transfer descriptors (TDs) per urb
 * @extra: descriptors following this endpoint in the configuration
 * @extralen: how many bytes of "extra" are valid
 *
 * USB requests are always queued to a given endpoint, identified by a
 * descriptor within an active interface in a given USB configuration.
 */
/**
 * USB端点。分控制、中断、批量、等时端点。
 */
struct usb_host_endpoint {
	/**
	 * 真正的端点信息。
	 */
	struct usb_endpoint_descriptor	desc;
	struct list_head		urb_list;
	void				*hcpriv;

	unsigned char *extra;   /* Extra descriptors */
	int extralen;
};

/* host-side wrapper for one interface setting's parsed descriptors */
struct usb_host_interface {
	struct usb_interface_descriptor	desc;

	/* array of desc.bNumEndpoint endpoints associated with this
	 * interface setting.  these will be in no particular order.
	 */
	struct usb_host_endpoint *endpoint;

	unsigned char *extra;   /* Extra descriptors */
	int extralen;
};

enum usb_interface_condition {
	USB_INTERFACE_UNBOUND = 0,
	USB_INTERFACE_BINDING,
	USB_INTERFACE_BOUND,
	USB_INTERFACE_UNBINDING,
};

/**
 * struct usb_interface - what usb device drivers talk to
 * @altsetting: array of interface structures, one for each alternate
 * 	setting that may be selected.  Each one includes a set of
 * 	endpoint configurations.  They will be in no particular order.
 * @num_altsetting: number of altsettings defined.
 * @cur_altsetting: the current altsetting.
 * @driver: the USB driver that is bound to this interface.
 * @minor: the minor number assigned to this interface, if this
 *	interface is bound to a driver that uses the USB major number.
 *	If this interface does not use the USB major, this field should
 *	be unused.  The driver should set this value in the probe()
 *	function of the driver, after it has been assigned a minor
 *	number from the USB core by calling usb_register_dev().
 * @condition: binding state of the interface: not bound, binding
 *	(in probe()), bound to a driver, or unbinding (in disconnect())
 * @dev: driver model's view of this device
 * @class_dev: driver model's class view of this device.
 *
 * USB device drivers attach to interfaces on a physical device.  Each
 * interface encapsulates a single high level function, such as feeding
 * an audio stream to a speaker or reporting a change in a volume control.
 * Many USB devices only have one interface.  The protocol used to talk to
 * an interface's endpoints can be defined in a usb "class" specification,
 * or by a product's vendor.  The (default) control endpoint is part of
 * every interface, but is never listed among the interface's descriptors.
 *
 * The driver that is bound to the interface can use standard driver model
 * calls such as dev_get_drvdata() on the dev member of this structure.
 *
 * Each interface may have alternate settings.  The initial configuration
 * of a device sets altsetting 0, but the device driver can change
 * that setting using usb_set_interface().  Alternate settings are often
 * used to control the the use of periodic endpoints, such as by having
 * different endpoints use different amounts of reserved USB bandwidth.
 * All standards-conformant USB devices that use isochronous endpoints
 * will use them in non-default settings.
 *
 * The USB specification says that alternate setting numbers must run from
 * 0 to one less than the total number of alternate settings.  But some
 * devices manage to mess this up, and the structures aren't necessarily
 * stored in numerical order anyhow.  Use usb_altnum_to_altsetting() to
 * look up an alternate setting in the altsetting array based on its number.
 */
/**
 * USB端点被捆绑为接口。USB核心把该结构体传递给设备驱动程序，之后由USB驱动程序来负责控制该结构体。
 */
struct usb_interface {
	/* array of alternate settings for this interface,
	 * stored in no particular order */
	/**
	 * 一个接口结构体数组。包含了所有可能用于该接口的可选配置。
	 */
	struct usb_host_interface *altsetting;

	/**
	 * 指向altsetting数组内部的指针，表示该接口的当前活动配置。
	 */
	struct usb_host_interface *cur_altsetting;	/* the currently
					 * active alternate setting */
	/**
	 * altsetting指针所指向的可选设置的数量。
	 */
	unsigned num_altsetting;	/* number of alternate settings */

	/**
	 * 如果捆绑到该接口的USB驱动程序使用USB主设备号，这个变量包含USB核心分配给该接口的次设备号。
	 * 这仅在一个成功的usb_register_dev调用之后才有效。
	 */
	int minor;			/* minor number this interface is bound to */
	enum usb_interface_condition condition;		/* state of binding */
	struct device dev;		/* interface specific device info */
	struct class_device *class_dev;
};
#define	to_usb_interface(d) container_of(d, struct usb_interface, dev)
/**
 * 把一个给定的usb_interface结构体转换为usb_device结构体。
 */
#define	interface_to_usbdev(intf) \
	container_of(intf->dev.parent, struct usb_device, dev)

static inline void *usb_get_intfdata (struct usb_interface *intf)
{
	return dev_get_drvdata (&intf->dev);
}

static inline void usb_set_intfdata (struct usb_interface *intf, void *data)
{
	dev_set_drvdata(&intf->dev, data);
}

struct usb_interface *usb_get_intf(struct usb_interface *intf);
void usb_put_intf(struct usb_interface *intf);

/* this maximum is arbitrary */
#define USB_MAXINTERFACES	32

/**
 * struct usb_interface_cache - long-term representation of a device interface
 * @num_altsetting: number of altsettings defined.
 * @ref: reference counter.
 * @altsetting: variable-length array of interface structures, one for
 *	each alternate setting that may be selected.  Each one includes a
 *	set of endpoint configurations.  They will be in no particular order.
 *
 * These structures persist for the lifetime of a usb_device, unlike
 * struct usb_interface (which persists only as long as its configuration
 * is installed).  The altsetting arrays can be accessed through these
 * structures at any time, permitting comparison of configurations and
 * providing support for the /proc/bus/usb/devices pseudo-file.
 */
struct usb_interface_cache {
	unsigned num_altsetting;	/* number of alternate settings */
	struct kref ref;		/* reference counter */

	/* variable-length array of alternate settings for this interface,
	 * stored in no particular order */
	struct usb_host_interface altsetting[0];
};
#define	ref_to_usb_interface_cache(r) \
		container_of(r, struct usb_interface_cache, ref)
#define	altsetting_to_usb_interface_cache(a) \
		container_of(a, struct usb_interface_cache, altsetting[0])

/**
 * struct usb_host_config - representation of a device's configuration
 * @desc: the device's configuration descriptor.
 * @interface: array of pointers to usb_interface structures, one for each
 *	interface in the configuration.  The number of interfaces is stored
 *	in desc.bNumInterfaces.  These pointers are valid only while the
 *	the configuration is active.
 * @intf_cache: array of pointers to usb_interface_cache structures, one
 *	for each interface in the configuration.  These structures exist
 *	for the entire life of the device.
 * @extra: pointer to buffer containing all extra descriptors associated
 *	with this configuration (those preceding the first interface
 *	descriptor).
 * @extralen: length of the extra descriptors buffer.
 *
 * USB devices may have multiple configurations, but only one can be active
 * at any time.  Each encapsulates a different operational environment;
 * for example, a dual-speed device would have separate configurations for
 * full-speed and high-speed operation.  The number of configurations
 * available is stored in the device descriptor as bNumConfigurations.
 *
 * A configuration can contain multiple interfaces.  Each corresponds to
 * a different function of the USB device, and all are available whenever
 * the configuration is active.  The USB standard says that interfaces
 * are supposed to be numbered from 0 to desc.bNumInterfaces-1, but a lot
 * of devices get this wrong.  In addition, the interface array is not
 * guaranteed to be sorted in numerical order.  Use usb_ifnum_to_if() to
 * look up an interface entry based on its number.
 *
 * Device drivers should not attempt to activate configurations.  The choice
 * of which configuration to install is a policy decision based on such
 * considerations as available power, functionality provided, and the user's
 * desires (expressed through hotplug scripts).  However, drivers can call
 * usb_reset_configuration() to reinitialize the current configuration and
 * all its interfaces.
 */
/**
 * 一个USB设备可以有多个配置，而且可以在配置之间切换以改变设备的状态。
 */
struct usb_host_config {
	struct usb_config_descriptor	desc;

	/* the interfaces associated with this configuration,
	 * stored in no particular order */
	struct usb_interface *interface[USB_MAXINTERFACES];

	/* Interface information available even when this is not the
	 * active configuration */
	struct usb_interface_cache *intf_cache[USB_MAXINTERFACES];

	unsigned char *extra;   /* Extra descriptors */
	int extralen;
};

int __usb_get_extra_descriptor(char *buffer, unsigned size,
	unsigned char type, void **ptr);
#define usb_get_extra_descriptor(ifpoint,type,ptr)\
	__usb_get_extra_descriptor((ifpoint)->extra,(ifpoint)->extralen,\
		type,(void**)ptr)

/* -------------------------------------------------------------------------- */

struct usb_operations;

/* USB device number allocation bitmap */
struct usb_devmap {
	unsigned long devicemap[128 / (8*sizeof(unsigned long))];
};

/*
 * Allocated per bus (tree of devices) we have:
 */
struct usb_bus {
	struct device *controller;	/* host/master side hardware */
	int busnum;			/* Bus number (in order of reg) */
	char *bus_name;			/* stable id (PCI slot_name etc) */
	u8 otg_port;			/* 0, or number of OTG/HNP port */
	unsigned is_b_host:1;		/* true during some HNP roleswitches */
	unsigned b_hnp_enable:1;	/* OTG: did A-Host enable HNP? */

	int devnum_next;		/* Next open device number in round-robin allocation */

	struct usb_devmap devmap;	/* device address allocation map */
	struct usb_operations *op;	/* Operations (specific to the HC) */
	struct usb_device *root_hub;	/* Root hub */
	struct list_head bus_list;	/* list of busses */
	void *hcpriv;                   /* Host Controller private data */

	int bandwidth_allocated;	/* on this bus: how much of the time
					 * reserved for periodic (intr/iso)
					 * requests is used, on average?
					 * Units: microseconds/frame.
					 * Limits: Full/low speed reserve 90%,
					 * while high speed reserves 80%.
					 */
	int bandwidth_int_reqs;		/* number of Interrupt requests */
	int bandwidth_isoc_reqs;	/* number of Isoc. requests */

	struct dentry *usbfs_dentry;	/* usbfs dentry entry for the bus */

	struct class_device class_dev;	/* class device for this bus */
	void (*release)(struct usb_bus *bus);	/* function to destroy this bus's memory */
};
#define	to_usb_bus(d) container_of(d, struct usb_bus, class_dev)


/* -------------------------------------------------------------------------- */

/* This is arbitrary.
 * From USB 2.0 spec Table 11-13, offset 7, a hub can
 * have up to 255 ports. The most yet reported is 10.
 */
#define USB_MAXCHILDREN		(16)

struct usb_tt;

/*
 * struct usb_device - kernel's representation of a USB device
 *
 * FIXME: Write the kerneldoc!
 *
 * Usbcore drivers should not set usbdev->state directly.  Instead use
 * usb_set_device_state().
 */
struct usb_device {
	int		devnum;		/* Address on USB bus */
	char		devpath [16];	/* Use in messages: /port/port/... */
	enum usb_device_state	state;	/* configured, not attached, etc */
	enum usb_device_speed	speed;	/* high/full/low (or error) */

	struct usb_tt	*tt; 		/* low/full speed dev, highspeed hub */
	int		ttport;		/* device port on that tt hub */

	struct semaphore serialize;

	unsigned int toggle[2];		/* one bit for each endpoint ([0] = IN, [1] = OUT) */

	struct usb_device *parent;	/* our hub, unless we're the root */
	struct usb_bus *bus;		/* Bus we're part of */
	struct usb_host_endpoint ep0;

	struct device dev;		/* Generic device interface */

	struct usb_device_descriptor descriptor;/* Descriptor */
	struct usb_host_config *config;	/* All of the configs */

	struct usb_host_config *actconfig;/* the active configuration */
	struct usb_host_endpoint *ep_in[16];
	struct usb_host_endpoint *ep_out[16];

	char **rawdescriptors;		/* Raw descriptors for each config */

	int have_langid;		/* whether string_langid is valid yet */
	int string_langid;		/* language ID for strings */

	struct list_head filelist;
	struct dentry *usbfs_dentry;	/* usbfs dentry entry for the device */

	/*
	 * Child devices - these can be either new devices
	 * (if this is a hub device), or different instances
	 * of this same device.
	 *
	 * Each instance needs its own set of data structures.
	 */

	int maxchild;			/* Number of ports if hub */
	struct usb_device *children[USB_MAXCHILDREN];
};
#define	to_usb_device(d) container_of(d, struct usb_device, dev)

extern struct usb_device *usb_get_dev(struct usb_device *dev);
extern void usb_put_dev(struct usb_device *dev);

extern void usb_lock_device(struct usb_device *udev);
extern int usb_trylock_device(struct usb_device *udev);
extern int usb_lock_device_for_reset(struct usb_device *udev,
		struct usb_interface *iface);
extern void usb_unlock_device(struct usb_device *udev);

/* USB port reset for device reinitialization */
extern int usb_reset_device(struct usb_device *dev);

extern struct usb_device *usb_find_device(u16 vendor_id, u16 product_id);

/*-------------------------------------------------------------------------*/

/* for drivers using iso endpoints */
extern int usb_get_current_frame_number (struct usb_device *usb_dev);

/* used these for multi-interface device registration */
extern int usb_driver_claim_interface(struct usb_driver *driver,
			struct usb_interface *iface, void* priv);

/**
 * usb_interface_claimed - returns true iff an interface is claimed
 * @iface: the interface being checked
 *
 * Returns true (nonzero) iff the interface is claimed, else false (zero).
 * Callers must own the driver model's usb bus readlock.  So driver
 * probe() entries don't need extra locking, but other call contexts
 * may need to explicitly claim that lock.
 *
 */
static inline int usb_interface_claimed(struct usb_interface *iface) {
	return (iface->dev.driver != NULL);
}

extern void usb_driver_release_interface(struct usb_driver *driver,
			struct usb_interface *iface);
const struct usb_device_id *usb_match_id(struct usb_interface *interface,
					 const struct usb_device_id *id);

extern struct usb_interface *usb_find_interface(struct usb_driver *drv,
		int minor);
extern struct usb_interface *usb_ifnum_to_if(struct usb_device *dev,
		unsigned ifnum);
extern struct usb_host_interface *usb_altnum_to_altsetting(
		struct usb_interface *intf, unsigned int altnum);


/**
 * usb_make_path - returns stable device path in the usb tree
 * @dev: the device whose path is being constructed
 * @buf: where to put the string
 * @size: how big is "buf"?
 *
 * Returns length of the string (> 0) or negative if size was too small.
 *
 * This identifier is intended to be "stable", reflecting physical paths in
 * hardware such as physical bus addresses for host controllers or ports on
 * USB hubs.  That makes it stay the same until systems are physically
 * reconfigured, by re-cabling a tree of USB devices or by moving USB host
 * controllers.  Adding and removing devices, including virtual root hubs
 * in host controller driver modules, does not change these path identifers;
 * neither does rebooting or re-enumerating.  These are more useful identifiers
 * than changeable ("unstable") ones like bus numbers or device addresses.
 *
 * With a partial exception for devices connected to USB 2.0 root hubs, these
 * identifiers are also predictable.  So long as the device tree isn't changed,
 * plugging any USB device into a given hub port always gives it the same path.
 * Because of the use of "companion" controllers, devices connected to ports on
 * USB 2.0 root hubs (EHCI host controllers) will get one path ID if they are
 * high speed, and a different one if they are full or low speed.
 */
static inline int usb_make_path (struct usb_device *dev, char *buf, size_t size)
{
	int actual;
	actual = snprintf (buf, size, "usb-%s-%s", dev->bus->bus_name, dev->devpath);
	return (actual >= (int)size) ? -1 : actual;
}

/*-------------------------------------------------------------------------*/

#define USB_DEVICE_ID_MATCH_DEVICE		(USB_DEVICE_ID_MATCH_VENDOR | USB_DEVICE_ID_MATCH_PRODUCT)
#define USB_DEVICE_ID_MATCH_DEV_RANGE		(USB_DEVICE_ID_MATCH_DEV_LO | USB_DEVICE_ID_MATCH_DEV_HI)
#define USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION	(USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_DEV_RANGE)
#define USB_DEVICE_ID_MATCH_DEV_INFO \
	(USB_DEVICE_ID_MATCH_DEV_CLASS | USB_DEVICE_ID_MATCH_DEV_SUBCLASS | USB_DEVICE_ID_MATCH_DEV_PROTOCOL)
#define USB_DEVICE_ID_MATCH_INT_INFO \
	(USB_DEVICE_ID_MATCH_INT_CLASS | USB_DEVICE_ID_MATCH_INT_SUBCLASS | USB_DEVICE_ID_MATCH_INT_PROTOCOL)

/**
 * USB_DEVICE - macro used to describe a specific usb device
 * @vend: the 16 bit USB Vendor ID
 * @prod: the 16 bit USB Product ID
 *
 * This macro is used to create a struct usb_device_id that matches a
 * specific device.
 */
/**
 * 创建一个usb_device_id结构体，仅和指定的制造商和产品ID值相匹配。该宏常用于需要一个特定驱动程序的USB设备。
 */
#define USB_DEVICE(vend,prod) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE, .idVendor = (vend), .idProduct = (prod)
/**
 * USB_DEVICE_VER - macro used to describe a specific usb device with a version range
 * @vend: the 16 bit USB Vendor ID
 * @prod: the 16 bit USB Product ID
 * @lo: the bcdDevice_lo value
 * @hi: the bcdDevice_hi value
 *
 * This macro is used to create a struct usb_device_id that matches a
 * specific device, with a version range.
 */
/**
 * 创建一个usb_device_id结构体，仅和某版本范围内的指定制造商和产品ID值相匹配。
 */
#define USB_DEVICE_VER(vend,prod,lo,hi) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION, .idVendor = (vend), .idProduct = (prod), .bcdDevice_lo = (lo), .bcdDevice_hi = (hi)

/**
 * USB_DEVICE_INFO - macro used to describe a class of usb devices
 * @cl: bDeviceClass value
 * @sc: bDeviceSubClass value
 * @pr: bDeviceProtocol value
 *
 * This macro is used to create a struct usb_device_id that matches a
 * specific class of devices.
 */
/**
 * 创建一个usb_device_id结构体，仅和USB设备的指定类型相匹配。
 */
#define USB_DEVICE_INFO(cl,sc,pr) \
	.match_flags = USB_DEVICE_ID_MATCH_DEV_INFO, .bDeviceClass = (cl), .bDeviceSubClass = (sc), .bDeviceProtocol = (pr)

/**
 * USB_INTERFACE_INFO - macro used to describe a class of usb interfaces 
 * @cl: bInterfaceClass value
 * @sc: bInterfaceSubClass value
 * @pr: bInterfaceProtocol value
 *
 * This macro is used to create a struct usb_device_id that matches a
 * specific class of interfaces.
 */
/**
 * 创建一个usb_device_id结构体，仅和USB接口的指定类型相匹配。
 */
#define USB_INTERFACE_INFO(cl,sc,pr) \
	.match_flags = USB_DEVICE_ID_MATCH_INT_INFO, .bInterfaceClass = (cl), .bInterfaceSubClass = (sc), .bInterfaceProtocol = (pr)

/* -------------------------------------------------------------------------- */

/**
 * struct usb_driver - identifies USB driver to usbcore
 * @owner: Pointer to the module owner of this driver; initialize
 *	it using THIS_MODULE.
 * @name: The driver name should be unique among USB drivers,
 *	and should normally be the same as the module name.
 * @probe: Called to see if the driver is willing to manage a particular
 *	interface on a device.  If it is, probe returns zero and uses
 *	dev_set_drvdata() to associate driver-specific data with the
 *	interface.  It may also use usb_set_interface() to specify the
 *	appropriate altsetting.  If unwilling to manage the interface,
 *	return a negative errno value.
 * @disconnect: Called when the interface is no longer accessible, usually
 *	because its device has been (or is being) disconnected or the
 *	driver module is being unloaded.
 * @ioctl: Used for drivers that want to talk to userspace through
 *	the "usbfs" filesystem.  This lets devices provide ways to
 *	expose information to user space regardless of where they
 *	do (or don't) show up otherwise in the filesystem.
 * @suspend: Called when the device is going to be suspended by the system.
 * @resume: Called when the device is being resumed by the system.
 * @id_table: USB drivers use ID table to support hotplugging.
 *	Export this with MODULE_DEVICE_TABLE(usb,...).  This must be set
 *	or your driver's probe function will never get called.
 * @driver: the driver model core driver structure.
 *
 * USB drivers must provide a name, probe() and disconnect() methods,
 * and an id_table.  Other driver fields are optional.
 *
 * The id_table is used in hotplugging.  It holds a set of descriptors,
 * and specialized data may be associated with each entry.  That table
 * is used by both user and kernel mode hotplugging support.
 *
 * The probe() and disconnect() methods are called in a context where
 * they can sleep, but they should avoid abusing the privilege.  Most
 * work to connect to a device should be done when the device is opened,
 * and undone at the last close.  The disconnect code needs to address
 * concurrency issues with respect to open() and close() methods, as
 * well as forcing all pending I/O requests to complete (by unlinking
 * them as necessary, and blocking until the unlinks complete).
 */
/**
 * USB设备驱动。由驱动设置，向USB核心代码描述USB驱动程序。
 */
struct usb_driver {
	/**
	 * 指向该驱动程序的模块所有者指针。
	 */
	struct module *owner;

	/**
	 * 指向驱动程序名字的指针。在内核的所有USB驱动程序中它必须是唯一的。
	 * 通常被设置为和驱动程序模块名字相同的名字。
	 */
	const char *name;

	/**
	 * 指向USB驱动程序的探测函数的指针。当USB核心认为它有一个struct usb_interface可以由该驱动程序处理时，它将调用该函数。
	 * USB核心用来作判断的指向struct usb_device_id的指针也被传递给该函数。
	 * 如果USB驱动程序确认传递给它的struct usb_interface，它应该初始化设备然后返回0，否则应该返回一个负值。
	 */
	int (*probe) (struct usb_interface *intf,
		      const struct usb_device_id *id);

	/**
	 * 指向USB驱动程序中的断开函数的指针。当struct usb_interface被从系统中移除或者驱动程序正在从USB核心中卸载时，USB核心将调用该函数。
	 */
	void (*disconnect) (struct usb_interface *intf);

	/**
	 * 指向USB驱动程序中的ioctl函数。如果该函数存在，当用户空间的程序对usbfs文件系统中的设备文件进行了ioctl调用，而和该设备文件相关联的USB设备在该USB驱动程序上时，它将被调用。
	 * 实际上，只有USB集线器驱动程序使用该ioctl。
	 */
	int (*ioctl) (struct usb_interface *intf, unsigned int code, void *buf);

	/**
	 * 指向USB驱动程序中的挂起函数的指针。当设备被USB核心挂起时调用该函数。
	 */
	int (*suspend) (struct usb_interface *intf, u32 state);
	/**
	 * 指向USB驱动程序中的恢复函数的指针。当设备将被USB核心恢复时调用该函数。
	 */
	int (*resume) (struct usb_interface *intf);

	/**
	 * 指向struct usb_device_id表的指针，该表包含了一列该驱动程序可以支持的所有不同类型的USB设备。
	 * 如果没有设置该变量，USB驱动程序中的探测回调函数不会被调用。
	 */
	const struct usb_device_id *id_table;

	struct device_driver driver;
};
#define	to_usb_driver(d) container_of(d, struct usb_driver, driver)

extern struct bus_type usb_bus_type;

/**
 * struct usb_class_driver - identifies a USB driver that wants to use the USB major number
 * @name: devfs name for this driver.  Will also be used by the driver
 *	class code to create a usb class device.
 * @fops: pointer to the struct file_operations of this driver.
 * @mode: the mode for the devfs file to be created for this driver.
 * @minor_base: the start of the minor range for this driver.
 *
 * This structure is used for the usb_register_dev() and
 * usb_unregister_dev() functions, to consolidate a number of the
 * parameters used for them.
 */
/**
 * USB设备所属类别。
 */
struct usb_class_driver {
	/**
	 * sysfs用来描述设备的名字。如果需要包含设备编号，需要在字符串中包含字符%d。
	 */
	char *name;
	/**
	 * 使用它来将USB设备注册为一个字符设备。
	 */
	struct file_operations *fops;
	/**
	 * 为该驱动程序创建的devfs文件的模式。典型设置是S_IRUSR和S_IWUSR值的组合。
	 */
	mode_t mode;
	/**
	 * 这是为该驱动程序指派的次设备号范围的开始值。
	 */
	int minor_base;	
};

/*
 * use these in module_init()/module_exit()
 * and don't forget MODULE_DEVICE_TABLE(usb, ...)
 */
extern int usb_register(struct usb_driver *);
extern void usb_deregister(struct usb_driver *);

extern int usb_register_dev(struct usb_interface *intf,
			    struct usb_class_driver *class_driver);
extern void usb_deregister_dev(struct usb_interface *intf,
			       struct usb_class_driver *class_driver);

extern int usb_disabled(void);

/* -------------------------------------------------------------------------- */

/*
 * URB support, for asynchronous request completions
 */

/*
 * urb->transfer_flags:
 */
/**
 * 如果被设置，说明任何发生的对IN端点的简短读取应该被USB核心当作是一个错误。
 * 该值只对从USB设备读取的urb有用，对用于写入的urb没有意义。
 */
#define URB_SHORT_NOT_OK	0x0001	/* report short reads as errors */
/**
 * 如果该urb是等时的，当驱动程序想要该urb被调度时可以设置这个位。只要带宽允许它这么做，而且想要在此时设置urb的start_frame变量。
 * 如果一个等时的urb没有设置该位，驱动程序必须指定start_frame的值。如果传输在当时不能启动的话，必有能够正确的恢复。
 */
#define URB_ISO_ASAP		0x0002	/* iso-only, urb->start_frame ignored */
/**
 * 当urb包含一个即将传输的DMA缓冲区时应该设置该闰。USB核心使用transfer_data变量所指向的缓冲区，而不是transfer_buffer变量所指向的。
 */
#define URB_NO_TRANSFER_DMA_MAP	0x0004	/* urb->transfer_dma valid on submit */
/**
 * 和URB_NO_TRANSFER_DMA_MAP位类似，该位用于控制带有已设置好的DMA缓冲区的urb。如果它被设置，USB核心使用setup_dma变量所指向的缓冲区。而不是set_packet变量。
 */
#define URB_NO_SETUP_DMA_MAP	0x0008	/* urb->setup_dma valid on submit */
/**
 * 如果被设置，对该urb的usb_unlink_urb调用几乎立即返回。该urb的链接在后台被解开。
 * 否则，此函数一直等到urb被完全解开链接和结束才返回。使用该位时要小心，因为它可能会造成非常难以调试的同步问题。
 */
#define URB_ASYNC_UNLINK	0x0010	/* usb_unlink_urb() returns asap */
/**
 * 仅由UHCI USB主控制器驱动程序使用，指示它不要企图使用前端总线回收逻辑。该位通常不应该被设置，因为带有UHCI主控制器的机器会导致大量的CPU负载，而PCI总线忙于等待一个设置了该位的urb。
 */
#define URB_NO_FSBR		0x0020	/* UHCI-specific */
/**
 * 如果被设置，一个批量输出urb以发送一个不包含数据的小数据包来结束。这时数据对齐到一个端点数据包边界。一些断线的USB设备需要该位才能正确的工作。
 */
#define URB_ZERO_PACKET		0x0040	/* Finish bulk OUTs with short packet */
/**
 * 如果被设置，当urb结束时，硬件可能不会产生一个中断。对该位的使用应当小心谨慎，只有把多个urb排队到同一个端点时才使用。
 * USB核心的函数使用该位来进行DMA缓冲区传输。
 */
#define URB_NO_INTERRUPT	0x0080	/* HINT: no non-error interrupt needed */

struct usb_iso_packet_descriptor {
	/**
	 * 该数据包的数据在传输缓冲区中的偏移量(第一个字节为0)
	 */
	unsigned int offset;
	/**
	 * 该数据包的传输缓冲区大小。
	 */
	unsigned int length;		/* expected length */
	/**
	 * 该等时数据包接收到传输缓冲区中的数据长度。
	 */
	unsigned int actual_length;
	/**
	 * 该数据包的单个等时传输的状态。它可以把相同的返回值作为urb结构体的状态变量。
	 */
	unsigned int status;
};

struct urb;
struct pt_regs;

typedef void (*usb_complete_t)(struct urb *, struct pt_regs *);

/**
 * struct urb - USB Request Block
 * @urb_list: For use by current owner of the URB.
 * @pipe: Holds endpoint number, direction, type, and more.
 *	Create these values with the eight macros available;
 *	usb_{snd,rcv}TYPEpipe(dev,endpoint), where the TYPE is "ctrl"
 *	(control), "bulk", "int" (interrupt), or "iso" (isochronous).
 *	For example usb_sndbulkpipe() or usb_rcvintpipe().  Endpoint
 *	numbers range from zero to fifteen.  Note that "in" endpoint two
 *	is a different endpoint (and pipe) from "out" endpoint two.
 *	The current configuration controls the existence, type, and
 *	maximum packet size of any given endpoint.
 * @dev: Identifies the USB device to perform the request.
 * @status: This is read in non-iso completion functions to get the
 *	status of the particular request.  ISO requests only use it
 *	to tell whether the URB was unlinked; detailed status for
 *	each frame is in the fields of the iso_frame-desc.
 * @transfer_flags: A variety of flags may be used to affect how URB
 *	submission, unlinking, or operation are handled.  Different
 *	kinds of URB can use different flags.
 * @transfer_buffer:  This identifies the buffer to (or from) which
 * 	the I/O request will be performed (unless URB_NO_TRANSFER_DMA_MAP
 *	is set).  This buffer must be suitable for DMA; allocate it with
 *	kmalloc() or equivalent.  For transfers to "in" endpoints, contents
 *	of this buffer will be modified.  This buffer is used for the data
 *	stage of control transfers.
 * @transfer_dma: When transfer_flags includes URB_NO_TRANSFER_DMA_MAP,
 *	the device driver is saying that it provided this DMA address,
 *	which the host controller driver should use in preference to the
 *	transfer_buffer.
 * @transfer_buffer_length: How big is transfer_buffer.  The transfer may
 *	be broken up into chunks according to the current maximum packet
 *	size for the endpoint, which is a function of the configuration
 *	and is encoded in the pipe.  When the length is zero, neither
 *	transfer_buffer nor transfer_dma is used.
 * @actual_length: This is read in non-iso completion functions, and
 *	it tells how many bytes (out of transfer_buffer_length) were
 *	transfe