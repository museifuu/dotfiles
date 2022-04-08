# The following lines were added by compinstall

zstyle ':completion:*' completer _complete _ignored _approximate
zstyle ':completion:*' group-name ''
zstyle ':completion:*' insert-unambiguous true
zstyle ':completion:*' list-colors ''
zstyle ':completion:*' max-errors 1
zstyle ':completion:*' menu select=long
zstyle ':completion:*' original true
zstyle ':completion:*' squeeze-slashes true
zstyle ':completion:*' verbose true
zstyle :compinstall filename '/home/kauan/.zshrc'

autoload -Uz compinit
compinit
# End of lines added by compinstall
# Lines configured by zsh-newuser-install
HISTFILE=~/.zsh_history
HISTSIZE=20000
SAVEHIST=20000
setopt autocd extendedglob notify
unsetopt beep nomatch
bindkey -v
# End of lines configured by zsh-newuser-install
bindkey '^R' history-incremental-search-backward
bindkey "^[[2~" overwrite-mode
bindkey "^[[H"  beginning-of-line
bindkey "^[[5~" up-line-or-history
bindkey "^[[3~" delete-char
bindkey "^[[F"  end-of-line
bindkey "^[[6~" down-line-or-history

PS1="%(!.%B%F{red}.%B%F{green}%n@)%m %F{blue}%(!.%1~.%~) %(!.#.$) %b%f"
source /usr/share/zsh/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh
export _JAVA_AWT_WM_NONREPARENTING=1
