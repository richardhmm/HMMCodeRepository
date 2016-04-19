
### 来源


### 常用命令
1 F2打开tags列表窗口(居左部).

2 F3打开文件浏览窗口(居右部).

3 F4打开最近阅读的源码(居下部).

4 F9创建或更新ctags和cscope.

5 Ctrl-O返回上次位置.

6 :cs find s wrod查找工程内变量或函数.

7 :cs find t word查找工程内文本.

8 Ctrl-]跳转到工程内变量或函数的定义处.

9 移动操作
`
gg         将光标定位到文件第一行起始位置。
G          将光标定位到文件最后一行起始位置。
NG或Ngg    将光标定位到第 N 行的起始位置。
`

10 分屏与标签页
`
:split（可用缩写 :sp）            上下分屏
:vsplit（可用缩写 :vsp）          左右分屏
vim -On file1 file2...   打开 file1 和 file2 ，垂直分屏
vim -on file1 file2...   打开 file1 和 file2 ，水平分屏
Ctrl+ww                  切换到当前分屏的左边一屏,循环操作
vimdiff file1 file2      Vim里分屏显示两个文件内容的对比结果
`

