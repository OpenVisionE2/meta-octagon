SUMMARY = "halt for ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

COMPATIBLE_MACHINE = "^(sf8008|sf8008m)$"

RDEPENDS_${PN} = "harfbuzz"

SRCDATE = "20200601"

PV = "${SRCDATE}"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

SRC_URI  = "http://source.mynonpublic.com/octagon/${SOC_FAMILY}-hihalt-${SRCDATE}.tar.gz \
    file://suspend.sh \
    file://standby_leave.sh \
    file://standby_enter.sh \
"

SRC_URI[md5sum] = "7ff28a04e12e17c780b2b30bafb678a9"
SRC_URI[sha256sum] = "c7c9fba8894685d307e7d987c8050f4a41605f4095296123027ea8a47ba60207"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/hihalt ${D}${bindir}
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${S}/suspend.sh ${D}${sysconfdir}/init.d/suspend
    install -d ${D}${prefix}/script
    install -m 0755 ${S}/standby_leave.sh ${D}${prefix}/script/standby_leave.sh
    install -m 0755 ${S}/standby_enter.sh ${D}${prefix}/script/standby_enter.sh
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/hihalt ${sysconfdir}/init.d /usr/script"


