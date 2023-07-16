#ifndef FGOBJ_OBJECTBASE_HPP
#define FGOBJ_OBJECTBASE_HPP

#include "types.h"
#include "ssys/st/ListNodePriorityBase.hpp"
#include "item/Item.hpp"

namespace fgobj
{

	struct ModelInfo
	{
		const char* nameOutside;
		const char* nameInside;
		u8 flagOutside;
		u8 flagInside;
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

#endif
