SUMMARY = "libreader for Octagon Model ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "libsdl"

COMPATIBLE_MACHINE = "sf8008"

SRCDATE = "20181114"

PV = "${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/octagon/${MACHINE}-libreader-${SRCDATE}.tar.gz"

SRC_URI[md5sum] = "001d6e9ade7a2a3807f2833d4a702a9c"
SRC_URI[sha256sum] = "e1ee3550e55c0e5ae62e56c2ad3dd36b36beb796f3e272b5eb9aa72ce844bac5"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/libreader ${D}/${bindir}
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/libreader"
