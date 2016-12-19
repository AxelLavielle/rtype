#include	"ACommand.hh"

ACommand::ACommand()
{
	_cmdType = EMPTY_TYPE;
	_cmdName = EMPTY_NAME;
	_arg = "";
	_separator = '|';
}

ACommand::~ACommand()
{

}

CmdName ACommand::getCommandName() const
{
	return (_cmdName);
}

const std::string ACommand::getCommandArg() const
{
	return (_arg);
}

void ACommand::setCommandArg(const std::string & arg)
{
	_arg = arg;
}

void ACommand::setCommandType(CmdType type)
{
	_cmdType = type;
}

CmdType ACommand::getCommandType() const
{
	return (_cmdType);
}
