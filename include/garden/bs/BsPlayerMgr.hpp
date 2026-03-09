#pragma once

#include "UtlBase.hpp"
#include "Base.hpp"
#include "../human/BankTable.hpp"
#include "../human/ToolBank.hpp"
#include "../human/HumanResTextureAnimBank.hpp"
#include "../player/PlayerFaceBank.hpp"
#include "../player/PlayerTopsBank.hpp"
#include "../player/PlayerAcceBank.hpp"
#include "../player/PlayerCapBank.hpp"
#include "../player/PlayerBottomsBank.hpp"
#include "../player/PlayerHeadBank.hpp"
#include "../player/PlayerLegsBank.hpp"
#include "../player/PlayerShoesBank.hpp"

class BsPlayerMgr : UtlBase<Base>
{
public:

	class BankTables
	{
	public:

	private:
		BankTable<Bank<11059u, 1u, false, EmptyBankVramConfig>, 7u> m_Body;
		BankTable<PlayerFaceBank, 14> m_Face;
		BankTable<PlayerHeadBank, 7> m_Head;
		BankTable<PlayerBottomsBank, 7> m_Bottoms;
		BankTable<PlayerTopsBank, 7> m_Tops;
		BankTable<PlayerLegsBank, 7> m_Legs;
		BankTable<PlayerShoesBank, 7> m_Shoes;
		BankTable<PlayerAcceBank, 7> m_Acce;
		BankTable<PlayerCapBank, 7> m_Cap;
		BankTable<ToolBank, 7> m_Tool;
		BankTable<HumanResTextureAnimBank, 14> m_EyeTextureAnim;
		BankTable<HumanResTextureAnimBank, 14> m_MouthTextureAnim;
	};
	ASSERT_SIZE(BankTables, 0x12bc8);

private:
	u8 data[0x12ccc];
};
ASSERT_SIZE(BsPlayerMgr, 0x12ce0);
