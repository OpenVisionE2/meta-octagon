SUMMARY = "libreader for Octagon Model ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "libsdl"

COMPATIBLE_MACHINE = "sf8008"

SRCDATE = "20190814"

PV = "${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/octagon/${MACHINE}-libreader-${SRCDATE}.tar.gz"

SRC_URI[md5sum] = "b420df107cd736eb34dc6a20beff370e"
SRC_URI[sha256sum] = "abf8acbad7fd365a57e2a393a57dd891a035f45333edd15416eaf4774575c6b2"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/libreader ${D}/${bindir}
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/libreader"
