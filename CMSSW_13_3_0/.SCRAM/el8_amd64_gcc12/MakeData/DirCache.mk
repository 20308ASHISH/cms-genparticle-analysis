ifeq ($(strip $(CMSSW_13_3_0/config)),)
src_CMSSW_13_3_0_config := self/CMSSW_13_3_0/config
CMSSW_13_3_0/config  := src_CMSSW_13_3_0_config
src_CMSSW_13_3_0_config_BuildFile    := $(WORKINGDIR)/cache/bf/src/CMSSW_13_3_0/config/BuildFile
src_CMSSW_13_3_0_config_LOC_USE := self 
src_CMSSW_13_3_0_config_EX_USE   := $(foreach d,$(src_CMSSW_13_3_0_config_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
ALL_EXTERNAL_PRODS += src_CMSSW_13_3_0_config
src_CMSSW_13_3_0_config_INIT_FUNC += $$(eval $$(call EmptyPackage,src_CMSSW_13_3_0_config,src/CMSSW_13_3_0/config))
endif

ifeq ($(strip $(PhysicsAnalysisGenParticleAnalyzerAuto)),)
PhysicsAnalysisGenParticleAnalyzerAuto := self/src/PhysicsAnalysis/GenParticleAnalyzer/plugins
PLUGINS:=yes
PhysicsAnalysisGenParticleAnalyzerAuto_files := $(patsubst src/PhysicsAnalysis/GenParticleAnalyzer/plugins/%,%,$(wildcard $(foreach dir,src/PhysicsAnalysis/GenParticleAnalyzer/plugins ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PhysicsAnalysisGenParticleAnalyzerAuto_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsAnalysis/GenParticleAnalyzer/plugins/BuildFile
PhysicsAnalysisGenParticleAnalyzerAuto_LOC_USE := self   FWCore/Framework FWCore/ParameterSet FWCore/ServiceRegistry CommonTools/UtilAlgos DataFormats/HepMCCandidate root rootcore 
PhysicsAnalysisGenParticleAnalyzerAuto_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PhysicsAnalysisGenParticleAnalyzerAuto,PhysicsAnalysisGenParticleAnalyzerAuto,$(SCRAMSTORENAME_LIB),src/PhysicsAnalysis/GenParticleAnalyzer/plugins))
PhysicsAnalysisGenParticleAnalyzerAuto_PACKAGE := self/src/PhysicsAnalysis/GenParticleAnalyzer/plugins
ALL_PRODS += PhysicsAnalysisGenParticleAnalyzerAuto
PhysicsAnalysis/GenParticleAnalyzer_forbigobj+=PhysicsAnalysisGenParticleAnalyzerAuto
PhysicsAnalysisGenParticleAnalyzerAuto_INIT_FUNC        += $$(eval $$(call Library,PhysicsAnalysisGenParticleAnalyzerAuto,src/PhysicsAnalysis/GenParticleAnalyzer/plugins,src_PhysicsAnalysis_GenParticleAnalyzer_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS),edm))
PhysicsAnalysisGenParticleAnalyzerAuto_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,PhysicsAnalysisGenParticleAnalyzerAuto,src/PhysicsAnalysis/GenParticleAnalyzer/plugins))
endif
ALL_COMMONRULES += src_PhysicsAnalysis_GenParticleAnalyzer_plugins
src_PhysicsAnalysis_GenParticleAnalyzer_plugins_parent := PhysicsAnalysis/GenParticleAnalyzer
src_PhysicsAnalysis_GenParticleAnalyzer_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsAnalysis_GenParticleAnalyzer_plugins,src/PhysicsAnalysis/GenParticleAnalyzer/plugins,PLUGINS))
