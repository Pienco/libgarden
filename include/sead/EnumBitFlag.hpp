#ifndef SEAD_ENUMBITFLAG_HPP
#define SEAD_ENUMBITFLAG_HPP

#include <concepts>
#include <type_traits>

namespace sead
{

	template <typename Enum, typename Storage> requires (std::is_enum_v<Enum>)
	struct EnumBitFlag
	{

	public:

		using Underlying = std::underlying_type_t<Enum>;

		static constexpr Storage GetMask(std::convertible_to<Enum> auto... values)
		{
			return ((1u << static_cast<Underlying>(values)) | ...);
		}

		consteval EnumBitFlag() = default;
		constexpr EnumBitFlag(std::convertible_to<Enum> auto... val) : value { GetMask(val...) } { }
		
		constexpr EnumBitFlag& operator=(Enum right)
		{
			value = GetMask(right);
			return *this;
		}

		constexpr void Reset() { value = 0; }
		constexpr void SetAll() { value = ~Storage { 0 }; }

		constexpr void SetRaw(Storage val, bool set = true) 
		{ 
			if (set) value |= val;
			else value &= ~val;
		}
		constexpr void Set(EnumBitFlag<Enum, Storage> other, bool set = true) { SetRaw(other.value, set); }
		constexpr void ResetRaw(Storage val) { SetRaw(val, false); }
		constexpr void ResetExceptRaw(Storage val) { value &= val; }
		constexpr void Set(std::convertible_to<Enum> auto... val) { SetRaw(GetMask(val...), true); }
		constexpr void Reset(std::convertible_to<Enum> auto... val) { ResetRaw(GetMask(val...)); }
		constexpr void ResetExcept(std::convertible_to<Enum> auto... val) { ResetExceptRaw(GetMask(val...)); }
		constexpr void Toggle(std::convertible_to<Enum> auto... val) { value ^= GetMask(val...); }

		constexpr bool IsZero() const { return value == 0; }
		constexpr bool IsSet(Enum val) const { return (value & GetMask(val)) != 0; }
		constexpr bool IsAny(std::convertible_to<Enum> auto... val) const { return (value & GetMask(val...)) != 0; }

		constexpr bool IsAll(std::convertible_to<Enum> auto... val) const 
		{
			const auto mask = GetMask(val...);
			return (value & mask) == mask; 
		}

		constexpr bool IsNone(std::convertible_to<Enum> auto... val) const { return !IsAny(val...); }

		constexpr bool TestAndClear(std::convertible_to<Enum> auto... val)
		{
			if (IsNone(val...))
				return false;
			Reset(val...);
			return true;
		}

		constexpr void ForEachEnabled(Underlying count, auto&& fn)
		{
			for (Underlying i = 0; i < count; i++)
			{
				if ((value & (1 << i)) != 0)
					std::forward<decltype(fn)>(fn)(static_cast<Enum>(i));
			}
		}


		Storage value { };
	};
}

#endif
