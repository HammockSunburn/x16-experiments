# x16 Software Development Notes

These notes document how I've gotten basic x16 development working on Fedora Linux. If you run another flavor of Linux, these notes may still be useful, you'll just need to substitute some package names for your distribution of choice.

## Preliminaries

You'll need the `cc65` cross development package to build the ROM and `SDL2` to build the emulator. These are both pre-packaged for Fedora:

```shell
sudo dnf install cc65 SDL2-devel
```

## x16 ROM

To build the x16 ROM, you'll need to checkout the project from its Github home. I put these in `$HOME/git`.

To ensure that the ROM and emulator are compatible, checkout the latest tag for each of them. As of this writing, that happens to be `r37`.

```shell
mkdir -p ~/git
cd ~/git
git clone https://github.com/commanderx16/x16-rom.git
cd x16-rom
git checkout tags/r37
make -j6
mkdir ~/x16
cp build/x16/rom.bin ~/x16
```

The output of the build process is a binary file containing the ROM in `build/x16/rom.bin`. I copy that to `~/x16`.

## x16 Emulator

Next, we'll build the emulator and have it use the ROM we just built.

```shell
cd ~/git
git clone https://github.com/commanderx16/x16-emulator.git
cd x16-emulator
git checkout tags/r37
make -j6
cp x16emu ~/x16
```

Like the ROM above, I copy this to `~/x16`.

You can start the emulator now:

```shell
cd ~/x16
./x16emu
```

As is customary, you must now enter a simple BASIC program and ensure it runs.

```basic
10 PRINT "HELLO WORLD"
20 GOTO 10
RUN
```

Stop execution with `CTRL+C`.

## ACME Cross Assembler

One must transport oneself back in time and use Sourceforge to get the code for ACME. Even though it's `svn`, I still put it in a directory called `git`.

```shell
cd ~/git
svn checkout https://svn.code.sf.net/p/acme-crossass/code-0/trunk acme-crossass-code-0
cd acme-crossass-code-0/src
make
cp acme ~/x16
```

As with 

## Run a Simple C Example

In the `c` directory, I've prepared the code from the `cc65` tutorial. It's pretty simple to get it built, but the documentation doesn't take into account case-sensitive filenames, but I do below.

```shell
cd c
cl65 -O -t cx16 -o HELLO hello.c text.s
```

You should now be able to run `~/git/x16-emulator/x16emu` and load the program we just built from within the emulator:

```basic
LOAD "HELLO",8
RUN
```

This will run the program and leave the emulator's graphics in lowercase capable mode.

## Run a Simple Assembly Example

In the `asm` directory, I've prepared the code from [Dansbo Tech Blog](https://techblog.dansbo.dk/?p=191). To build this:

```shell
cd asm
~/x16/acme --cpu w65c02 -f cbm -o HELLO hello.asm
```

You should then be able to run `~/git/x16-emulator/x16emu` and load the program we just built from within the emulator:

```basic
LOAD "HELLO",8
RUN
```