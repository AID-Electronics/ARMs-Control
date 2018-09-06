#ifndef Trigonometria_H
#define Trigonometria_H

typedef struct Vector3D{
  double x;
  double y;
  double z;
};

Vector3D V3D_media(Vector3D v[], int tot){
  Vector3D aux;
  aux.x = 0;
  aux.y = 0;
  aux.z = 0;
  
  for(int i=0; i < tot; i++){
    aux.x += v[i].x;
    aux.y += v[i].y;
    aux.z += v[i].z;
  }

  aux.x = aux.x / tot;
  aux.y = aux.y / tot;
  aux.z = aux.z / tot;

  return aux;
}

#endif
