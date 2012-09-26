#!/usr/bin/env python

"""
Loops through the directory path passed to it in sys.argv[1], finds any .test files, strips the .vtt file from it, and
saves it to a mirrored directory structure under webvtt/objdir/spec
"""

import os
import sys

def stripVTT(filePath):
  testFile = open(filePath, 'r')
  fileData = testFile.read()

  # Rip the VTT
  return fileData[fileData.find('*/\n') + 3:]

def findTestFiles(root, fileList):
	#List the directory
	dirList = os.listdir(root)

	for d in dirList:
		#Join the folder and/or file name that has been listed to the root path
		dir_path = os.path.join(root, d)
		#If the path is a directory than recursivley walk the directory tree
		if os.path.isdir(dir_path):
			findTestFiles(dir_path, fileList)
		#If the file path is for a .test file than append it to the file list
		elif os.path.splitext(dir_path)[1] == ".test":
			fileList.append(dir_path)

def main():
	#List that will contain the file paths of the .test files
	fileList = list()

	#Find all the test files in the directory specified by the first command line argument
	findTestFiles(sys.argv[1], fileList)
	
	#Get the absolute path to the directory which will contain the ripped vtt files
	#This path is specified by the second command line argument
	pathToObjDir = os.path.realpath(sys.argv[2])

	for f in fileList:
		#Strip the .test file of its .vtt
		vttFileInfo = stripVTT(f)

		#Get the absolute file path of the new .vtt file
		vttFilePath = os.path.join(pathToObjDir, f[2:])
		#Get the directory path where the new .vtt file will be stored
		vttFileDirPath = os.path.dirname(vttFilePath)

		#If the directory path of the .vtt file does not exist then create it
		if os.path.exists(vttFileDirPath) != 1:
			os.makedirs(vttFileDirPath)

		#Open the new vtt file and write the vtt content to it
		vttFile = open(vttFilePath, 'w')

		for fileLine in vttFileInfo:
			vttFile.writelines(fileLine)

		vttFile.close()

if __name__ == '__main__':
	status = main()
	sys.exit(status)