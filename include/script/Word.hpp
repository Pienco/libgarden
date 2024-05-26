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
		virtual size_t GetSize() const = 0;

	};
	ASSERT_SIZE(IWord, 4);

	class WordPtr : public IWord
	{
	
	public:

		constexpr WordPtr(char16* textBuffer, size_t size): m_pText(textBuffer), m_Size(size)
		{

		}

		template<size_t N>
		constexpr WordPtr(char16(&textBuffer)[N]): m_pText(&textBuffer), m_Size(N)
		{

		}

		virtual ~WordPtr() override;
		virtual inline char16* GetWord() final override { return m_pText; }
		virtual inline const char16* GetWord() const final override { return m_pText; }
		virtual inline size_t GetSize() const final override { return m_Size; }

	private:

		char16* m_pText;
		size_t m_Size;
	};
	ASSERT_SIZE(WordPtr, 0xc);


	template<size_t N>
	class WordFix final : public WordPtr
	{

	public:

		constexpr WordFix(): WordPtr(m_TextBuffer.data(), N)
		{
		}

		constexpr WordFix(const char16* str, size_t len) : WordFix()
		{
			std::copy(str, str + std::min(len, N), m_TextBuffer.begin());
		}

		constexpr WordFix(const char16(&str)[N]) : WordPtr(m_TextBuffer.data(), N), m_TextBuffer { std::to_array(str) }
		{
		}

		constexpr WordFix(const std::array<char16, N>& str) : WordPtr(m_TextBuffer.data(), N), m_TextBuffer { str }
		{
		}

		virtual constexpr ~WordFix() override = default;

		static consteval auto GetSizeFix() { return N; }

	private:

		using Buffer = std::array<char16, N>;

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

		Span m_Span { };
		Buffer m_TextBuffer { };
	};
	ASSERT_SIZE(WordFix<128u>, 0x118);
	
}

namespace detail
{
	template<size_t N>
	struct CaptureStringLiteral
	{
		static constexpr size_t size = N;

		constexpr CaptureStringLiteral(const char16(&arr)[N])
		{
			std::copy(arr, arr + N, str);
		}

		char16 str[N] { };
	};
}

template<detail::CaptureStringLiteral String>
inline constexpr script::WordPtr operator""_wp()
{
	static constinit detail::CaptureStringLiteral copy { String };
	// static constexpr script::WordPtr wp { &copy.str[0], copy.sizr };
	return script::WordPtr { copy.str, copy.size };
}

template<detail::CaptureStringLiteral String>
inline constexpr auto operator""_wf()
{
	return script::WordFix { String.str };
}

#endif
