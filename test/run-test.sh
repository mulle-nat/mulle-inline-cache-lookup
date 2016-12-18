#! /bin/sh
#
# (c) 2016 Codeon GmbH, coded by Nat!
#
#

___run()
{
   ( time -p ./test $1 $2 ) 2>&1 | grep user | awk '{ print $2 }' | tr '.' ','
}


__run()
{
   local i

   i="$1"

   [ -f call.o ] && rm call.o
   make -s

   local textsize

   textsize="`size call.o | tail -1 | awk '{print $1}'`"

   local hit1
   local hit2
   local hit3

   hit1="`___run hit 500`"
   hit2="`___run hit 500`"
   hit3="`___run hit 500`"

   local miss1
   local miss2
   local miss3

   miss1="`___run miss 500`"
   miss2="`___run miss 500`"
   miss3="`___run miss 500`"

   local name

   name="`basename "$i" .txt`"

   echo "${name};${textsize};${hit1};${hit2};${hit3};${miss1};${miss2};${miss3}"
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

