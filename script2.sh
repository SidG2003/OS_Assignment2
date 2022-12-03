#!/bin/bash
rm -r linux-5.19.8
echo "deleted"
tar xvf linux-5.19.8.tar.xz
echo "untarred"
cp /home/user1/Ass2config /home/user1/Ass2/linux-5.19.8/.config
cd linux-5.19.8
echo "copied config and entered linux-5.19.8"
make -j2
