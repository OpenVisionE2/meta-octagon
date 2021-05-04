require octagon-stb-kodi.inc

EXTRA_OECMAKE += " \
    -DWITH_PLATFORM=nextv-cortexa15 \
    -DWITH_FFMPEG=stb \
"

COMPATIBLE_MACHINE = "^(sf5008)$"
