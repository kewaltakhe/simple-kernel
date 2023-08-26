# A Simple Bootloader for x86 machine

A simple bootloader for x86 machine. It contains a kernel with screen driver. The project is tested on Qemu emulator.<br><br>
During my college years, I learned about computer system architecture and operating systems. While I gained insights through separate experiments, I always wanted a more holistic understanding of the intricate connection between hardware and software.<br><br>
This project, born from that curiosity, provides a hands-on exploration of the fascinating journey from computer hardware to software. It experiments with BIOS loading the bootsector, Memory-mapped device drivers. Then, step by step, towards a kernel using the higher-level language C is created. This project acts as an entry point to the process of building an operating system from scratch.

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Screenshots](#screenshots)
- [Technologies Used](#technologies-used)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## About


## Features Included
In this repository, instead of making separate folders and walking through each steps, I have uploaded a working version of the project. This includes (in order)

- BIOS loading the boot sector code
- BIOS disk read to main memory
- Switch from 16-bit real mode to 32-bit protected mode
- Screen driver
- Keyboard driver

## How To Experiment 
(for Linux )
In order to build the os-image, you will need to install NASM, Qemu and 32-bit [cross-compiler](https://wiki.osdev.org/GCC_Cross-Compiler) to compile the kernel.
Once the cross compiler is installed. Update the line 7 of makefile `CC = i686-elf-gcc` to the path of your cross-compiler installed. <br><br>
Then run these commands
```bash
git clone https://github.com/kewaltakhe/simple-kernel.git
cd simple-kernel
make clean
make
make run
```

