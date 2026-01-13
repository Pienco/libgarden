#pragma once

#include "../human/EmoticonName.hpp"
#include "../sv/SvFgName.hpp"
#include "../fgobj/PlaceType.hpp"

#include <nn/math/Vector.hpp>

struct PACKED PlayerAction
{
	#include "PlayerAction_Name.hpp"

	struct CompactBase
	{
		static constexpr float scale = 4.0f;
		static constexpr float invScale = 1.0f / scale;
	};

	struct PACKED CompactXZ : public CompactBase
	{
		constexpr CompactXZ() = default;
		explicit constexpr CompactXZ(const Vector3& vec)
			: vector {static_cast<s16>(vec[0] * scale), static_cast<s16>(vec[2] * scale)}
		{
		}

		constexpr void Set(const Vector3& vec)
		{
			vector = {static_cast<s16>(vec[0] * scale), static_cast<s16>(vec[2] * scale)};
		}

		constexpr Vector3 Get() const
		{
			return { GetX(), 0.0f, GetZ() };
		}

		float GetX() const { return vector[0] * invScale; }
		float GetZ() const { return vector[2] * invScale; }

		Vector2s16 vector;
	};
	ASSERT_SIZE(CompactXZ, 0x4);

	struct PACKED CompactXYZ : public CompactBase
	{
		constexpr CompactXYZ() = default;
		explicit constexpr CompactXYZ(const Vector3& pos)
			:  vector {static_cast<s16>(pos[0] * scale), static_cast<s16>(pos[1] * scale), static_cast<s16>(pos[2] * scale)}
		{
		}

		constexpr void Set(const Vector3& pos)
		{
			vector = {static_cast<s16>(pos[0] * scale), static_cast<s16>(pos[1] * scale), static_cast<s16>(pos[2] * scale)};
		}

		constexpr Vector3 Get() const
		{
			return {GetX(), GetY(), GetZ()};
		}

		float GetX() const { return vector[0] * invScale; }
		float GetY() const { return vector[1] * invScale; }
		float GetZ() const { return vector[2] * invScale; }

		Vector3s16 vector;
	};
	ASSERT_SIZE(CompactXYZ, 0x6);

	struct PACKED Fx32
	{
		static constexpr float scale = 4096.0f;

		constexpr Fx32() = default;
		constexpr Fx32(float f) : value {static_cast<s32>(0.0f <= f ? f * scale + 0.5f : f * scale - 0.5f)} {}

		constexpr operator float() const
		{
			constexpr float invScale = 1.0f / scale;
			return static_cast<float>(value) * invScale;
		}

		s32 value;
	};
	ASSERT_SIZE(Fx32, 0x4);

	enum class OrderType : u8
	{
		THINK,
		TALK,
		NONE
	};

	using ActionRotation = u8;
	using ActionXYZ = CompactXYZ;
	using ActionPosition = CompactXZ;
	using Angle16 = u16;
	using AnimationName = u16;

	struct PACKED ActNone { };

	using Act00 = ActNone;

	struct PACKED Act01
	{
		Fx32 value;
	};
	ASSERT_SIZE(Act01, 0x4);

	struct PACKED Act02
	{
		Fx32 value;
	};
	ASSERT_SIZE(Act02, 0x4);

	using Act03 = ActNone;

	using Act04 = ActNone;

	using Act05 = ActNone;

	struct PACKED Act06
	{
		Fx32 value;
	};
	ASSERT_SIZE(Act06, 0x4);

	using Act07 = ActNone;
	using Act08 = ActNone;
	using Act09 = ActNone;
	using Act0a = ActNone;
	using Act0b = ActNone;
	using Act0c = ActNone;
	using Act0d = ActNone;
	using Act0e = ActNone;

	struct PACKED Act0f
	{
		ActionPosition position;
		bool positionInitialized;
	};
	ASSERT_SIZE(Act0f, 0x5);

	using Act10 = Act0f; // sit
	using Act11 = Act0f; // lie
	using Act12 = Act0f; // swim
	using Act13 = ActNone;

	enum WalkType : u8
	{
		TYPE_0,
		TYPE_1,
		TYPE_2,
		TYPE_3,
		TYPE_4,
	};

	struct PACKED Act14
	{
		enum NextAct : u8
		{
			TALK,
			ACT_13,
			ENTER_DOOR_0,
			ENTER_DOOR_1,
			ENTER_DOOR_2,
		};

		ActionPosition target;
		Angle16 targetRotation;
		WalkType walkType;
		NextAct nextAct;
		bool useTargetRotation;
		Fx32 targetSpeed;
	};
	ASSERT_SIZE(Act14, 0xd);

