#! /bin/sh
#
# (c) 2016 Codeon GmbH, coded by Nat!
#
#
__run()
{
   local i

   i="$1"

   [ -f call.o ] && rm call.o
   make -s

   local textsize

   textsize="`size call.o | tail -1 | awk '{print $1}'`"

   echo "`basename "$i" .txt`(${textsize}):" \
   `( time -p ./test 1000 ) 2>&1 | grep user | awk '{ print $2 }'` \
   `( time -p ./test 1000 ) 2>&1 | grep user | awk '{ print $2 }'` \
   `( time -p ./test 1000 ) 2>&1 | grep user | awk '{ print $2 }'`

}


_run()
{
   local i

   i="$1"
   cat <<EOF > call.s
        .globl _call    # $i
_call:
EOF
   sed '1d' < "$i" >> call.s

   __run "$i"
}


run()
{
   local i

   i="$1"

   if [ "`basename "$i" .s`" = "`basename $i`" ]
   then
      _run "$i"
   else
      cp "$i" call.s
      __run "$i"
   fi
}


main()
{
   local i

   if [ $# -eq 0 ]
   then
      for i in ../results/clang-*.txt ../results/gcc-*.txt ../results/icc-*.txt nat-*.s
      do
         run "$i"
      done
   else
      for i in "$@"
      do
         run "$i"
      done
   fi
}

main "$@"

