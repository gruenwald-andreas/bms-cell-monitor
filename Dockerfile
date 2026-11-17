FROM ubuntu:24.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install compiler toolchain, CMake, Git, and static code analyzer
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    cppcheck \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
