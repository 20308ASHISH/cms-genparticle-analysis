ALL_COMMONRULES += src_MyAnalysis_PhotonAnalyzer_plugins
src_MyAnalysis_PhotonAnalyzer_plugins_parent := MyAnalysis/PhotonAnalyzer
src_MyAnalysis_PhotonAnalyzer_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_MyAnalysis_PhotonAnalyzer_plugins,src/MyAnalysis/PhotonAnalyzer/plugins,PLUGINS))
