set -x
modprobe -r debugfs
modprobe debugfs
FOLDER=/sys/kernel/debug/fortytwo

ls -l $FOLDER

cat $FOLDER/id
cat $FOLDER/jiffies
sleep .1;
cat $FOLDER/jiffies

echo "coucou" > $FOLDER/id
echo -n "jcamhi" > $FOLDER/id
cat $FOLDER/foo
echo "Example" > $FOLDER/foo
cat $FOLDER/foo
