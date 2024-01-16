#!/bin/sh

if [[ "$1" == "" ]] ; then
        echo "Please specify the project name!"
        exit 0
fi

P="LTE5398-M904_Generic"

echo "P=$P"

echo "copy $TOPDIR/configs/$P.defconfig to .config!"
cp $TOPDIR/configs/$P.defconfig $TOPDIR/.config


