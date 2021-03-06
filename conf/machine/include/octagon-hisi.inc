# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

KERNELVERSION = "4.4.35"

BOX_BRAND = "octagon"

DISTRO_FEATURES_remove += "x11 wayland"

IMAGEDIR = "octagon/${MACHINE}"

MTD_KERNEL = "mmcblk0p12"
MTD_ROOTFS = "mmcblk0p16"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.tar.bz2"
MTD_BLACK  = "mmcblk0"

SOC_FAMILY = "hisi3798mv200"
HICHIPSET = "3798mv200"
CHIPSET = "Hi3798Mv200"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	octagon-dvb-modules-${MACHINE} \
	octagon-loadmodules-${SOC_FAMILY} \
	octagon-opengl-${SOC_FAMILY} \
	octagon-libs-${MACHINE} \
	octagon-hihalt-${SOC_FAMILY} \
	octagon-reader-${MACHINE} \
	octagon-libreader-${SOC_FAMILY} \
	octagon-partitions-${MACHINE} \
	e2fsprogs-resize2fs \
	gptfdisk \
	kernel-module-extrawlan-rtl8192eu \
	firmware-rtl8192eu \
	kernel-module-mt7601u \
	firmware-mt7601u \
	kernel-module-extrawlan-rtl8822cu \
	${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'partitions-by-name' , '', d)} \
	"

MACHINE_FEATURES += "switchoff 7segment hdmicec textlcd emmc mmc blindscan-dvbs alsa hisil multitranscoding HDMI AV_JACK vfdsymbol kodi19"

IMAGE_CLASSES  += "octagon-emmc_image"
IMAGE_FSTYPES += "octagonemmc"
IMAGE_ROOTFS_SIZE ?= "524288"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

PREFERRED_PROVIDER_virtual/kernel = "linux-octagon"
PREFERRED_VERSION_linux-octagon = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/egl ?= "octagon-opengl-${SOC_FAMILY}" 
PREFERRED_PROVIDER_virtual/libgles1 ?= "octagon-opengl-${SOC_FAMILY}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "octagon-opengl-${SOC_FAMILY}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "octagon-blindscan-${SOC_FAMILY}"
PREFERRED_RPROVIDER_showiframe = "octagon-showiframe-${SOC_FAMILY}"
PREFERRED_RPROVIDER_aio-grab = "octagon-grab-${SOC_FAMILY}"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

require conf/machine/include/tune-cortexa15.inc


require conf/machine/include/soc-family.inc

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-spark --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

EXTRA_OECONF_append_pn-enigma2 = "--with-lcddev=/dev/null --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250 --with-fillaccelerationthreshold=190000 --with-subttxtabnormalptsdiffs=3600000"

IMAGE_CMD_octagonemmc_append = " \
	mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
	mv -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ext4 ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/rootfs.ext4; \
	cd ${IMAGE_ROOTFS}; \
	tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
	mv -f ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${KERNEL_FILE}; \
	echo ${IMAGE_NAME} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/donate.txt; \
	cd ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions; \
	mkupdate -s 00000003-00000001-01010101 -f ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/emmc_partitions.xml -d ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
	cd ${DEPLOY_DIR_IMAGE}; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.manifest ${IMAGE_NAME}_usb.zip.manifest; \
	zip -j ${IMAGE_NAME}_recovery_emmc.zip ${DEPLOY_DIR_IMAGE}/usb_update.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/donate.txt ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/apploader.bin; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
	rm -f ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
	rm -Rf ${IMAGEDIR}; \
	rm -Rf userdata; \
	"

IMAGE_CMD_prepend = "\
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/userdata; \
	"

STB_PLATFORM = "octagonhisil"

EXTRA_ALSA = "mv200"

BLINDSCAN_BINARY = "octagon-blindscan"

RCNAME = "sf8008"
