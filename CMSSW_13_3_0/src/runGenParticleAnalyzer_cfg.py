import FWCore.ParameterSet.Config as cms

process = cms.Process("GENANA")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/eos/home-a/asmishra/cms_project/CMSSW_10_6_29/src/MySampleProduction/MyPiZeros/python/step1AToGG_Gamma50_M1.root'
    )
)

process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string("genparticle_hist.root")
)

process.genana = cms.EDAnalyzer(
    "GenParticleAnalyzer",
    genParticles = cms.InputTag("genParticles")
)

process.p = cms.Path(process.genana)
