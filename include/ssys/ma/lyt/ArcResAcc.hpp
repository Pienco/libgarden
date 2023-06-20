#ifndef SSYS_MA_LYT_ARCRESACC_HPP
#define SSYS_MA_LYT_ARCRESACC_HPP

#include "ssys/ma/lyt/ResAccInterface.hpp"

#include "ssys/ma/lyt/ArcResourceAccessorVRAM.hpp"

namespace ssys::ma::lyt
{

	class ArcResAcc : public ResAccInterface
	{
	
	public:

		virtual ~ArcResAcc();

		bool SetData(const void* arcData, const char* rootName);

	protected:
	
		inline ArcResourceAccessorVRAM* GetResourceAccessor() { return &m_ArcResourceAccessor; }

	private:

		ArcResourceAccessorVRAM m_ArcResourceAccessor; 
	};
	ASSERT_SIZE(ArcResAcc, 0x148);
}
#endif
