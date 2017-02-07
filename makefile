CC=gcc
CPPFLAGS= -I./include   
CFLAGS=-Wall 
LIBS= 

#找到当前目录下所有的.c文件
src = $(wildcard *.c)

#将当前目录下所有的.c  转换成.o给obj
obj = $(patsubst %.c, %.o, $(src))

#目标
fdfs_upload_test=test
target=$(fdfs_upload_test)

ALL:$(target)

#生成所有的.o文件
$(obj):%.o:%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS) 

#将所有的.o联合编译为可执行目标程序
$(fdfs_upload_test):$(obj)
	$(CC) $^ -o $@ $(LIBS)

#clean指令
clean:
	-rm -rf $(obj) $(target) 

distclean:
	-rm -rf $(obj) $(target) 

#将clean目标 改成一个虚拟符号
.PHONY: clean ALL distclean
