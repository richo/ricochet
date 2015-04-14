#!/bin/sh -x

inputs="./src/protocol/ContactRequestChannel.proto ./src/protocol/ControlChannel.proto ./src/protocol/AuthHiddenService.proto ./src/protocol/ChatChannel.proto"

for i in $inputs; do
    protoc --proto_path src/protocol $i --python_out protobufs
done
