#ifndef SEAD_STRING_HPP
#define SEAD_STRING_HPP

#include "types.h"

namespace sead
{

	template<typename T>
	class SafeStringBase
	{

	public:

		constexpr SafeStringBase(const T* string) : m_pString(string)
		{
		}
		virtual constexpr ~SafeStringBase() = default;
		virtual void SetNT();

		const T* GetString() const { return m_pString; }

	private:

		const T* m_pString;
	};

	template<typename T>
	class BufferedSafeStringBase : public SafeStringBase<T>
	{

	public:

		virtual ~BufferedSafeStringBase() override;
		virtual void SetNT() override;
	
	private:

		size_t m_Size;
	};


	template<typename T, size_t Length>
	class FixedSafeStringBase : public BufferedSafeStringBase<T>
	{

	public:

	private:

		T m_String[Length];
	};

	template<size_t Length>
	class FixedSafeString final : public FixedSafeStringBase<char, Length>
	{

	};

	template<size_t Length>
	class WFixedSafeString final : public FixedSafeStringBase<char16, Length>
	{

	};

	extern template class FixedSafeString<24>;
	extern template class FixedSafeString<32>;
	extern template class FixedSafeString<64>;

	extern template class WFixedSafeString<18>;
	extern template class WFixedSafeString<32>;
	extern template class WFixedSafeString<64>;

	using SafeString = SafeStringBase<char>;
	using WSafeString = SafeStringBase<char16>;
}

#endif
