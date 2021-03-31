#!/bin/bash
#
# Copyright © 2021 Maxim Morozov. All rights reserved.
#
# Created by Maxim Morozov on 31/03/2021.
#
# bijective-numeration
#
# build.sh
#

APPLICATION_HOME="$(pwd)"
APPLICATION_BUILD="${APPLICATION_HOME}/build"

rm -rf "${APPLICATION_BUILD}"
mkdir -p "${APPLICATION_BUILD}"

pushd "${APPLICATION_BUILD}" >/dev/null

# CMake supports the build types: Debug, Release, MinSizeRel, RelWithDebInfo.
cmake -DCMAKE_BUILD_TYPE=Release "${APPLICATION_HOME}"
EXIT_CODE=$?
if [[ "$EXIT_CODE" -ne 0 ]]; then
    echo "ERROR: CMake failed with exit code $EXIT_CODE"
    exit "$EXIT_CODE"
fi

make
EXIT_CODE=$?
if [[ "$EXIT_CODE" -ne 0 ]]; then
    echo "ERROR: Make failed with exit code $EXIT_CODE"
    exit "$EXIT_CODE"
fi

make install
EXIT_CODE=$?
if [[ "$EXIT_CODE" -ne 0 ]]; then
    echo "ERROR: Install failed with exit code $EXIT_CODE"
    exit "$EXIT_CODE"
fi

popd >/dev/null
