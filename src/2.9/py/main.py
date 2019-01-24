class Mot():
    def __init__(self,mot):
        self.mot = mot
        motOpti = ""
        mal = 0
        for k in mot:
            if not k in motOpti:
                motOpti += k
            else:
                mal -= 1
        self.motSimple = motOpti
        self.malus = mal 

    
    def poids(self,tableauUtilise):
        poid = self.malus
        nouvellesLettres = []
        for k in self.motSimple:
            if k in tableauUtilise:
                poid -= 1
            else:
                poid += 2
                nouvellesLettres.append(k)
        return poid,nouvellesLettres


def best(retour,mot,lettresVu,mots):
    if len(mot.mot) < len(retour.mot):
        return mot,mot.poids(lettresVu)[1]
    elif len(mot.mot) > len(retour.mot):
        return retour,retour.poids(lettresVu)[1]
    pointRetour = 0
    pointMot = 0
    for k in retour.motSimple:
        for i in mot.motSimple:
            if k not in i and k not in lettresVu:
                for m in mots:
                    if k in m.motSimple:
                        pointRetour=1
    for k in mot.motSimple:
        for i in retour.motSimple:
            if k not in i and k not in lettresVu:
                for m in mots:
                    if k in m.motSimple:
                        pointRetour=1
    if pointRetour < pointMot:
        return retour,retour.poids(lettresVu)[1]
    else:
        return mot,mot.poids(lettresVu)[1]

def maxVal(lettresVu,mots):
    Max = None
    newLettres = []
    retour = []
    for mot in mots:
        temp = mot.poids(lettresVu)
        if Max == None or temp[0] > Max:
            Max = temp[0]
            retour = mot
            newLettres = temp[1]
        elif temp[0] == Max:
            retour,newLettres = best(retour,mot,lettresVu,mots)
    mots.remove(retour)
    return newLettres,retour

def compteLettres(mots):
    somme = 0
    for mot in mots:
        for lettre in mot:
            if lettre != " ":
                somme+=1
    return somme

def afficherMots(mots):
    sousmot = []
    for k in mots:
        sousmot.append(k.mot)
    sousmot.sort()
    sortie = ""
    for k in sousmot:
        sortie+=k+" "
    print(compteLettres(sortie[:-1]),sortie)

def inutile(mot,lettresVu):
    for k in mot.mot:
        if k not in lettresVu:
            return False
    return True

lettreMax = ord(input()) - ord("a")
longueurMax = int(input())
nbMots = int(input())
mots = []
for k in range(nbMots):
    mots.append(Mot(input()))

lettresVu = []
motsFinaux = []
#verif impossible
for k in mots:
    lettresVu += (k.poids(lettresVu))[1]

if len(lettresVu) < lettreMax + 1:
    print(0)
else:
    lettresVu = []
    while len(lettresVu) < lettreMax + 1:
        val = maxVal(lettresVu,mots)
        lettresVu += val[0]
        motsFinaux.append(val[1])
        for k in mots:
            if inutile(k,lettresVu):
                mots.remove(k)
    afficherMots(motsFinaux)


