def modif(grille,taille,devientVivant,resteVivant):
    newGrille = list(grille)
    for k in range(0,taille):
        newGrille[k] = ""
    for i in range(0,taille):
        for j in range(0,taille):
            nb = nbVoisins(grille,taille,i,j)
            if (grille[i][j] == "0" and nb in devientVivant) or (grille[i][j] == "1" and nb in resteVivant):
                newGrille[i]+= "1"
            else:
                newGrille[i]+= "0"

    return newGrille

def nbVoisins(grille,taille,i,j):
    compte = 0
    for a in range(i-1,i+2):
        for b in range(j-1,j+2):
            if (a != i or b != j) and a < taille and b < taille and a >= 0 and b >= 0 and grille[a][b] == '1':
                compte+=1

    return compte

def afficher(grille):
    for k in grille:
        sortie = ""
        for a in k:
            sortie+=a
        print(sortie)



mode = int(input())
N = int(input())
taille = int(input())
grille = []
for k in range(0,int(taille)):
    grille.append(input())

devientVivant = [0]
resteVivant = [0]
if(mode == 0):
    devientVivant = [3]
    resteVivant = [2,3]
elif(mode == 1):
    devientVivant = [3,6,7,8]
    resteVivant = [3,4,6,7,8]
elif(mode == 2):
    devientVivant = [3,6]
    resteVivant = [2,3]

for k in range(0,N):
    grille = modif(grille,taille,devientVivant,resteVivant)

afficher(grille)
