# IDS peak

## Installation Instructions

### System requirements

Install the following libraries for the IDS peak Cockpit:

Debian based distributions:

    sudo apt-get install libqt5core5a libqt5gui5 libqt5widgets5 libqt5multimedia5 libqt5x11extras5 libusb-1.0-0 libatomic1 libc6 \
    libstdc++6
       
For running the Qt qml samples you will further require:
     
    QtQuick, QtQuick.Window
     
For building the Qt qml samples you will further require:
     
    QtBase-dev, Qt 5 declarative development files
     
Debian based distributions:
      
    sudo apt-get install libqt5quick5 qml-module-qtquick-window2 qml-module-qtquick2 qml-module-qtquick-dialogs \
    qml-module-qtquick-controls qml-module-qtquick-layouts

And for development:

    sudo apt-get install qtbase5-dev qtdeclarative5-dev cmake gcc g++

### Vision GEV cameras
#### Automatic configuration of the IP address of a camera:
Add a link-local profile to the NetworkManager and assign it to the network interface where your camera is connected.

When running a Debian based distribution you need to install the following package beforehand for the link-local profile
to work:

    sudo apt-get install avahi-autoipd

#### Manual configuration of the IP address of a camera:

To configure the IP address of a camera either the ids_ipconfig tool or
ids_peak_cockpit can be used. When the camera is in a different subnet it
is only visible when using root privileges and can't be configured without root privileges for the default
configuration. The Debian package enables the possibility to do this without root privileges. For the archive
installation in order to configure the camera in this case the ids_ipconfig tool
or ids_peak_cockpit need to be run with root privileges e.g. sudo:

For the Debian package:

    IDS peak Cockpit:   sudo /usr/bin/ids_peak_cockpit
    IP Config:      sudo /usr/bin/ids_ipconfig

For the archive installation:

    IDS peak Cockpit:   sudo <archive_extract_dir>/bin/ids_peak_cockpit
    IP Config:      sudo <archive_extract_dir>/bin/ids_ipconfig

### Vision U3V cameras

#### udev rule
To use the USB Vision cameras you will need to set up an udev rule. The Debian package does this already but
for manual installation you can find an udev rule file in <archive_extract_dir>/local/scripts, which is
capable of setting the udev rule automatically.

For the archive installation:

    sudo <archive_extract_dir>/local/scripts/ids_install_udev_rule.sh

#### USB3 Vision cameras under USB 2.0
USB3 Vision cameras are limited usable under USB 2.0. Depending on the camera model, not all camera functions are
available in USB 2.0 mode. USB3 cameras are optimized for USB 3.0 ports and are not tested under USB 2.0.

Note that due to the high performance of modern sensors, some USB3 models are not supported in USB 2.0 mode anymore,
as the USB 2.0 interface does not provide enough power.


### Environment variables

The IDS peak packages uses the environment variable GENICAM_GENTL32_PATH / GENICAM_GENTL64_PATH to
find the GenTL producer libraries. The shipped executables in the bin folder are actually shell scripts which export the
variables for the current session and call the actual executables. For the source code of the samples CMake will
generate a starter script and copy it to the output folder which you should use to run the built samples. If you want to
build your own application you can either set the variables for your user account manually or build your own shell
script the same way CMake does for the shipped samples (see CMakeLists.txt for the samples).  
  
### The applications are started with their corresponding shell script files:
  
For the package installation run in a terminal:

    IDS peak Cockpit:    ids_peak_cockpit
    IP Config:       ids_ipconfig
    Device Command:  ids_devicecommand
    Device Update:   ids_deviceupdate

For the archive installation:

    IDS peak Cockpit:    <archive_extract_dir>/bin/ids_peak_cockpit
    IP Config:       <archive_extract_dir>/bin/ids_ipconfig
    Device Command:  <archive_extract_dir>/bin/ids_devicecommand
    Device Update:   <archive_extract_dir>/bin/ids_deviceupdate

### Building samples and own programs with CMake
  
When installed by Debian package the samples are copied to /usr/local/src/ids where you should
have no writing permissions. Please copy the samples to a folder with write permissions e.g. your home folder,
otherwise CMake will fail building them. The installation ships with a CMake config file for the shipped libraries.
If you use the Debian package you can simply use find_package since it will automatically find the config.cmake files. 
For the tar.gz installation file you have to set the CMAKE_PREFIX_PATH to the folder with the config files or the
library root with -DCMAKE_PREFIX_PATH="lib/".

### Documentation for shipped libraries

