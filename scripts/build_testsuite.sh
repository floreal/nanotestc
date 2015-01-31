#!/bin/sh

# ---------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <floreal@nimukaito.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and you
# think this stuff is worth it, you can buy me a beer in return.
# Floréal Toumikian
# ---------------------------------------------------------------------------

parse_file()
{
  CAPTURE=""
  DESC=""
  FUNCTION=""
  for token in $(cat $1); do
    case $token in
      "//")
        CAPTURE=description
        DESC=""
        ;;
      "TestResult")
        CAPTURE=function
        FUNCTION=""
        ;;
      *)
        if [ "$CAPTURE" = "description" ]; then
          if [ -z "$DESC" ]; then
            DESC="$token"
          else
            DESC="$DESC $token"
          fi
        elif [ "$CAPTURE" = "function" ]; then
          FUNCTION=$(echo $token | sed "s/[\(\);]//g")
          echo "  test_suite_add(suite, &$FUNCTION, \"$DESC\");"
          CAPTURE=""
        fi
        ;;
    esac
  done
}

add_tests()
{
  for file in $@; do
    parse_file $file
  done
}

cd $(dirname $0)/../test/

FILES=$(find . -name test*.h)

echo "#include <tap.h>"

for header in $FILES ; do \
   echo "#include \"$header\""
done ; \

cat <<EOF

int main() {
  TestSuite* suite = test_suite_new();

EOF

add_tests $FILES

cat <<EOF

  test_suite_run(suite);

  test_suite_delete(suite);

  return 0;
}
EOF
