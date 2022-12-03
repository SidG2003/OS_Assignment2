#!/bin/bash
cd /home/user1/kernelbuild/linux-5.19.8/os-repo
cp .config /home/user1/kernelbuild/linux-5.19.8
cd ..
make menuconfig
make -j2
make modules_install
cp -v arch/x86_64/boot/bzImage /boot/vmlinuz-linux2
mkinitcpio -k 5.19.8 -g /boot/initramfs-linux2.img
cp System.map /boot/System.map-linux2
cp /boot/System.map-linux2 System.map
grub-mkconfig -o /boot/grub/grub.cfg
update-grub
