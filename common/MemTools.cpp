#include "MemTools.hh"

void MemTools::copy(void *dest, const void *src, size_t n)
{
  memcpy(dest, src, n);
}

void MemTools::set(void *s, int c, size_t n)
{
  memset(s, c, n);
}

int MemTools::cmp(const void *s1, const void *s2, size_t n)
{
	return (memcmp(s1, s2, n));
}