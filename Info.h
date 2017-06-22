#pragma once

enum StuffCode
{
	STUFF_NONE,

	STUFF_CROWBAR,
	STUFF_PAPER1,
	STUFF_PAPER2,
	STUFF_PAPER3,
	STUFF_KEY1,
	STUFF_KEY2,
	STUFF_KEY3,
	STUFF_KEY4,
	STUFF_KEY5,
	STUFF_BRICK1,
	STUFF_BRICK2,
	STUFF_BRICK3,
	STUFF_BRICK4,
	STUFF_BRICK5,

	STUFF_BOARDBLOCK,
	STUFF_BOX1,
	STUFF_BRICK,
	STUFF_BRICKPILE,
	STUFF_CHEST2,
	STUFF_CHEST3,
	STUFF_EMPTYBOX,
	STUFF_TRAP,
	STUFF_VALVE1,
	STUFF_VALVE2,
	STUFF_WOOD1,
	STUFF_WOOD2,
	STUFF_WOOD3,
	STUFF_WOODBOARD1,
	STUFF_WOODBOARD2,
	STUFF_BUTTON1,
	STUFF_BUTTON2,
	STUFF_BUTTON3,
	STUFF_BUTTON4,

	STUFF_DOOR_PRISON,
	STUFF_DOOR_1STROOM,
	STUFF_DOOR_1STTOILET,
	STUFF_DOOR_2NDROOM1,
	STUFF_DOOR_2NDROOM2,
	STUFF_DOOR_FINAL,

	STUFF_LASTNUM,
};

enum SwitchInfo
{
	SWITCH_STARTNUM,

	SWITCH_ONMAP_CROWBAR,
	SWITCH_ONMAP_PAPER1,
	SWITCH_ONMAP_PAPER2,
	SWITCH_ONMAP_PAPER3,
	SWITCH_ONMAP_KEY1,
	SWITCH_ONMAP_KEY2,
	SWITCH_ONMAP_KEY3,
	SWITCH_ONMAP_KEY4,
	SWITCH_ONMAP_KEY5,
	SWITCH_ONMAP_BRICK1,
	SWITCH_ONMAP_BRICK2,
	SWITCH_ONMAP_BRICK3,
	SWITCH_ONMAP_BRICK4,
	SWITCH_ONMAP_BRICK5,

	SWITCH_BASEMENT_BOX1,
	SWITCH_BASEMENT_CHEST,
	SWITCH_FIRSTFLOOR_TRAP,
	SWITCH_FIRSTFLOOR_WOODBOARD1,
	SWITCH_FIRSTFLOOR_WOODBOARD2,
	SWITCH_FIRSTFLOOR_BLOCK,
	SWITCH_SECONDFLOOR_VALVE1,
	SWITCH_SECONDFLOOR_VALVE2,
	SWITCH_SECONDFLOOR_BUTTON1,
	SWITCH_SECONDFLOOR_BUTTON2,

	SWITCH_DOOR_PRISON,
	SWITCH_DOOR_1STROOM,
	SWITCH_DOOR_1STTOILET,
	SWITCH_DOOR_2NDROOM1,
	SWITCH_DOOR_2NDROOM2,
	SWITCH_DOOR_FINAL,

	SWITCH_LASTNUM
};
//<수정주의> StuffCode에 crowbar ~ brick5 의 넘버와 SwitchInfo의 crowbar ~ brick5 의 번호가 일치해야함


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

enum eButtonTag
{
	E_IP_OK,
	E_IP_RESET
};
enum eITEMTYPE
{
	ITEMTYPE_NONE,
	ITEMTYPE_KEY,
	ITEMTYPE_THROW,
	ITEMTYPE_COMBINE,
	ITEMTYPE_NORMAL,
	ITEMTYPE_ATTACK,
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
	int			gender;
};

#define CHATSIZE			30
#define CHATTIME			300
#define CHATWORDHEIGHT		30
#define CHATWORDWIDTH		(CHATWORDHEIGHT / 2)
#define TOTALINVENSIZE		25

enum animationState
{
	ANIM_IDLE,
	ANIM_WALK,
	ANIM_ATTACK,
	ANIM_DEATH,
};