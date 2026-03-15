ifeq ($(strip $(CMSSW_13_3_0/config)),)
src_CMSSW_13_3_0_config := self/CMSSW_13_3_0/config
CMSSW_13_3_0/config  := src_CMSSW_13_3_0_config
src_CMSSW_13_3_0_config_BuildFile    := $(WORKINGDIR)/cache/bf/src/CMSSW_13_3_0/config/BuildFile
src_CMSSW_13_3_0_config_LOC_USE := self 
src_CMSSW_13_3_0_config_EX_USE   := $(foreach d,$(src_CMSSW_13_3_0_config_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
ALL_EXTERNAL_PRODS += src_CMSSW_13_3_0_config
src_CMSSW_13_3_0_config_INIT_FUNC += $$(eval $$(call EmptyPackage,src_CMSSW_13_3_0_config,src/CMSSW_13_3_0/config))
endif

