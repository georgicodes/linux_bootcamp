# Linux Bootcamp: From Casual Linux User to Kernel Hacker (Workshop)

Session Info:
[OSCON:Linux Bootcamp: From Casual Linux User to Kernel Hacker](http://www.oscon.com/open-source-2015/public/schedule/detail/41300)

Monday, July 20th 2015 at 9:00am to 12:30pm

## How to use these materials
This GitHub repo contains an Ubuntu installation guide as well as all the workshop exercises.

All workshop exercises can be found [here](workshop).
All instructions below are for MAC OS but they should be easily translatable to Windows/Linux machines.

## Ubuntu Setup
For this workshop, we will use a program called Vagrant to run a full copy of Ubuntu Desktop version 15.04 (the latest and greatest). Vagrant requires that VirtualBox be pre-installed and is a handy tool which allows users to load pre-installed software. If we didn't use Vagrant we'd have to spend a good chunk of the class just installing Ubuntu on VirutalBox which is pretty boring :)

## Prerequsites
1. Free up around 10GB's on your laptop to get started.
2. It's important that you download the following software:
1. **Download and install** [VirtualBox for your OS](https://www.virtualbox.org/wiki/Downloads)
1. **Download and install** [Vagrant for your OS](https://www.vagrantup.com/downloads)
3. **Navigate to** the latest [Ubuntu Vagrant Box](https://app.vagrantup.com/ubuntu) and note the name. i.e: `ubuntu/focal64`

## Setting up Ubuntu with Vagrant

#### Check Vagrant is installed
Open up the Terminal program from Finder > Applications > Utilities > Terminal.
Check that you have Vagrant installed successfully by typing `vagrant --version` in your Terminal and hitting enter. You should see something like `Vagrant 1.7.2` [By the time this tutorial is written, it can differ].
![](images/vagrant_finder.png)
)

#### Creating a directory to initiate a Ubuntu Vagrant Box
From your Terminal, create a directory as `vagrant_ubuntu`.

```bash
$ cd ~/Desktop (This might be a different location for you)           # cd = change directory
$ mkdir vagrant_ubuntu                                                # mkdir = make directory
$ cd vagrant_ubuntu
```

#### Initialize the Vagrant box
```
$ vagrant init {latest_ubuntu_vagrant_box}
```
in our case:
```
$ vagrant init ubuntu/focal64
```
If you list the contents of this directory (`ls`), you'll now see a new file that was created `Vagrantfile`.

```bash
$ ls -la
total 3372
drwxr-xr-x@ 4 georgi  staff         136 Jul  7 20:59 .
drwx------+ 6 georgi  staff         204 Jul  7 20:47 ..
-rw-r--r--  1 georgi  staff        3032 Jul  7 20:59 Vagrantfile
```

#### Enable GUI
We now need to enable the GUI (Graphical User Interface). To do this edit the generated `Vagrantfile` with any text editor (Sublime, vi, Atom, TextEdit) by adding the following lines to the end of the file before the final line which says `end`.

```bash
config.vm.provider "virtualbox" do |v|
  v.gui = true
end
```
Your file should now look like this:

![](images/vagrantfile.png)

#### Spin it up!
We now have one final step to finish all the necessary initialization steps to setup Ubuntu with Vagrant.

Firstly open up the VirtualBox program from your Finder in Applications > VirtualBox. We'll come back to this program in a second.

**Note:** This command can take some time depending on your Network connection, as it's downloading Ubuntu.

Next, we run our final command:
```bash
$ vagrant up
Bringing machine 'default' up with 'virtualbox' provider...
==> default: Importing base box 'ubuntu/focal64'...
==> default: Matching MAC address for NAT networking...
==> default: Setting the name of the VM: vagrant_ubuntu_default_1437153016907_32911
==> default: Clearing any previously set network interfaces...
==> default: Preparing network interfaces based on configuration...
    default: Adapter 1: nat
==> default: Forwarding ports...
    default: 22 => 2222 (adapter 1)
==> default: Booting VM...
==> default: Waiting for machine to boot. This may take a few minutes...
    default: SSH address: 127.0.0.1:2222
    default: SSH username: vagrant
    default: SSH auth method: private key
    default: Warning: Connection timeout. Retrying...
    default:
    default: Vagrant insecure key detected. Vagrant will automatically replace
    default: this with a newly generated keypair for better security.
    default:
    default: Inserting generated public key within guest...
    default: Removing insecure key from the guest if its present...
    default: Key inserted! Disconnecting and reconnecting using new SSH key...
==> default: Machine booted and ready!
==> default: Checking for guest additions in VM...
==> default: Mounting shared folders...
    default: /vagrant => /Users/georgi/Downloads/vagrant_ubuntu
The following SSH command responded with a non-zero exit status.
Vagrant assumes that this means the command failed!

/sbin/initctl emit --no-wait vagrant-mounted MOUNTPOINT=/vagrant

Stdout from the command:



Stderr from the command:

stdin: is not a tty
initctl: Unable to connect to Upstart: Failed to connect to socket /com/ubuntu/upstart: Connection refused
```
Don't worry about those connection refused errors.

Vagrant has now done its job and we will only use VirtualBox from now on.

Open up VirutalBox and you will see and Ubuntu image called something like "vagrant_ubuntu_image_xxxxxx" listed on the left. Under the image name you will see the words "running" - this means that your Ubuntu image is up and running.

![](images/vagrant_version.png)

**The username and password for this Ubuntu image are both `vagrant`.**

#### Starting up and shutting down your Ubuntu image
You can shut it down at any time by pressing the red x on the Ubuntu window.
![](images/shutdown.png)

You can start it up by selecing the image name on the left and pressing the green Start button inside VirtualBox
![](images/startup.png)
