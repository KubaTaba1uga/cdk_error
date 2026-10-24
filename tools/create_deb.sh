#!/bin/bash

set -xeu

. /etc/os-release

export PACKAGE_NAME=$1
export VERSION=$2
export REVISION=$3
export DESCRIPTION=$4
export DEBIAN_DIST=$VERSION_CODENAME
export ARCH=$(dpkg --print-architecture)

rm -rf /tmp/${PACKAGE_NAME}-${VERSION}*

mkdir -p build /tmp/${PACKAGE_NAME}-${VERSION} \
         /tmp/${PACKAGE_NAME}-${VERSION}/DEBIAN \
         /tmp/${PACKAGE_NAME}-${VERSION}/usr \
	 /tmp/${PACKAGE_NAME}-${VERSION}/usr/lib

j2 --import-env='' deb/DEBIAN/control.j2 -o /tmp/${PACKAGE_NAME}-${VERSION}/DEBIAN/control

meson setup -Dbuildtype=release --prefix=/tmp/${PACKAGE_NAME}-${VERSION}/usr /tmp/${PACKAGE_NAME}-${VERSION}-build
meson compile -C /tmp/${PACKAGE_NAME}-${VERSION}-build
meson install -C /tmp/${PACKAGE_NAME}-${VERSION}-build

chmod 755 -R /tmp/${PACKAGE_NAME}-${VERSION}/DEBIAN
dpkg-deb --root-owner-group --build /tmp/${PACKAGE_NAME}-${VERSION}

mv /tmp/${PACKAGE_NAME}-${VERSION}.deb build/${PACKAGE_NAME}-${VERSION}+${DEBIAN_DIST}_${ARCH}.deb
