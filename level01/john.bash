if [ -z $1 ]; then
	echo "usage: $0 password_file"
	exit 1
fi

if ! docker image ls | grep jtr; then
	docker build -t jtr .
fi
docker run -it -v $PWD/$1:/crackme.txt jtr /crackme.txt
