# Alamance Maker's Guild Big Tetris

This is my fork of the AMG's Big Tetris project from the 2016 [Burlington Mini Maker Faire](https://burlingtonminimakerfaire.com/).
The purpose of this project is twofold:

- to gussy up the code to make it available as an example for other people to develop against
- to provide a reasonably cross-platform simulator so people can test their code in software before taking it to the Big League

Most of the focus is currently on the simulator, but once I get a chance I'll be truing up
the code to make sure it still works on the Big Tetris board.

## Building the simulator

Minimal effort has been put into making it easy to use. It depends on FLTK, so it should build pretty easily for
Linux or OSX>

### OSX

```
brew install fltk # if you have homebrew installed
git clone <this repo>
cd <repo>/sim
make
./sim
# profit
```

### Linux

```
sudo apt-get install lib-fltk #maybe? or yum install, or whatever
git clone <this repo>
cd <repo>/sim
make
./sim
# profit
```

### Windows

TBD
