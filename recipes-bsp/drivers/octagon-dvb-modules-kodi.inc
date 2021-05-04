SUMMARY = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc

PACKAGE_ARCH = "${MACHINE}"

PV = "${KV}+${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/octagon/${MACHINE}-drivers-${KV}-${GCCREV}-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

do_compile() {
}

do_populate_sysroot() {
}

do_install() {
	install -d ${D}${nonarch_base_libdir}/modules/${KV}/extra
	install -d ${D}${sysconfdir}/modules-load.d
	install -m 0755 ${WORKDIR}/linuxtv.ko ${D}${nonarch_base_libdir}/modules/${KV}/extra/linuxtv-kodi.ko
	touch ${D}${sysconfdir}/${MACHINE}-kodi
}

pkg_postinst_${PN}() {
#!/bin/sh
if [ -e ${nonarch_base_libdir}/modules/${KV}/extra/linuxtv-kodi.ko ]; then
 mv -f ${nonarch_base_libdir}/modules/${KV}/extra/linuxtv-kodi.ko ${nonarch_base_libdir}/modules/${KV}/extra/linuxtv.ko
fi
exit 0
}

FILES_${PN} += "${sysconfdir}/${MACHINE}-kodi ${nonarch_base_libdir}/modules/${KV}/extra"
