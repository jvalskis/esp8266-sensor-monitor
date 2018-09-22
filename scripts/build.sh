#!/usr/bin/env bash

# Works only when run from scripts directory
project="$(dirname $(readlink -f "$0"))/.."
backup_properties=Properties.h.BACKUP
project_properties=${project}/src/Properties.h
new_properties=${2}

if [[ ! -e "${new_properties}" ]]
then
	echo "Error: no properties file provided"
	exit 1
fi

cp "${project_properties}" ./"${backup_properties}" && echo "Backed up ${project_properties} to ${backup_properties}" || { echo "Failed to copy ${new_properties} over ${project_properties}"; exit 1; }
cp "${new_properties}" "${project_properties}" && echo "Copied ${new_properties} over ${project_properties}" || { echo "Failed to copy ${new_properties} over ${project_properties}"; exit 1; }
docker run -v ${project}:/project --device=/dev/ttyS1:/dev/ttyS0 esp8266build make ${1}
cp "${backup_properties}" "${project_properties}" && echo "Restored ${project_properties} with ${backup_properties}" || { echo "Failed to restore ${project_properties} with ${backup_properties}"; exit 1; }