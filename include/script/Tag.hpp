#ifndef SCRIPT_TAG_HPP
#define SCRIPT_TAG_HPP

#include "types.h"
#include <limits>

namespace script
{
	using Str = const char16_t*;


	struct Tag
	{
		static constexpr char16 TAG_BEGIN = 0xe;

		enum class Type : s32
		{
			NONE = std::numeric_limits<s32>::max(),
			RENDER = 0,
			GENERIC = 0xff,
		};
		
		enum Render : s32
		{
			SCALE = 2,
			SET_COLOR = 3,
		};

		enum Generic : s32
		{
			STORE_CURSOR_SET_Y = 0,
			SET_CURSOR_X = 1,
			SET_COLOR_RGBA = 6,
		};

		enum TextColor : char16
		{
			WHITE = 0,
			PINK,
			BLUE,
			GREEN,
			ORANGE,
			GREY,
			RED,
			RESTORE,
		};

		static Tag GetTag(const Str* text);


		const char16_t* data = nullptr;
		Type type = Type::NONE;
		s32 index = -1;
		size_t argCount = 0;
		const char16_t* args = nullptr;
		size_t length = 0;
	};


	consteval auto MakeTag(Tag::Type type, s32 cmd, std::convertible_to<char16> auto... args)
	{
		return std::array
		{
			Tag::TAG_BEGIN,
			(char16)type,
			(char16)cmd,
			(char16)(sizeof...(args)),
			(char16)args...,
		};
	}

	consteval auto MakeTextColorTag(Tag::TextColor color)
	{
		return MakeTag(Tag::Type::RENDER, Tag::Render::SET_COLOR, color);
	}

	consteval auto GetRestoreColorTag() { return MakeTextColorTag(Tag::TextColor::RESTORE); }
	consteval auto GetGreenColorTag() { return MakeTextColorTag(Tag::TextColor::GREEN); }
	consteval auto GetRedColorTag() { return MakeTextColorTag(Tag::TextColor::RED); }
}
#endif