	struct PACKED Act15
	{
		Angle16 targetRotation;
		s8 rotationStepScale;
		bool isNextAct13;
		bool useWalkAnimation;
		u8 unknown;
	};
	ASSERT_SIZE(Act15, 0x6);

	struct PACKED Act16
	{
		Fx32 menuThinkAnimParam;
	};
	ASSERT_SIZE(Act16, 0x4);

	using Act17 = ActNone;
	using Act18 = ActNone;
	using Act19 = ActNone;
	using Act1a = ActNone;

	struct PACKED Act1b
	{
		enum State : u8
		{
			START,
			WAIT,
			END,
		};

		State state; // private
	};
	ASSERT_SIZE(Act1b, 0x1);

	struct Act1c
	{
		ActionPosition target;
		u8 unknown;
		bool slow;
	};
	ASSERT_SIZE(Act1c, 0x6);

	struct PACKED Act1d
	{
		ActionPosition target;
		u8 unknown;
	};
	ASSERT_SIZE(Act1d, 0x5);

	using Act1e = ActNone;
	using Act1f = ActNone;

	struct PACKED Act20
	{
		enum class AccelMode : u8
		{
			MODE_0,
			MODE_1,
			MODE_2
		};

		AccelMode accelMode;
		Fx32 propulsion;
	};
	ASSERT_SIZE(Act20, 0x5);

	using Act21 = ActNone;
	using Act22 = ActNone;

	struct PACKED Act23
	{
		SvFgName caught;
		Fx32 shadowScale;
		bool diveTimeExpired;
	};
	ASSERT_SIZE(Act23, 0x9);

	struct PACKED Act24
	{
		SvFgName caught;
		bool hasFreeItemSlot;
		bool allOwned;
		bool hasSwappableItem;
		bool isOwned;
		bool wait;
	};
	ASSERT_SIZE(Act24, 0x9);

	struct PACKED Act25
	{
		ActionPosition target;
		u8 targetRotation;
	};
	ASSERT_SIZE(Act25, 0x5);

	using Act26 = ActNone;
	
	struct PACKED Act27
	{
		Fx32 animSpeed;
	};
	ASSERT_SIZE(Act27, 0x4);

	using Act28 = ActNone;

	enum class MessagePool : u8
	{
		PLAYER,
		ERROR,
		GET_BADGE,
		COUNT
	};

	struct PACKED Act29
	{
		MessagePool pool;
		u8 msg;
		ActionXYZ vec;
	};
	ASSERT_SIZE(Act29, 0x8);

	struct PACKED Act2a
	{
		struct PACKED Cam
		{
			enum Mode : u8
			{
				NONE,
				CAM_CATCH,
				CAM_SHOW_OFF,
			};

			bool faceCamera : 1;
			Mode cam : 3;
			bool isAnimDone : 1;
			u16 reserved : 11;
		};
		ASSERT_SIZE(Cam, 0x2);

		// enum Type : u8
		// {
		// 	NONE,
		// 	SET_WARP_ENABLE_FLAG = 7, // enables warp if MessagePool == SYS_Player
		// 	DONATION_COMPLETE = 8,
		// 	DONATION_COMPLETE_VST = 9,

		// };

		MessagePool pool; // 0x0
		u8 b; // 0x1
		u8 msg1; // 0x2
		AnimationName anim; // 0x3
		u8 unk; // 0x5
		u16 anim1Mode; // 0x6
		u8 msg2; // 0x8
		AnimationName anim2; // 0x9
		u8 field_b; // 0xb
		u16 animMode; // 0xc
		u8 anim2Mode; // 0xe
		SvFgName item; // 0xf
		u8 delay; // 0x13
		u8 frameOffs; // 0x14
		u8 reserved;
		Cam cam; // 0x16
	};
	ASSERT_SIZE(Act2a, 0x18);

	struct Act2b
	{
		ActionPosition ctrlPos;
		ActionPosition otherPos;
		ActionRotation rotation;
		bool skipFade;
	};
	ASSERT_SIZE(Act2b, 0xa);

	using Act2c = Act2b;
	using Act2d = Act2b;
	using Act2e = Act2b;

	struct PACKED Act2f
	{
		ActionPosition target;
		ActionRotation rotation; // 0x4
		bool isHome; // 0x5
		bool isPrevOutdoor; // 0x6
		bool isCurOutdoor; // 0x7
	};
	ASSERT_SIZE(Act2f, 0x8);

	using Act30 = Act2f;
	using Act31 = Act2f;
	using Act32 = Act2f;

	struct PACKED Act33
	{
		ActionXYZ position;
		ActionRotation rotation;
		bool isUp; // 0x7
	};
	ASSERT_SIZE(Act33, 0x8);

