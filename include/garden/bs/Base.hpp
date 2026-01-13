#pragma once

#include "../oml/framework/Process.hpp"

class Base : public oml::framework::Process
{

	protected:

		using ProcessResult = oml::framework::Result;

		virtual ~Base() override;
		virtual bool CanInitialize() const override;
		virtual void HandleInitializationResult(ProcessResult) override;
		virtual bool CanFinalize() const override;
		virtual void HandleFinalizationResult(ProcessResult) override;
		virtual bool CanCalc() const override;
		virtual void HandleCalcResult(ProcessResult) override;
		virtual bool CanDraw() const override;

		virtual bool Unk0();
		
	private:
};
ASSERT_SIZE(Base, 0x14);
