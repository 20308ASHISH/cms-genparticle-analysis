ALL_TOOLS      += clhepheader
clhepheader_EX_INCLUDE := /cvmfs/cms.cern.ch/el8_amd64_gcc12/external/clhep/2.4.7.1-5bfe601b6d65215d210a10fe9d6d7478/include
clhepheader_EX_USE := root_cxxdefaults
clhepheader_EX_FLAGS_ROOTCLING_ARGS  := -moduleMapFile=$(CLHEP_BASE)/include/module.modulemap
clhepheader_EX_FLAGS_SYSTEM_INCLUDE  := 1

