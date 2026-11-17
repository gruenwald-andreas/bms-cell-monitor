FROM ubuntu:24.04

# Zeitzonen-Abfrage beim Installieren verhindern
ENV DEBIAN_FRONTEND=noninteractive

# Compiler, CMake, Git und statische Code-Analyse installieren
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    cppcheck \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
