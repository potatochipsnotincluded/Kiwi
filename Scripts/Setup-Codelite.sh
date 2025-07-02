#!/bin/bash

pushd ..
Vendor/Binaries/Premake/Linux/premake5 --file=Build.lua codelite
popd
