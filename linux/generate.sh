#!/bin/bash

# setup
script_path=$(realpath "${0}")
script_dir=$(dirname "${script_path}")
. ${script_dir}/set_env.sh


# Act
# print_cyan "cmake \\\\\n \
#   -G Ninja \\\\\n \
#   -S ${source_dir} \\\\\n \
#   -B ${build_dir}"

cd ${root_dir}


command="cmake --preset=linux_${build_type}"

print_cyan "${command}"
${command}
