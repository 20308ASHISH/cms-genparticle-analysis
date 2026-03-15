ifeq ($(strip $(demoDemoAnalyzerAuto)),)
demoDemoAnalyzerAuto := self/src/demo/DemoAnalyzer/plugins
PLUGINS:=yes
demoDemoAnalyzerAuto_files := $(patsubst src/demo/DemoAnalyzer/plugins/%,%,$(wildcard $(foreach dir,src/demo/DemoAnalyzer/plugins ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
demoDemoAnalyzerAuto_BuildFile    := $(WORKINGDIR)/cache/bf/src/demo/DemoAnalyzer/plugins/BuildFile
demoDemoAnalyzerAuto_LOC_USE := self  FWCore/Framework FWCore/ParameterSet FWCore/PluginManager CommonTools/UtilAlgos FWCore/ServiceRegistry DataFormats/TrackReco
demoDemoAnalyzerAuto_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,demoDemoAnalyzerAuto,demoDemoAnalyzerAuto,$(SCRAMSTORENAME_LIB),src/demo/DemoAnalyzer/plugins))
demoDemoAnalyzerAuto_PACKAGE := self/src/demo/DemoAnalyzer/plugins
ALL_PRODS += demoDemoAnalyzerAuto
demo/DemoAnalyzer_forbigobj+=demoDemoAnalyzerAuto
demoDemoAnalyzerAuto_INIT_FUNC        += $$(eval $$(call Library,demoDemoAnalyzerAuto,src/demo/DemoAnalyzer/plugins,src_demo_DemoAnalyzer_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS),edm))
demoDemoAnalyzerAuto_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,demoDemoAnalyzerAuto,src/demo/DemoAnalyzer/plugins))
endif
ALL_COMMONRULES += src_demo_DemoAnalyzer_plugins
src_demo_DemoAnalyzer_plugins_parent := demo/DemoAnalyzer
src_demo_DemoAnalyzer_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_demo_DemoAnalyzer_plugins,src/demo/DemoAnalyzer/plugins,PLUGINS))