	struct PACKED Act34
	{
		bool isUp;
	};
	ASSERT_SIZE(Act34, 0x1);

	using Act35 = Act34;

	struct PACKED Act36
	{
		struct PACKED OutfitItem
		{
			SvFgName item;
			u8 outfitIndex;
		};
		ASSERT_SIZE(OutfitItem, 0x5);

		OutfitItem items[3];
		ActionRotation rotation; // 0xf
		OrderType order : 3; // 0x10
		u8 itemCount : 2;
		bool isForced : 1;
		bool immediate : 1;
		bool skipFrame : 1; 
		bool rotationInitialized : 1; // 0x11
	};
	ASSERT_SIZE(Act36, 0x12);

	struct PACKED Act37
	{
		u8 unk;
		u8 unk2;
		OrderType order;
	};
	ASSERT_SIZE(Act37, 0x3);

	struct PACKED Act38
	{
		SvFgName item;
		bool isShortcutEquip;
		OrderType order; // 0x5
	};
	ASSERT_SIZE(Act38, 0x6);

	struct PACKED Act39
	{
		bool isEquip;
		OrderType order;
	};
	ASSERT_SIZE(Act39, 0x2);

	enum class PutAwayNextAct : u8
	{
		PREVIOUS = 0,
		JUMP = 1,
		SWIM = 2,
		LIE = 3,
		IDLE = 4,
		BOAT = 5,
	};

	struct PACKED Act3a
	{
		PutAwayNextAct nextAct;
		ActionPosition targetPosition;
		ActionRotation rotation;
		u8 unknown2;
		u8 unknown3;
	};
	ASSERT_SIZE(Act3a, 0x8);

	enum class IsTalk : u8
	{
		IDLE,
		TALK,
	};

	struct Act3b
	{
		u8 unknown;
		EmoticonName emote;
		IsTalk next;
	};
	ASSERT_SIZE(Act3b, 0x3);

	struct PACKED Act3c
	{
		SvFgName item;
		Vector2u8 placePos;
		u8 layer;
		fgobj::PlaceType placeType; // accepted values: 1, 2, 3, 4, 5, 6
		bool alternativeAnimation;
		ActionPosition position;
	};
	ASSERT_SIZE(Act3c, 0xd);

	struct PACKED Act3d
	{
		SvFgName item;
		Vector2u8 placePos;
		u8 layer;
		fgobj::PlaceType placeType;
		bool alternativeAnimation;
		ActionPosition position;
	};
	ASSERT_SIZE(Act3d, 0xd);

	enum PutAwayMode : u8
	{
		PICK_UP,
		TOOL,
		CATCH,
	};

	struct PACKED Act3e
	{
		enum NextAct : u8
		{
			PUT_AWAY_FAIL,
			NORMAL,
			SWIM,
			THINK,
		};

		SvFgName item;
		AnimationName anim;
		NextAct next;
		bool addToInventory;
		PutAwayMode mode;
		ActionPosition position; // 0x9
	};
	ASSERT_SIZE(Act3e, 0xd);

	struct PACKED Act3f
	{
		u8 msg;
		SvFgName item;
		PutAwayMode mode;
		ActionPosition position; // 0x6
	};
	ASSERT_SIZE(Act3f, 0xa);

	struct PACKED Act40
	{
		SvFgName item;
		Vector2u8 placePos;
		ActionPosition position; // 0x6
	};
	ASSERT_SIZE(Act40, 0xa);

	struct PACKED Act41
	{
		SvFgName item;
		Vector2u8 placePos;
		fgobj::PlaceType mode;
		ActionPosition position; // 0x7
		ActionRotation rotation; // 0xb
	};
	ASSERT_SIZE(Act41, 0xc);

	struct PACKED Act42
	{
		SvFgName item;
		Vector2u8 placePos;
		fgobj::PlaceType mode;
		ActionPosition position; // 0x7
		ActionRotation rotation; // 0xb
	};
	ASSERT_SIZE(Act42, 0xc);

	using Act43 = ActNone;

	enum class DoorMode : u8
	{
		DOOR,
		NODOOR,
		NODOOR_TENT,
		RESET,
		PHOTOBOX,
		DEPART,
		R_VCAR,
		COUNT
	};

	struct PACKED Act44
	{
		DoorMode mode;
		u8 delay;
		ActionPosition position;
		ActionRotation rotation;
		bool pause;
		bool lockStrc;
	};
	ASSERT_SIZE(Act44, 0x9);

	struct PACKED Act45
	{
		s32 se;
		ActionPosition position;
		ActionRotation rotation;
		bool talk : 1;
		u8 delay : 7;
	};
	ASSERT_SIZE(Act45, 0xa);

