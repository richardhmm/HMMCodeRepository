" 开启语法高亮功能
syntax enable
" 允许用指定语法高亮配色方案替换默认方案
syntax on
filetype plugin indent on
set number

" 高亮显示当前行/列
set cursorline
set cursorcolumn

" 代码折叠
" 基于缩进或语法进行代码折叠
"set foldmethod=indent
set foldmethod=syntax
" 启动 vim 时关闭折叠代码
set nofoldenable

set statusline=[%F]%y%r%m%*%=[Line:%l/%L,Column:%c][%p%%]

" 设置 tagbar 子窗口的位置出现在主编辑区的左边
let tagbar_left=1
" 设置显示／隐藏标签列表子窗口的快捷键。速记：identifier list by tag
nnoremap <Leader>ilt :TagbarToggle<CR>
" 设置标签子窗口的宽度
let tagbar_width=32
" tagbar 子窗口中不显示冗余帮助信息
let g:tagbar_compact=1
" 设置 ctags 对哪些代码标识符生成标签
let g:tagbar_type_cpp = {
\ 'ctagstype' : 'c++',
\ 'kinds' : [
\ 'c:classes:0:1',
\ 'd:macros:0:1',
\ 'e:enumerators:0:0',
\ 'f:functions:0:1',
\ 'g:enumeration:0:1',
\ 'l:local:0:1',
\ 'm:members:0:1',
\ 'n:namespaces:0:1',
\ 'p:functions_prototypes:0:1',
\ 's:structs:0:1',
\ 't:typedefs:0:1',
\ 'u:unions:0:1',
\ 'v:global:0:1',
\ 'x:external:0:1'
\ ],
\ 'sro' : '::',
\ 'kind2scope' : {
\ 'g' : 'enum',
\ 'n' : 'namespace',
\ 'c' : 'class',
\ 's' : 'struct',
\ 'u' : 'union'
\ },
\ 'scope2kind' : {
\ 'enum' : 'g',
\ 'namespace' : 'n',
\ 'class' : 'c',
\ 'struct' : 's',
\ 'union' : 'u'
\ }
\ }

" 使用 NERDTree 插件查看工程文件。设置快捷键，速记：file list
nmap <Leader>fl :NERDTreeToggle<CR>
" 设置 NERDTree 子窗口宽度
let NERDTreeWinSize=22
" 设置 NERDTree 子窗口位置
let NERDTreeWinPos="right"
" 显示隐藏文件
let NERDTreeShowHidden=1
" NERDTree 子窗口中不显示冗余帮助信息
let NERDTreeMinimalUI=1
" 删除文件时自动删除文件对应 buffer
let NERDTreeAutoDeleteBuffer=1
" 多文档编辑
" 显示/隐藏 MiniBufExplorer 窗口
" map <Leader>bl :MBEToggle<cr>
" buffer 切换快捷键


let Tlist_Ctags_Cmd='ctags' "因为我们放在环境变量里，所以可以直接执行
let Tlist_Use_Right_Window=0 "让窗口显示在右边，0的话就是显示在左边
let Tlist_Show_One_File=0 "让taglist可以同时展示多个文件的函数列表
let Tlist_File_Fold_Auto_Close=1 "非当前文件，函数列表折叠隐藏
let Tlist_Exit_OnlyWindow=1 "当taglist是最后一个分割窗口时，自动推出vim
"是否一直处理tags.1:处理;0:不处理
let Tlist_Process_File_Always=1 "实时更新tags
let Tlist_Inc_Winwidth=0

