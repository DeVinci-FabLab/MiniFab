#!/bin/bash

cd $( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )

source minifab-config.txt 

echo "Minifab V3 started up."

gpio mode $PRINTER_IN_PIN in
gpio mode $CNC_IN_PIN in
gpio mode $ENGRAVER_IN_PIN in
