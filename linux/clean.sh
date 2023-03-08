#!/bin/bash

# setup
script_path=$(realpath "$0")
script_dir=$(dirname "$script_path")
. $script_dir/set_env.sh


# Act
print_cyan "rm -rf ${build_dir}"
rm -rf ${build_dir}
