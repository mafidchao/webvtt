#!/bin/bash
echo "Ratio used: $1"
mkdir fuzzedFiles
for file in $(ls ../objdir/test/spec/good)
do  
    zzuf -r $1 cat ../objdir/test/spec/good/$file > fuzzedFiles/good.$file.fuzzed.vtt
done
for file in $(ls ../objdir/test/spec/bad)

do
    zzuf -r $1 cat ../objdir/test/spec/bad/$file > fuzzedFiles/bad.$file.fuzzed.vtt
done

