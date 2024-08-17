#!/bin/bash

function clean_exit() {
  echo "stopping..."
  exit 1
}
trap 'clean_exit' SIGINT

for H in $(seq 2 16)
do
  for L in $(seq 50 50 1000)
  do
    sizes="$H $L"
    out_dir="1d/$H/$L"
    if [[ -d "$out_dir/bin" ]]; then
      continue
    fi
    echo "$sizes..."
    acc -o $out_dir -m inputs/star1d1r.alpha $sizes
  done
done

for H in $(seq 2 16)
do
  for L in $(seq 50 50 500)
  do
    sizes="$H $L $L"
    out_dir="2d/$H/$L"
    if [[ -d "$out_dir/bin" ]]; then
      continue
    fi
    echo "$sizes..."
    acc -o $out_dir -m inputs/star2d1r.alpha $sizes
  done
done

for H in $(seq 2 16)
do
  for L in $(seq 10 5 100)
  do
    sizes="$H $L $L $L"
    out_dir="3d/$H/$L"
    if [[ -d "$out_dir/bin" ]]; then
      continue
    fi
    echo "$sizes..."
    acc -o $out_dir -m inputs/star3d1r.alpha $sizes
  done
done