	struct PACKED Act46
	{
		bool isRVCar;
	};

	using Act47 = Act46;

	struct PACKED Act48
	{
		DoorMode mode;
		u8 delay;
	};
	ASSERT_SIZE(Act48, 0x2);

	using Act49 = ActNone;

	struct PACKED Act4a
	{
		Vector2u8 position;
		fgobj::PlaceType placeType;
	};
	ASSERT_SIZE(Act4a, 0x3);

	using Act4b = ActNone;

	struct PACKED Act4c
	{
		Vector2u8 target;
		bool isHard;
		bool isFgUpdate;
		ActionPosition bouncePosition; // private
		ActionPosition sourcePosition; // private
		bool breakRock; // 0xc
	};
	ASSERT_SIZE(Act4c, 0xd);

	struct PACKED Act4d
	{
		u8 mode;
		s32 snowball;
		ActionPosition bouncePosition; // private
		ActionPosition sourcePosition; // private
	};
	ASSERT_SIZE(Act4d, 0xd);

	using Act4e = ActNone;

	enum class DigItemMode : u8
	{
		NONE,
		NORMAL,
		FULL_INVENTORY,
		TOUR,
		FULL_MAIL,
		LOST_AND_FOUND,
		ASK_SWAP,
		WRONG_ITEM,
	};

	struct PACKED Act4f
	{
		Vector2u8 target;
		SvFgName item;
		bool isHeavy; // 0x6
		bool isTour;
		DigItemMode mode;
		ActionPosition position; // 0x9
	};
	ASSERT_SIZE(Act4f, 0xd);

	using Act50 = Act4f;
	using Act51 = Act4f;

	struct Act52
	{
		enum NextAct : u8
		{
			IDLE,
			THINK,
			TALK,
		};

		Vector2u8 target;
		bool isSwing;
		NextAct nextAct;
		ActionPosition position;
	};
	ASSERT_SIZE(Act52, 0x8);

	using Act53 = Act52;

	using Act54 = ActNone;

	using Act55 = ActNone;

	struct PACKED Act56
	{
		Vector2u8 target;
		SvFgName item;
		bool isDamage;
		fgobj::PlaceType placeType;
	};
	ASSERT_SIZE(Act56, 0x8);

	using Act57 = ActNone;

	struct PACKED Act58
	{
		Vector2u8 target;
		SvFgName item;
		ActionPosition bouncePosition; // 0x6
		ActionPosition sourcePosition; // 0xa
		bool isSuccess : 1; // 0xe
		bool isDamage : 1;
		bool isBreakRock : 1;
		bool isFgUpdate : 1; 
	};
	ASSERT_SIZE(Act58, 0xf);

	struct PACKED Act59
	{
		u8 mode;
		s32 snowball;
		ActionPosition bouncePosition; // 0x5
		ActionPosition sourcePosition;
	};
	ASSERT_SIZE(Act59, 0xd);

	struct PACKED Act5a
	{
		Vector2u8 target;
		SvFgName item;
		bool isDamage; // 0x6
		bool isInterrupt; // isBees
	};
	ASSERT_SIZE(Act5a, 0x8);

	struct PACKED Act5b
	{
		Vector2u8 target;
	};
	ASSERT_SIZE(Act5b, 0x2);

	struct PACKED Act5c
	{
		Vector2u8 target;
	};
	ASSERT_SIZE(Act5c, 0x2);

	struct PACKED Act5d
	{
		Vector2u8 target;
		bool isPattern;
	};
	ASSERT_SIZE(Act5d, 0x3);

	struct PACKED Act5e
	{
		Vector2u8 target;
	};
	ASSERT_SIZE(Act5e, 0x2);

	struct PACKED Act5f
	{
		Vector2u8 target;
		bool fromChair;
	};
	ASSERT_SIZE(Act5f, 0x3);

	using Act60 = ActNone;
	using Act61 = ActNone;

	struct Act62
	{
		ActionPosition position;
	};
	ASSERT_SIZE(Act62, 0x4);

	struct Act63
	{
		ActionPosition position;
	};
	ASSERT_SIZE(Act63, 0x4);

	struct Act64
	{
		ActionPosition position;
	};
	ASSERT_SIZE(Act64, 0x4);

	struct PACKED Act65 { };
	struct PACKED Act66 { };
	struct PACKED Act67 { };

	struct PACKED Act68
	{
		u8 direction;
	};
	ASSERT_SIZE(Act68, 0x1);

	struct PACKED Act69
	{
		Vector2u8 target;
		ActionPosition position;
		ActionRotation rotation;
	};
	ASSERT_SIZE(Act69, 0x7);

