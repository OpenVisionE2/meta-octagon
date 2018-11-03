SUMMARY = "libreader for Octagon Model ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "libsdl"

COMPATIBLE_MACHINE = "sf8008"

SRCDATE = "20181101"

PV = "${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/octagon/${MACHINE}-libreader-${SRCDATE}.tar.gz"

SRC_URI[md5sum] = "5ef6995a00320fad3d0a212c84e816a7"
SRC_URI[sha256sum] = "1a9f5316141be41326ab7ecc0a24b6d709bd10589aa4babb7d11c7e92f712362"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/libreader ${D}/${bindir}
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/libreader"
