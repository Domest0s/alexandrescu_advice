FROM ubuntu:latest
USER root
RUN apt-get update && apt-get -y install ninja-build
# CMake FetchContent needs git to
RUN apt-get update && apt-get -y install git
RUN apt-get -y install build-essential \
  && apt-get install -y wget \
  && rm -rf /var/lib/apt/lists/* \
  && wget https://github.com/Kitware/CMake/releases/download/v3.29.0-rc2/cmake-3.29.0-rc2-linux-x86_64.sh \
      -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /opt/cmake-3.29.0-rc2 \
      && /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake-3.29.0-rc2 \
      && rm /tmp/cmake-install.sh \
      && ln -s /opt/cmake-3.29.0-rc2/bin/* /usr/local/bin

# https://github.com/Kitware/CMake/releases/download/v3.29.0-rc2/cmake-3.29.0-rc2-linux-x86_64.sh

# RUN apt-get install -y cmake
# RUN curl -fsSLo /usr/share/keyrings/docker-archive-keyring.asc \
#   https://download.docker.com/linux/debian/gpg
# RUN echo "deb [arch=$(dpkg --print-architecture) \
#   signed-by=/usr/share/keyrings/docker-archive-keyring.asc] \
#   https://download.docker.com/linux/debian \
#   $(lsb_release -cs) stable" > /etc/apt/sources.list.d/docker.list
# RUN apt-get update && apt-get install -y docker-ce-cli
# USER jenkins
# RUN jenkins-plugin-cli --plugins "blueocean docker-workflow"



