# mulle-inline-cache-lookup

A test project to be used in conjunction with
[Godbolt's Compiler Explorer](https://godbolt.org). Possibly the greatest
project name in existence.




## ABI

The [AMD Call convention](//refspecs.linuxbase.org/elf/x86-64-abi-0.99.pdf)
is used by Unices and OS X it lists the available registers for function
call parameters. I've annotated them as they are used by *mulle-objc*:


## Available registers

* %rdi  # self
* %rsi  # _cmd
* %rdx  # _param
* %rcx  # free
* %r8   # free
* %r9   # free
