#!/usr/bin/env python

"""
run-tests-js.py <good_test_dir> <bad_test_dir>

Runs all spec tests for WebVTT using the JavaScript WebVTT Parser

Requires node.js and the webvtt npm module,
see https://github.com/humphd/node-webvtt
"""

import os
import sys
import subprocess
import commands

def checkForWebVTT():
  status, result = commands.getstatusoutput("webvtt")
  # This should fail with a "Missing input file(s).\nUsage: webvtt [options] <file...>"
  # message, so expecting 256.  TODO: confirm on other platforms (tested on Mac)
  return status == 256 or status == 1

def runTests(root, files, expected):
  failed = 0
  passed = 0

  # Run good tests
  for f in files:
    # Get file's absolute path
    file_path = os.path.join(root, f)
    # If the file is not a .vtt file, skip this iteration
    extension = os.path.splitext(file_path)[1]
    if extension != ".vtt": continue
    # Run file against webvtt parser (in silent mode) for Windows OS
    if os.name == 'nt':
      retcode = subprocess.call(["webvtt", "-s", file_path], stdout=subprocess.PIPE, shell=True)
    # Run file against webvtt parser (in silent mode) for other OSs
    else :
      retcode = subprocess.call(["webvtt", "-s", file_path], stdout=subprocess.PIPE)
    # If we did NOT get expected, add file to fail list & increase fail count.
    if retcode != expected:
      failed = failed + 1
      print "Failed %s" % file_path
    else:
      passed = passed + 1

  return failed, passed

def main():
  # Make sure that node.js + npm + webvtt are available
  if checkForWebVTT() == False:
    print "Error: missing npm webvtt module, see https://github.com/humphd/node-webvtt"
    sys.exit(1)

  test_root = sys.argv[1]

  failed_total = 0
  passed_total = 0

  for test_suite in [{'name': 'good', 'expected': 0},
                     {'name': 'bad', 'expected': 1}]:
    root = os.path.realpath(os.path.join(test_root, test_suite['name']))
    failed, passed = runTests(root, os.listdir(root), test_suite['expected'])
    failed_total = failed_total + failed
    passed_total = passed_total + passed

  print "\n%s Passed, %s Failed, %s Total." % (passed_total, failed_total, passed_total + failed_total)

if __name__ == '__main__':
  status = main()
  sys.exit(status)
