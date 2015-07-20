# Filesystem Basics

**Programs You Need:**

- `parted`
- `fsck`
-  mount

#### `parted`

GNU `parted` is a disk partitioning and partition resizing program. It allows 
you to create, destroy, resize, move and copy ext2, linux-swap, FAT, FAT32, 
and reiserfs partitions. It can create, resize, and move Macintosh HFS 
partitions, as well as detect jfs, ntfs, ufs, and xfs partitions. It is useful 
for creating space for new operating systems, reorganising disk usage, and 
copying data to new hard disks.


#### `fsck`

`fsck` stands for "file system consistency check". On most systems, `fsck` is 
run at boot time if certain conditions are detected. 

Usually, these conditions are:

- A file system is marked as "dirty" — its written state is inconsistent with 
data that was scheduled to be written; or,
- A file system has been mounted a set number of times without being checked.

The `fsck` command itself interacts with a matching filesystem-specific `fsck` 
command created by the filesystem's authors. 

Regardless of filesystem type, `fsck` generally has three modes of operation:

- Check for errors, and prompt the user interactively to decide how to resolve 
individual problems;
- Check for errors, and attempt to fix any errors automatically; or,
- Check for errors, and make no attempt to repair them, but display the errors 
on standard output.

### Exercises

1. List all available partitions

```console
$ parted /dev/sda 'print'
```

2. Create an aufs mount

```console
# install aufs tools
$ apt-get install aufs-tools

$ mkdir /tmp/dir1
$ touch /tmp/dir1/file_in_dir_1
$ ls /tmp/dir1

$ ls /home/vagrant

$ mkdir /tmp/aufs-root

# mount the home dir as a union mount
$ mount -t aufs -o br=/tmp/dir1:/home/vagrant none /tmp/aufs-root/

$ ls /tmp/aufs-root
# this will have the contents of /home/vagrant and /tmp/dir1

# unmount
$ umount /tmp/aufs-root
```

3. Check a specific device node

```console
$ fsck /dev/sda1
fsck from util-linux 2.25.2
e2fsck 1.42.9 (4-Feb-2014)
/dev/sda1: clean, 95/2240224 files, 3793506/4476416 blocks
```

4. Get the exit code

```console
$ echo $?
```

5. Translate the code

| Code | Meaning                            |
|------|------------------------------------|
|    0 | No errors                          |
|    1 | Filesystem errors corrected        |
|    2 | System should be rebooted          |
|    4 | Filesystem errors left uncorrected |
|    8 | Operational error                  |
|   16 | Usage or syntax error              |
|   32 | Fsck canceled by user request      |
|  128 | Shared-library error               |

> **Note:** should probably be a `0`

6. Check all filesystems in one run

```console
#  check the filesystem in the order given by the 
# fs_passno mentioned for each filesystem in /etc/fstab

$ cat /etc/fstab

# <file system>	<mount point>	<type>	<options>	<dump>	<pass>
/dev/md1	/	ext4	errors=remount-ro,relatime,discard	0	1
/dev/sda2	swap	swap	defaults	0	0
/dev/sdb2	swap	swap	defaults	0	0
/dev/sdc2	swap	swap	defaults	0	0
proc		/proc	proc	defaults		0	0
sysfs		/sys	sysfs	defaults		0	0
tmpfs		/dev/shm	tmpfs	defaults	0	0
devpts		/dev/pts	devpts	defaults	0	0

# run fsck over all with -A
# exclude the root filesytem with -R
# automatically fix problems with -y
$ fsck -AR -y
e2fsck 1.42.9 (4-Feb-2014)
/dev/sda2: clean, 95/2240224 files, 3793506/4476416 blocks
```

7. Check only a specific filesystem type

```console
# check only on ext4
$ fsck -AR -t ext4 -y
fsck from util-linux 2.25.2

# check on everything that is NOT ext4
$ fsck -AR -t noext4 -y
fsck from util-linux 2.25.2
e2fsck 1.42.9 (4-Feb-2014)
/dev/sda2: clean, 95/2240224 files, 3793506/4476416 blocks
```


Checkout `man fsck` for more options
