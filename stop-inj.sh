#!/bin/bash

DIR=`dirname -- $0`

machines=(anchovy barracuda blowfish bonito brill bullhead char cod dorado eel flounder grouper halibut herring mackerel marlin perch pollock sardine shark sole swordfish tarpon turbot tuna wahoo)

DIR=`dirname -- $0`
FQDIR=`realpath -- $DIR`

for m in ${machines[@]}
do
  echo $m
  ssh $m "tmux kill-session -t abft-inj"
done

