#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os

################################### Protoc Compiler ###############################

def parseFileTypeFromeFilePath(filePath):
    if os.path.isdir(filePath):
        return ""

    fileName = os.path.basename(filePath)
    return parseFileTypeFromFileName(fileName)

def parseFileTypeFromFileName(fileName):
    fileNameSplit = fileName.split(".")
    fileType = ""

    if len(fileNameSplit) > 1:
        fileType = fileNameSplit[1]
    elif len(fileNameSplit) == 1:
        fileType = fileNameSplit[0]

    return fileType

################################### Protoc Compiler ###############################

def compileObjectiveC(protocFilePath, outputPath):
    if os.path.exists(protocFilePath) == False:
        print "file not exist: " + protocFilePath
        return

    fileType = parseFileTypeFromeFilePath(protocFilePath)

    if fileType != "proto" and fileType != "protoc":
        print "file type not support: " + protocFilePath
        return

    fileFolder = os.path.dirname(protocFilePath);
    fileParentFolder = os.path.dirname(fileFolder)
    resultStr = os.popen("protoc " + protocFilePath + " --proto_path=" + fileParentFolder + " --objc_out=" + outputPath).read()
    print resultStr

def compileCpp(protocFilePath, outputPath):
    if os.path.exists(protocFilePath) == False:
        print "file not exist: " + protocFilePath
        return

    fileType = parseFileTypeFromeFilePath(protocFilePath)

    if fileType != "proto" and fileType != "protoc":
        print "file type not support: " + protocFilePath
        return

    fileFolder = os.path.dirname(protocFilePath);
    fileParentFolder = os.path.dirname(fileFolder)
    resultStr = os.popen("protoc " + protocFilePath + " --proto_path=" + fileParentFolder + " --cpp_out=" + outputPath).read()
    print resultStr

################################### Main ###############################

def searchAllFilesToCompile(projectPath, output, compileFunc):
    rootDir = os.path.abspath(projectPath)
    for lists in os.listdir(rootDir):
        if lists == ".DS_Store":
            continue

        newOutput = output
        newPath = os.path.join(rootDir, lists);

        # print newPath
        if os.path.isdir(newPath):
            newOutput = os.path.join(output, lists)
            searchAllFilesToCompile(newPath, newOutput, compileFunc)
        else:
            if os.path.exists(newOutput) == False:
                os.makedirs(newOutput)
            compileFunc(newPath, newOutput)

if __name__ == '__main__':
    # # For Test
    # projectPath = "./3.4"
    # outputPath = "./3.4/objectiveC"

    projectPath = raw_input("Project Folder Path: ")
    outputPath = raw_input("Output Folder Path: ")
    compileLanguage = raw_input("What language need to export, [objectiveC:1], please input number: ")
    compileFunc = None

    if int(compileLanguage) == 1:
        compileFunc = compileObjectiveC

    if not compileFunc:
        pass

    projectPath = os.path.abspath(projectPath)
    outputPath = os.path.abspath(outputPath)

    if os.path.exists(outputPath) == False:
        os.makedirs(outputPath)

    searchAllFilesToCompile(projectPath, outputPath, compileFunc, projectPath)
