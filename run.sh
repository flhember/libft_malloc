#!/bin/sh
export LD_LIBRARY_PATH=`pwd`/lib
export LD_PRELOAD=`pwd`/libft_malloc.so
$@
