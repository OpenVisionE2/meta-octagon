# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

BOX_BRAND = "octagon"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	octagon-dvb-modules-${MACHINE} \
	octagon-initrd-${MACHINE} \
	gstreamer1.0-plugin-dvbmediasink \
	gstreamer1.0-libav \
	"

DVBPROVIDER = "kernel"
DVBSKYPROVIDER = "kernel"

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts=no --with-dtsdownmix --with-eac3 --with-h265 --with-vb6 --with-vb8 --with-vb9 --with-spark"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"
IMAGE_FSTYPES += "tar.bz2"

PREFERRED_PROVIDER_virtual/kernel = "linux-octagon"
PREFERRED_VERSION_directfb = "1.7.7"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "octagon-blindscan-utils"
PREFERRED_PROVIDER_virtual/blindscan-dvbc = "octagon-blindscan-utils"

MTD_ROOTFS = "mmcblk0p4"
MTD_KERNEL = "mmcblk0p3"

KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.tar.bz2"
MTD_BLACK  = "mmcblk0"

IMAGE_CMD_tar_prepend = "\
	mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
	cp -f ${DEPLOY_DIR_IMAGE}/${MACHINE}_update.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/update.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zImage ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
	echo ${IMAGE_NAME} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/donate.txt; \
	echo "rename this file to 'force' to force an update without confirmation" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/noforce; \
	echo "this file enable kernel update" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/partition.update; \
	cd ${IMAGE_ROOTFS}; \
	tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
	mv -f ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
	cd ${DEPLOY_DIR_IMAGE}; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.tar.bz2; \
	rm -Rf ${IMAGEDIR}; \
	"

IMAGE_CMD_tar_prepend = " \
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

MACHINE_FEATURES += "alsa switchoff hdmicec blindscan-tbs blindscan-dvbc dvb-c ci textlcd videoenhancement emmc mmc HDMI"

BOOTLOGO_FILENAME = "splash.bin"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/soc-family.inc
