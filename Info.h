#pragma once

enum StuffCode
{
	STUFF_NONE,
	STUFF_BOARDBLOCK,
	STUFF_BOX1,
	STUFF_BRICK,
	STUFF_BRICKPILE,

	STUFF_CHEST2,
	STUFF_CHEST3,
	STUFF_CROWBAR,
	STUFF_DOOR1,
	STUFF_EMPTYBOX,
	STUFF_KEY1,
	STUFF_KEY2,
	STUFF_KEY3,
	STUFF_KEY4,
	STUFF_KEY5,
	STUFF_PAPER1,
	STUFF_PAPER2,
	STUFF_PAPER3,
	STUFF_POSTER1,
	STUFF_POSTER2,
	STUFF_POSTER3,
	STUFF_POSTER4,
	STUFF_TRAP,
	STUFF_VALVE1,
	STUFF_VALVE2,
	STUFF_WOOD1,
	STUFF_WOOD2,
	STUFF_WOOD3,
	STUFF_WOODBOARD1,
	STUFF_WOODBOARD2
};

enum SwitchInfo
{
	SWITCH_BASEMENT_BOX1,
	SWITCH_BASEMENT_CHEST,
	SWITCH_FIRSTFLOOR_TRAP,
	SWITCH_FIRSTFLOOR_WOODBOARD1,
	SWITCH_FIRSTFLOOR_WOODBOARD2,
	SWITCH_FIRSTFLOOR_BLOCK,
	SWITCH_SECONDFLOOR_VALVE1,
	SWITCH_SECONDFLOOR_VALVE2,
	SWITCH_LASTNUM
};

enum eLIGHT
{
	//s = Spot, d = Direction, p = Point
	D_MAIN_LIGHT,
	D_DARK,
	S_CHARACTERSELECT_PLAYER1,
	S_CHARACTERSELECT_PLAYER2,
};

enum eUITAG
{
	EMPTY,

	E_CHARACTERSELECT_IMAGE_BACKGROUND,
	E_CHARACTERSELECT_IMAGE_EXPLAIN,
	E_CHARACTERSELECT_IMAGE_PLAYER1FACE,
	E_CHARACTERSELECT_IMAGE_PLAYER2FACE,
	E_CHARACTERSELECT_IMAGE_PLAYER1TEXT,
	E_CHARACTERSELECT_IMAGE_PLAYER2TEXT,
	E_CHARACTERSELECT_IMAGE_GAMESTART1,
	E_CHARACTERSELECT_IMAGE_GAMESTART2,
	E_CHARACTERSELECT_IMAGE_GAMESTART3,
	E_CHARACTERSELECT_IMAGE_GAMESTART4,
	E_CHARACTERSELECT_IMAGE_GAMESTART5,
	E_CHARACTERSELECT_IMAGE_GAMESTART6,

	E_CHARACTERSELECT_BUTTON_START,

	E_CHARACTERSELECT_MESH_PLAYER1,
	E_CHARACTERSELECT_MESH_PLAYER2,

	E_CHARACTERSELECT_LIGHT_PLAYER1,
	E_CHARACTERSELECT_LIGHT_PLAYER2,

	E_CHARACTERSELECT_TEXT_EXPLAIN,
	E_CHARACTERSELECT_TEXT_GAMESTART,

	//------------------------------
	INVENTORY_IMAGE_BACKGROUND,
	INVENTORY_IMAGE_MAINUPLINE,

	INVENTORY_1,
	INVENTORY_2,
	INVENTORY_3,
	INVENTORY_4,
	INVENTORY_5,
	INVENTORY_6,
	INVENTORY_7,
	INVENTORY_8,
	INVENTORY_9,
	INVENTORY_10,
	INVENTORY_11,
	INVENTORY_12,
	INVENTORY_13,
	INVENTORY_14,
	INVENTORY_15,
	INVENTORY_16,
	INVENTORY_17,
	INVENTORY_18,
	INVENTORY_19,
	INVENTORY_20,
	INVENTORY_21,

	INVENTORY_COMBINE_1,
	INVENTORY_COMBINE_2,
	INVENTORY_COMBINE_3,
	INVENTORY_USINGITEM,
	INVENTORY_GABAGE,

	INVENTORY_BUTTON_COMBINE,
	INVENTORY_TEXT_COMBINE,

	CHAT_TEXT1,
};


enum eITEMTYPE
{
	ITEMTYPE_NONE,
	ITEMTYPE_KEY,
	ITEMTYPE_THROW,
	ITEMTYPE_COMBINE,
	ITEMTYPE_NORMAL,
};

struct ITEMINFO
{
	LPDIRECT3DTEXTURE9		Texture;
	eITEMTYPE				ItemType;
	RECT					rc;
};

struct CHATINFO
{
	float		time;
	float		alpha;
	string		strChat;
};

#define CHATSIZE			5
#define CHATTIME			300
#define CHATWORDHEIGHT		30
#define CHATWORDWIDTH		(CHATWORDHEIGHT / 2)

enum animationState
{
	ANIM_IDLE,
	ANIM_WALK,
	ANIM_ATTACK,
	ANIM_DEATH,
};