	struct PACKED Act6a
	{
		Vector2u8 target;
		bool interrupt;
	};
	ASSERT_SIZE(Act6a, 0x3);

	using Act6b = Act6a;

	struct Act6c
	{
		ActionPosition position;
		Angle16 rotation;
	};
	ASSERT_SIZE(Act6c, 0x6);

	using Act6d = Act06;
	using Act6e = Act0d;

	using Act6f = ActNone;
	using Act70 = ActNone;

	struct PACKED Act71
	{
		SvFgName item;
		bool fullInventory;
		bool completesBook;
		bool isNew;
		bool animDone;
	};
	ASSERT_SIZE(Act71, 0x8);

	struct PACKED Act72
	{
		SvFgName item;
		bool canRelease;
		bool forceRelease;
		ActionPosition releasePosition;
		bool animDone;
	};
	ASSERT_SIZE(Act72, 0xb);

	struct PACKED Act73
	{
		enum NextAct : u8
		{
			IDLE,
			THINK,
		};

		SvFgName item;
		ActionPosition position;
		bool isPutOnGround; // private
		NextAct next;
		bool canShow; // 0xa
	};
	ASSERT_SIZE(Act73, 0xb);

	enum TransactionMode : u8
	{
		ITEM_1,
		ITEM_2,
		MAIL,
		ITEM_3,
	};

	struct PACKED Act74
	{
		TransactionMode mode;
		SvFgName item;
	};
	ASSERT_SIZE(Act74, 0x5);

	struct PACKED Act75
	{
		ActionPosition position;
		TransactionMode mode;
		ActionRotation rotation;
	};
	ASSERT_SIZE(Act75, 0x6);

	struct PACKED Act76
	{
		TransactionMode mode;
	};
	ASSERT_SIZE(Act76, 0x1);

	struct PACKED Act77
	{
		TransactionMode mode;
		bool talk;
	};
	ASSERT_SIZE(Act77, 0x2);

	using Act78 = ActNone;

	enum class SitDownDirection : u8
	{
		FRONT,
		RIGHT,
		LEFT,
		NONE,
	};

	struct PACKED Act79
	{
		SitDownDirection mode;
		ActionPosition target;
		ActionRotation rotation;
		bool isFtr;
	};
	ASSERT_SIZE(Act79, 0x7);

	struct PACKED Act7a
	{
		u8 msg;
		SitDownDirection mode;
		ActionPosition target;
		ActionRotation rotation;
		bool isFtr; // 0x7;
	};
	ASSERT_SIZE(Act7a, 0x8);

	struct PACKED Act7b
	{
		SitDownDirection mode;
		ActionPosition target;
		ActionRotation rotation;
		bool isFtr; // 0x6;
		bool isBadLuckEvent; // 0x7
	};
	ASSERT_SIZE(Act7b, 0x8);

	struct PACKED Act7c
	{
		Fx32 arg;
	};
	ASSERT_SIZE(Act7c, 0x4);

	struct PACKED Act7d
	{
		SitDownDirection dir;
		ActionPosition target;
		ActionRotation rotation;
		u8 delay; // 0x6;
	};
	ASSERT_SIZE(Act7d, 0x7);

	enum class StandupMode : u8
	{
		FALL_IN_PITFALL,
		FALL_IN_HOLE,
		NORMAL,
	};

	struct PACKED Act7e
	{
		enum NextAct : u8
		{
			TALK,
			NORMAL,
			ACT_0C,
		};

		SitDownDirection dir;
		ActionPosition position;
		ActionRotation rotation;
		StandupMode mode; // 0x6;
		bool isBadLuckEvent; // 0x7
		NextAct next; // 0x8
		ActionPosition target; // 0x9
	};
	ASSERT_SIZE(Act7e, 0xd);

	struct PACKED Act7f
	{
		u8 delay;
	};
	ASSERT_SIZE(Act7f, 0x1);

	enum class LieDownDirection : u8
	{
		RIGHT,
		LEFT
	};

	enum class BedTurnDirection : u8
	{
		R_L,
		L_R,
	};

	struct PACKED Act80
	{
		ActionPosition position;
		ActionRotation rotation;
		LieDownDirection dir;
	};
	ASSERT_SIZE(Act80, 0x6);

	struct PACKED Act81
	{
		ActionPosition position;
		ActionRotation rotation;
		LieDownDirection dir;
		IsTalk next;
	};
	ASSERT_SIZE(Act81, 0x7);

	struct PACKED Act82
	{
		Fx32 value;
	};
	ASSERT_SIZE(Act82, 0x4);

