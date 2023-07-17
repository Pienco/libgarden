.SUFFIXES:

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR 		?= 	$(CURDIR)
include $(DEVKITARM)/3ds_rules

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
subdirs=$(sort $(dir $(call rwildcard,$1/,)))
findindir=$(shell find $1 -name '$2')
findallfiles=$(shell find $1 -type f)

INCLUDES	:= 	$(call subdirs,include)

LIBDIRS		:= 	
SOURCES 	:= 	$(call subdirs,source)

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH		:=	-march=armv6k+fp -mlittle-endian -mtune=mpcore -mfloat-abi=hard \
				-mfpu=vfpv2 -mtp=soft

CFLAGS		:=	-Wall -Wextra -Wpedantic -Wconversion -Os -mword-relocations -nostdlib -nostartfiles \
				-fomit-frame-pointer -ffunction-sections -fno-strict-aliasing \
				$(ARCH)

CFLAGS		+=	$(INCLUDE) -DARM11 -D_3DS -D__3DS__

CXXFLAGS	= 	$(CFLAGS) -fno-rtti \
				-fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables \
				-fno-threadsafe-statics -std=gnu++23 \
				-fverbose-asm -Wa,-acdghlmns=$*.s,--listing-lhs-width2=400,--listing-rhs-width=400,--listing-cont-lines=2  \
				
ASFLAGS		:=	$(ARCH) -nostartfiles -nostdlib

LDFLAGS		:=	-static $(ARCH) -Os -Wl,-R,$(TOPDIR)/source/symbols_$(BUILD).txt \
				-Wl,-Map,$(notdir $*.map),--strip-discarded,--strip-debug,--print-gc-sections,--no-undefined 



export DEPSDIR	:=	$(TOPDIR)/$(BUILD)

ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export TOPDIR	:=	$(CURDIR)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

CFILES			:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES			:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
#BINFILES		:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bin)))

export LD 		:= 	$(CXX)
export OFILES	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I $(CURDIR)/$(dir) ) \
					$(foreach dir,$(LIBDIRS),-I $(dir)/include) \
					-I $(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L $(dir)/lib) 

.PHONY: re clean all eu us

#---------------------------------------------------------------------------------
all: us eu

us:
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) BUILD=$@ TARGET=$(notdir $(TOPDIR))_$@ --no-print-directory -C $@	-f $(CURDIR)/Makefile

eu:
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) BUILD=$@ TARGET=$(notdir $(TOPDIR))_$@ --no-print-directory -C $@	-f $(CURDIR)/Makefile
	

#---------------------------------------------------------------------------------
clean:
	@echo clean ... 
	@rm -fr us eu lib

re: clean all

#---------------------------------------------------------------------------------

else

.PHONY: all

#---------------------------------------------------------------------------------

export OUTPUT	:=	$(TOPDIR)/lib/$(TARGET).a

all: $(OUTPUT)

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

$(BUILD).o : $(OFILES)
	$(SILENTMSG) linking $(notdir $@)
	$(SILENTCMD)$(LD) $(LDFLAGS) $(OFILES) $(LIBPATHS) $(LIBS) -r -o $@
	$(SILENTCMD)$(NM) -CSn $@ > $(notdir $*.lst)

$(OUTPUT) : $(BUILD).o $(BUILD).elf
	@mkdir -p $(dir $@)
	$(SILENTMSG) $(notdir $@)
	$(SILENTCMD)$(AR) -rc $@ $<

#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)


-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
