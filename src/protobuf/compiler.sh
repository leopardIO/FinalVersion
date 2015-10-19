#!/bin/bash

protoc -I=. --cpp_out=. *.proto
cp -f ./SearchResultMessage.pb.h ../nodeserver/
cp -f ./SearchResultMessage.pb.cc ../nodeserver/
cp -f ./SearchResultMessage.pb.h ../RS/
cp -f ./SearchResultMessage.pb.cc ../RS/
