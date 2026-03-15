import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run2_2018_cff import Run2_2018

process = cms.Process('HLT', Run2_2018)

# Standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# Maximum events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

# Input source
process.source = cms.Source("PoolSource",
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
    fileNames = cms.untracked.vstring('file:step1_GEN_SIM.root'),
    inputCommands = cms.untracked.vstring(
        'keep *', 
        'drop *_genParticles_*_*', 
        'drop *_genParticlesForJets_*_*', 
        'drop *_kt4GenJets_*_*', 
        'drop *_kt6GenJets_*_*', 
        'drop *_iterativeCone5GenJets_*_*', 
        'drop *_ak4GenJets_*_*', 
        'drop *_ak7GenJets_*_*', 
        'drop *_ak8GenJets_*_*', 
        'drop *_ak4GenJetsNoNu_*_*', 
        'drop *_ak8GenJetsNoNu_*_*', 
        'drop *_genCandidatesForMET_*_*', 
        'drop *_genParticlesForMETAllVisible_*_*', 
        'drop *_genMetCalo_*_*', 
        'drop *_genMetCaloAndNonPrompt_*_*', 
        'drop *_genMetTrue_*_*', 
        'drop *_genMetIC5GenJs_*_*'
    ),
    secondaryFileNames = cms.untracked.vstring()
)

# Production info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step1_GEN_SIM.py nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition
process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('file:step2_DIGI_L1_DIGI2RAW_HLT.root'),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Mixing module (pileup) setup
process.mix.input.nbPileupEvents.averageNumber = cms.double(0.0)
process.mix.input.type = cms.string('poisson')
process.mix.input.fileNames = cms.untracked.vstring()                # primary input
process.mix.input.fileNamesSecondary = cms.untracked.vstring()      # secondary input (must exist)
# Empty mix objects (to avoid default GEN-SIM mixing)
process.mix.mixObjects.mixCH = cms.PSet()
process.mix.mixObjects.mixTracks = cms.PSet()
process.mix.mixObjects.mixVertices = cms.PSet()
process.mix.mixObjects.mixSH = cms.PSet()
process.mix.mixObjects.mixHepMC = cms.PSet()
process.mix.mixObjects.mixEcalHits = cms.PSet()
process.mix.mixObjects.mixHcalHits = cms.PSet()
process.mix.mixObjects.mixHFHITS = cms.PSet()
process.mix.mixObjects.mixSimTracks = cms.PSet()
process.mix.mixObjects.mixSimVertices = cms.PSet()
process.mix.mixObjects.mixMuonSimHits = cms.PSet()
process.mix.mixObjects.mixPixelDigi = cms.PSet()
process.mix.mixObjects.mixStripDigi = cms.PSet()

# Global Tag
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2018_realistic', '')

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,
                                process.L1simulation_step,
                                process.digi2raw_step)
#process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step, process.FEVTDEBUGHLToutput_step])

from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

# HLT customization
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC
process = customizeHLTforMC(process)