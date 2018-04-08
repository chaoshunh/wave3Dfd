#include "kernels.hpp"

KERNEL::KERNEL(SDM *inFWD,SDM *inADJ){
  FWD = inFWD;
  ADJ = inADJ;


  KRHO = new Dfloat [FWD->SDMGeom->HALO_Node()];
  KMU = new Dfloat [FWD->SDMGeom->HALO_Node()];
  KLAMBDA = new Dfloat [FWD->SDMGeom->HALO_Node()];
  KDEN = new Dfloat [FWD->SDMGeom->HALO_Node()];
  KVP = new Dfloat [FWD->SDMGeom->HALO_Node()];
  KVS = new Dfloat [FWD->SDMGeom->HALO_Node()];
 

  ux_dx = new Dfloat [FWD->SDMGeom->HALO_Node()];
  ux_dy = new Dfloat [FWD->SDMGeom->HALO_Node()];
  ux_dz = new Dfloat [FWD->SDMGeom->HALO_Node()];
  uy_dx = new Dfloat [FWD->SDMGeom->HALO_Node()];
  uy_dy = new Dfloat [FWD->SDMGeom->HALO_Node()];
  uy_dz = new Dfloat [FWD->SDMGeom->HALO_Node()];
  uz_dx = new Dfloat [FWD->SDMGeom->HALO_Node()];
  uz_dy = new Dfloat [FWD->SDMGeom->HALO_Node()];
  uz_dz = new Dfloat [FWD->SDMGeom->HALO_Node()];

  ux_dx_ad = new Dfloat [ADJ->SDMGeom->HALO_Node()];
  ux_dy_ad = new Dfloat [ADJ->SDMGeom->HALO_Node()];
  ux_dz_ad = new Dfloat [ADJ->SDMGeom->HALO_Node()];
  uy_dx_ad = new Dfloat [ADJ->SDMGeom->HALO_Node()];
  uy_dy_ad = new Dfloat [ADJ->SDMGeom->HALO_Node()];
  uy_dz_ad = new Dfloat [ADJ->SDMGeom->HALO_Node()];
  uz_dx_ad = new Dfloat [ADJ->SDMGeom->HALO_Node()];
  uz_dy_ad = new Dfloat [ADJ->SDMGeom->HALO_Node()];
  uz_dz_ad = new Dfloat [ADJ->SDMGeom->HALO_Node()];

  InitVar(ZERO);

}


KERNEL::~KERNEL(){
  
  delete [] KRHO;
  delete [] KMU;
  delete [] KLAMBDA;
  delete [] KDEN;
  delete [] KVP;
  delete [] KVS;


  delete [] ux_dx;
  delete [] ux_dy;
  delete [] ux_dz;
  delete [] uy_dx;
  delete [] uy_dy;
  delete [] uy_dz;
  delete [] uz_dx;
  delete [] uz_dy;
  delete [] uz_dz;

  delete [] ux_dx_ad;
  delete [] ux_dy_ad;
  delete [] ux_dz_ad;
  delete [] uy_dx_ad;
  delete [] uy_dy_ad;
  delete [] uy_dz_ad;
  delete [] uz_dx_ad;
  delete [] uz_dy_ad;
  delete [] uz_dz_ad;

  FWD = NULL;
  ADJ = NULL;
  
}


