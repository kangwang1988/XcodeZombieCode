#!/bin/bash
dir=`dirname $0`
priorPWD=$PWD
cd $dir

$dir/XcodeZombieCodeAnalyzer $dir AppDelegate

#Clear Invalid Data.
rm *.jsonpart

cd $priorPWD
