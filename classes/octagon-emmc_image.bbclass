inherit image_types

IMAGE_TYPEDEP_octagonemmc = "ext4"

do_image_octagonemmc[depends] = " \
    parted-native:do_populate_sysroot \
    dosfstools-native:do_populate_sysroot \
    mtools-native:do_populate_sysroot \
    virtual/kernel:do_populate_sysroot \
    octagon-buildimage-native:do_populate_sysroot \
    "

IMAGE_CMD_octagonemmc () {
    mkdir -p ${IMGDEPLOYDIR}/userdata
    mkdir -p ${IMGDEPLOYDIR}/userdata/linuxrootfs1
    mkdir -p ${IMGDEPLOYDIR}/userdata/linuxrootfs2
    mkdir -p ${IMGDEPLOYDIR}/userdata/linuxrootfs3
    mkdir -p ${IMGDEPLOYDIR}/userdata/linuxrootfs4
    echo "${MACHINE}'s ${IMAGE_ROOTFS}" >/tmp/${MACHINE}-image-log
    ls -la "${IMAGE_ROOTFS}" >> /tmp/${MACHINE}-image-log
    cp -fr --preserve=links,mode ${IMAGE_ROOTFS}/* ${IMGDEPLOYDIR}/userdata/linuxrootfs1/
    echo "Using ${IMGDEPLOYDIR}/userdata/linuxrootfs1" >> /tmp/${MACHINE}-image-log
    /usr/bin/fakeroot ls -la "${IMGDEPLOYDIR}/userdata/linuxrootfs1/" >> /tmp/${MACHINE}-image-log
    eval local COUNT=\"0\"
    eval local MIN_COUNT=\"60\"
    if [ $ROOTFS_SIZE -lt $MIN_COUNT ]; then
        eval COUNT=\"$MIN_COUNT\"
    fi
    dd if=/dev/zero of=${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ext4 seek=${IMAGE_ROOTFS_SIZE} count=$COUNT bs=1024
    /usr/bin/fakeroot mkfs.ext4 -F -i 4096 ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ext4 -d ${IMGDEPLOYDIR}/userdata
}
