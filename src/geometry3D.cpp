#include "geometry3D.hpp"
#include "definitions.hpp"



geometry3D::geometry3D(VecF IlimI,VecF IlimF,VecI InElem){
  
  // PML OR HALO NODES
  HALO.x = PML.x;
  HALO.y = PML.y;
  HALO.z = PML.z;

  // NUMBER ELEMENTS
  ne.x = InElem.x ;
  ne.y = InElem.y ;
  ne.z = InElem.z ;

  // NUMBER OF NODES ORIGINAL DOMAIN
  nod.x = InElem.x + 1;
  nod.y = InElem.y + 1;
  nod.z = InElem.z + 1;  

  // INITIAL LIMIT DOMAIN 
  limI.x = IlimI.x;
  limI.y = IlimI.y;
  limI.z = IlimI.z;

  // END LIMIT DOMAIN
  limF.x = IlimF.x;
  limF.y = IlimF.y;
  limF.z = IlimF.z;

  // DELTA DISCRETIZATION
  Delta.x = (limF.x - limI.x) / Dfloat(ne.x);
  Delta.y = (limF.y - limI.y) / Dfloat(ne.y);
  Delta.z = (limF.z - limI.z) / Dfloat(ne.z);

  // NUMBER ELEMENTS WITH PML OR HALO
  NE.x = InElem.x + 2 * HALO.x;
  NE.y = InElem.y + 2 * HALO.y;
  NE.z = InElem.z + HALO.z;

  // NUMBER OF NODES WITH PML OR HALO
  NOD.x = NE.x + 1;
  NOD.y = NE.y + 1;
  NOD.z = NE.z + 1;  
  
}



geometry3D::geometry3D(VecF IlimI,VecF IlimF,VecI InElem, VecI IHALO){
  

  // PML OR HALO NODES
  HALO.x = IHALO.x;
  HALO.y = IHALO.y;
  HALO.z = IHALO.z;

  // NUMBER ELEMENTS
  ne.x = InElem.x;
  ne.y = InElem.y;
  ne.z = InElem.z;

  // NUMBER OF NODES ORIGINAL DOMAIN
  nod.x = InElem.x + 1;
  nod.y = InElem.y + 1;
  nod.z = InElem.z + 1;  

  // INITIAL LIMIT DOMAIN 
  limI.x = IlimI.x;
  limI.y = IlimI.y;
  limI.z = IlimI.z;

  // END LIMIT DOMAIN
  limF.x = IlimF.x;
  limF.y = IlimF.y;
  limF.z = IlimF.z;

  // DELTA DISCRETIZATION
  Delta.x = (limF.x - limI.x) / Dfloat(ne.x);
  Delta.y = (limF.y - limI.y) / Dfloat(ne.y);
  Delta.z = (limF.z - limI.z) / Dfloat(ne.z);

// NUMBER ELEMENTS WITH PML OR HALO
  NE.x = InElem.x + 2 * HALO.x;
  NE.y = InElem.y + 2 * HALO.y;
  NE.z = InElem.z + 2 * HALO.z;

  // NUMBER OF NODES WITH PML OR HALO
  NOD.x = NE.x + 1;
  NOD.y = NE.y + 1;
  NOD.z = NE.z + 1;  

}






// COORDINATE ORIGINAL DOMAIN

Dfloat geometry3D::CoorX(int i){
  Dfloat coord;

  if (i < nod.x){

    coord = limI.x + (Dfloat) i * Dx();

  return coord;

  } else {
    
    std::cout<<"Out of Dimension_X"<<std::endl;

  }
}


Dfloat geometry3D::CoorY(int i){
  Dfloat coord;

  if (i < nod.y){
    
    coord = limI.y + (Dfloat) i * Dy();

  return coord;

  }else{
    
    std::cout<<"Out of Dimension_Y"<<std::endl;
    
  }   
}


Dfloat geometry3D::CoorZ(int i){
  Dfloat coord;

  if (i < nod.z) {
    coord = limI.z + (Dfloat) i * Dz();
    return coord;
    
  }else{

    std::cout<<"Out of Dimension_Z"<<std::endl;

  }
}



Dfloat geometry3D::CoorXHalf(int i){
  Dfloat coord;

  if (i < nod.x-1){

    coord = limI.x + (Dx() / 2.0) + (Dfloat) i * Dx();

  return coord;

  } else {
    
    std::cout<<"Out of Dimension_X_half"<<std::endl;

  }  
}


Dfloat geometry3D::CoorYHalf(int i){
  Dfloat coord;

  if (i < nod.y-1){
    
    coord = limI.y + (Dy() / 2.0) + (Dfloat) i * Dy();

  return coord;

  }else{
    
    std::cout<<"Out of Dimension_Y_half"<<std::endl;
    
  }    
}


Dfloat geometry3D::CoorZHalf(int i){
  Dfloat coord;

  if (i < nod.z-1) {
    coord = limI.z + (Dz() / 2.0) + (Dfloat) i * Dz();
    return coord;
    
  }else{

    std::cout<<"Out of Dimension_Z_half"<<std::endl;
  }
}


// THICKNES PML 

VecF geometry3D::thickness_PML(){

  VecF thickness;

  thickness.x =  (Dfloat) PML.x * Delta.x;
  thickness.y =  (Dfloat) PML.y * Delta.y;
  thickness.z =  (Dfloat) PML.z * Delta.z;

  return thickness;
  
}

// THICKNES HALO

VecF geometry3D::thickness_HALO(){

  VecF thickness;

  thickness.x =  (Dfloat) HALO.x * Delta.x;
  thickness.y =  (Dfloat) HALO.y * Delta.y;
  thickness.z =  (Dfloat) HALO.z * Delta.z;

  return thickness;
  
}

/*
void geometry3D::FindNode(VecF coord, VecI ind){

  Dfloat dist1 = 1.0e30;
  Dfloat dist2;
  
   for (int iz=0;iz<nod.z;iz++){
     for (int iy=0;iy<nod.y;iy++){
       for (int ix=0;ix<nod.x;ix++){
	 
	 dist2 = sqrt( pow( coord.x - CoorDx(ix),2.0) +	\
		       pow( coord.y - CoorDy(iy),2.0) +	\
		       pow( coord.z - CoorDz(iz),2.0) );
	 
	 if (dist2 < dist1){
	   dist1 = dist2;
	   ind.x = ix + PML.x;
	   ind.y = iy + PML.y;
	   ind.z = (nod.z - 1) - (iz + PML.z);
	 }
		       	 
       }
     }
   }

}

*/



