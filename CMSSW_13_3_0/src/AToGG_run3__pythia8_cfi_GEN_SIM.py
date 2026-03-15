import FWCore.ParameterSet.Config as cms

process = cms.Process("GEN")

# Standard services
process.load("Configuration.StandardSequences.Services_cff")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.Generator_cff")
process.load("GeneratorInterface.Core.genFilterSummary_cff")
process.load("Configuration.StandardSequences.EndOfProcess_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

# genParticles for analysis
process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")

# Number of events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)

# Empty source
process.source = cms.Source("EmptySource")

# Run-3 GlobalTag
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic", "")

# Generator (A -> gamma gamma)
process.generator = cms.EDFilter(
    "Pythia8EGun",

    PGunParameters = cms.PSet(
        AddAntiParticle = cms.bool(False),
        MaxEta = cms.double(2.4),
        MinEta = cms.double(-2.4),
        MaxPhi = cms.double(3.14159265359),
        MinPhi = cms.double(-3.14159265359),
        MaxE = cms.double(50.0),
        MinE = cms.double(0.0),
        ParticleID = cms.vint32(36)
    ),

    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring(
            "pythia8CommonSettings",
            "py8ADecaySettings"
        ),

        py8ADecaySettings = cms.vstring(
            "36:onMode = off",
            "36:onIfAny = 22 22"
        ),

        pythia8CommonSettings = cms.vstring(
            "Tune:preferLHAPDF = 2",
            "Main:timesAllowErrors = 10000",
            "Check:epTolErr = 0.01",
            "ParticleDecays:limitTau0 = on",
            "ParticleDecays:tau0Max = 10",
            "ParticleDecays:allowPhotonRadiation = on",
            "Higgs:useBSM = on",
            "HiggsBSM:all = on",
            "35:m0 = 125",
            "36:m0 = 10"
        )
    )
)

# Output file
process.GENoutput = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string("file:AToGG_Run3_GEN.root"),
    outputCommands = process.GENEventContent.outputCommands
)

# keep genParticles
process.GENoutput.outputCommands.append("keep *_genParticles_*_*")

# Paths
process.generation_step = cms.Path(process.pgen_genonly)
process.genparticles_step = cms.Path(process.genParticles)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.GENoutput_step = cms.EndPath(process.GENoutput)

# Schedule
process.schedule = cms.Schedule(
    process.generation_step,
    process.genparticles_step,
    process.genfiltersummary_step,
    process.endjob_step,
    process.GENoutput_step
)

# Insert generator
for path in process.paths:
    getattr(process, path).insert(0, process.generator)
