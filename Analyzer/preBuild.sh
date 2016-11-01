#!/bin/bash
dir=`dirname $0`
priorPWD=$PWD
cd $dir

#Clear Invalid Data.
rm *.jsonpart
#rm *.json

#clang-format
prjDir=$(dirname $dir)
find $prjDir -type f -name "*.m" | xargs /opt/llvm/llvm_build/bin/clang-format -i -style=LLVM
find $prjDir -type f -name "*.h" | xargs /opt/llvm/llvm_build/bin/clang-format -i -style=LLVM
cd $priorPWD
