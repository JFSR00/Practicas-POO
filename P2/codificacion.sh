#!/bin/bash
for fileName in *pp; do
    file "$fileName" --mime-encoding  # --mime-encoding da específicamente lo que buscamos
done
