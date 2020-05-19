#!/bin/bash
mkdir -p utf8-versions
for fileName in *pp; do
    fileEncoding=$(file "$fileName" --mime-encoding -b)  # -b omite el nombre del fichero
    iconv -f "$fileEncoding" -t utf-8//TRANSLIT "$fileName" -o utf8-versions/"$fileName";
done
