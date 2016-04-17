
### 来源
https://github.com/langsim/vim-ide

### 常用命令
1 F2打开当前工程.

2 F5更新工程index.

3 Ctrl-O返回上次位置.

4 :cs find s wrod查找工程内变量或函数.

5 :cs find t word查找工程内文本.

6 :Tlist打开tags列表.

7 Ctrl-]跳转到工程内变量或函数的定义处.

### how to use it read and write c/c++ project

1. open project:
    * cd into project root dir，vim (press enter button), must in project root dir. press F2 to open file tree, and select file to open.
2. update index:
    * first time open project or update some code in project, press F5 to update index，the index function is same to source insight index.
3. read c/c++ code:
    * jump
        * F3         throught tagbar to jump to another function in the file
        * gd         jump to local varibale defination
        * ctrl-]     jump to variable or function defination in project。(can't jump to local variable defination) (:ts word)
        * [[         jump to start of function
        * ][         jump to end of function
        * ctrl-o     jump to cursor last position
        * ctrl-i     return after press ctrl-o
        * ctrl-h     move cursor to left window in vim
        * ctrl-j     move cursor to down window in vim
        * ctrl-k     move cursor to up window in vim
        * ctrl-l     move cursor to right window in vim
    * search
        * ctrl-[ s   search variable or function in project (:cs find s word)
        * ctrl-[ t   search text in project (:cs find t word)
        * F7         highlight word under the cursor 
        * /word      search word in the file
    * open another file in project
        * F2         throught file tree
        * F8         throught opened file list
        * F4         switch of include file and implement file
    * display
        * F6         switch of display invisible character or not 
        * F10        change tab display as space mount
4. write c/c++ code：
    * align
        * =          align selected code
        * ==         align current line code
    * comment
        * ,          comment selected code
        * .          uncomment selected code
    * replace
        * :%s /word1/word2/g  replace word1 to word2 in the file
    * expand tab to space or not
        * F9         exapnd tab to space or not


