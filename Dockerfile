FROM ubuntu:22.04

ARG SDK_KEY
ENV SDK_KEY=${SDK_KEY}

RUN apt-get update && \
  apt-get install -y g++ make cmake libcurl4-openssl-dev libz-dev && \
  apt-get clean

WORKDIR /parse_flyrecord

COPY . .

WORKDIR /parse_flyrecord/dji-flightrecord-kit/build/Ubuntu/FRSample
RUN sh generate.sh

ENTRYPOINT ["./FRSample"]