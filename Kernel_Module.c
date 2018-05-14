/*
 * 
 *
 *  Created on: Aug 31, 2016
 *      Author: Zhentao Xie
 */

#ifndef MODULE
#define MODULE
#endif

#ifndef __KERNEL__
#define __KERNEL__
#endif

#include<linux/module.h>
#include<linux/kernel.h>
#include<rtai.h>
#include<rtai_lxrt.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
	unsigned long *PBDR,*PBDDR;  //create pointer to port B DR/DDR
	unsigned long *ptr;
	ptr = (unsigned long*)__ioremap(0x80840000,4096,0);
    /*if(ptr == MAP_FAILED){
        printf("\n Unable to map memory space \n");
        return(-2);
    }  // failed mmap*/
	PBDR = ptr+1;
	PBDDR = ptr+5;
	*PBDDR = 0xE0;  // give LEDs output, pbddr 11100000
    printk("Turn on bit5 and bit6 LEDs\n");
    *PBDR |= 0x60; //Turn on bit5 and bit6 LEDs
    printk("PBDR on is %lu\n",*PBDR);

	return 0;
}

void cleanup_module(void)
{
    unsigned long *PBDR,*PBDDR;  //create pointer to port B DR/DDR
    unsigned long *ptr;
    ptr = (unsigned long*)__ioremap(0x80840000,4096,0);
    /*if(ptr == MAP_FAILED){
        printf("\n Unable to map memory space \n");
        return;
    }  // failed mmap*/
    PBDR = ptr+1;
    PBDDR = ptr+5;
    *PBDDR = 0xE0;  // give LEDs output, pbddr 11100000
    printk("Turn off bit5 and bit6 LEDs\n");
    *PBDR &= 0x9F; //Turn on bit6 and bit7 LEDs
    printk("PBDR off is %lu\n",*PBDR);


}
