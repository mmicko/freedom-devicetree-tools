set -ex

tempdir="$(mktemp -d)"
trap "rm -rf $tempdir" EXIT

cd "$tempdir"

dtc $SOURCE_DIR/tests/hifive1.dts -o hifive1.dtb -O dtb
$WORK_DIR/freedom-zephyrdtsfixup-generator -d hifive1.dtb -o hifive1-dts.fixup

cat hifive1-dts.fixup

