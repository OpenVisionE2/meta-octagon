SUMMARY = "libreader for Octagon Model ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "libsdl"

COMPATIBLE_MACHINE = "^(sf8008)$"

SRCDATE = "20200108"

PV = "${SRCDATE}"

SRC_URI = "http://define-sw.dyndns.tv/openatv/openpli/${MACHINE}-libreader-${SRCDATE}.tar.gz"

SRC_URI[md5sum] = "4599e059a72a22a4125242fe7c930b6e"
SRC_URI[sha256sum] = "ea2f80dfe7e3718a20bed52c75425ed47adaf06be2364ee394bd74b25c8ee39d"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/libreader ${D}/${bindir}
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/libreader"
