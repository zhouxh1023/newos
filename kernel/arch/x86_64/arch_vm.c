/*
** Copyright 2001-2004, Travis Geiselbrecht. All rights reserved.
** Distributed under the terms of the NewOS License.
*/
#include <kernel/kernel.h>
#include <kernel/console.h>
#include <kernel/vm.h>
#include <kernel/vm_page.h>
#include <kernel/vm_priv.h>
#include <kernel/debug.h>

#include <kernel/arch/vm.h>
#include <kernel/arch/int.h>
#include <kernel/arch/cpu.h>

#include <kernel/arch/x86_64/interrupts.h>

int arch_vm_init(kernel_args *ka)
{
	dprintf("arch_vm_init: entry\n");
	return 0;
}

int arch_vm_init2(kernel_args *ka)
{
	dprintf("arch_vm_init2: entry\n");

	// account for DMA area and mark the pages unusable
	vm_mark_page_range_inuse(0x0, 0xa0000 / PAGE_SIZE);

	return 0;
}

int arch_vm_init_existing_maps(kernel_args *ka)
{
	return 0;
}

int arch_vm_init_endvm(kernel_args *ka)
{
	region_id id;
	void *ptr;

	dprintf("arch_vm_init_endvm: entry\n");

	// map 0 - 0xa0000 directly
	id = vm_map_physical_memory(vm_get_kernel_aspace_id(), "dma_region", &ptr,
		REGION_ADDR_ANY_ADDRESS, 0xa0000, LOCK_RW|LOCK_KERNEL, 0x0);
	if(id < 0) {
		panic("arch_vm_init_endvm: unable to map dma region\n");
		return ERR_NO_MEMORY;
	}
	return 0;
}

void arch_vm_aspace_swap(vm_address_space *aspace)
{
	x86_64_swap_pgdir(vm_translation_map_get_pgdir(&aspace->translation_map));
}


