# Advanced

### `strace`

`strace` is a tool that can trace syscalls (system calls). These calls can be 
intercepted and read, allowing for a better understanding of what a process is 
trying to do at a given runtime.

Common times to use `strace` are to get to the bottom of _why_ something is 
not working.

Say a program is throwing a suspicious error. If you want to see what file the 
program is opening, writing to, signals the program is passing etc, `strace` 
is the easiest way.

There are a few ways to run strace. Let's explore them.

1. Run strace on `ls`

Hopefully you are familiar with the unix command `ls`, if so then you can 
probably assume how it works. So to really dive in and see an example of `stace
` output lets run it on `ls`.

```console
$ strace ls

execve("/bin/ls", ["ls"], [/* 19 vars */]) = 0
brk(0)                                  = 0x2486000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 
0x7f6dad1b0000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=32310, ...}) = 0
mmap(NULL, 32310, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f6dad1a8000
close(3)                                = 0
...
```

So you can see from that output exactly what the command is doing.

2. Run strace on a PID

You can run `strace` on a process without running the process directly with 
`strace`.

```console
# checkout the options on strace --help
$ strace --help

# run strace on a process with -p
# lets run it on our init system
$ strace -p 1

...
sendmsg(11, {msg_name(0)=NULL, msg_iov(2)=[{"l\4\1\1\303\0\0\0\343_\253\0a\0\0\0\1\1o\0\23\0\0\0/com/ubu"..., 120}, {"\23\0\0\0queues-device-added\0\247\0\0\0\v\0\0\0"..., 195}], msg_controllen=0, msg_flags=0}, MSG_NOSIGNAL) = 315
sendmsg(13, {msg_name(0)=NULL, msg_iov(2)=[{"l\4\1\1\303\0\0\0\"\201Y\0a\0\0\0\1\1o\0\23\0\0\0/com/ubu"..., 120}, {"\23\0\0\0queues-device-added\0\247\0\0\0\v\0\0\0"..., 195}], msg_controllen=0, msg_flags=0}, MSG_NOSIGNAL) = 315
sendmsg(12, {msg_name(0)=NULL, msg_iov(2)=[{"l\4\1\1\303\0\0\0G}Y\0a\0\0\0\1\1o\0\23\0\0\0/com/ubu"..., 120}, {"\23\0\0\0queues-device-added\0\247\0\0\0\v\0\0\0"..., 195}], msg_controllen=0, msg_flags=0}, MSG_NOSIGNAL) = 315
sendmsg(10, {msg_name(0)=NULL, msg_iov(2)=[{"l\4\1\1\303\0\0\0{}Y\0a\0\0\0\1\1o\0\23\0\0\0/com/ubu"..., 120}, {"\23\0\0\0queues-device-added\0\247\0\0\0\v\0\0\0"..., 195}], msg_controllen=0, msg_flags=0}, MSG_NOSIGNAL) = 315
select(20, [3 5 6 7 10 11 12 13 19], [], [7 10 11 12 13], NULL^CProcess 1 detached
...
```

That one is not that exciting so let's find another process to run `strace` on.

```console
# list processes
$ ps -aux

# play around using strace on different processes
$ strace -p <PID>
```

### Linux Namespaces

I could have rewritten a great tutorial on namespaces but...

this one is already so great [http://crosbymichael.com/creating-containers-part-1.html](http://crosbymichael.com/creating-containers-part-1.html).

It requires installing docker, so lets go ahead and do that.

```console
$ curl -sSL https://get.docker.com | sh

# make sure it is running correctly
$ docker ps
```

### `sysctl`

The following is taken directly from [https://github.com/torvalds/linux/blob/master/Documentation/sysctl/README](https://github.com/torvalds/linux/blob/master/Documentation/sysctl/README). But it's a pretty great resource.

`sysctl` is a means of configuring certain aspects of the kernel at run-time, 
and the /proc/sys/ directory is there so that you don't even need special 
tools to do it!

In fact, there are only four things needed to use these config facilities:

- a running Linux system
- root access
- common sense (this is especially hard to come by these days)
- knowledge of what all those values mean

As a quick 'ls /proc/sys' will show, the directory consists of several 
(arch-dependent?) subdirs. Each subdir is mainly about one part of the kernel, 
so you can do configuration on a piece by piece basis, or just some 'thematic 
frobbing'.

The subdirs are about:

```
abi/		execution domains & personalities
debug/		<empty>
dev/		device specific information (eg dev/cdrom/info)
fs/		specific filesystems
filehandle, inode, dentry and quota tuning
binfmt_misc <Documentation/binfmt_misc.txt>
kernel/		global kernel info / tuning
miscellaneous stuff
net/		networking stuff, for documentation look in:
<Documentation/networking/>
proc/		<empty>
sunrpc/		SUN Remote Procedure Call (NFS)
vm/		memory management tuning
buffer and cache management
```

Kernel settings are viewable here [https://github.com/torvalds/linux/blob/master/Documentation/sysctl/kernel.txt](https://github.com/torvalds/linux/blob/master/Documentation/sysctl/kernel.txt).


1. Change an option and update

```console
# show all system params
$ sysctl -A

# grep for file-max
$ sysctl -A | grep file-max
fs.file-max = 1631327

# open up /etc/sysctl.conf
$ vim /etc/sysctl.conf

# Increase size of file handles and inode cache
fs.file-max = 2097152

# save and quit (:wq)

# load the changes
$ sysctl -p

# grep for the one we changed
$ sysctl -A | grep file-max
fs.file-max = 2097152

# show the ones we modified
$ sysctl -p

# show value for a single paramater
$ sysctl fs.file-max
fs.file-max = 2097152

# change the value back without editing sysctl.conf
$ sysctl -w fs.file-max=1631327

# make sure it worked
$ sysctl fs.file-max
fs.file-max = 1631327
```
