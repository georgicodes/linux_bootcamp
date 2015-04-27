# Filesystem Basics

**Programs You Need:**

- `parted`
- `fsck`

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

2. Create a new partition

```console
# bring up the parted menu
$ parted /dev/sda

GNU Parted 2.3
Using /dev/sda
Welcome to GNU Parted! Type 'help' to view a list of commands.
(parted) help                                                             
  align-check TYPE N                        check partition N for TYPE(min|opt) alignment
  check NUMBER                             do a simple check on the file system
  cp [FROM-DEVICE] FROM-NUMBER TO-NUMBER   copy file system to another partition
  help [COMMAND]                           print general help, or help on COMMAND
  mklabel,mktable LABEL-TYPE               create a new disklabel (partition table)
  mkfs NUMBER FS-TYPE                      make a FS-TYPE file system on partition NUMBER
  mkpart PART-TYPE [FS-TYPE] START END     make a partition
  mkpartfs PART-TYPE FS-TYPE START END     make a partition with a file system
  resizepart NUMBER END                    resize partition NUMBER
  move NUMBER START END                    move partition NUMBER
  name NUMBER NAME                         name partition NUMBER as NAME
  print [devices|free|list,all|NUMBER]     display the partition table, available devices, free
        space, all found partitions, or a particular partition
  quit                                     exit program
  rescue START END                         rescue a lost partition near START and END
  resize NUMBER START END                  resize partition NUMBER and its file system
  rm NUMBER                                delete partition NUMBER
  select DEVICE                            choose the device to edit
  set NUMBER FLAG STATE                    change the FLAG on partition NUMBER
  toggle [NUMBER [FLAG]]                   toggle the state of FLAG on partition NUMBER
  unit UNIT                                set the default unit to UNIT
  version                                  display the version number and copyright information of
        GNU Parted


# run mkpart to create a new partition
(parted) (parted) mkpart
Partition name?  []?                                                      
File system type?  [ext2]?                                                
Start? 1048                                                               
End? 8930293                                                              
Error: The location 8930293 is outside of the device /dev/vda.            
(parted) mkpart                                                        
Partition name?  []?                                                      
File system type?  [ext2]?                                                
Start? 1048                                                               
End? 12342                                                                
Warning: You requested a partition from 1048MB to 12.3GB.                 
The closest location we can manage is 172GB to 172GB.
Is this still acceptable to you?
Yes/No? y                                                                               

# view the new partition
(parted) print all                                                        
Model: Virtio Block Device (virtblk)
Disk /dev/sda: 172GB
Sector size (logical/physical): 512B/512B
Partition Table: gpt

Number  Start   End    Size   File system  Name     Flags
 1      1049kB  172GB  172GB  ext4         primary
 2      172GB   172GB  512B

# quit
(parted) q                                                                
Information: You may need to update /etc/fstab.  
```

2. Check a specific device node

```console
$ fsck /dev/sda2
fsck from util-linux 2.25.2
e2fsck 1.42.9 (4-Feb-2014)
/dev/sda2: clean, 95/2240224 files, 3793506/4476416 blocks
```

3. Get the exit code

```console
$ echo $?
```

4. Translate the code

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

5. Check all filesystems in one run

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

6. Check only a specific filesystem type

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