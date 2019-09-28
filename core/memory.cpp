#include "memory.h"
#include "heap.h"
#include "assert.h"
#include "filesystem.h"

#include <iostream>

heap g_main_heap;

void* operator new(size_t size)
{
	return g_main_heap.allocate(size, "", 0);
}

void* operator new(size_t size, const char* pathname, int line)
{
	char filename[32];
	filesystem::get_filename(pathname, filename, 32);

	return g_main_heap.allocate(size, filename, line);
}

void* operator new[](size_t size)
{
	return g_main_heap.allocate(size, "", 0);
}

void* operator new[](size_t size, const char* pathname, int line)
{
	char filename[32];
	filesystem::get_filename(pathname, filename, 32);

	return g_main_heap.allocate(size, filename, line);
}

void operator delete(void* address)
{
	ASSERT_MSG(address != nullptr, "error: trying to delete null pointer");
	g_main_heap.free(address);
}

void operator delete(void* address, const char* pathname, int line)
{
	ASSERT_MSG(address != nullptr, "error: trying to delete null pointer");
	g_main_heap.free(address);
}

void operator delete[](void* address)
{
	ASSERT_MSG(address != nullptr, "error: trying to delete null pointer");
	g_main_heap.free(address);
}

void operator delete[](void* address, const char* pathname, int line)
{
	ASSERT_MSG(address != nullptr, "error: trying to delete null pointer");
	g_main_heap.free(address);
}