#include "SocketAddress.hh"


SocketAddress::SocketAddress(struct in_addr addr)
{
	_addr = addr;
}

SocketAddress::~SocketAddress()
{
}

in_addr		SocketAddress::getAddr() const
{
	return (_addr);
}

bool		SocketAddress::operator==(const SocketAddress &other)
{
	if (MemTools::cmp(&_addr, &other, sizeof(struct in_addr)) == 0)
		return (true);
	return (false);
}
