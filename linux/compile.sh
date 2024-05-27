#!/bin/bash

# setup
script_path=$(realpath "${0}")
script_dir=$(dirname "${script_path}")
. ${script_dir}/set_env.sh


# Act
command="cmake --build --preset=linux_${build_type}"

print_cyan "${command}"
${command}
