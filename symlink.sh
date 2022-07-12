#!/bin/sh

ln -siv $PWD/.local/bin/* -t ~/.local/bin
ln -siv $PWD/.local/src/status -t ~/.local/src
ln -siv $PWD/.local/src/dwmblocks/blocks.h ~/.local/src/dwmblocks/blocks.h
ln -siv $PWD/.config/* -t ~/.config
ln -siv $PWD/.vimrc ~/.vimrc
ln -siv $PWD/.zshrc ~/.zshrc
