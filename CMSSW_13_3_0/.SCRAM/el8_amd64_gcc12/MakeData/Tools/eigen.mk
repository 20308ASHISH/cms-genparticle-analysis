ALL_TOOLS      += eigen
eigen_EX_INCLUDE := /cvmfs/cms.cern.ch/el8_amd64_gcc12/external/eigen/3bb6a48d8c171cf20b5f8e48bfb4e424fbd4f79e-36a69a0d7b82bf7496dcc3ff29886d0d/include/eigen3
eigen_EX_FLAGS_CPPDEFINES  := -DEIGEN_DONT_PARALLELIZE
eigen_EX_FLAGS_CUDA_FLAGS  := --diag-suppress 20014

