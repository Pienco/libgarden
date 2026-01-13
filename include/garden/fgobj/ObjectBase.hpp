#pragma once

#include "../ssys/st/ListNodePriorityBase.hpp"
#include "../item/Item.hpp"

namespace fgobj
{

	enum class TextureID : u8
	{
		DEFAULT,
		T_FG_OUTSIDE,
		T_FG_OUTSIDE_2,
	};

	struct ModelInfo
	{
		const char* nameOutside;
		const char* nameInside;
		TextureID textureOutside;
		TextureID textureInside;
	};
	ASSERT_SIZE(ModelInfo, 0xc);

	extern const ModelInfo s_ModelInfos[(size_t)item::ModelID::COUNT];

	// const char* GetModelName(const item::ModelID& modelID, bool isOutside);

	class ObjectBase : ssys::st::ListNodePriorityBase
	{

	public:


	private:

		u8 m_Data[0x118];
	};
	ASSERT_SIZE(ObjectBase, 0x124);
}
