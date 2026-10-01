FROM debian:bookworm-slim AS build

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      g++ make libcurl4-openssl-dev zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /build
COPY src/ ./src/

RUN g++ -std=c++11 -O2 \
      src/main.cpp src/step1.cpp src/step2.cpp src/step3.cpp src/step4.cpp \
      src/common.cpp src/straw.cpp \
      -lm -lcurl -lz -o OnTAD

FROM debian:bookworm-slim AS runtime

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      libcurl4 zlib1g ca-certificates \
 && rm -rf /var/lib/apt/lists/*

COPY --from=build /build/OnTAD /usr/local/bin/OnTAD

WORKDIR /data
CMD ["/bin/bash"]
