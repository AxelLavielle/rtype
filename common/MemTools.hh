#pragma once

#include <cstring>

class MemTools
{
public:
  static void	copy(void *, const void *, size_t);
  static void	set(void *, int, size_t);
  static int	cmp(const void *, const void *, size_t);
};
