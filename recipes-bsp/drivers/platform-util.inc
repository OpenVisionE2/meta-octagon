SUMMARY = "Platform Util drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc

PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "16.4"

PR = "${SRCDATE}.${SRCDATE_PR}"

SRC_URI = " \
	http://source.mynonpublic.com/octagon/platform-util-${MACHINE}-${PV}-${PR}.tar.gz \
	file://${INITSCRIPT_NAME}.sysvinit \
	"

do_install() {
	install -d ${D}${bindir}
	install -m 0755 ${WORKDIR}/nxserver ${D}${bindir}
	install -d ${D}${INIT_D_DIR}
	install -m 0755 ${WORKDIR}/${INITSCRIPT_NAME}.sysvinit ${D}${INIT_D_DIR}/${INITSCRIPT_NAME}
}

do_package_qa() {
}

FILES_${PN} = "/"

inherit update-rc.d

INITSCRIPT_PARAMS = "start 65 S . stop 90 0 ."
INITSCRIPT_NAME = "platform-util"
