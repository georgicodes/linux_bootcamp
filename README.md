# Linux Bootcamp: From Casual Linux User to Kernel Hacker (Workshop)

Session Info:
[Codepalousa:Linux Bootcamp: From Casual Linux User to Kernel Hacker](http://codepalousa.com/schedule/sessions/linux-bootcamp-from-casual-linux-user-to-kernel-hacker/)

Monday, April 27   1:00 to 5:30 in room 112

## Laying the foundations
1. Introduction - All - 30 mins
    * Intro ourselves - All
    * Attendees intro
    	* Name, Job, How do you currently use Linux?
    * Linux history - Georgi
    * Linux distributions - Georgi
    * Who uses Linux and why? - Jessie
      * Talks about how our companies use linux - All
    * Fun Linux easter eggs - Tammy

1. Boot Process - Georgi - 15mins
    * Boot sequence steps
        * BIOS
        * MBR
        * Boot Loader
        * Kernel
        * Inital RAM
        * `init`/`systemd`
        * X Windows
    * Shutdown/reboot

1. Linux Filesystem - Jessie - 30mins
    * Filesystem types
    * Standard disk filesystems: `ext2, ext3, ext4, XFS, Btrfs, JFS, NTFS`
    * Partitions
    * Filesystem Hierarchy Standard (FHS)
    * Disk + filesystem usage
        * differences between Linux and Windows
        * case sensistive
        * relative v absolute paths
  * Overlay file systems
  * Exercises and examples and pictres
  * `fsck`

1. Command Line - Tammy - 15mins
    * types of shells
    * getting help - man pages
    * basic commands `pwd, cd, cd .., ls`
    * searching for files
    * working with files `cat, less, tail, head`
    * Package Management System
        * Installing software

1. Processes - Tammy - 15min
    * what is a process
    * types of processes
    * how the shell creates processes 
    * running processes in background and foreground
    * execution modes
    * daemons
    * manage processes, `ps`, `top`

## The Kernel
1. Kernel Basics - Georgi - 60 mins
	* What are system calls?
    * what is a kernel
    * kernel configuration
    * `sysctl` - Jessie
    * build your own kernel + name
    * How does Linux get updated? - Georgi
    	* Explanation of patches + mailing list etc.

## Advanced Topics -
1. Advanced - Jessie
	* How to use `strace` for diagnostics and debugging
	* What is a namespace?
	* How to use ‘livepatch’
	* Controlling hardware with `ioctl`

## Summary - 5 mins
1. Summary - Georgi
	* Finale exercise!
	* Where can I learn more? 

References
* [http://training.linuxfoundation.org/linux-courses/linux-system-administration/outline](http://training.linuxfoundation.org/linux-courses/linux-system-administration/outline)
* [https://www.edx.org/course/introduction-linux-linuxfoundationx-lfs101x-2](https://www.edx.org/course/introduction-linux-linuxfoundationx-lfs101x-2)
