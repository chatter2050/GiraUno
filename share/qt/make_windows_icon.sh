#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/girauno.png
ICON_DST=../../src/qt/res/icons/girauno.ico
convert ${ICON_SRC} -resize 16x16 girauno-16.png
convert ${ICON_SRC} -resize 32x32 girauno-32.png
convert ${ICON_SRC} -resize 48x48 girauno-48.png
convert girauno-16.png girauno-32.png girauno-48.png ${ICON_DST}

