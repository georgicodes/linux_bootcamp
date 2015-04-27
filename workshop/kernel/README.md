# Kernel   

## How to configure and build your own kernel

#### EXERCISE: Fetch kernel source and create a kernel config file
This first way to create a config file, is to use the `make localmodconfig` build target. It runs `lsmod` to find all the modules loaded on the current running system and initializes the config with those modules. 

1. Fetch the latest kernel source from kernel.org into `/usr/src`
1. Unpack it
1. Run `make localmodconfig` This oldconfig process will carry over your previous settings, and prompt you if there are new features not covered by your earlier .config file. You will be asked lots of questions, if you just keep pressing (or holding down) enter, the default answer will be selected.
1. Confirm that a file called `.config` was created
1. Note down the value of the following configuration setting `CONFIG_LOCALVERSION_AUTO`. HINT: `cat` the config file and `grep` for this setting.

#### EXERCISE: Customize the kernel config
We are now going to update this .config file with some custom settings. For this config file we want to set the `CONFIG_LOCALVERSION_AUTO=y` and to turn on support for thunderbolt.

The second method of creating a config file is to uses the menu UI. It will read from the `.config` file already created in the previous step and allow you to further customize.

1. Firstly install `libncurses5-dev` as this is needed for the GUI to work.
1. Run `make menuconfig`
1. Turn on 'Automatically append version information...' under the `General Setup` menu.
1. Search for and select Thuderbolt support under `Device Drivers` menu. Ensure to turn this on as a `built-in` kernel option not a `module` option.
1. Spend some time poking around and looking at all the different options. Its dizzying how many there are, setting each on individually would take you all day!
1. Save and exit
1. Note down the value of the following configuration setting `CONFIG_LOCALVERSION_AUTO`. Make sure its set to `CONFIG_LOCALVERSION_AUTO=y`. (Setting to be explained in next exercise)

#### EXERCISE: Customizing your kernel release string
It's always fun to personalize things. The `CONFIG_LOCALVERSION_AUTO=y` config option we set previously allows us to append a version name to our kernel version string.

1. Update the `EXTRAVERSION` field in the `Makefile` found in the root of the kernel source tree. Adding your name here or something silly like `-rainbow-unicorns-rule`. This will be appended to your kernel version name string. Note, start this with a dash `-`.
1. Now find out what the final kernel release string will be by running `make kernelrelease`.

#### EXERCISE: Configuring for another architecture
Let's take a brief look at how you would configure your kernel for building on another architecture.

1. `ls arch` lists out all the supported architectures.
1. `make ARCH=blackfin menuconfig`
NOTE: you can't actually build a kernel for any other architecture until you install the appropriate cross-compiler toolchain.
1. Exit and Save but rename the file to be `.config-blackfin`

#### EXERCISE: Buliding your kernel - TO DO AT HOME!!
There are multiple ways that you can build and install your own kernel, here I have presented one way. This will install the new (compressed) kernel image into the `/boot` directory so that GRUB can find it at boot time

1. Run the following commands and wait for victory!
```bash
make 	# builds a kernel ready to be installed
make modules_install: # Installs all of the newly-built modules. They will now show up under a directory in `/lib/modules`
make install 	#  Install the new (compressed) kernel image into the `/boot` directory so that GRUB can find it at boot time. And it also create a new initrd initial ram disk that goes along with that kernel to support the early part of the boot process
```

#### EXERCISE: Install a pre-built kernel
As it will take too long build a kernel in this workshop as asked in exercie "Buliding your kernel" we are going to instead install kernel version 4.0 from the ubuntu kernel mainline repo: [http://kernel.ubuntu.com/~kernel-ppa/mainline/](http://kernel.ubuntu.com/~kernel-ppa/mainline/).

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
