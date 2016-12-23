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
