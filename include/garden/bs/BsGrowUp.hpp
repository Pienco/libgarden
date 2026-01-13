#ifndef BS_BSGROWUP_HPP
#define BS_BSGROWUP_HPP

#include "Base.hpp"
#include "../stage/stage.hpp"
#include "../item/Item.hpp"

#include <bit>

struct RandomPlacerUsual;

struct RandomPlacer
{
	using Word = u16;
	using Bits = std::array<Word, stage::GetTownItemBlockCount() * stage::GetBlockSize().y()>;

	struct Info
	{
		size_t index;
		size_t localIndex;
		stage::Position pos;
		Word bit;
	};

	using Func = void(*)(RandomPlacerUsual&, RandomPlacer&, const Info&);

	THUMB size_t UpdateCount();
	THUMB size_t UpdateCount(stage::Position pos);
	THUMB bool Find(Info& out, s32 number) const;
	THUMB void DoRandom(Func func, RandomPlacerUsual* rpu);
	THUMB void DoRandom(Func func, RandomPlacerUsual* rpu, size_t maxCount);
	THUMB void DoRandom(Func func, RandomPlacerUsual* rpu, size_t maxCount, size_t startIndex);
	THUMB void DoEach(Func func, RandomPlacerUsual* rpu) const;

	constexpr void Remove(const Info& info)
	{
		bits[info.index] &= ~info.bit;
		count--;
	}

	Bits bits;
	size_t count;
};
ASSERT_SIZE(RandomPlacer, 0x284);

struct RandomPlacerUsual
{
	INSERT_PAD(0x44);
	RandomPlacer rock;
	RandomPlacer specialRock;
	RandomPlacer placeable;
	RandomPlacer treeSapling;
	RandomPlacer cedarSapling;
	RandomPlacer palmSapling;
	RandomPlacer bushSapling;
	RandomPlacer bambooSapling;
	RandomPlacer allTreeSaplings;
	RandomPlacer allTree;
	RandomPlacer soilTree;
	RandomPlacer bush;
	RandomPlacer cutTree;
	RandomPlacer specialStump;
	RandomPlacer nonFruitTree;
	RandomPlacer cedar;
	RandomPlacer xmas;
	RandomPlacer fruitTree;
	RandomPlacer treeGrowUp;
	RandomPlacer bamboo;
	RandomPlacer bambooShoot;
	RandomPlacer deadTree;
	RandomPlacer flower;
	RandomPlacer flowerForWilt;
	RandomPlacer randomFlowers;
	RandomPlacer wiltedFlower;
	RandomPlacer usualFlower;
	RandomPlacer dandelions;
	RandomPlacer dandelionPuffs;
	RandomPlacer empty;
	RandomPlacer manure;
	RandomPlacer specialManure;
	RandomPlacer unk1;
	RandomPlacer unk2;
	RandomPlacer misc;
	item::Item pitfall;
	s32 unk3[6];
	s32 passedDays;
	s32 unk4;
	s32 flowerMax;
	s32 currentIndex;
	INSERT_PAD(0x4c);
};
ASSERT_SIZE(RandomPlacerUsual, 0x58c8);


class BsGrowUp
{

public:

	static stage::Field* GetCurrentField()
	{
		return stage::GetField(s_CurrentField);
	}

private:

	static stage::FieldID s_CurrentField;
};

#endif
