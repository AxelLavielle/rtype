#pragma once

enum		CmdType
  {
    REPLYCODE,
    CMDNAME,
    CMDARG,
	SYN,
	ACK,
    EMPTYTYPE
  };

enum		CmdName
  {
    CHATINFO,
    ROOMINFO,
    ROOMLIST,
    ENTITY,
    INPUTCMD,
	BASICCMD,
    EMPTYNAME
  };
