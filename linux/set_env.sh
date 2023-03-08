#!/bin/bash

script_path=$(realpath "$0")
script_dir=$(dirname "$script_path")
root_dir=$(dirname "$script_dir")

source_dir=${root_dir}
build_dir=${root_dir}/build
install_dir=${root_dir}/install


# echo source_dir=${source_dir}
# echo build_dir=${build_dir}
# echo install_dir=${install_dir}

# colored output
color_red="\033[31m"
color_cyan="\033[36m"
color_default="\033[39m"

function print_cyan()
{
  printf "${color_cyan}> $1\n${color_default}"
}