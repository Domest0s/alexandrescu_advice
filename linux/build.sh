#!/bin/bash

# setup
script_path=$(realpath "${0}")
script_dir=$(dirname "${script_path}")
. ${script_dir}/set_env.sh


# Act
print_cyan "cmake --build ${build_dir}"

cmake --build ${build_dir}