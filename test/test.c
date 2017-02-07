#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#include "make_log.h"

#define FDFS_TEST_MODULE "test"
#define FDFS_TEST_PROC   "fdfs_test"

int main(int argc,const char *argv[])
{
    if(argc!=2)
    {
        printf("a.out filename\n");
        exit(0);
    }
    int ret=0;
    int fd[2];
    ret=pipe(fd);
    if(ret!=0)
    {
        perror("pipe() error!");
    }

    pid_t pid=fork();
    if(pid==-1)
    {
        perror("fork() error!");
    }
    if(pid==0)
    {
        /* printf("我是子进程！\n"); */
        //关闭读端
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("fdfs_upload_file","upload","/etc/fdfs/client.conf",argv[1],NULL);
        LOG(FDFS_TEST_MODULE,FDFS_TEST_PROC,"execlp fdfs_upload_file error");
        exit(1);
    } 
    else
    {
        /* printf("我是父进程！\n"); */
        //关闭写端
        close(fd[1]);
        char buf[1024]={0};
        wait(NULL);
        int ret=read(fd[0],buf,sizeof(buf));
        if(ret==-1)
        {
            perror("read() error!\n");
        }
        printf("buf:%s\n",buf);
        LOG(FDFS_TEST_MODULE,FDFS_TEST_PROC,"fileid=[%s]",buf);
    }
    return 0;
}
