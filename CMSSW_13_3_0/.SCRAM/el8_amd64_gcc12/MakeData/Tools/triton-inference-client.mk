ALL_TOOLS      += triton-inference-client
triton-inference-client_EX_INCLUDE := /cvmfs/cms.cern.ch/el8_amd64_gcc12/external/triton-inference-client/2.25.0-d9efed4bee1f73308d72a3c3216a3954/include
triton-inference-client_EX_LIB := grpcclient tritoncommonmodelconfig
triton-inference-client_EX_USE := protobuf grpc cuda re2

