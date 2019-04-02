SUMMARY = "libreader for Octagon Model ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "libsdl"

COMPATIBLE_MACHINE = "sf8008"

SRCDATE = "20190402"

PV = "${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/octagon/${MACHINE}-libreader-${SRCDATE}.tar.gz"

SRC_URI[md5sum] = "5af4077161ac107f5dc42c7661021b6e"
SRC_URI[sha256sum] = "ba51292674337904c2d97b1b098791d874461a3ba57656361e3f5e4b95ce0926"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/libreader ${D}/${bindir}
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/libreader"
