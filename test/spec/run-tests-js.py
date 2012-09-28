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
  # 32512 is 'command not found' in python's OS module exit codes
  # 256 occurs on some platforms (mac, maybe linux?)
  # 1 occurs on windows
  return status != 32512, 256, 1

def runTests(root, files, expected):
  failed = 0
  passed = 0

  # Run good tests
  for f in files:
    # Get file's absolute path
    file_path = os.path.join(root, f)

    # Run file against webvtt parser (in silent mode)
    retcode = subprocess.call(["webvtt", "-s", file_path], stdout=subprocess.PIPE, shell=True)

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
