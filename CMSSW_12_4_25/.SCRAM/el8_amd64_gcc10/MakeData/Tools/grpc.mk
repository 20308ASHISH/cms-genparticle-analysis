ALL_TOOLS      += grpc
grpc_EX_INCLUDE := /cvmfs/cms.cern.ch/el8_amd64_gcc10/external/grpc/1.35.0-1bd69a243ff070cfbfbff0f7e608eafc/include
grpc_EX_LIB := grpc grpc++ grpc++_reflection
grpc_EX_USE := protobuf openssl pcre
grpc_EX_FLAGS_SYSTEM_INCLUDE  := 1

