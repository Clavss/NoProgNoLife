#include <stdio.h>
#include <stdlib.h>


int Estsuprimmer(int ***resultcpy,int ibu,int nbcdt);
int leader (int ***result,int nbb,int nbcdt,int *vote){
   int  max =-1;int  indcad=-2;  int temp;  int  somme=0;  int maj=0;
  for (int i=0;i<nbb;i++){
    if(Estsuprimmer(result,i,nbcdt)!=0){
      maj+=vote[i];
    } }
  if (maj==0){
    return -1;
  }
  maj=maj/2;

  for(int i=0;i<nbcdt;i++){
    somme=0;
    for(int w=0;w<nbcdt;w++){
       temp=0;
    for(int j=0;j<nbb;j++){
       if(Estsuprimmer(result,j,nbcdt)!=0){
      temp+=result[j][i][w];
	}
       }
    if (temp>maj){
      somme++;
    }
    }
    if (somme > max){
      max=somme;
      indcad=i;
    }
    else  if (somme == max && indcad==0 ){
      indcad=i;
    }
  }
  return indcad;
}


int minimum (int a, int b ){
  if (a== -1){
    return b;
  } if (b == -1){
    return a;}
  if (a > b){
    return b;
  }
  return a;
}

void suprimer (int ***resultcpy,int ibu, int nbcdt){
  for(int i=0;i<nbcdt;i++){
    for (int j=0;j<nbcdt;j++){
    resultcpy[ibu][i][j]=-1;
  }
  }
}

void restaurer (int ***result ,int ***resultcpy,int ibu, int nbcdt){
  for (int i=0;i<nbcdt;i++){
    for(int j=0;j<nbcdt;j++){
    resultcpy[ibu][i][j]=result[ibu][i][j];
  }
}
}

int Estsuprimmer(int ***resultcpy,int ibu,int nbcdt){
  int supr=0;
  for (int i=0;i<nbcdt;i++){
    for(int j=0;j<nbcdt;j++){
    if (resultcpy[ibu][i][j]!=-1)
      return 1;
  }
  }
  return supr;
}










// 1 si vide
int  Estvide(int ***result,int nbb,int nbcdt){
  int vide=1;
  for(int i=0;i<nbb;i++){
    for(int j=0;j<nbcdt;j++){
      for (int y=0;y<nbcdt;y++){
      if (result[i][j][y]!=-1)
	return 0;
    }
    }
  }
  return vide;

}

int minus(int **result,int nbb,int nbcdt){
  int ptt=0;
  int minind=0;
  int mine=0;
  int cpt=0;
  for (int i=0;i<nbb;i++){
    ptt=result[i][0];
    for(int j =1;j<nbcdt;j++){
      ptt-=result[i][j];
    }
    if (cpt == 0){
      cpt++;
      minind=0;
      mine=ptt;
	}
    if (ptt < mine){
      mine=ptt;
      minind=i;
  }
  }
    return minind;
}

int moinsmajorite(int ***result,int nbb,int nbcdt,int *nbvt,int leader){
  int nbind=-1;
  int min=1;;
  int somme=0;
  for (int i=0;i<nbb;i++){
    somme=0;
      if(Estsuprimmer(result,i,nbcdt)!=0)
      somme=result[i][0][leader]-result[i][leader][0];
    if ( min  > somme){
      min=somme;
      nbind=i;
    }
    if (min == somme && nbvt[nbind] < nbvt[i]){
      nbind=i;
    }
  }

return nbind;

}


void Choisir_difference(int ***result,int nbb,int nbcdt){





}


int main (void){
  int nbcdt=0;
  int nbb=0;
  int moin=0;
  int cpt=0;
  scanf(" %d",&nbb);
  scanf(" %d",&nbcdt);
  int *nbvt=malloc (sizeof(int)*(nbb));
  int ***result=(int ***) malloc(sizeof(int **)*nbb);
  for (int i=0;i<nbb;i++){
     result[i]=(int **)malloc (sizeof(int *)*(nbcdt));
   for(int j=0;j<nbcdt;j++){
result[i][j]=malloc (sizeof(int)*(nbcdt));
   }
}


   int *vote = malloc (sizeof(int)*(nbcdt));
   for (int w=0;w<nbb;w++){
  for(int i=0;i<nbcdt;i++){
    for(int j=0;j<nbcdt;j++){//init
      result[w][i][j]=0;
    }
    }
   }


  for (int w=0;w<nbb;w++){
     scanf(" %d",&nbvt[w]);
   for(int i=0;i<nbvt[w];i++){
    for(int j=0;j<nbcdt;j++){
      scanf("%d",&vote[j]);
      }
    for (int j=0;j<nbcdt;j++){
        for(int x=j+1;x<nbcdt;x++){
	result[w][vote[j]][vote[x]]++;
      }
    }
   }
  }

  while (Estvide(result,nbb,nbcdt)== 0 && leader (result,nbb,nbcdt,nbvt)!=0 && leader (result,nbb,nbcdt,nbvt)!=-1){
    moin=moinsmajorite(result,nbb,nbcdt,nbvt,leader (result,nbb,nbcdt,nbvt));
  suprimer (result,moin,nbcdt);
  cpt++;
  }

 if(  Estvide(result,nbb,nbcdt)== 1 || leader (result,nbb,nbcdt,nbvt)== -1){
   printf("-1\n");;
 }
 else {
 printf("%d\n",cpt);
 }








  return 0;
}
