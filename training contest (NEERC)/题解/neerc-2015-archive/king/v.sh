#!/bin/bash

cd visualized
rm *.pdf
dot -O -Tpdf *.dot
pdfunite *.pdf ../tests.pdf
rm *.pdf
