ALL_TOOLS      += grpc
grpc_EX_INCLUDE := /cvmfs/cms.cern.ch/el8_amd64_gcc12/external/grpc/1.35.0-f327d65411de1c515e097e9893c667f1/include
grpc_EX_LIB := grpc grpc++ grpc++_reflection
grpc_EX_USE := protobuf openssl pcre abseil-cpp c-ares re2
grpc_EX_FLAGS_SYSTEM_INCLUDE  := 1

