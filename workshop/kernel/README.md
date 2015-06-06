# Kernel

## How to configure and build your own kernel

#### 1. EXERCISE: Fetch kernel source and create a kernel config file

##### Download the kernel source
1. Open up a terminal (side bar blackbox icon).
1. Switch to superuser `sudo -i`. This command switches your current terminal to be logged in as a superuser.
1. Install curl as we are going to need it `sudo apt-get install curl`
1. `cd /usr/src`. Kernel source is always stored in this directory.
1. Fetch the latest stable kernel source from kernel.org. You can use the curl command to do this: `curl -O https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.0.5.tar.xz`. (File is about 85mg) OR if the internet is slow then we have already put this file in the home directory so you can just simply copy it across `cp /home/vagrant/handy_workshop_files/linux-4.0.5.tar.xz .`.
1. Unpack the tarball `tar -xvf linux-4.0.5.tar.xz`. If you list the contents of your directory it should look like this:
```bash
root@vagrant-VirtualBox:/usr/src# ls
linux-4.0.5              linux-headers-3.19.0-15-generic  vboxguest-4.3.28
linux-4.0.5.tar.xz       linux-headers-3.19.0-18
linux-headers-3.19.0-15  linux-headers-3.19.0-18-generic
```

##### Customizing the kernel
We are now going to customize our kernel by toggling on two options as explained below.

* Firstly install `sudo apt-get install libncurses5-dev` as this is needed for the GUI to work.
* Run `make menuconfig`
* Select `General Setup` from the list and turn on 'Automatically append version information...'.
![](../../images/menu_config.png)
* Select `Device Drivers` from the main menu. Scroll right down to the bottom and select `Thunderbolt support for Apple Devices`. Now we will turn this on as a `built-in` kernel option not a `module` option. To do this, hit space bar until an `M` appears. Please do this even if you are not on a Mac - this is merely a learning exercise :)
* Spend some time poking around and looking at all the different options. Its dizzying how many there are, setting each on individually would take you all day!
* Save and exit.
* Confirm that a file called `.config` was created
* Take a look at the contents of the file by using the `cat` command. By setting 'Automatically append version information...' in the GUI we have set `CONFIG_LOCALVERSION_AUTO=y`. (Setting to be explained in next exercise)
```bash
root@vagrant-VirtualBox:/usr/src/linux-4.0.5# cat .config | grep CONFIG_LOCALVERSION_AUTO
CONFIG_LOCALVERSION_AUTO=y
```

#### 2. EXERCISE: Customizing your kernel release string
It's always fun to personalize things. The `CONFIG_LOCALVERSION_AUTO=y` config option we set previously allows us to append a version name to our kernel version string.

* Update the `EXTRAVERSION` field in the `Makefile` found in the root of the kernel source tree. Adding your name here or something silly like `-rainbow-unicorns-rule`. This will be appended to your kernel version name string. Note, start this with a dash `-`.
```bash
root@vagrant-VirtualBox:/usr/src/linux-4.0.5# vi Makefile
```
* Now find out what the final kernel release string will be by running `make kernelrelease`.

#### EXERCISE: Configuring for another architecture
TODO - remove me??
Let's take a brief look at how you would configure your kernel for building on another architecture.

1. `ls arch` lists out all the supported architectures.
1. `make ARCH=blackfin menuconfig`
NOTE: you can't actually build a kernel for any other architecture until you install the appropriate cross-compiler toolchain.
1. Exit and Save but rename the file to be `.config-blackfin`

#### 2B. EXERCISE: Building your kernel - TO DO AT HOME!!
There are multiple ways that you can build and install your own kernel, here I have presented one way. This will install the new (compressed) kernel image into the `/boot` directory so that GRUB can find it at boot time.

We will not do this in this workshop as building a kernel can take hours depending on how much grunt your laptop has!

1. Run the following commands and wait for victory!
```bash
make 	# builds a kernel ready to be installed
make modules_install: # Installs all of the newly-built modules. They will now show up under a directory in `/lib/modules`
make install 	#  Install the new (compressed) kernel image into the `/boot` directory so that GRUB can find it at boot time. And it also create a new initrd initial ram disk that goes along with that kernel to support the early part of the boot process
```

