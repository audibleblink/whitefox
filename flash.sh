#!/usr/bin/env bash
set -e

export KEYMAP=alex
sleepTime=5
serialNum=mk20dx256vlh7

echo "[+] Building firmware..."
make

echo "[*] Press Magic + B to enter bootloader"
echo "[+] Sleeping $sleepTime seconds..."
sleep $sleepTime

echo "[+] Attempting to flash..."
dfu-util -D build/ch.bin -S $serialNum
