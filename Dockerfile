FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y g++

COPY . /usr/src/app

WORKDIR /usr/src/app

RUN chmod +x /usr/src/app/entrypoint.sh

ENTRYPOINT ["/usr/src/app/entrypoint.sh"]
