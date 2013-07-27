DIM FSO, ARGV, DIR
SET FSO = wscript.CreateObject("Scripting.FileSystemObject")
SET ARGV = wscript.arguments

SRC = "c:\"
OPT = FALSE
IF NOT ARGV.count = 0 THEN
'verification de l'option "-t"
   FOR i=0 TO ARGV.count-1 STEP 1
       IF ARGV(i) = "-t" THEN
           OPT = TRUE
       ELSE
           SRC = ARGV(i)
       END IF
   NEXT
END IF



wscript.echo "On liste " & SRC

'construction de la liste des fichiers
SET DIR = FSO.getfolder(src)

FOR EACH FIC IN DIR.files
    IF OPT THEN
        wscript.echo FIC.path & " " & FIC.size
    ELSE
        wscript.echo FIC.path
    END IF
NEXT