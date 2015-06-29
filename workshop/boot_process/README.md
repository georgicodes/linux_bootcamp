

#### EXERCISE: Intro to GRUB command line
The GRUB 2 command shell allows you to discover boot images, kernels, and root filesystems.

Tab completion and history work in the GRUB shell.

* `reboot` Ubuntu
* When your system starts up hold down the `shift` key until a black screen with the GRUB menu appears. 
* Drop into the Grub command shell by pressing `c`.
![](http://pix.toile-libre.org/upload/original/1353953772.png)
* `ls` as the `grub>` prompt. (The msdos stuff means this system has the old-style MS-DOS partition table, rather than the shiny new Globally Unique Identifiers partition table (GPT))
```bash
grub> ls
(hd0) (hd0,msdos2) (hd0,msdos1)
```
* List the files on the system, the syntax looks a little quirky but we are specifying the partition we want to view with `ls (hd0,1)`. The grub `ls` command documentation is [here](https://www.gnu.org/software/grub/manual/html_node/ls.html). 

From the [GRUB documentation](https://www.gnu.org/software/grub/manual/html_node/Device-syntax.html#Device-syntax):
> The syntax `(hd0)` represents using the entire disk (or the MBR when installing GRUB), while the syntax `(hd0,1)` represents using the first partition of the disk (or the boot sector of the partition when installing GRUB).
```bash
grub> ls (hd0,1)/
lost+found/ bin/ boot/ cdrom/ dev/ etc/ home/  lib/
lib64/ media/ mnt/ opt/ proc/ root/ run/ sbin/ 
srv/ sys/ tmp/ usr/ var/ vmlinuz vmlinuz.old 
initrd.img initrd.img.old
```

What we are seeing here is the root filesystem. 

* You can read any file on the system using the `cat` command. We can view the contents of the same config file we viewed earlier.
```
grub> cat (hd0,1)/boot/config-4.0.5-040005-generic
```
We actually have complete access to all filesystems on the local machine regardless of permissions or other protections.


#### EXERCISE: Booting From grub>
This is how to set the boot files and boot the system from the `grub>` prompt. We know from running the `ls` command that there is a Linux root filesystem on `(hd0,1)`, and our boot files are in `/boot`. We are going to fun a few commands to boot into a different version of our kernel, `3.19.0-18-generic`. 

```bash
Sets the partition that the root filesystem is on (we know this to be (hd0,1)).
grub> set root=(hd0,1)
Tells GRUB the location of the kernel you want to use. How do you know the correct partition? `hd0,1 = /dev/sda1. hd1,1 = /dev/sdb1. hd3,2 = /dev/sdd2`. 
grub> linux /boot/vmlinuz-3.19.0-18-generic root=/dev/sda1
Sets the `initrd` file, which must be the same version number as the kernel.
grub> initrd /boot/initrd.img-XXX
Boot your system
grub> boot
```

Once booted open up a terminal and confirm that we are now running kernel `3.19.0-18-generic`. 
```bash
$ uname -r
3.19.0-18-generic
```

##### References
* [http://www.ibm.com/developerworks/library/l-initrd/](http://www.ibm.com/developerworks/library/l-initrd/)
* [https://www.linux.com/learn/tutorials/776643-how-to-rescue-a-non-booting-grub-2-on-linux/](https://www.linux.com/learn/tutorials/776643-how-to-rescue-a-non-booting-grub-2-on-linux/)
