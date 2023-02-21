#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
from Utils.compileProtoc import *

if __name__ == '__main__':
    print "Build Protoc Begin"

    standardProtocFolder = os.path.abspath("./standard/protoc")
    standardCppFolder = os.path.abspath("./standard/cpp")

    searchAllFilesToCompile(standardProtocFolder, standardCppFolder, compileCpp)

    print "Build Protoc End"

    print "============================================================================="

