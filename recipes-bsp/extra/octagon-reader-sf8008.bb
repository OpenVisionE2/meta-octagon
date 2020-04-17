SUMMARY = "libreader for ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "libsdl"

COMPATIBLE_MACHINE = "^(sf8008)$"

SRCDATE = "20200227"

PV = "${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/octagon/${MACHINE}-libreader-${SRCDATE}.tar.gz"

SRC_URI[md5sum] = "636bf340515819ff688adbe90ffb8c9d"
SRC_URI[sha256sum] = "7ce70894f4de4564bb7926ba077e2f45a6cb16e9ffb9780e4e473b7fcd05a73f"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/libreader ${D}/${bindir}
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/libreader"
