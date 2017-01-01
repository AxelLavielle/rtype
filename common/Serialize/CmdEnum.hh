#pragma once

enum		CmdType
  {
    REPLY_CODE,
    HANDSHAKE_SYN,
    HANDSHAKE_SYN_ACK,
    HANDSHAKE_ACK,
    GET_ROOM_LIST,
    CREATE_ROOM,
    LEAVE_ROOM,
    JOIN_ROOM,
    GET_ROOM,
    SET_STATUS,
    RENAME_ROOM,
	QUIT_GAME,
    ALIVE,
    UPDATE_ROOM,
    LAUNCH_GAME,
    EMPTY_TYPE
  };

enum		CmdName
  {
    CHAT_INFO,
    ROOM_INFO,
    ROOM_LIST,
    ENTITY,
    INPUT_CMD,
    BASIC_CMD,
	END_GAME,
    EMPTY_NAME
  };

typedef enum	ReplyCodes
{
	BUSY = 120,
	UNDERSTOOD = 200,
	CHAT_MSG_SENT = 201,
	IS_ALIVE = 220,
	STATUS_CHANGED = 221,
	PLAYER_RECONNECT_SUCCESS = 230,
	ROOM_JOINED = 231,
	LEFT_ROOM = 232,
	ROOM_CREATED = 260,
	ROOM_NAME_CHANGED = 261,
	NOT_IN_LOBBY = 450,
	NOT_IN_ROOM = 451,
	ROOM_FULL = 452,
	ROOM_NOT_EXIST = 530
}				ReplyCodes;