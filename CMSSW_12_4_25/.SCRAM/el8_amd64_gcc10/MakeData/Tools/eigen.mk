ALL_TOOLS      += eigen
eigen_EX_INCLUDE := /cvmfs/cms.cern.ch/el8_amd64_gcc10/external/eigen/82dd3710dac619448f50331c1d6a35da673f764a-cc5ed88b76e386be0baea3ab0a896c6a/include/eigen3
eigen_EX_FLAGS_CPPDEFINES  := -DEIGEN_DONT_PARALLELIZE
eigen_EX_FLAGS_CUDA_FLAGS  := --diag-suppress 20014

