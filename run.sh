#!/bin/bash
#
# Copyright © 2021 Maxim Morozov. All rights reserved.
#
# Created by Maxim Morozov on 31/03/2021.
#
# bijective-numeration
#
# run.sh
#

APPLICATION_HOME="$(pwd)"
APPLICATION_BIN="${APPLICATION_HOME}/bin"
APPLICATION_EXE="${APPLICATION_BIN}/bijective-numeration"

"${APPLICATION_EXE}" $@
