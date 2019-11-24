SUMMARY = "player daemon helper"
MAINTAINER = "octagon"

require conf/license/license-gplv2.inc

PV = "1.0"

COMPATIBLE_MACHINE = "^(sf8008|sf8008m)$"

SRC_URI = "file://octagon-libreader-hisi3798mv200.sh"

INITSCRIPT_NAME = "octagon-libreader"
INITSCRIPT_PARAMS = "start 05 S ."

inherit update-rc.d

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}${sysconfdir}/init.d/
    install -m 0755 ${WORKDIR}/octagon-libreader-hisi3798mv200.sh ${D}${sysconfdir}/init.d/octagon-libreader
}
