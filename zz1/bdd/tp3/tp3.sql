/*Q1*/
CREATE TABLE Fournisseur
    (NumFour number(2) CONSTRAINT PK_NumFour PRIMARY KEY,
     NomFour varchar2(30) CONSTRAINT C_NomFour NOT NULL);

CREATE TABLE Article
    (NumArt number(2) CONSTRAINT PK_NumArt PRIMARY KEY,
     Libelle varchar2(30),
     NumFour number(2),
     CONSTRAINT FK_NumFourArt FOREIGN KEY(NumFour) REFERENCES Fournisseur);

CREATE TABLE Client
    (NumClt number(2) CONSTRAINT PK_NumClt PRIMARY KEY,
     NomClt varchar2(30) CONSTRAINT C_NomClt NOT NULL,
     Adresse varchar2(100),
     NumTel varchar2(20));

CREATE TABLE Commande
    (NumArt number(2),
     CONSTRAINT FK_NumArt FOREIGN KEY(NumArt) REFERENCES Article,
     NumClt number(2),
     CONSTRAINT FK_NumClt FOREIGN KEY(NumClt) REFERENCES Client,
     Quantite number(3) CONSTRAINT C_Quantite CHECK (Quantite > 0) NOT NULL);

/*Q2*/
INSERT INTO Fournisseur VALUES (1,'Magouille');
INSERT INTO Fournisseur VALUES (2,'Rigolo');
INSERT INTO Fournisseur VALUES (3,'Sympa');
INSERT INTO Fournisseur VALUES (4,'Chouette');

INSERT INTO Article VALUES (1,'Pomme',3);
INSERT INTO Article VALUES (2,'Poire',3);
INSERT INTO Article VALUES (3,'Fraise',1);
INSERT INTO Article VALUES (4,'Prune',2);

INSERT INTO Client VALUES (10,'Picsou','Nice',null);
INSERT INTO Client VALUES (40,'Dingo','Clermont-Ferrand','04-73-42-58-12');
INSERT INTO Client VALUES (15,'Picsou','Nantes','02-40-12-15-65');
INSERT INTO Client VALUES (55,'Mickey','Brest','02-51-24-52-87');

INSERT INTO Commande VALUES (1,15,10);
INSERT INTO Commande VALUES (3,40,35);
INSERT INTO Commande VALUES (2,40,42);
INSERT INTO Commande VALUES (3,15,12);
INSERT INTO Commande VALUES (2,55,80);
INSERT INTO Commande VALUES (1,10,60);

/*Q3*/
/*1)*/
INSERT INTO Article VALUES (1,'Pomme',5);
/*
INSERT INTO Article VALUES (1,'Pomme',5)
*
ERROR at line 1:
ORA-00001: unique constraint (LAURENTV.PK_NUMART) violated
Une clé primaire est unique !
/*

/*2)*/
INSERT INTO Commande VALUES (1,55,0);
/*
INSERT INTO Commande VALUES (1,55,0)
*
ERROR at line 1:
ORA-02290: check constraint (LAURENTV.C_QUANTITE) violated
On viole la contrainte Quantite > 0
*/

/*3)*/
INSERT INTO Commande VALUES (1,55,NULL);
/*
INSERT INTO Commande VALUES (1,55,NULL)
                                  *
ERROR at line 1:
ORA-01400: cannot insert NULL into ("LAURENTV"."COMMANDE"."QUANTITE")
On viole la contrainte Quantite NOT NULL
*/

/*4)*/
DELETE FROM Client
WHERE NumClt=15;
/*
WHERE NumClt=15;  2  
DELETE FROM Client
*
ERROR at line 1:
ORA-02292: integrity constraint (LAURENTV.FK_NUMCLT) violated - child record
found
La contrainte d'inclusion avec la table Commande a été outrepassée
*/

/*5)*/
ALTER TABLE Commande DROP CONSTRAINT FK_NumClt;
ALTER TABLE Commande ADD CONSTRAINT FK_NumClt FOREIGN KEY(NumClt) REFERENCES Client ON DELETE CASCADE;

DELETE FROM Client
WHERE NumClt=15;
/*ça marche !*/

/*6)*/
ALTER TABLE Fournisseur ADD NumTel varchar2(20);
UPDATE Fournisseur SET NumTel='02-23-15-98-87' WHERE NumFour=3;
/*ça marche bien aussi !*/

/*7)*/
UPDATE Fournisseur SET NomFour=LPAD(NomFour,6);
ALTER TABLE Fournisseur MODIFY NomFour varchar2(6);

/*8)*/
CREATE VIEW Livraison AS
    SELECT NomClt, Libelle, Quantite
    FROM Client, Article, Commande;

SELECT * FROM Livraison;
/* Affichage :
NOMCLT                         LIBELLE                          QUANTITE
------------------------------ ------------------------------ ----------
Picsou                         Pomme                                  35
Picsou                         Poire                                  35
Picsou                         Fraise                                 35
Picsou                         Prune                                  35
Dingo                          Pomme                                  35
Dingo                          Poire                                  35
Dingo                          Fraise                                 35
Dingo                          Prune                                  35
Mickey                         Pomme                                  35
Mickey                         Poire                                  35
Mickey                         Fraise                                 35
Mickey                         Prune                                  35
Picsou                         Pomme                                  42
Picsou                         Poire                                  42
Picsou                         Fraise                                 42
Picsou                         Prune                                  42
Dingo                          Pomme                                  42
Dingo                          Poire                                  42
Dingo                          Fraise                                 42
Dingo                          Prune                                  42
Mickey                         Pomme                                  42
Mickey                         Poire                                  42
Mickey                         Fraise                                 42
Mickey                         Prune                                  42
Picsou                         Pomme                                  80
Picsou                         Poire                                  80
Picsou                         Fraise                                 80
Picsou                         Prune                                  80
Dingo                          Pomme                                  80
Dingo                          Poire                                  80
Dingo                          Fraise                                 80
Dingo                          Prune                                  80
Mickey                         Pomme                                  80
Mickey                         Poire                                  80
Mickey                         Fraise                                 80
Mickey                         Prune                                  80
/*

/*Q4*/
DROP VIEW Livraison;
DROP TABLE Commande;
DROP TABLE Article;
DROP TABLE Client;
DROP TABLE Fournisseur;

/*THE END*/