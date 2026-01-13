#pragma once

#include <concepts>

namespace util
{
	template<typename T, typename U>
	concept SimilarTo = std::same_as<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;
}

