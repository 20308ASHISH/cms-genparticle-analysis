import FWCore.ParameterSet.Config as cms

process = cms.Process('SIM')

# Standard sequences
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')

process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')

# Run3 beamspot
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic25ns13p6TeVEarly2022Collision_cfi')

process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')

process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


# number of events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)

# empty event source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet()

# metadata
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('AToGG_Run3_EGun'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('1.0')
)

# Output
process.RAWSIMoutput = cms.OutputModule(
    "PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('file:step1AToGG_Run3.root'),
    outputCommands = process.RAWSIMEventContent.outputCommands
)

# GlobalTag (Run3)
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2022_realistic', '')


# A0 Event Gun
process.generator = cms.EDFilter("Pythia8EGun",

    PGunParameters = cms.PSet(
        ParticleID = cms.vint32(36),

        MinE = cms.double(0.0),
        MaxE = cms.double(50.0),

        MinEta = cms.double(-2.4),
        MaxEta = cms.double(2.4),

        MinPhi = cms.double(-3.14159265359),
        MaxPhi = cms.double(3.14159265359),

        AddAntiParticle = cms.bool(False)
    ),

    PythiaParameters = cms.PSet(

        parameterSets = cms.vstring(
            'pythia8CommonSettings',
            'py8ADecaySettings'
        ),

        py8ADecaySettings = cms.vstring(
            '36:onMode = off',
            '36:onIfMatch = 22 22'
        ),

        pythia8CommonSettings = cms.vstring(
            'Tune:preferLHAPDF = 2',
            'Main:timesAllowErrors = 10000',
            'Check:epTolErr = 0.01',
            'SLHA:keepSM = on',
            'SLHA:minMassSM = 1000.',
            'ParticleDecays:limitTau0 = on',
            'ParticleDecays:tau0Max = 10',
            'ParticleDecays:allowPhotonRadiation = on',

            'Higgs:useBSM = on',
            'HiggsBSM:all = on',

            '35:m0 = 125',
            '36:m0 = 10'
        )
    ),

    Verbosity = cms.untracked.int32(0),
    psethack = cms.string('A0 -> gamma gamma')
)


# Paths
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)

process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)

process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)


# Schedule
process.schedule = cms.Schedule(
    process.generation_step,
    process.genfiltersummary_step,
    process.simulation_step,
    process.endjob_step,
    process.RAWSIMoutput_step
)


# PAT task helper
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)


# insert generator in all paths (same concept as your file)
for path in process.paths:
    getattr(process, path).insert(0, process.generator)


# early deletion
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
