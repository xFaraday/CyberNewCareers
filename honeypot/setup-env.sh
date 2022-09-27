#!/bin/bash

#root check
if [ "$EUID" -ne 0 ]; then
  echo 'Error: Please run as root'
  exit 1
fi

echo -e "\nPlease stop this script if internet access is not avaliable...in"
sleep 1
echo "5..."
sleep 1
echo "4..."
sleep 1
echo "3..."
sleep 1
echo "2..."
sleep 1
echo "1..."
sleep 1

#getting docker
which docker || snap install docker

mkdir honeypot; cd honeypot

#create docker network
docker network create honeytrap

#increasing docker limit size
sysctl -w vm.max_map_count=262144

#get config files
wget https://raw.githubusercontent.com/xFaraday/CyberNewCareers/main/honeypot/config.toml || curl https://raw.githubusercontent.com/xFaraday/CyberNewCareers/main/honeypot/config.toml -o config.toml
wget https://raw.githubusercontent.com/xFaraday/CyberNewCareers/main/honeypot/docker-compose.yml || curl https://raw.githubusercontent.com/xFaraday/CyberNewCareers/main/honeypot/docker-compose.yml -o docker-compose.yml

#elastic search startup
mkdir -p ./data/elasticsearch/data && sudo chown -R 1000:1000 ./data/elasticsearch

#start up containers
docker-compose -f docker-compose.yml up -d
