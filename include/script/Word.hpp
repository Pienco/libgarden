#ifndef SCRIPT_WORD_HPP
#define SCRIPT_WORD_HPP

#include "types.h"

namespace script
{

	class IWord
	{
	
	public:

		virtual constexpr ~IWord() = default;
		virtual char16* GetWord() = 0;
		virtual const char16* GetWord() const = 0;
		virtual size_t GetLength() const = 0;

	};
	ASSERT_SIZE(IWord, 4);

	class WordPtr : public IWord
	{
	
	public:

		constexpr WordPtr(char16* textBuffer, size_t length): m_pText(textBuffer), m_Length(length)
		{

		}

		template<size_t N>
		constexpr WordPtr(char16(&textBuffer)[N]): m_pText(&textBuffer), m_Length(N)
		{

		}

		virtual ~WordPtr() override;
		virtual char16* GetWord() override;
		virtual const char16* GetWord() const override;
		virtual size_t GetLength() const override;

	private:

		char16* m_pText;
		size_t m_Length;
	};
	ASSERT_SIZE(WordPtr, 0xc);


	template<size_t N>
	class WordFix final : public WordPtr
	{

	public:

		constexpr WordFix(): WordPtr(m_TextBuffer.data(), N), m_Span {}, m_TextBuffer {}
		{
		}

		constexpr WordFix(const char16* str, size_t len) : WordPtr(m_TextBuffer.data(), len), m_Span {}
		{
			std::copy(str, str + len, m_TextBuffer.begin());
		}

		constexpr WordFix(const char16(&str)[N]) : m_TextBuffer { std::to_array(str) }, WordPtr(m_TextBuffer.begin(), N), m_Span {}
		{
		}

		virtual constexpr ~WordFix() override = default;

	private:

		struct Span
		{
			u8 unk0;
			u8 unk1;
			u8 unk2;
			u8 unk3;
			s32 begin;
			char16* buf;
		};
		ASSERT_SIZE(Span, 0xc);

		Span m_Span;
		std::array<char16, N> m_TextBuffer;
	};
	ASSERT_SIZE(WordFix<128u>, 0x118);
	
}

namespace detail
{
	template<size_t N>
	struct CaptureStringLiteral
	{
		static constexpr size_t length = N;

		constexpr CaptureStringLiteral(const char16(&arr)[N])
		{
			std::copy(arr, arr + N, str);
		}

		char16 str[N] { };
	};
}

template<detail::CaptureStringLiteral String>
inline constexpr const script::WordPtr* operator""_wp()
{
	static constinit detail::CaptureStringLiteral copy { String };
	static constexpr script::WordPtr internal { &copy.str[0], copy.length };
	return &internal;
}

template<detail::CaptureStringLiteral String>
inline constexpr auto operator""_wf()
{
	return script::WordFix { String.str };
}

#endif
