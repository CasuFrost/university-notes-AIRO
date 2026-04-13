from pathlib import Path


percorso_cartella = Path("")

# Itera su tutto il contenuto
for elemento in percorso_cartella.iterdir():
    if elemento.is_file():
        n = elemento.name
        if len(n)>5:
            arr=n.split("_")
            year = arr[2].split(".")[1]
            formato = arr[2].split(".")[0]
            day = arr[0]
            month = arr[1]
            if month=="aprile":
                month='04'
            else:
                month='03'
            new_name=year+"_"+month+"_"+day+"."+formato
            print(new_name)
            #elemento.rename(year+"_"+month+"_"+day+"."+formato)