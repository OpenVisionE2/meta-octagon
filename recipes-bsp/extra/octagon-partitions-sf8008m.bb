SUMMARY = "${MACHINE} partitions files"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy update-rc.d

SRCDATE = "20200423"

COMPATIBLE_MACHINE = "^(sf8008m)$"

S = "${WORKDIR}/patitions"

SRC_URI = "http://source.mynonpublic.com/octagon/${MACHINE}-partitions-${SRCDATE}.zip \
  file://flash-apploader \
"

INITSCRIPT_NAME = "flash-apploader"
INITSCRIPT_PARAMS = "start 90 S ."

SRC_URI[md5sum] = "cc5e7d4a7545cd93393d3578373462f5"
SRC_URI[sha256sum] = "9af2952f33d2da93af094775f8b6c43070aee76567b1d2576dc47734b3ac0a47"

ALLOW_EMPTY_${PN} = "1"
do_configure[nostamp] = "1"

do_install() {
    install -d ${D}${datadir}
    install -m 0644 ${S}/bootargs.bin ${D}${datadir}/bootargs.bin
    install -m 0644 ${S}/fastboot.bin ${D}${datadir}/fastboot.bin
    install -m 0644 ${S}/apploader.bin ${D}${datadir}/apploader.bin
    install -m 0755 -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/flash-apploader ${D}${sysconfdir}/init.d/flash-apploader
}

FILES_${PN} = "${datadir} ${sysconfdir}"

do_deploy() {
    install -d ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/boot.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/apploader.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/pq_param.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/emmc_partitions.xml ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/baseparam.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/logo.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/deviceinfo.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
}

addtask deploy before do_build after do_install

