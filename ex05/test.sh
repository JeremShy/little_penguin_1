set -x

make re
make test
cat /dev/fortytwo
echo "test" > /dev/fortytwo
echo -n "jcamhi" > /dev/fortytwo
