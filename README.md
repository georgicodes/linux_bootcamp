# Linux Bootcamp: From Casual Linux User to Kernel Hacker (Workshop)

Session Info:
[Codepalousa:Linux Bootcamp: From Casual Linux User to Kernel Hacker](http://codepalousa.com/schedule/sessions/linux-bootcamp-from-casual-linux-user-to-kernel-hacker/)

Monday, April 27   1:00 to 5:30 in room 112

## Installation
You will likely need around 10GB's on your laptop to get started.

1. Download and install VirtualBox 4.3.26 for your OS: https://www.virtualbox.org/wiki/Downloads
Download Ubuntu Desktop 14.10 iso image: http://www.ubuntu.com/download/desktop. (this is about 1GB so may take a while to download)
1. In VirutalBox, click on the New button and name you system "Ubuntu". Complete the wizard leaving all the default options selected.
1. Select your "Ubuntu" system and click start then at the prompt point VirtualBox to the downloaded Ubuntu iso image.
Complete the Ubuntu installation process.
1. All done - you should now be able to boot into your Ubuntu virtual system!

# Rough Agenda
## Laying the foundations
### Introduction - All - 30 mins
	* Intro ourselves - All
	* Attendees intro
	    * Name, Job, How do you currently use Linux?
	* Linux history - Georgi
	* Linux distributions - Georgi
	* Who uses Linux and why? - Jessie
	* Talks about how our companies use linux - All
	* Fun Linux easter eggs - Tammy

### Boot Process + Kernel Intro - Georgi - 15mins
	* What is the kernel?
	* Boot process

### Linux Filesystem - Jessie - 30mins
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

### Command Line - Tammy - 15mins
	* types of shells
	* getting help - man pages
	* basic commands `pwd, cd, cd .., ls`
	* searching for files
	* working with files `cat, less, tail, head`
	* Package Management System
		* Installing software

### Processes - Tammy - 15min
	* what is a process
	* types of processes
	* how the shell creates processes 
	* running processes in background and foreground
	* execution modes
	* daemons
	* manage processes, `ps`, `top`

## The Kernel
### Kernel Basics - Georgi - 60 mins +
	* How to build your own kernel
	* More about the kernel
	* System calls
	* Kernel v User space
	* Kernel Modules
	* How does Linux get updated?
	    * Explanation of patches + mailing list etc.
	* Character device drivers
	* `sysctl` - Jessie

## Advanced Topics 
### Advanced - Jessie - 15mins +
	* How to use `strace` for diagnostics and debugging
	* What is a namespace?
	* How to use ‘livepatch’
	* Controlling hardware with `ioctl`

## Summary
### Summary - All - 5 mins
	* Finale exercise!
	* Where can I learn more? 
