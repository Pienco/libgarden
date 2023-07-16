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
		virtual constexpr ~SafeStringBase() {}
		virtual void SetNT();

		inline const T* GetString() const { return m_pString; }


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
	class FixedSafeString : public FixedSafeStringBase<char, Length>
	{

	};

	extern template class FixedSafeString<32>;

	using SafeString = SafeStringBase<char>;
	using SafeString16 = SafeStringBase<char16>;
}

#endif