The HTML documentation for the shipped libraries can be found in 
<archive_extract_dir>/share/doc/ids-peak/LibraryName-Version/doc and for the Debian package
installation in /usr/share/doc/ids-peak/LibraryName-Version/doc.
   
### Note on installed and created files
  
The shipped programs may create config files in the .config directory of your home folder under the subdirectory
"IDS Imaging Development Systems GmbH".

## Uninstallation instructions
For the archive installation:

For the Tar archive, run the uninstall-udev-rule.sh in the folder "<archive_extract_dir>/local/scripts" to
remove the udev rule or remove it manually.
<br />
To uninstall the IDS peak delete the folder which was extracted from the tar archive. 
Check your .config directory in your home folder and delete the folder "IDS Imaging Development Systems GmbH" if you do not want
to reuse the configurations.

For the Debian package:
   
    run "sudo apt-get purge ids-peak"

## System Optimizations

### USB

#### Multi-camera system with USB cameras/high resolution cameras/cameras without image memory

The buffer memory's default value of the USB file system is often too
low for a multi-camera system/high resolution cameras. Increase
the memory value to avoid transfer losses. To adjust the memory value,
you must change the `usbfs_memory_mb` parameter with root privileges.

Example: Increase temporarily the parameter `usbfs_memory_mb` to 1000 MB (until the next PC reboot):

    echo 'new size' > /sys/module/usbcore/parameters/usbfs_memory_mb
    echo 1000 > /sys/module/usbcore/parameters/usbfs_memory_mb

In the folder `local/scripts` respectively `/usr/local/scripts` for the
Debian package, you find a script to change the `usbfs_memory_mb`
parameter persistently.

For the Debian package:

    sudo /usr/local/scripts/ids_set_usb_mem_size.sh

For the archive installation:

    sudo <archive_extract_dir>/local/scripts/ids_set_usb_mem_size.sh

### Networking

#### Enabling Jumbo Frames for GigE Vision cameras

For optimal performance it is recommended to use Ethernet package sizes
which are larger than 1500 bytes. Recommended package size is ~9000
bytes or higher depending on the support of the used network controller.
Your whole network infrastructure e.g. switches should support this
Ethernet package size; if not the GenTL will use the largest possible size.

To set the MTU to 9000 bytes on interface `eth0`:
```bash
sudo ip link set eth0 mtu 9000
```

> Note: This setting will be reset after a reboot. In order to make
>       it persistent, you could e.g. make a `systemd` service.
>       Refer to section *Maximizing the "Receive Buffer" size* for
>       an example service file.

#### Optimizing network stack buffer sizes:

The default Linux network stack is not optimized for transferring large
amounts of data. Therefore, it is recommended to increase the internal
buffer size of the UDP network stack to improve camera performance and
avoid package loss. But keep in mind that this increases the buffer
sizes only at the endpoints if you are you using switches or other
network infrastructure this might not have an effect:

To increase the network stack buffer size for UDP edit the file
`/etc/sysctl.conf`. If not present add the following lines:

    net.core.rmem_max=26214400
    net.core.rmem_default=26214400

This sets the maximum buffer size to ~25 MB, whereas the default buffer
size is usually 128 KB. In the folder `<archive_extract_dir>/local/scripts`
respectively `/usr/local/scripts` for the installed Debian package, you
will find a script, which is capable of adding the rmem sizes
automatically run it with sudo:

For the Debian package:

    sudo /usr/local/scripts/set_receive_buffer_size.sh

For the archive installation:

    sudo <archive_extract_dir>/local/scripts/set_receive_buffer_size.sh
 
Note that the script will not change the values if the entries are
already present, but it will tell you to check your values manually
since they might already be higher than the 26214400 bytes. For the
changes to become effective you have to reboot the system.

#### Maximizing the "Receive Buffer" size

For operating GigE cameras, it is recommended to set the receive buffer
size (so-called receive descriptors) of the network card to its maximum
value. Note that not all network cards provide this option.

To determine the maximum possible buffer sizes, you can use the `ethtool`
with the following command:

```bash
ethtool -g <interface_name>
```

Set the sizes of the rx and tx buffers:

```bash
ethtool -G <interface_name> rx <buffer_size>
ethtool -G <interface_name> tx <buffer_size>
```
> Note: These settings will be reset after a reboot. In order to
>       make the settings persistent, you could make a `systemd` service,
>       for example.

An example `systemd` service could look like this, for example:
```ini
[Unit]
Description=Set ethtool parameters for eth0
After=network-online.target
Wants=network-online.target

[Service]
Type=oneshot
ExecStart=/sbin/ethtool -G eth0 rx 4096 tx 4096
RemainAfterExit=yes

[Install]
WantedBy=multi-user.target
```