set t_Co=256
set background=dark  "dark light "can switch it to find which is look pretty
set nocompatible                 "some plugin need it
set hlsearch                     "highlight the search
set incsearch                    "move to fit position after one char input
set nobackup                     "won't produce the backup file when save file
set nowritebackup                "won't produce the backup file when save file
set noswapfile                   "won't use swapfile
set hidden                       "can open other file when a file is not saved
set ruler                        "show ruler at the right bottom
set nowrap                       "disable auto newline
set laststatus=2                 "status bar will show anytime
set updatetime=200               "tagbar response 800ms
set showmatch matchtime=0        "show the other bracket
set wmnu wildmode=longest:full   "when in command mode can use auto complete same as bash
set expandtab tabstop=4          "expand the tab to 4 space
set si ai ci cinkeys-=0# cinoptions=g0,:0   "some indent rules
set shiftwidth=4                 "make the indent 4 length
set softtabstop=4                "backspace can del 4 space
set lcs=eol:$,tab:\|\            "display tab to green line
set backspace=indent,eol,start   "better backspace
set fileencodings=utf-8,cp936    "auto test the file is uft-8 or cp936
set fileformats=unix,dos,mac     "line feed different in different mode
set completeopt=menuone,longest

highlight TagbarHighlight guifg=Green ctermfg=Green
let NERDTreeQuitOnOpen=1
let NERDTreeDirArrows=0
let NERDTreeWinSize=40
let NERDRemoveExtraSpaces=0
let g:bufExplorerDisableDefaultKeyMapping = 1
let g:tagbar_sort=0
let g:tagbar_compact=1
let g:tagbar_foldlevel=1
let g:tagbar_iconchars=['+', '-']
let OmniCpp_SelectFirstItem = 2
let OmniCpp_ShowPrototypeInAbbr = 1 
let OmniCpp_MayCompleteScope = 1

func! Turntabstop()

    let tablength = &tabstop
    if tablength == 1
        set tabstop=2
        set softtabstop=2
        set shiftwidth=2
    elseif tablength==2
        set tabstop=4
        set softtabstop=4
        set shiftwidth=4
    elseif tablength==4
        set tabstop=8
        set softtabstop=8
        set shiftwidth=8
    elseif tablength==8
        set tabstop=1
        set softtabstop=1
        set shiftwidth=1
    endif
endfunc

"file list
map <silent> <F2> :NERDTreeToggle<cr>
"tarbar functon list
map <silent> <F3> :TagbarToggle<cr>
"header and implement file switch
map <F4> :A<cr>
"update index
map <F5> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q<cr><cr>:cs kill cscope.out<cr>:!cscope -Rb<cr><cr>:cs add cscope.out<cr>
"switch display invisable char or not
map <F6> :set list!<cr>:set list?<cr>
"highlight
map <F7> ms:%s /\<<C-R>=expand("<cword>")<CR>\>//gn<cr>`s
"swapfile list
map <silent> <F8> :BufExplorer<CR>
"switch tab expand to space or not
map <F9> :set expandtab!<cr>:set expandtab?<cr>
"switch tab expand to space or not
map <silent> <F10> :call Turntabstop()<cr>:set tabstop?<cr>
""comment visual line
vnoremap <silent> , :call NERDComment(1, "alignLeft")<cr>
"uncomment visual line
vnoremap <silent> . :call NERDComment(1, "uncomment")<cr>
"show list if more tag 
nnoremap <c-]> g<c-]>
"move to right window
noremap <c-l> <c-w>l
"move to up window
noremap <c-k> <c-w>k
"move to down window
noremap <c-j> <c-w>j
"move to left window
noremap <c-h> <c-w>h
"goto the place where word definition
nmap <C-[>g :cs find g <C-R>=expand("<cword>")<CR><CR>
"list the funcion called by this function
nmap <C-[>d :cs find d <C-R>=expand("<cword>")<CR><CR>
"list the position where to call this word
nmap <C-[>c :cs find c <C-R>=expand("<cword>")<CR><CR>
"search word in the project
nmap <C-[>s :cs find s <C-R>=expand("<cword>")<CR><CR>
"search word in the project and the word can be in text
nmap <C-[>t :cs find t <C-R>=expand("<cword>")<CR><CR>
"search word in the project and the word can be in text, support regex
nmap <C-[>e :cs find e <C-R>=expand("<cword>")<CR><CR>
"list the file which filename is this word
nmap <C-[>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
"list the file include the file which filename is this word
nmap <C-[>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
"list the file which include this file
nmap <C-[>I :cs find i <C-R>=expand("%:t")<CR><CR>

if has("cscope") 
    set nocsverb
    if filereadable("cscope.out")
        cs add cscope.out
    endif
endif
