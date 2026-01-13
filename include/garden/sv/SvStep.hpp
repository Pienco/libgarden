#pragma once

#include "SvStepInner.hpp"
#include "../state/Step.hpp"

template<typename T, typename TStep>
class SvStep : public state::Step<T, TStep>, public SvStepInner
{
public:

private:
};
