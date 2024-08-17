#!/bin/bash

function clean_exit() {
  echo "stopping..."
  exit 1
}
trap 'clean_exit' SIGINT

DIR=`dirname -- $0`

echo "# dimensionality,(H,L),T,N,version,stencil,checksum,overhead"

T=1000
N=1e9
for H in $(seq 2 16)
do
  for L in $(seq 50 50 1000)
  do
    binary="$DIR/1d/$H/$L/bin/star1d1r.$H.$L.complexity"
    if [[ ! -f "$binary" ]]; then 
      continue
    fi
    $binary $T $N | sed 's~ (Y,C,overhead): ~,~' | sed "s~^~1d,($H,$L),$T,$N,~"
  done
done

N=1e9
for H in $(seq 2 16)
do
  for L in $(seq 50 50 500)
  do
    binary="$DIR/2d/$H/$L/bin/star2d1r.$H.$L.$L.complexity"
    if [[ ! -f "$binary" ]]; then 
      continue
    fi
    $binary $T $N | sed 's~ (Y,C,overhead): ~,~' | sed "s~^~2d,($H,$L),$T,$N,~"
  done
done

N=1e6
for H in $(seq 2 16)
do
  for L in $(seq 10 5 100)
  do
    binary="$DIR/3d/$H/$L/bin/star3d1r.$H.$L.$L.$L.complexity"
    if [[ ! -f "$binary" ]]; then 
      continue
    fi
    $binary $T $N | sed 's~ (Y,C,overhead): ~,~' | sed "s~^~3d,($H,$L),$T,$N,~"
  done
done

