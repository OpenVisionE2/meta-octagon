SUMMARY = "kernel modules load helper"
MAINTAINER = "octagon"

require conf/license/license-gplv2.inc

COMPATIBLE_MACHINE = "^(sf8008|sf8008m)$"

SRC_URI = "file://octagon-loadmodules-hisi3798mv200.sh"

INITSCRIPT_NAME = "octagon-loadmodules"
INITSCRIPT_PARAMS = "start 01 S ."

inherit update-rc.d

S = "${WORKDIR}"

do_compile() {
}

do_install() {
	install -d ${D}${sysconfdir}/init.d/
	install -m 0755 ${WORKDIR}/octagon-loadmodules-hisi3798mv200.sh ${D}${sysconfdir}/init.d/octagon-loadmodules
}