void KERNEL::InitVar(Dfloat f){

  for (int i=0; i<FWD->SDMGeom->HALO_Node(); ++i){


    KRHO[i] = f;
    KMU[i] = f;
    KLAMBDA[i] = f;
    KDEN[i] = f;
    KVP[i] = f;
    KVS[i] = f;
  

  ux_dx[i] = f;
  ux_dy[i] = f;
  ux_dz[i] = f;
  uy_dx[i] = f;
  uy_dy[i] = f;
  uy_dz[i] = f;
  uz_dx[i] = f;
  uz_dy[i] = f;
  uz_dz[i] = f;

  ux_dx_ad[i] = f;
  ux_dy_ad[i] = f;
  ux_dz_ad[i] = f;
  uy_dx_ad[i] = f;
  uy_dy_ad[i] = f;
  uy_dz_ad[i] = f;
  uz_dx_ad[i] = f;
  uz_dy_ad[i] = f;
  uz_dz_ad[i] = f;

  }
  
}
void KERNEL::DevX(Dfloat *in_var,Dfloat *out_var){

  for (int k=KHALO;k<FWD->SNodeZ()-KHALO;k++){
    for (int j=KHALO;j<FWD->SNodeY()-KHALO;j++){
      for (int i=KHALO;i<FWD->SNodeX()-KHALO;i++){


	if ((i >= 2*KHALO) && (i < FWD->SNodeX()-2*KHALO)){
	  
	  out_var[FWD->IJK(i,j,k)] = ( (1.0 / 12.0) * in_var[FWD->IJK(i-2,j,k)] - \
				(2.0 / 3.0) * in_var[FWD->IJK(i-1,j,k)] + \
				(2.0 / 3.0) * in_var[FWD->IJK(i+1,j,k)] - \
				(1.0 / 12.0) * in_var[FWD->IJK(i+2,j,k)] ) / FWD->SDMGeom->Dx();
	}


	//RIGHT SIDE

	if (i < 2*KHALO) {

	  out_var[FWD->IJK(i,j,k)] = ( - (25.0 / 12.0) * in_var[FWD->IJK(i,j,k)] + \
				 4.0 * in_var[FWD->IJK(i+1,j,k)] - \
				 3.0 * in_var[FWD->IJK(i+2,j,k)] + \
				(4.0 / 3.0) * in_var[FWD->IJK(i+3,j,k)] -
				  (1.0 / 4.0) * in_var[FWD->IJK(i+4,j,k)] ) / FWD->SDMGeom->Dx();
	}

	// LEFT SIDE
	
	if (i >= FWD->SNodeX()-2*KHALO){

	  out_var[FWD->IJK(i,j,k)] = (  (25.0 / 12.0) * in_var[FWD->IJK(i,j,k)] - \
				 4.0 * in_var[FWD->IJK(i-1,j,k)] + \
				 3.0 * in_var[FWD->IJK(i-2,j,k)] - \
				(4.0 / 3.0) * in_var[FWD->IJK(i-3,j,k)] +
				   (1.0 / 4.0) * in_var[FWD->IJK(i-4,j,k)] ) / FWD->SDMGeom->Dx();

	}
	

	}
      }
  }

  

  
}


void KERNEL::DevY(Dfloat *in_var,Dfloat *out_var){
    for (int k=KHALO;k<FWD->SNodeZ()-KHALO;k++){
    for (int j=KHALO;j<FWD->SNodeY()-KHALO;j++){
      for (int i=KHALO;i<FWD->SNodeX()-KHALO;i++){


	if ((j >= 2*KHALO) && (j < FWD->SNodeY()-2*KHALO)){
	  
	out_var[FWD->IJK(i,j,k)] = ( (1.0 / 12.0) * in_var[FWD->IJK(i,j-2,k)] - \
				(2.0 / 3.0) * in_var[FWD->IJK(i,j-1,k)] + \
				(2.0 / 3.0) * in_var[FWD->IJK(i,j+1,k)] - \
				(1.0 / 12.0) * in_var[FWD->IJK(i,j+2,k)] ) / FWD->SDMGeom->Dy();
	}


	//RIGHT SIDE

	if (j < 2*KHALO) {

	  out_var[FWD->IJK(i,j,k)] = ( - (25.0 / 12.0) * in_var[FWD->IJK(i,j,k)] + \
				 4.0 * in_var[FWD->IJK(i,j+1,k)] - \
				 3.0 * in_var[FWD->IJK(i,j+2,k)] + \
				(4.0 / 3.0) * in_var[FWD->IJK(i,j+3,k)] -
				  (1.0 / 4.0) * in_var[FWD->IJK(i,j+4,k)] ) / FWD->SDMGeom->Dy();
	}

	// LEFT SIDE
	
	if (j >= FWD->SNodeY()-2*KHALO){

	  out_var[FWD->IJK(i,j,k)] = (  (25.0 / 12.0) * in_var[FWD->IJK(i,j,k)] - \
				 4.0 * in_var[FWD->IJK(i,j-1,k)] + \
				 3.0 * in_var[FWD->IJK(i,j-2,k)] - \
				(4.0 / 3.0) * in_var[FWD->IJK(i,j-3,k)] +
				  (1.0 / 4.0) * in_var[FWD->IJK(i,j-4,k)] ) / FWD->SDMGeom->Dy();

	}
	

	}
      }
    }

    
}