	struct PACKED Act83
	{
		ActionPosition position;
		ActionRotation rotation;
		BedTurnDirection dir;
	};
	ASSERT_SIZE(Act83, 0x6);

	struct PACKED Act84
	{
		ActionPosition position;
		ActionRotation rotation;
		BedTurnDirection dir;
	};
	ASSERT_SIZE(Act84, 0x6);

	struct PACKED Act85
	{
		enum Mode : u8
		{
			TURN,
			WAIT,
		};

		BedTurnDirection dir;
		Mode mode;
	};
	ASSERT_SIZE(Act85, 0x2);

	struct PACKED Act86
	{
		ActionPosition position;
		ActionRotation rotation;
		BedTurnDirection dir;
	};
	ASSERT_SIZE(Act86, 0x6);

	struct PACKED Act87
	{
		ActionPosition position;
		ActionRotation rotation;
		BedTurnDirection dir;
		StandupMode mode;
		IsTalk next;
	};
	ASSERT_SIZE(Act87, 0x8);

	struct PACKED Act88
	{
		EmoticonName emote;
	};
	ASSERT_SIZE(Act88, 0x1);

	struct PACKED Act89
	{
		PutAwayNextAct nextAct;
		ActionPosition position;
		ActionRotation rotation;
		LieDownDirection dir;
		IsTalk next;
	};
	ASSERT_SIZE(Act89, 0x8);

	using Act8a = ActNone;

	struct PACKED Act8b
	{
		ActionPosition position;
		ActionRotation rotation;
		bool isWait; // private
	};
	ASSERT_SIZE(Act8b, 0x6);

	struct PACKED Act8c
	{
		ActionPosition position;
		ActionRotation rotation;
		IsTalk next;
	};
	ASSERT_SIZE(Act8c, 0x6);

	struct PACKED Act8d
	{
		IsTalk next;
	};
	ASSERT_SIZE(Act8d, 0x1);

	using Act8e = ActNone;
	using Act8f = ActNone;
	using Act90 = ActNone;
	using Act91 = ActNone;

	struct PACKED Act92
	{
		SvFgName item;
		ActionRotation rotation;
		bool animDone;
	};
	ASSERT_SIZE(Act92, 0x6);

	struct PACKED Act93
	{
		enum Mode : u8
		{
			EAT_1,
			EAT_2,
			EAT_3,
		};

		enum NextAct : u8
		{
			THINK,
			NORMAL,
		};

		SvFgName item;
		SvFgName item2;
		NextAct next;
		Mode mode; // 0x9
	};
	ASSERT_SIZE(Act93, 0xa);

	using Act94 = Act93;

	enum class ChestType : u8
	{
		CHEST_A,
		CHEST_B,
		CHEST_C,
		COUNT
	};

	struct PACKED Act95
	{
		ChestType chestType;
		ActionPosition position;
		ActionRotation rotation;
	};
	ASSERT_SIZE(Act95, 0x6);

	struct PACKED Act96
	{
		ChestType chestType;
	};
	ASSERT_SIZE(Act96, 0x1);

	struct PACKED Act97
	{
		ChestType chestType;
	};
	ASSERT_SIZE(Act97, 0x1);

	using Act98 = ActNone;

	struct PACKED Act99
	{
		u8 mode;
	};
	ASSERT_SIZE(Act99, 0x1);

	using Act9a = ActNone;

	struct PACKED Act9b
	{
		ActionPosition position;
		ActionRotation rotation;
	};
	ASSERT_SIZE(Act9b, 0x5);

	struct PACKED Act9c
	{
		enum HitType : u8
		{
			PLAYER,
			NPC,
			PIKO_HAN_OBJ,
		};

		HitType hitType;
		s32 hitPlayer;
		ActionPosition position;
		ActionRotation rotation;
	};
	ASSERT_SIZE(Act9c, 0xa);

	struct PACKED Act9d
	{
		u8 mode;
		ActionPosition position;
		ActionRotation rotation;
	};
	ASSERT_SIZE(Act9d, 0x6);

	using Act9e = ActNone;
	using Act9f = ActNone;
	using Acta0 = ActNone;
	using Acta1 = ActNone;
	using Acta2 = ActNone;
	using Acta3 = ActNone;
	using Acta4 = ActNone;

	using Acta5 = ActNone;
	using Acta6 = ActNone;

	struct PACKED Acta7
	{
		bool mode;
		ActionRotation rotation;
		OrderType order;
	};
	ASSERT_SIZE(Acta7, 0x3);

	struct PACKED Acta8
	{
		ActionPosition position;
		ActionRotation rotation;
	};
	ASSERT_SIZE(Acta8, 0x5);

