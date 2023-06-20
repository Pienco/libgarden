#ifndef UTIL_NONCOPYABLE_HPP
#define UTIL_NONCOPYABLE_HPP

class NonCopyable
{

public:

	NonCopyable(NonCopyable& other) = delete;
	NonCopyable& operator=(NonCopyable& other) = delete;

protected:

	constexpr NonCopyable() = default;
	constexpr ~NonCopyable() = default;

};

#endif
