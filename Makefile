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

INCLUDES	:= 	include libraries/nnsdk/include libraries/nw4c/include libraries/sead/include 

VERSIONS	:=	us eu
LIBDIRS		:= 	
SOURCES 	:= 	$(call subdirs,source)

BUILDDIR	:=	build
OUTDIR		:=	lib

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH		:=	-march=armv6k+fp -mlittle-endian -mtune=mpcore -mfloat-abi=hard \
				-mfpu=vfpv2 -mtp=soft

CFLAGS		:=	$(ARCH) -Wall -Wextra -Wpedantic -Wconversion -Os -mword-relocations -nostdlib -nostartfiles \
				-fomit-frame-pointer -ffunction-sections -fshort-wchar # -fno-strict-aliasing

CFLAGS		+=	$(INCLUDE) -DARM11 -D_3DS -D__3DS__

CXXFLAGS	= 	$(CFLAGS) -fno-rtti \
				-fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables \
				-fno-threadsafe-statics -std=gnu++26 \
				-fverbose-asm -Wa,-acdghlmns=$*.s,--listing-lhs-width2=400,--listing-rhs-width=400,--listing-cont-lines=2  \
				
ASFLAGS		:=	$(ARCH) -nostartfiles -nostdlib

LDFLAGS		:=	-static $(ARCH) -Os -Wl,--strip-discarded,--strip-debug,--print-gc-sections,--no-undefined 


export DEPSDIR	:=	$(TOPDIR)/$(BUILDDIR)

ifneq ($(BUILDDIR),$(notdir $(CURDIR)))
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
					-I $(CURDIR)/$(BUILDDIR)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L $(dir)/lib) 

.PHONY: re clean all $(VERSIONS)

#---------------------------------------------------------------------------------
all: $(VERSIONS)

$(VERSIONS):
	@[ -d $(BUILDDIR) ] || mkdir -p $(BUILDDIR)
	@$(MAKE) BUILD=$@ --no-print-directory -C $(BUILDDIR) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ... 
	@rm -fr $(BUILDDIR) $(OUTDIR)

re: clean all

#---------------------------------------------------------------------------------

else

SYMFILE	:=	$(TOPDIR)/source/symbols_$(BUILD).txt

LDFLAGS	+=	-Wl,-R,$(SYMFILE),-Map,$(BUILD).map

.PHONY: all

#---------------------------------------------------------------------------------

export OUTPUT	:=	$(TOPDIR)/$(OUTDIR)/$(notdir $(TOPDIR))_$(BUILD).a

all: $(OUTPUT)

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

$(BUILD).o : $(OFILES) $(SYMFILE)
	$(SILENTMSG) linking $(notdir $@)
	$(SILENTCMD)$(LD) $(LDFLAGS) $(OFILES) $(LIBPATHS) $(LIBS) -r -o $@
	$(SILENTCMD)$(NM) -CSn $@ > $(basename $(notdir $@)).lst

$(OUTPUT) : $(BUILD).o 
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
