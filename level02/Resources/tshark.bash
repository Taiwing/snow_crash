for payload in $(docker run \
	--network host \
	-v $PWD/level02.pcap:/data/level02.pcap \
	toendeavour/tshark \
	-r /data/level02.pcap -T fields -e tcp.payload); do
	printf $payload | xxd -r -p
	printf "\n"
done
