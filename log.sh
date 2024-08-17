#!/bin/bash

DIR=`dirname -- $0`

function clean_exit() {
  exit
}

trap 'clean_exit' SIGINT

BINARY=`realpath -- $1`
BINARY_BASENAME=`basename -- $BINARY`

LOG_FILE="${DIR}/data-logs/${BINARY_BASENAME}.$(hostname).log"

echo "# $(date)" > $LOG_FILE
echo "# $@" >> $LOG_FILE

LOG=1 $@ | tee -a $LOG_FILE

echo "# $(date)" >> $LOG_FILE

