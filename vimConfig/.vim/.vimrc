":if 0=="main"
":	echo "Yes"
":endif

autocmd Bufread *.cpp,*.[ch],*.java exec":call Gengxin()" 

filetype on 	 "文件类型识别开启 
filetype indent on 	 "s
filetype plugin on 	 "s
filetype plugin indent on "开启插件

set laststatus=2
highlight StatusLine cterm=bold ctermfg=yellow ctermbg=blue

function! CurDir()
let curdir = substitute(getcwd(), $HOME, "~", "g")
return curdir
endfunction
set statusline=%{CurDir()}\/%f%m%r%h
"%{$USER}\@%{hostname()}

"""""""""""""""""""""""""""""""""""""""""""""""
" 	 显示设置 	 "
"""""""""""""""""""""""""""""""""""""""""""""""
set number 	  "显示行号
syntax on 	  "自动语法高亮
set cursorline "突出当前行
set nobackup   "覆盖文件时不备份

"""""""""""""""""""""""""""""""""""""""""""""""
" 	 编辑设置 	 "
"""""""""""""""""""""""""""""""""""""""""""""""
set autochdir  "自动切换到文件目录
set nowrapscan "禁止搜索到底时重新搜索
set incsearch  "输入搜索内容时就显示结果
set ignorecase smartcase "搜索时忽略大小写，但在有一个或以上大写字母时仍保持对大小写敏感
set hlsearch 	 "搜索时高亮显示被找到的文本
set showmatch 	"插入括号时，短暂地跳转到匹配的对应括号
set matchtime=1 "短暂跳转到匹配括号的时间
set magic 	 "设置魔术
set hidden 	 "允许在有未保存的修改时切换缓冲区，此时的修改由 vim 负责保存
set mouse=a
set guioptions-=T "隐藏工具栏
set guioptions-=m "隐藏菜单栏
set smartindent 	"开启新行时使用智能自动缩进
set tabstop=2
set shiftwidth=2
set autowrite
set nocompatible
set clipboard+=unnamed 


autocmd BufReadPost * 
\ if line("'\"") > 0 && line("'\"") <= line("$") | 
\   exe "normal! g`\"" | 
\ endif 

"""""""""""""""""""""""""""""""""""""""""""""""
" 	 Code Stype 	 "
"""""""""""""""""""""""""""""""""""""""""""""""
"Tlist
let Tlist_Sort_Type="name" 	 "按照名称排布
let Tlist_Show_One_File = 1 	 "不同时显示多个文件的tag，只显示当前文件的
let Tlist_Exit_OnlyWindow = 1 	 "如果taglist窗口是最后一个窗口，则退出vim
"let Tlist_Use_Right_Window = 1 	 "在右侧窗口中显示taglist窗口
let Tlist_File_Fold_Auto_Close=1 "自动折叠当前非编辑文件的方法列表
let Tlist_Auto_Open = 0
let Tlist_Auto_Update = 1
let Tlist_Hightlight_Tag_On_BufEnter = 1
let Tlist_Enable_Fold_Column = 0
let Tlist_Process_File_Always = 1
let Tlist_Display_Prototype = 0
let Tlist_Compact_Format = 1
map <C-L> :Tlist<CR><C-W><c-W>


"ctags
map <C-F12> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR><CR>

"
map qq :q!<CR>
map wq :wq<CR>
map wqa :wqa<CR>
map ww :w!<CR>
map <C-A> ggVGY
map <F5> :call Compile()<CR>
map <space> :

func Gengxin()
		call setline(2," * 文件名：".expand("%"))
		call setline(6," * 修改时间：".strftime("%Y年%m月%d日 %H时%M分%S秒",getftime(expand("%"))))
endfunc

func Compile()
exec "w"
if &filetype == 'c'
exec "!gcc % -g -o %<"
exec "!./%<"
endif
endfunc


autocmd BufNewFile *.cpp,*.[ch],*.sh,*.java exec ":call SetTitle()" 
func SetTitle() 
if &filetype == 'sh'
call append(0,"#!/bin/bash")
call append(1,"##########################################")
call append(2,"# 文件名：".expand("%")) 
call append(3,"# 作  者：张 鹏") 	
call append(4,"# 邮  箱：296945216@qq.com")
call append(5,"# 创建时间：".strftime("%Y年%m月%d日 %H时%M分%S秒"))
call append(6,"# 修改时间：".strftime("%Y年%m月%d日 %H时%M分%S秒"))
call append(7,"##########################################")
call append(8,"#描述：")
call append(9,"#")
call append(10,"##########################################")
else 
call append(0,"/*******************************************") 
call append(1," * 文件名：".expand("%")) 
call append(2," * 作  者：张 鹏") 	
call append(3," * 邮  箱：296945216@qq.com")
call append(4," * 创建时间：".strftime("%Y年%m月%d日 %H时%M分%S秒"))
call append(5," * 修改时间：".strftime("%Y年%m月%d日 %H时%M分%S秒"))
call append(6," *******************************************") 	
call append(7," *描述：")
call append(8," *")
call append(9," ******************************************/") 	
endif
normal G
endfunc

