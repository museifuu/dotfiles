#!/bin/sh

mkdir -p "$HOME/.local/bin"
mkdir -p "$HOME/.local/src"
mkdir -p "$HOME/.local/share/fonts"

BASEDIR=$(dirname "$(readlink -f "$BASH_SOURCE")")

ln -siv "$BASEDIR"/.local/bin/*                     -t  "$HOME/.local/bin"
ln -siv "$BASEDIR"/.local/src/status                -t  "$HOME/.local/src"
ln -siv "$BASEDIR"/.local/share/fonts/*             -t  "$HOME/.local/share/fonts"
ln -siv "$BASEDIR"/.local/src/dwmblocks/blocks.h        "$HOME/.local/src/dwmblocks/blocks.h"
ln -siv "$BASEDIR"/.config/*                        -t  "$HOME/.config"
ln -siv "$BASEDIR"/.vimrc                               "$HOME/.vimrc"
ln -siv "$BASEDIR"/.zshrc                               "$HOME/.zshrc"
