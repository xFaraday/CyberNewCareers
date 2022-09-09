#!/bin/bash

mkdir -p ./data/elasticsearch/data && sudo chown -R 1000:1000 ./data/elasticsearch

docker-compose -f docker-compose-honeytrap-playground.yml up
