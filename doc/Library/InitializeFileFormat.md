#严格的Initliaizle文件格式
Ini文件是Windows上比较常见的文件格式


##存储
可以是UTF-8(With BOM) UTF16 以及ANSI(与之对应的CodePage)
文件换行符可以是CRLF和LF,单独的CR是不被支持的.
每一行不能超过8196个字符，包括换行符。
文件大小不得超过0x100000000字节 即4GB,(这个是通过虚拟内存实现的)，实际上一般是256MB极限。

##解析
解析成UTF16,数据格式为UTF16LE

##限制
