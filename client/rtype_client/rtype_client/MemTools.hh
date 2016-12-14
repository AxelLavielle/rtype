#pragma once

class		MemTools
{
public:
  MemTools();
  ~MemTools();

  void		*set(void *, int, size_t);
  void		*copy(void *, const void *, size_t);

private:
};
