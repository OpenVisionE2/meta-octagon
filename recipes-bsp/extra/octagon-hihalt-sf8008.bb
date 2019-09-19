SUMMARY = "halt for Octagon Model ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

COMPATIBLE_MACHINE = "sf8008"

RDEPENDS_${PN} = "harfbuzz"

SRCDATE = "20190917"

PV = "${SRCDATE}"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

SRC_URI  = "http://source.mynonpublic.com/octagon/${MACHINE}-hihalt-${SRCDATE}.tar.gz \
    file://suspend.sh \
"

SRC_URI[md5sum] = "bae519aa059c42c559469cf9ef16bcd7"
SRC_URI[sha256sum] = "aa1616f08fe4b4c5e5431d5473bad6671e7b86958ca2a0be1373d79fee65199e"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/hihalt ${D}/${bindir}
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${S}/suspend.sh ${D}${sysconfdir}/init.d/suspend
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/hihalt ${sysconfdir}/init.d"


