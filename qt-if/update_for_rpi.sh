#!/bin/bash

make clean
rm -f ./Makefile
/opt/qtrpi/bin/qmake-qtrpi ./pro/gui.pro

echo "Makefile QT has been updated to support remote!"

