#ifndef LOADER_H
#define LOADER_H

#include "../../../libwiiu/src/types.h"
#include "../../../libwiiu/src/coreinit.h"
#include "../../../libwiiu/src/socket.h"

/* Wait times for CPU0 and CPU2 */
#define CPU0_WAIT_TIME		80
#define CPU2_WAIT_TIME		92

/* Gadget finding addresses */
#define JIT_ADDRESS			        0x01800000
#if VER == 300
	#define CODE_ADDRESS_START		0x0E000000
	#define CODE_ADDRESS_END		0x10000000
#else
	#define CODE_ADDRESS_START		0x0D800000
	#define CODE_ADDRESS_END		0x0F848A0C
#endif

/* Kernel addresses, for each new kernel */
#if VER == 200
	#define KERN_SYSCALL_TBL		0x0
	#define KERN_CODE_READ			0x0
	#define KERN_CODE_WRITE			0x0
	#define KERN_ADDRESS_TBL		0x0
	#define KERN_HEAP				0x0
#elif VER == 210
	#define KERN_SYSCALL_TBL		0x0
	#define KERN_CODE_READ			0x0
	#define KERN_CODE_WRITE			0x0
	#define KERN_ADDRESS_TBL		0x0
	#define KERN_HEAP				0x0
#elif VER == 300
	#define KERN_SYSCALL_TBL		0xFFE85950
	#define KERN_CODE_READ			0xFFF02214
	#define KERN_CODE_WRITE			0xFFF02234
	#define KERN_ADDRESS_TBL		0xFFEB66E4
	#define KERN_HEAP				0xFF200000
#elif VER == 310
	#define KERN_SYSCALL_TBL		0x0
	#define KERN_CODE_READ			0x0
	#define KERN_CODE_WRITE			0x0
	#define KERN_ADDRESS_TBL		0x0
	#define KERN_HEAP				0x0
#elif VER == 400
	#define KERN_SYSCALL_TBL		0x0
	#define KERN_CODE_READ			0x0
	#define KERN_CODE_WRITE			0x0
	#define KERN_ADDRESS_TBL		0x0
	#define KERN_HEAP				0x0
#elif VER == 410
	#define KERN_SYSCALL_TBL		0xffe85890
	#define KERN_CODE_READ			0xfff02214
	#define KERN_CODE_WRITE			0xfff02234
	#define KERN_ADDRESS_TBL		0xffeb902c
	#define KERN_HEAP				0xFF200000
#elif VER == 500
	#define KERN_SYSCALL_TBL		0xffea9520
	#define KERN_CODE_READ			0xfff021f4
	#define KERN_CODE_WRITE			0xfff02214
	#define KERN_ADDRESS_TBL		0xffea9e4c
	#define KERN_HEAP				0xFF200000
#elif VER == 532
	#define KERN_SYSCALL_TBL		0xFFEAA0E0
	#define KERN_CODE_READ			0xFFF02274
	#define KERN_CODE_WRITE			0xFFF02294
	#define KERN_ADDRESS_TBL		0xFFEAAA10
	#define KERN_HEAP				0xFF200000
#else
#error "Unsupported Wii U software version"
#endif

/* Browser PFID */
#define PFID_BROWSER				8

/* Size of a Cafe OS thread */
#define OSTHREAD_SIZE	0x1000

void _start();

void _entryPoint();

/* Find a ROP gadget by a sequence of bytes */
void *find_gadget(uint32_t code[], uint32_t length, uint32_t gadgets_start);

/* Arbitrary read and write syscalls */
uint32_t kern_read(const void *addr);
void kern_write(void *addr, uint32_t value);

#endif /* LOADER_H */