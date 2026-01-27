#!/bin/bash

# install Homebrew package manager, which also install Xcode Command Line Tools
which -s brew
if [[ $? != 0 ]] ; then
    # Install Homebrew
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
else
    brew update
fi

# install Bazel build system
brew install bazel buildifier

# install colima, with support for cross-compilation
brew install colima lima-additional-guestagents qemu
eval "$(brew shellenv)"
# install docker
brew install docker docker-buildx docker-compose
INS=",\n\t\"cliPluginsExtraDirs\": [\n\t\t\"$HOMEBREW_PREFIX/lib/docker/cli-plugins\"\n\t]"
sed -i "" "s|\"currentContext\": \"colima\"|\"currentContext\": \"colima\"${INS}|" ~/.docker/config.json
mkdir -p ~/.docker/certs.d && cp certs/* ~/.docker/certs.d

# if using container registry then build multi-platform
# if multi-platform and macos arm then vz and rosetta
# if multi-platform and macos intel then qemu
$ROSETTA=
if [[ $(arch) == 'arm64' ]]; then
    softwareupdate --install-rosetta
    $ROSETTA='--vz-rosetta'
fi

# enable multi-platform builds
colima start --memory 4 --vm-type=vz $ROSETTA && colima stop # --cpus 4 --disk 128
# sed -i "" "s|docker: {}|docker:\n  features:\n    containerd-snapshotter: true|" ~/.colima/default/colima.yaml # default since v29
