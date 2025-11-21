FROM mcr.microsoft.com/devcontainers/base:bookworm

USER root

# Install needed packages. Use a separate RUN statement to add your own dependencies.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install \
        build-essential \
        git \
        cppcheck \
        clang lldb \
        llvm gdb \
        libcunit1 libcunit1-doc libcunit1-dev \
        && apt-get autoremove -y \
        && apt-get clean -y \
        && rm -rf /var/lib/apt/lists/*

# Install HID Cloudflare CA certificate from local assets
COPY assets/CF_ca.crt /usr/local/share/ca-certificates/Cloudflare_HID_CA.crt
RUN update-ca-certificates 

ARG USERNAME=vscode