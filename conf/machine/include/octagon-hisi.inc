# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

BOX_BRAND = "octagon"

DISTRO_FEATURES_remove = "x11 wayland"

IMAGEDIR = "octagon/${MACHINE}"

MTD_KERNEL = "mmcblk0p12"
MTD_ROOTFS = "mmcblk0p16"
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

KERNEL_MODULE_AUTOLOAD += "xfs"

require conf/machine/include/soc-family.inc

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-spark --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

IMAGE_CMD_octagonemmc_append = "\
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/userdata; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/userdata/linuxrootfs1; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/userdata/linuxrootfs2; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/userdata/linuxrootfs3; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/userdata/linuxrootfs4; \
    cp -a ${IMAGE_ROOTFS}/* ${DEPLOY_DIR_IMAGE}/userdata/linuxrootfs1/; \
    mkfs.ext4 -F -i 4096 ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/rootfs.ext4 -d ${DEPLOY_DIR_IMAGE}/userdata; \
    cd ${IMAGE_ROOTFS}; \
    tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
    mv ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
    bzip2 ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
    cp ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
    cp ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${KERNEL_FILE}; \
    echo ${IMAGE_NAME} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    cd ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions; \
    mkupdate -s 00000003-00000001-01010101 -f ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/emmc_partitions.xml -d ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
    cd ${DEPLOY_DIR_IMAGE}; \
    cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.manifest ${IMAGE_NAME}_usb.zip.manifest; \
    zip -j ${IMAGE_NAME}_recovery_emmc.zip ${DEPLOY_DIR_IMAGE}/usb_update.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/apploader.bin; \
    zip ${IMAGE_NAME}_mmc.zip ${IMAGEDIR}/*; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
    rm -Rf ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
    rm -Rf ${IMAGEDIR}; \
    rm -Rf ${DEPLOY_DIR_IMAGE}/userdata; \
    "
