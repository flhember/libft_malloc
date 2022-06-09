#!/bin/sh
export LD_LIBRARY_PATH=`pwd`/lib
export LD_PRELOAD=`pwd`/lib/libft_malloc.so
$@
