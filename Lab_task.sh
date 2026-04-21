#!/usr/bin/bash

# Default values
NAME="${1:-SANJIDUR RAHMAN}"
ROLL="${2:-2307006}"

# Run the generate script with name and roll
python generate_pdf.py --name "$NAME" --roll "$ROLL"

# Open the PDF
firefox notebook.pdf
