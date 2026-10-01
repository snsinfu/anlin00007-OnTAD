FROM debian:bookworm-slim AS build

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      g++ make libcurl4-openssl-dev zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /build
COPY src/ ./src/

RUN make -C src

FROM debian:bookworm-slim AS runtime

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      libcurl4 zlib1g ca-certificates procps \
 && rm -rf /var/lib/apt/lists/*

COPY --from=build /build/src/OnTAD /usr/local/bin/OnTAD

WORKDIR /data
CMD ["/bin/bash"]