Such service files can be saved under
`/etc/systemd/system/ethtool-settings.service`, for example,
and enabled via the following commands:

```bash
sudo systemctl enable ethtool-settings
sudo systemctl start ethtool-settings
```

You can extend the service file by adding more `ExecStart=<command>`
lines to the file.

If using Ubuntu's NetworkManager,
you could utilize a NetworkManager dispatcher script instead.

#### Disabling interrupt throttling rate (ITR) for 10GigE cameras

Modern network interface drivers try to avoid high CPU load by reducing
the number of interrupts they generate. Although this is generally good,
the default settings of this option are not optimal for fast 10GigE
cameras. In this case, the "interrupt throttling rate" (depending on the
card manufacturer also: interrupt moderation rate) should be disabled.

> **Note**: If you disable the interrupt throttling rate, the CPU load increases.

You can use the `ethtool` to disable the interrupt throttling rate (ITR).

1. **Check the current interrupt coalescing settings**

    You can view the current interrupt moderation settings for your
    network interface using the `ethtool -c` command. Replace
    `<interface>` with the name of your network interface (e.g., `eth0`,
    `enp3s0`, etc.):

    ```bash
    sudo ethtool -c <interface>
    ```

    This shows the current settings for **Coalescing** parameters
    like **usecs** (microseconds between interrupts) and **pkts** (the
    number of packets before generating an interrupt). You typically
    see something like this:

    ```bash
    Coalesce parameters for <interface>:
    Pre-set maximums:
    RX-usecs:  0
    RX-frames: 0
    TX-usecs:  0
    TX-frames: 0
    Current settings:
    RX-usecs:  20
    RX-frames:  0
    TX-usecs:  0
    TX-frames:  0
    ```
2. **Disable interrupt throttling**

   To disable the interrupt throttling (moderation), you set
   **RX-usecs** to 0, which effectively disables interrupt moderation
   for the receiving side. 
   
   Set **adaptive-rx** to off to improve the latency at high
   packet receiving rates.

   > **Note**: Some NIC drivers do not support this feature.

    ```bash
    sudo ethtool -C <interface> rx-usecs 0 adaptive-rx off
    sudo ethtool -C <interface> tx-usecs 0 adaptive-tx off
    ```

> Note: These settings will be reset after a reboot. In order to make
>       the settings persistent, you could make a `systemd` service,
>       for example.
>       Refer to section *Maximizing the "Receive Buffer" size* for
>       an example service file.

#### Further settings

If you have still issues, you may find some of these settings helpful.

##### Enabling receive packet steering (RPS)

By default, the CPU that handles the network interrupt will also handle
the processing of the relevant packets. This may result in a performance
bottleneck, especially in high-bandwidth applications such as GigE
Vision cameras, where a large number of packets must be processed at
high speeds.

Receive Packet Steering (RPS) allows the network stack to distribute
packet processing across multiple CPU cores, reducing CPU contention and
improving overall throughput. This is particularly useful when dealing
with high frame rates and large image sizes, as it helps prevent a
single core from becoming overwhelmed, reducing packet loss and
improving real-time performance.

RPS is enabled by writing to
`/sys/class/net/<device>/queues/<rx-queue>/rps_cpus`, which defines a
bitmap indicating which CPUs are allowed to handle packet processing.

By default, all bits are set to 0, disabling RPS. As a result, the CPU
handling the interrupt will also process the packet.

To enable RPS and designate specific CPUs for packet processing on the
receive queue, you must set the corresponding bits in the bitmap to 1.

The following example would allow all cores on a quad core CPU to be
used for packet processing:
```bash
sudo echo f > /sys/class/net/<device>/queues/<rx-queue>/rps_cpus
```

If there are multiple queues, each file in `<rx-queue>` must be written
separately to configure this setting.

> Note: These settings will be reset after a reboot. In order to make
>       the settings persistent, you could make a `systemd` service,
>       for example.
>       Refer to section *Maximizing the "Receive Buffer" size* for
>       an example service file.

##### Fair Queueing (FQ)

Fair Queueing (FQ) ensures that packets from multiple flows are
distributed fairly. There are different fair queue modes available. If
supported, it is recommended to use `fq_codel`, otherwise use `fq`.

FQ helps reduce out-of-order packet issues and minimize latency,
particularly under heavy load. If available, use `fq_codel` for
UDP streams and real-time applications as it actively reduces
packet congestion.

