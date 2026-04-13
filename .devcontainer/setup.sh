#!/bin/bash
set -e

sudo apt-get update

sudo apt-get install -y gcc make valgrind gdb

sudo apt update

sudo apt install python3-pip

sudo python3 -m pip install --upgrade pip setuptools

sudo python3 -m pip install norminette
