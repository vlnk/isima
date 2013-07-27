DIM FSO, DEST, ARGV
SET FSO = wscript.CreateObject("Scripting.FileSystemObject")
SET ARGV = wscript.arguments

SRC = "C:\"
OPT = FALSE
IF NOT ARGV.count = 2 THEN
   wscript.echo "USAGE : cp.vbs <SOURCE> <DESTINATION>"
ELSE
    OPT = TRUE
    SRC = ARGV(0)
    DEST = ARGV(1)
END IF

IF OPT THEN
   wscript.echo "On copie le contenu de " & SRC & " dans le dossier " & DEST

   'construction de la liste des fichiers
   SET DIR = FSO.getfolder(src)

   FOR EACH FIC IN DIR.files
       FIC.Copy DEST
   NEXT
END IF