#### 4. EXERCISE: Install a pre-built kernel
As it will take too long build a kernel in this workshop, we are going to instead install kernel version 4.0 from the ubuntu kernel mainline repo: [http://kernel.ubuntu.com/~kernel-ppa/mainline/](http://kernel.ubuntu.com/~kernel-ppa/mainline/).

```bash
cd /usr/src
# get the pre-built kernel package
curl -O http://kernel.ubuntu.com/~kernel-ppa/mainline/v4.0-vivid/linux-image-4.0.0-040000-generic_4.0.0-040000.201504121935_amd64.deb
curl -O http://kernel.ubuntu.com/~kernel-ppa/mainline/v4.0-vivid/linux-headers-4.0.0-040000-generic_4.0.0-040000.201504121935_amd64.deb
curl -O http://kernel.ubuntu.com/~kernel-ppa/mainline/v4.0-vivid/linux-headers-4.0.0-040000_4.0.0-040000.201504121935_all.deb
# install the new kernel
sudo dpkg -i linux-headers-4.0*.deb linux-image-4.0*.deb
```

#### EXERCISE: Confirm your build and install worked
1. Take a look at `/boot` and confirm that there is a new vmlinuz, initrd image file and config file corresponding to your build verison.
1. Take a look that `/lib/modules/$KERNEL_VERSION` has your new modules.

#### EXERCISE: Boot into your new kernel
Now your new kernel is built, let's boot into it! GRUB will automatically choose the latest kernel version to boot into.

1. `vim /etc/default/grub`
1. update the `GRUB_TIMEOUT` value to be 10 seconds or -1 to make it mandatory to choose a version upon every boot
1. run `update-grub` to regenerate grub.conf changes
1. `reboot` and now select your newest version of the kernel by selecting 'Advanced options for Debian GNU/Linux' and then the version.
1. Check for your custom kernel release string with `uname -a`

## /proc filesystem

#### EXERCISE: A tour of /proc
1. list the contents of `/proc`
1. Note the series of numbered files on the left. Each of these is a directory representing a process in the system. Because the first process created in GNU/Linux is the init process, it has a `process-id` of `1`. Next, performing an `ls` on this directory shows a list of files.
1. Each file provides details on the particular process. For example, to see the command-line entry for init, simply `cat` the `cmdline` file.
1. There are many useful files in /proc. To use them you just simply `cat` them. Try that out for the following: `cpuinfo`, `meminfo`, `filesystems`, `modules`, `mounts`.

#### EXERCISE: Dynamically update the running kernel with /proc
1. Run `cat /proc/sys/kernel/hostname` to see what the hostname is currently set too.
1. Write to the same file and update the hostname to be "Code PaLOUsa" or something else of your choice.

## Loadable Kernel Modules

**Helpful module Commands**
```bash
lsmod	# lists currently loaded modules
modinfo	# info about module

# loading/unloading
modprobe my_module	# loads module and its dependencies
modprobe -r my_module	# unloads module at its dependencies
OR
insmod my_module.ko # loads just the module (no dependencies)
rmmod my_module.ko # unloads just the module

# view kernel messages with either of:
/var/log/messages
dmesg | tail

uname -r 	# displays currently running kernel version
/lib/modules/`uname -r`/	# where module files are stored
```

#### EXERCISE: Learn about `lsmod`

1. Find out what file `lsmod` reads from

#### EXERCISE: Build your first kernel module

1. Install the Linux kernel headers `apt-get install linux-headers-$(uname -r)`. We need this so that we can build our own modules later on.
1. the base module code can be found [here](code/hi)
1. update the licence information to have your name
1. update the `hello_init` function to printk to debug ">>> Hello World! <<<"
1. update the `hello_exit` to printk ">>> Goodbye Cruel World... <<<" (HINT: `printk(KERN_DEBUG "my msg")`)
1. build it
1. verify your module works

#### EXERCISE: Returning negative number

1. modify your `hello_init` function to return -7
1. build and load it
1. what happens? check `dmesg` as you are trying this

#### EXERCISE: Returning positive number

1. modify your init method to return 7
1. build and load it
1. what happens? check `dmesg` as you are trying this

#### EXERCISE: Load an LKM on boot

1. Add an entry for our module to `/etc/modules` and reboot
1. Prove its loaded

#### EXERCISE: Checkstyle
Code won't be accepted into the kernel source tree unless it has the correct coding style. There is a hany tool which helps you meet these requirements.

1. find the `checkstyle.pl` script in the kernel source tree (HINT: `checkstyle.pl --file foo.c --no-tree is a good way to check a single file)
1. run it on your kernel module file and make updates as suggested

#### EXERCISE: Load a character device driver
1. the base module code can be found [here](code/char_mod)
1. build and load `hello_char.c`
1. Create the device file as per the `dmesg` output
1. Prove its been loaded
1. Check `/proc/devices` and `/proc/modules` for further proof its been loaded

##### References
* [http://www.tldp.org/HOWTO/Module-HOWTO/index.html](http://www.tldp.org/HOWTO/Module-HOWTO/index.html)
* [http://www.cyberciti.biz/tips/compiling-linux-kernel-module.html](http://www.cyberciti.biz/tips/compiling-linux-kernel-module.html)
* [http://www.linuxvoice.com/be-a-kernel-hacker/](http://www.linuxvoice.com/be-a-kernel-hacker/)
* [http://kernelnewbies.org/FirstKernelPatch](http://kernelnewbies.org/FirstKernelPatch)
