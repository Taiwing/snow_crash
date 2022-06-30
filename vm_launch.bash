#!/usr/bin/env bash

ISO_PATH="${1-$HOME/sgoinfre/SnowCrash.iso}"

qemu-system-x86_64 -m 512 -net nic \
	-net user,hostfwd=tcp::2222-:4242,hostfwd=tcp::3333-:4747 \
	-cdrom $ISO_PATH