	struct PACKED Acta9
	{
		ActionPosition position;
		ActionRotation rotation;
	};
	ASSERT_SIZE(Acta9, 0x5);

	struct PACKED Actaa
	{
		Fx32 value;
	};

	struct PACKED Actab
	{
		ActionPosition position;
		ActionRotation rotation;
		ActionPosition position2;
		ActionRotation rotation2;
	};
	ASSERT_SIZE(Actab, 0xa);

	struct PACKED Actac
	{
		enum Mode : u8
		{
			FALL_IN_HOLE,
			FALL_IN_PITFALL,
			NORMAL,
		};

		ActionPosition fg;
		ActionRotation rotation; // private
		ActionPosition position;
		ActionRotation rotation2;
		Mode mode;
	};
	ASSERT_SIZE(Actac, 0xb);

	struct PACKED Actad { };

	enum class StandupChairDirection : u8
	{
		R,
		L,
	};

	struct PACKED Actae
	{
		enum ChairType : u8
		{
			FTR,
			FG,
		};

		ActionPosition position;
		ActionRotation rotation;
		StandupChairDirection direction; // 0x5
		ChairType chairType;
	};
	ASSERT_SIZE(Actae, 0x7);

	struct PACKED Actaf
	{
		enum NextAct : u8
		{
			TALK,
			IDLE,
			THINK,
			COMMON_NEXT_ACT,
		};

		EmoticonName emoticon;
		NextAct nextAct;
		u8 delay;
		u8 duration;
		Angle16 targetRotation; // 0x4
		u8 npcMode;
		bool unknown : 1;
		bool useTargetRotation : 1;
		bool loop : 1;
	};
	ASSERT_SIZE(Actaf, 0x8);

	struct PACKED Actb0
	{
		ActionXYZ target;
		ActionPosition position;
	};
	ASSERT_SIZE(Actb0, 0xa);

	struct PACKED Actb1
	{
		ActionXYZ target;
		ActionPosition position;
	};
	ASSERT_SIZE(Actb1, 0xa);

	struct PACKED Actb2
	{
		ActionPosition position;
	};
	ASSERT_SIZE(Actb2, 0x4);

	struct PACKED Actb3
	{
		ActionPosition position;
	};
	ASSERT_SIZE(Actb3, 0x4);

	struct PACKED Actb4
	{
		ActionPosition position;
		SvFgName fish;
	};
	ASSERT_SIZE(Actb4, 0x8);

	struct PACKED Actb5
	{
		ActionPosition position;
	};
	ASSERT_SIZE(Actb5, 0x4);

	struct PACKED Actb6
	{
		enum NextAct : u8
		{
			NORMAL = 0,
			STING_1,
			STING_2,
			FAINT_1,
			FAINT_2,
		};

		ActionPosition position;
		NextAct nextAct;
	};
	ASSERT_SIZE(Actb6, 0x5);

	struct PACKED Actb7
	{
		SvFgName fish;
		bool fullInventory;
		ActionPosition position;
		bool completesBook; // private
		bool isNew; // private
		bool animDone; // private
	};
	ASSERT_SIZE(Actb7, 0xc);

	struct PACKED Actb8
	{
		ActionRotation rotation;
		Vector2u8 strcPos;
	};
	ASSERT_SIZE(Actb8, 0x3);

	struct PACKED Actb9
	{
		u8 hairStyle;
		u8 hairColor;
		u8 eyeColor;
		SvFgName miiMask;
	};
	ASSERT_SIZE(Actb9, 0x7);

	struct PACKED Actba
	{
		SvFgName mask;
		SvFgName accessory;
	};
	ASSERT_SIZE(Actba, 0x8);

	struct PACKED Actbb { };
	
	struct PACKED Actbc
	{
		u8 seat;
	};
	ASSERT_SIZE(Actbc, 0x1);

	struct PACKED Actbd { };

	struct PACKED Actbe { };

	struct PACKED Actbf
	{
		u8 unkown;
	};
	ASSERT_SIZE(Actbf, 0x1);

	struct PACKED Actc0
	{
		enum NextAct : u8
		{
			TALK,
			NORMAL,
		};

		SvFgName item;
		u8 outfitIndex;
		NextAct nextAct;
	};
	ASSERT_SIZE(Actc0, 0x6);

	struct PACKED Actc1
	{
		ActionPosition position;
		ActionRotation rotation;
		u8 mode;
	};
	ASSERT_SIZE(Actc1, 0x6);

	struct PACKED Actc2 { };

	struct PACKED Actc3
	{
		u8 type; // private
	};
	ASSERT_SIZE(Actc3, 0x1);