void KERNEL::DevZ(Dfloat *in_var,Dfloat *out_var){


  for (int k=KHALO;k<FWD->SNodeZ()-KHALO;k++){
    for (int j=KHALO;j<FWD->SNodeY()-KHALO;j++){
      for (int i=KHALO;i<FWD->SNodeX()-KHALO;i++){


	if ((k >= 2*KHALO) && (k < FWD->SNodeZ()-2*KHALO)){
	  
	out_var[FWD->IJK(i,j,k)] = ( (1.0 / 12.0) * in_var[FWD->IJK(i,j,k-2)] - \
				(2.0 / 3.0) * in_var[FWD->IJK(i,j,k-1)] + \
				(2.0 / 3.0) * in_var[FWD->IJK(i,j,k+1)] - \
				(1.0 / 12.0) * in_var[FWD->IJK(i,j,k+2)] ) / FWD->SDMGeom->Dz();
	}


	//RIGHT SIDE

	if (k < 2*KHALO) {

	  out_var[FWD->IJK(i,j,k)] = ( - (25.0 / 12.0) * in_var[FWD->IJK(i,j,k)] + \
				 4.0 * in_var[FWD->IJK(i,j,k+1)] - \
				 3.0 * in_var[FWD->IJK(i,j,k+2)] + \
				(4.0 / 3.0) * in_var[FWD->IJK(i,j,k+3)] -
				  (1.0 / 4.0) * in_var[FWD->IJK(i,j,k+4)] ) / FWD->SDMGeom->Dz();
	}

	// LEFT SIDE
	
	if (k >= FWD->SNodeZ()-2*KHALO){

	  out_var[FWD->IJK(i,j,k)] = (  (25.0 / 12.0) * in_var[FWD->IJK(i,j,k)] - \
				 4.0 * in_var[FWD->IJK(i,j,k-1)] + \
				 3.0 * in_var[FWD->IJK(i,j,k-2)] - \
				(4.0 / 3.0) * in_var[FWD->IJK(i,j,k-3)] +
				  (1.0 / 4.0) * in_var[FWD->IJK(i,j,k-4)] ) / FWD->SDMGeom->Dz();

	}

	

	}
      }
    }

}



void KERNEL::RHO(){

  for (int k=KHALO;k<FWD->SNodeZ()-KHALO;k++){
    for (int j=KHALO;j<FWD->SNodeY()-KHALO;j++){
      for (int i=KHALO;i<FWD->SNodeX()-KHALO;i++){

	KRHO[FWD->IJK(i,j,k)] = KRHO[FWD->IJK(i,j,k)] - (	\
	  FWD->vx[FWD->IJK(i,j,k)] * ADJ->vx[ADJ->IJK(i,j,k)] + \
	  FWD->vy[FWD->IJK(i,j,k)] * ADJ->vy[ADJ->IJK(i,j,k)] + \
	  FWD->vz[FWD->IJK(i,j,k)] * ADJ->vz[ADJ->IJK(i,j,k)] ) * FWD->dt;

      }
    }
  }

}


void KERNEL::LAMBDA(){

  for (int k=KHALO;k<FWD->SNodeZ()-KHALO;k++){
    for (int j=KHALO;j<FWD->SNodeY()-KHALO;j++){
      for (int i=KHALO;i<FWD->SNodeX()-KHALO;i++){

	KLAMBDA[FWD->IJK(i,j,k)] = KLAMBDA[FWD->IJK(i,j,k)] + (	\
	  ux_dx[FWD->IJK(i,j,k)] + uy_dy[FWD->IJK(i,j,k)] + \
	  uz_dz[FWD->IJK(i,j,k)] ) * (ux_dx_ad[ADJ->IJK(i,j,k)] + \
		    uy_dy_ad[ADJ->IJK(i,j,k)] + uz_dz_ad[ADJ->IJK(i,j,k)]) * FWD->dt;
					    
	  
      }
    }
  }

}


