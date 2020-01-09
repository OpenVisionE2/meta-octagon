SUMMARY = "halt for Octagon Model ${SOC_FAMILY}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"

COMPATIBLE_MACHINE = "^(sf8008|sf8008m)$"

RDEPENDS_${PN} = "harfbuzz"

SRCDATE = "20190917"

PV = "${SRCDATE}"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

SRC_URI  = "http://source.mynonpublic.com/octagon/${SOC_FAMILY}-hihalt-${SRCDATE}.tar.gz \
    file://suspend.sh \
    file://standby_leave.sh \
    file://standby_enter.sh \
"

SRC_URI[md5sum] = "bae519aa059c42c559469cf9ef16bcd7"
SRC_URI[sha256sum] = "aa1616f08fe4b4c5e5431d5473bad6671e7b86958ca2a0be1373d79fee65199e"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/hihalt ${D}/${bindir}
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${S}/suspend.sh ${D}${sysconfdir}/init.d/suspend
    install -d ${D}/usr/script
    install -m 0755 ${S}/standby_leave.sh ${D}/usr/script/standby_leave.sh
    install -m 0755 ${S}/standby_enter.sh ${D}/usr/script/standby_enter.sh
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/hihalt ${sysconfdir}/init.d"


