SUMMARY = "blindscan for ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"

COMPATIBLE_MACHINE = "^(sf8008|sf8008m)$"

PROVIDES += "virtual/blindscan-dvbs"
RPROVIDES_${PN} += "virtual/blindscan-dvbs"

SRCDATE = "20190305"

PV = "${SRCDATE}"

SRC_URI  = "http://source.mynonpublic.com/octagon/${SOC_FAMILY}-blindscan-${SRCDATE}.zip"

SRC_URI[md5sum] = "643ec0736a15f3aa16023772d1462a13"
SRC_URI[sha256sum] = "c1c72d745d094c6b78203302e187e828e2293b72c804030c9246c296f63d4aa1"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/${BLINDSCAN_BINARY} ${D}${bindir}
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}"

do_prepare_recipe_sysroot[noexec] = "1"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
do_compile[noexec] = "1"
deltask do_populate_sysroot
