if ! docker image ls | grep jtr; then
	docker build -t jtr .
fi
docker run -it -v $PWD/$1:/crackme.txt jtr /crackme.txt
