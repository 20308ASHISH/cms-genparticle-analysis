ALL_TOOLS      += geant4_interface
geant4_interface_EX_INCLUDE := /cvmfs/cms.cern.ch/el8_amd64_gcc12/external/geant4/11.1.2-e4b0fd9c4dcfc32da99906ef9483f04e/include/Geant4 /cvmfs/cms.cern.ch/el8_amd64_gcc12/external/geant4/11.1.2-e4b0fd9c4dcfc32da99906ef9483f04e/include
geant4_interface_EX_USE := clhep vecgeom zlib expat xerces-c root_cxxdefaults
geant4_interface_EX_FLAGS_CPPDEFINES  := -DGNU_GCC -DG4V9
geant4_interface_EX_FLAGS_CXXFLAGS  := -ftls-model=global-dynamic -pthread