void KERNEL::MU(){
  Dfloat e[3][3],e_ad[3][3],buff;


  for (int k=KHALO;k<FWD->SNodeZ()-KHALO;k++){
    for (int j=KHALO;j<FWD->SNodeY()-KHALO;j++){
      for (int i=KHALO;i<FWD->SNodeX()-KHALO;i++){
  


	e[0][0]= 2.0 * ux_dx[FWD->IJK(i,j,k)];
	e[0][1]= ux_dy[FWD->IJK(i,j,k)] + uy_dx[FWD->IJK(i,j,k)];
	e[0][2]= ux_dz[FWD->IJK(i,j,k)] + uz_dx[FWD->IJK(i,j,k)];
	e[1][0]= e[0][1];
	e[1][1]= 2.0 * uy_dy[FWD->IJK(i,j,k)];
	e[1][2]= uy_dz[FWD->IJK(i,j,k)] + uz_dy[FWD->IJK(i,j,k)];
	e[2][0]= e[0][2];
	e[2][1]= e[1][2];
	e[2][2]= 2.0 * uz_dz[FWD->IJK(i,j,k)];


	e_ad[0][0]= 2.0 * ux_dx_ad[ADJ->IJK(i,j,k)];
	e_ad[0][1]= ux_dy_ad[ADJ->IJK(i,j,k)] + uy_dx_ad[ADJ->IJK(i,j,k)];
	e_ad[0][2]= ux_dz_ad[ADJ->IJK(i,j,k)] + uz_dx_ad[ADJ->IJK(i,j,k)];
	e_ad[1][0]= e_ad[0][1];
	e_ad[1][1]= 2.0 * uy_dy_ad[ADJ->IJK(i,j,k)];
	e_ad[1][2]= uy_dz_ad[ADJ->IJK(i,j,k)] + uz_dy_ad[ADJ->IJK(i,j,k)];
	e_ad[2][0]= e_ad[0][2];
	e_ad[2][1]= e_ad[1][2];
	e_ad[2][2]= 2.0 * uz_dz_ad[ADJ->IJK(i,j,k)];


	buff = 0.0;
	
	for (int jj = 0;jj<3;++jj){
	  for (int ii = 0;ii<3;++ii){

	    buff += e[jj][ii] * e_ad[jj][ii];

	  }
	}


	KMU[FWD->IJK(i,j,k)] = KMU[FWD->IJK(i,j,k)] + 0.5 * FWD->dt * buff;
	


      }
    }
  }

}

void KERNEL::CALC(){

  DevX(FWD->ux,ux_dx);
  DevY(FWD->ux,ux_dy);
  DevZ(FWD->ux,ux_dz);
  
  DevX(FWD->uy,uy_dx);
  DevY(FWD->uy,uy_dy);
  DevZ(FWD->uy,uy_dz);
  
  DevX(FWD->uz,uz_dx);
  DevY(FWD->uz,uz_dy);
  DevZ(FWD->uz,uz_dz);

  DevX(ADJ->ux,ux_dx_ad);
  DevY(ADJ->ux,ux_dy_ad);
  DevZ(ADJ->ux,ux_dz_ad);
  
  DevX(ADJ->uy,uy_dx_ad);
  DevY(ADJ->uy,uy_dy_ad);
  DevZ(ADJ->uy,uy_dz_ad);
  
  DevX(ADJ->uz,uz_dx_ad);
  DevY(ADJ->uz,uz_dy_ad);
  DevZ(ADJ->uz,uz_dz_ad);
  
  RHO();
  MU();
  LAMBDA();
}


void  KERNEL::KERNELS(){
   Dfloat vp,vs,rho;

 
    
    for (int k=KHALO;k<FWD->SNodeZ()-KHALO;k++){
      for (int j=KHALO;j<FWD->SNodeY()-KHALO;j++){
	for (int i=KHALO;i<FWD->SNodeX()-KHALO;i++){

	  rho = FWD->rho[FWD->IJK(i,j,k)];
	  
	  vp = (FWD->lamb[FWD->IJK(i,j,k)] \
		+ 2.0 * FWD->mu[FWD->IJK(i,j,k)]) / rho;

	  vs = FWD->mu[FWD->IJK(i,j,k)]  / rho;

	  
	  KDEN[FWD->IJK(i,j,k)] = KRHO[FWD->IJK(i,j,k)] +	\
	    (vp - 2.0 * vs) * KLAMBDA[FWD->IJK(i,j,k)] + \
	    vs * KMU[FWD->IJK(i,j,k)];

	  KVS[FWD->IJK(i,j,k)] = 2.0 * rho * sqrt(vs) * KMU[FWD->IJK(i,j,k)] - \
	    4.0 * rho * sqrt(vs) * KLAMBDA[FWD->IJK(i,j,k)];

	  KVP[FWD->IJK(i,j,k)] = 2.0 * rho * sqrt(vp) * KLAMBDA[FWD->IJK(i,j,k)];
	    
	  
	}
      }
    }

}

  
  
