#!/bin/env sh

set -e

gcc -fPIC -c main.c
ld -x --shared -o /lib/security/pam_trusthome.so main.o
chmod 755 /lib/security/pam_trusthome.so
rm main.o

cp ishome /usr/local/bin/
chown root:root /usr/local/bin/ishome
chmod 005 /usr/local/bin/ishome

cp hasyubi /usr/local/bin/
chown root:root /usr/local/bin/hasyubi
chmod 005 /usr/local/bin/hasyubi

cp isbypass /etc/security/
chown root:root /etc/security/isbypass
chmod 005 /etc/security/isbypass
