#pragma once

void* operator new(size_t size);
void* operator new(size_t size, const char* pathname, int line);
void* operator new[](size_t size);
void* operator new[](size_t size, const char* pathname, int line);
void  operator delete(void* address);
void  operator delete(void* address, const char* pathname, int line);
void  operator delete[](void* address);
void  operator delete[](void* address, const char* pathname, int line);