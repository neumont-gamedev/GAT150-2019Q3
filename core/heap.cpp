#include "heap.h"
#include "assert.h"
#include "types.h"

#include <new>
#include <iostream>
#include <iomanip>

#define MEMORY_SIGNATURE 0xDEADC0DE

heap::~heap()
{
	//ASSERT_MSG(m_allocations == 0, "memory leak.");
	if (m_allocations)
	{
		report();
	}
}

void* heap::allocate(size_t size)
{
	size_t total_size = size + sizeof(alloc_header);
	u8* memory = static_cast<u8*>(malloc(total_size));
	alloc_header* header = (alloc_header*)(memory);
	header->size = size;
	header->signature = MEMORY_SIGNATURE;
	header->next = m_alloc_head;
	header->prev = nullptr;

	if (m_alloc_head != nullptr)
	{
		m_alloc_head->prev = header;
	}
	m_alloc_head = header;

	m_allocated += size;
	m_allocated_total += size;
	if (m_allocated > m_allocated_peak) m_allocated_peak = m_allocated;
	m_allocations++;
	m_allocations_total++;

	void* ptr = memory + sizeof(alloc_header);

	return ptr;
}

void* heap::allocate(size_t size, const char* filename, int line)
{
	size_t total_size = size + sizeof(alloc_header);
	u8* memory = static_cast<u8*>(malloc(total_size));
	alloc_header* header = (alloc_header*)(memory);
	header->size = size;
	strcpy_s(header->file, 32, filename);
	header->line = line;
	header->signature = MEMORY_SIGNATURE;
	header->next = m_alloc_head;
	header->prev = nullptr;

	if (m_alloc_head != nullptr)
	{
		m_alloc_head->prev = header;
	}
	m_alloc_head = header;

	m_allocated += size;
	m_allocated_total += size;
	if (m_allocated > m_allocated_peak) m_allocated_peak = m_allocated;
	m_allocations++;
	m_allocations_total++;

	void* ptr = memory + sizeof(alloc_header);

	return ptr;
}

void heap::free(void* ptr)
{
	alloc_header* header = (alloc_header*)((u8*)ptr - sizeof(alloc_header));
	ASSERT(header->signature == MEMORY_SIGNATURE);

	free(header);
}

void heap::report()
{
	std::cout << "MEMORY REPORT:\n";
	
	std::cout << std::left << std::setw(25) << "allocated (bytes): " << std::right << std::setw(10)  << m_allocated << std::endl;
	std::cout << std::left << std::setw(25) << "allocated total (bytes): " << std::right << std::setw(10) << m_allocated_total << std::endl;
	std::cout << std::left << std::setw(25) << "allocated peak (bytes): " << std::right << std::setw(10) << m_allocated_peak << std::endl;

	std::cout << std::left << std::setw(25) << "allocations: " << std::right << std::setw(10) << m_allocations << std::endl;
	std::cout << std::left << std::setw(25) << "allocations total: " << std::right << std::setw(10) << m_allocations_total << std::endl;
	
	alloc_header* header = m_alloc_head;
	std::cout << "|" << std::right << std::setw(25) << "allocation |" << std::setw(25) << "file |" << std::setw(25) << "line|\n";
	while (header)
	{
		//std::cout << header->size << std::endl;
		std::cout << "allocation: " << header->size << " " << std::dec << " - " << header->file << "(" << header->line << ")" << std::endl;

		header = header->next;
	}
}

void heap::free(alloc_header* header)
{
	if (header->prev == nullptr)
	{
		ASSERT(header == m_alloc_head);
		m_alloc_head = header->next;
	}
	else
	{
		header->prev->next = header->next;
	}

	if (header->next != nullptr)
	{
		header->next->prev = header->prev;
	}

	m_allocated -= header->size;
	m_allocations--;

	::free(header);
}
