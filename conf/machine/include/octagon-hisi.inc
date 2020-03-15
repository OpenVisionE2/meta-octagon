# We know about rtc
require conf/machine/include/build-extras.inc

BOX_BRAND = "octagon"

DISTRO_FEATURES_remove = "x11 wayland"

IMAGEDIR = "octagon/${MACHINE}"

MTD_KERNEL = "mmcblk0p12"

KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.tar.bz2"
MTD_BLACK  = "mmcblk0"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
    octagon-dvb-modules-${MACHINE} \
    octagon-loadmodules-${SOC_FAMILY} \ 
    octagon-libs-${MACHINE} \
    octagon-hihalt-${SOC_FAMILY} \
    octagon-reader-${MACHINE} \
    octagon-libreader-${SOC_FAMILY} \
    octagon-partitions-${MACHINE} \
    e2fsprogs-resize2fs \
    gptfdisk \
    rtl8192eu \
    firmware-rtl8192eu \
    kernel-module-mt7601u \
    firmware-mt7601u \
    ${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'partitions-by-name' , '', d)} \
"

MACHINE_FEATURES += "switchoff 7segment hdmicec textlcd emmc mmc blindscan-dvbs alsa hisil"

IMAGE_CLASSES  += "octagon-emmc_image"
IMAGE_FSTYPES += "octagonemmc"
IMAGE_ROOTFS_SIZE ?= "524288"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

PREFERRED_PROVIDER_virtual/kernel = "linux-octagon"
PREFERRED_VERSION_linux-octagon = "4.4.35"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "octagon-blindscan-${SOC_FAMILY}"
PREFERRED_RPROVIDER_showiframe = "octagon-showiframe-${SOC_FAMILY}"
PREFERRED_RPROVIDER_aio-grab = "octagon-grab-${SOC_FAMILY}"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice ?= "enigma2-plugin-systemplugins-servicehisilicon"
PREFERRED_VERSION_ffmpeg = "3.4.2"

require conf/machine/include/tune-cortexa15.inc

MACHINE_EXTRA_RRECOMMENDS += "\
    gstreamer1.0-plugin-dvbmediasink \
    "

DVBPROVIDER = "kernel"
DVBSKYPROVIDER = "kernel"

require conf/machine/include/autoload-filesystems.inc
require conf/machine/include/soc-family.inc

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-spark --with-wma --with-wmv --with-pcm --with-dts --with-eac3"