	enum class NextActNormal : u8
	{
		TALK,
		SWIM_TALK,
		SIT_TALK,
		LIE_TALK,
		IDLE,
		NONE,
	};

	struct PACKED Actc4
	{
		AnimationName animation;
		s32 sound; // 0x2
		u8 soundTime; // 0x6
		u16 duration; // 0x7
		NextActNormal nextAct; // 0x9
		ActionRotation rotation; // 0xa
		bool waitWhenDone; // 0xb
	};
	ASSERT_SIZE(Actc4, 0xc);

	struct PACKED Actc5
	{
		AnimationName animation;
		AnimationName animation2;
		ActionRotation rotation; // 0x4
		u8 duration; // 0x5
		NextActNormal nextAct; // 0x6
		bool waitWhenDone; // 0x7
	};
	ASSERT_SIZE(Actc5, 0x8);

	struct PACKED Actc6 { };

	struct PACKED Actc7
	{
		Fx32 unknown;
	};
	ASSERT_SIZE(Actc7, 0x4);
	
	struct PACKED Actc8
	{
		Fx32 unknown;
	};
	ASSERT_SIZE(Actc8, 0x4);

	struct PACKED Actc9
	{
		Fx32 unknown;
	};
	ASSERT_SIZE(Actc9, 0x4);

	struct PACKED Actca
	{
		Fx32 unknown;
	};
	ASSERT_SIZE(Actca, 0x4);

	struct PACKED Actcb { };

	struct PACKED Actcc { };

	struct PACKED Actcd { };

	struct PACKED Actce { };

	struct PACKED Actcf { };

	struct PACKED Actd0 { };

	struct PACKED Actd1
	{ 
		u8 mode;
	};
	ASSERT_SIZE(Actd1, 0x1);

	struct PACKED Actd2
	{ 
		u8 mode;
	};
	ASSERT_SIZE(Actd2, 0x1);

	struct PACKED Actd3
	{ 
		u8 mode;
	};
	ASSERT_SIZE(Actd3, 0x1);

	struct PACKED Actd4
	{
		u8 unknown;
	};
	ASSERT_SIZE(Actd4, 0x1);

	struct PACKED Actd5
	{
		u8 unknown;
	};
	ASSERT_SIZE(Actd5, 0x1);

	struct PACKED Actd6
	{
		enum NextAct : u8
		{
			THINK,
			IDLE
		};

		NextAct nextAct;
	};
	ASSERT_SIZE(Actd6, 0x1);

	struct PACKED Actd7 { };

	struct PACKED Actd8 { };

	struct PACKED Actd9
	{
		ActionPosition position;
		ActionRotation rotation;
	};
	ASSERT_SIZE(Actd9, 0x5);

	struct PACKED Actda { };

	struct PACKED Actdb
	{
		IsTalk next;
	};
	ASSERT_SIZE(Actdb, 0x1);

	struct PACKED Actdc { };

	struct PACKED Actdd { };

	struct PACKED Actde
	{
		ActionPosition position;
		ActionRotation rotation;
		bool isWait; // private
	};
	ASSERT_SIZE(Actde, 0x6);

	struct PACKED Actdf
	{
		ActionPosition position;
		ActionRotation rotation;
		IsTalk next;
	};
	ASSERT_SIZE(Actdf, 0x6);

	struct PACKED Acte0 { };

	struct PACKED Acte1
	{
		ActionPosition position;
		ActionRotation rotation;
	};
	ASSERT_SIZE(Acte1, 0x5);

	struct PACKED Acte2
	{
		enum NextAct : u8
		{
			TALK,
			NORMAL,
		};

		ActionPosition position;
		ActionRotation rotation;
		NextAct nextAct;
	};
	ASSERT_SIZE(Acte2, 0x6);

	struct PACKED Acte3 { };

	struct PACKED Acte4 { };

	struct PACKED Acte5
	{
		ActionPosition position;
	};
	ASSERT_SIZE(Acte5, 0x4);

	struct PACKED Acte6 { };

	struct PACKED Acte7 { };

	struct PACKED Acte8
	{
		s32 se[2]; // private
	};

	struct PACKED Acte9 { };
	
	struct PACKED Actea { };

	std::byte data[0x18];

	template<typename T> requires (sizeof(T) <= sizeof(data))
	T* GetAction()
	{
		return reinterpret_cast<T*>(&data[0]);
	}

	template<typename T> requires (sizeof(T) <= sizeof(data) && std::is_trivially_destructible_v<T>)
	T* ConstructAction(auto&&... args)
	{
		return new (data) T {std::forward<decltype(args)>(args)...};
	}
};
ASSERT_SIZE(PlayerAction, 0x18);
