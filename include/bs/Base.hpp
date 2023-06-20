#ifndef BS_BASE_HPP
#define BS_BASE_HPP

#include "oml/framework/Process.hpp"

class Base : public oml::framework::Process
{

	protected:

		using ProcessResult = oml::framework::Result;

		virtual ~Base() override;
		virtual bool CanInitialize() const override;
		virtual void ProcessInitializationResult(ProcessResult) override;
		virtual bool CanFinalize() const override;
		virtual void ProcessFinalizationResult(ProcessResult) override;
		virtual bool CanProcess() const override;
		virtual void ProcessProcessingResult(ProcessResult) override;
		virtual bool CanStartup() const override;

		virtual bool Unk0();
		
	private:
};
ASSERT_SIZE(Base, 0x14);

#endif
