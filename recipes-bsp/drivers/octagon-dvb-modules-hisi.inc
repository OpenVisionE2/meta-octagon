SUMMARY = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc

PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "${KV}+${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/octagon/${MACHINE}-hiko-${SRCDATE}.zip"

S = "${WORKDIR}/hiko"

INHIBIT_PACKAGE_STRIP = "1"

FILES_${PN} += "${sysconfdir}/modules-load.d/_${MACHINE}.conf ${nonarch_base_libdir}/modules/${KV}/extra"

do_compile() {
}

do_install() {
	install -d ${D}${nonarch_base_libdir}/modules/${KV}/extra
	install -m 0644 ${S}/*.ko ${D}${nonarch_base_libdir}/modules/${KV}/extra
	install -m 0755  ${S}/load ${D}${nonarch_base_libdir}/modules/${KV}/extra
	install -d ${D}${sysconfdir}/modules-load.d
	echo "hi_media" >> ${D}${sysconfdir}/modules-load.d/_${MACHINE}.conf
}
