#!/bin/env sh

set -e

gcc -fPIC -c main.c
ld -x --shared -o /lib/security/pam_trusthome.so main.o
chmod 755 /lib/security/pam_trusthome.so
rm main.o

cp ishome /etc/security/
chown root:root /etc/security/ishome
chmod 005 /etc/security/ishome
