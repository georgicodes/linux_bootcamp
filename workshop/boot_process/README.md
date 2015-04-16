# Boot Process   

## Anatomy of the `initrd`
The initrd image contains the necessary executables and system files to support the second-stage boot of a Linux system.

#### EXERCISE: Inspecting the `initrd`
The default initrd image is a compressed cpio archive file. To inspect the contents of a cpio archive, use the following commands:

```bash
cd ~
mkdir temp ; cd temp
cp /boot/initrd-XXX initrd.img.gz
gunzip initrd.img.gz
cpio -i --make-directories < initrd.img
ls -la

# Not sure what cpio is? Remember you can always read the man pages
man cpio
```
The result is a small root file system. The small, but necessary, set of applications are present in the ./bin directory, including `nash` (not a shell, a script interpreter), `insmod` for loading kernel modules, and `lvm` (logical volume manager tools).

Of interest is the `initrd.img-xxx` file at the root. This file, like the traditional Linux boot process, is invoked when the initrd image is decompressed into the RAM disk. 

#### EXERCISE: Intro to GRUB command line
The GRUB 2 command shell allows you to discover boot images, kernels, and root filesystems.

Tab completion and history work in the GRUB shell.

1. `reboot` Ubuntu
1. very quickly as its booting up again drop into the Grub command shell by pressing `c`.
1. `ls` as the `grub>` prompt. (The msdos stuff means this system has the old-style MS-DOS partition table, rather than the shiny new Globally Unique Identifiers partition table (GPT))
1. `grub> ls (hd0,1)/` to list the files on the system. This is the root filesystem. We actually have complete access to all filesystems on the local machine regardless of permissions or other protections.
1. Find where you checked out the `linux-workshop` GitHub repo and display the README by using the `cat` command.

#### EXERCISE: Booting From grub>
This is how to set the boot files and boot the system from the `grub>` prompt. We know from running the `ls` command that there is a Linux root filesystem on `(hd0,1)`, and you can keep searching until you verify where `/boot/grub` is. Then run these commands, using your own root partition, kernel, and initrd image:

```bash
grub> set root=(hd0,1)
grub> linux /boot/vmlinuz-XXX root=/dev/sda1
grub> initrd /boot/initrd.img-XXX
grub> boot
```
The first line sets the partition that the root filesystem is on. The second line tells GRUB the location of the kernel you want to use. How do you know the correct partition? `hd0,1 = /dev/sda1. hd1,1 = /dev/sdb1. hd3,2 = /dev/sdd2`. The third line sets the `initrd` file, which must be the same version number as the kernel. The fourth line boots your system.


##### References
* [http://www.ibm.com/developerworks/library/l-initrd/](http://www.ibm.com/developerworks/library/l-initrd/)
* [https://www.linux.com/learn/tutorials/776643-how-to-rescue-a-non-booting-grub-2-on-linux/](https://www.linux.com/learn/tutorials/776643-how-to-rescue-a-non-booting-grub-2-on-linux/)
