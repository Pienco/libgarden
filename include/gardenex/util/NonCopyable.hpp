#pragma once

class NonCopyable
{

public:

	NonCopyable(NonCopyable& other) = delete;
	NonCopyable& operator=(NonCopyable& other) = delete;

protected:

	constexpr NonCopyable() = default;
	constexpr ~NonCopyable() = default;

};