> **Note**: These queue types are not supported by all NIC drivers.

To check the current queue settings, run the following command:
```bash
tc qdisc show dev <interface>
```

Use this command to set up FQ:
```bash
sudo tc qdisc replace dev <interface> root fq_codel
```

> Note: These settings will be reset after a reboot. In order to make
>       the settings persistent, you could make a `systemd` service,
>       for example.
>       Refer to section *Maximizing the "Receive Buffer" size* for
>       an example service file.

### Thread priority

Increasing the priority of the application that is running the image
acquisition can greatly improve performance, independent of the
underlying technology.

Start an application with real-time priority using the following command:

```bash
sudo chrt -f 99 <command>
```


## CURRENTLY KNOWN ISSUES
- Windows in the IDS peak Cockpit cannot be moved.
  - This is an issue with wayland and Qt.
  - The Qt programs need to be run under xwayland.
    - Run the executable with `QT_QPA_PLATFORM=xcb` e.g. `QT_QPA_PLATFORM=xcb /usr/bin/ids_peak_cockpit`.
    - The starter scripts include the workaround.
  - If an error occurs, try to install xwayland via the distribution installer e.g `apt install xwayland`.
- Issue on Nautilus (Ubuntu): The icon of a GUF File is not shown in the file system.
  - From version 2.2 it is possible to update a Vision camera by double-clicking on the GUF file. Unfortunately,
    no icon is shown for the GUF file under Nautilus.
  - Currently no solution as this is an issue in Nautilus itself.
- Default video player on Debian might cause stripes in recorded videos.
  - If you use the default Debian video player to replay the recorded AVI files, stripes may appear in the video.
  - This is caused by the "cluttervideosink" gstreamer plugin of Gnome.
  - Try to replay the video without stripes with the following command:<br/>
    ```gst-launch-1.0  filesrc location=<your video> ! decodebin ! videoconvert  ! autovideosink```
- The system's standard video player cannot replay the recorded video.
  - For recording, the GRAY8 MJPEG format is used. This format is not supported by all video players.
  - It is recommended to use the VLC video player.
- A connected GigE Vision camera is not visible in IDS peak Cockpit
  - If a GigE Vision camera is on a different subnet than the network adapter, the
    IDS peak Cockpit must be run as root to find the camera.
  - Start the IDS peak Cockpit as root to configure GigE Vision cameras from a different subnet.
- The reconnect function will not work if the IP address of a GigE camera is changed.
  - The reconnect feature (and the GenTL) cannot handle changes to the IP address of a GigE camera while the camera is
    in use.
  - Close the camera application before you change the camera's IP address and then restart the application.
- During runtime, changes to the network configuration are not detected by the GenTL
  - The GenTL cannot handle changes to the system's network configuration during runtime.
  - If you want to change the network configuration, first close the application and restart the application after you
    changed the network configuration.
- Running the  with QtWayland may cause flickering in combination with
  specific gnome-shell versions.
  This is a known bug of gnome-shell and should only occur on old gnome-shell versions < 3.32.
- It is not possible to start the IDS peak Cockpit as root
  - When you try to start the IDS peak Cockpit as root you get an error message like this:
    - "No protocol specified qt.qpa.screen: QXcbConnection: Could not connect to display :0 Could not connect to any X
    display"
  - This is caused by the fact that new Linux distributions and their display managers (GNOME, KDE, etc.) use Wayland as
  the display server protocol by default.
- On current Raspbian Buster versions there seems to be an issue with the DHCP daemon. If you use the GUI of Raspbian
  to set the network configuration there is an option to partially set options manually and let the system detect the
  other parts of the configuration. This option is called "Automatically configure empty options". If you do not have
  a DHCP server running, e.g. when you are directly connected to the camera this option may prevent you from using a
  GEV camera under Linux. The camera device will be detected but can not be used. The source of the issue is that the
  DHCP daemon does not set all network configurations properly, if it does not detect a DHCP server. Especially Kernel
  IP Routes will be wrong and will cause the described problem. If you experience these issues uncheck the option and 
  reboot your Raspberry Pi to make sure all options are set properly.
- The network performance on the Raspberry Pi may be extremely bad and can cause incomplete images. This is an issue
  with the network design of the Raspberry Pi which is actually connected via the USB controller. This may be 
  especially prominent on the Raspberry Pi 3 B+ which has a Gigabit Ethernet controller. To avoid these issues set the
  GEV SCPS Packet Size of your camera to 1500. Additionally reduce the DeviceLinkThroughPutLimit to a lower value
  e.g. 5301360.
