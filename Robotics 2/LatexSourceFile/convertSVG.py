import os
from reportlab.graphics import renderPDF
from svglib.svglib import svg2rlg
from pathlib import Path

def converti_svg(input_file, output_file):
    if not os.path.exists(input_file):
        print(f"File non trovato: {input_file}")
        return

    print(f"Converto {input_file} in {output_file}...")
    try:
        drawing = svg2rlg(input_file)
        renderPDF.drawToFile(drawing, output_file)
        print("Fatto!")
    except Exception as e:
        print(f"Errore: {e}")


if __name__ == "__main__":
    for elemento in Path("images").iterdir():
        if elemento.is_file():
            nome=elemento.stem
            tipo=elemento.suffix
            file_pdf = nome+".pdf"
            if tipo==".svg":
                if not Path("images/"+file_pdf).exists():
                    converti_svg(elemento, "images/"+file_pdf)