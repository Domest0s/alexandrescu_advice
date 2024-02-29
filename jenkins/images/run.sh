#!/bin/bash

docker run \
  --name agent-wip \
  --rm \
  work_agent:WIP \
  git --version
  # ninja --version
  # cmake --version

