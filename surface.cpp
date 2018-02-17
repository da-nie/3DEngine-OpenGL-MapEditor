#include "surface.h"

//------------------------------------------------------------------------------
void NewSurfaceSegment(SURFACE **Surface,SEGMENT_PACKAGE SP)
{
 SURFACE *NextSurface=new SURFACE;
 SURFACE *WorkSurface=*Surface;
 NextSurface->Next=NULL;
 NextSurface->Previous=WorkSurface;
 NextSurface->Texture=SP.Texture;
 SP.Normal=NormalizeVector(SP.Normal);
 NextSurface->Normal=SP.Normal;
 NextSurface->Location=SP.Location;
 NextSurface->Segment=SP.Segment;
 NextSurface->Sector=-1;
 NextSurface->SectorType=-1;
 NextSurface->Vertex=4;
 NextSurface->X_Left_Up=SP.X_Left_Up*16.0;
 NextSurface->Y_Left_Up=SP.Y_Left_Up*16.0;
 NextSurface->Z_Left_Up=SP.Z_Left_Up;
 NextSurface->BarrierType=SP.BarrierType;
 for(int n=0;n<4;n++)
 {
  NextSurface->X[n]=SP.X[n]*16.0;
  NextSurface->Y[n]=SP.Y[n]*16.0;
  NextSurface->Z[n]=SP.Z[n];
 }
 if (WorkSurface!=NULL) WorkSurface->Next=NextSurface;
 *Surface=NextSurface;
}
void NewSurfaceSector(SURFACE **Surface,SECTOR_PACKAGE SCP)
{
 SURFACE *NextSurface=new SURFACE;
 SURFACE *WorkSurface=*Surface;
 NextSurface->Next=NULL;
 NextSurface->Previous=WorkSurface;
 NextSurface->Texture=SCP.Texture;
 SCP.Normal=NormalizeVector(SCP.Normal);
 NextSurface->Normal=SCP.Normal;
 NextSurface->Location=SCP.Location;
 NextSurface->Segment=-1;
 NextSurface->Sector=SCP.Sector;
 NextSurface->SectorType=SCP.SectorType;
 NextSurface->Vertex=SCP.Vertex;
 NextSurface->BarrierType=SCP.BarrierType;
 NextSurface->Dz=SCP.Dz;
 for(int n=0;n<SCP.Vertex;n++)
 {
  NextSurface->X[n]=SCP.X[n]*16.0;
  NextSurface->Y[n]=SCP.Y[n]*16.0;
  NextSurface->Z[n]=SCP.Z[n];
 }
 if (WorkSurface!=NULL) WorkSurface->Next=NextSurface;
 *Surface=NextSurface;
}
void DeleteAllSurface(SURFACE **Surface)
{
 SURFACE *WorkSurface=*Surface;
 while(1)
 {
  if (WorkSurface==NULL) break;
  SURFACE *PreviousSurface=WorkSurface->Previous;
  delete(WorkSurface);
  WorkSurface=PreviousSurface;
 }
 *Surface=WorkSurface;
}
 
