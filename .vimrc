syntax on
set number
set relativenumber
set tabstop=4
set shiftwidth=4
set expandtab
set smartindent
set encoding=utf-8
set fileencoding=utf8
set background=dark
filetype indent plugin off

autocmd BufRead,BufNewFile *.ms,*.me,*.mom set filetype=groff
autocmd Filetype groff inoremap á \['a]
autocmd Filetype groff inoremap Á \['A]
autocmd Filetype groff inoremap é \['e]
autocmd Filetype groff inoremap É \['E]
autocmd Filetype groff inoremap í \['i]
autocmd Filetype groff inoremap Í \['I]
autocmd Filetype groff inoremap ó \['o]
autocmd Filetype groff inoremap Ó \['O]
autocmd Filetype groff inoremap ú \['u]
autocmd Filetype groff inoremap Ú \['U]
autocmd Filetype groff inoremap ã \[~a]
autocmd Filetype groff inoremap ç \[,c]
autocmd Filetype groff inoremap â \[^a]
autocmd Filetype groff inoremap ê \[^e]
autocmd Filetype groff inoremap ô \[^o]

call plug#begin()
Plug 'drewtempelmeyer/palenight.vim'
call plug#end()
colorscheme palenight
