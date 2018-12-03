#!/bin/bash

make clean
rm -f ./Makefile
/usr/bin/qmake ./pro/lib/gui.pro

echo "Makefile QT has been updated to support host!"

