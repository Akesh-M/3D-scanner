import numpy as np
import math
from stl import mesh
xy=51                        
array=np.loadtxt("1234.txt")
z=(len(array)/xy)
z=int(z)
mes=np.full((z,xy,3),0,dtype=float)
distance=np.full((z,xy,1),0,dtype=float)
p=0
for i in range(z):
    j=array[p:p+xy]
    for g in range(xy):
        distance[i][g]=j[g]
    p=p+xy
z3=0
z_axis_unit=0.25
for i in range(z):
    for j in range(xy):
        mes[i][j][2]=z3
    z3=z3+z_axis_unit
x=np.full((z,xy,1),0,dtype=float)
y=np.full((z,xy,1),0,dtype=float)
for i in range(z):
    pos=0
    deg=(360/xy)
    for j in range(xy):
	    x[i][j]=math.cos(math.radians(pos))*(10-distance[i][j])
	    y[i][j]=math.sin(math.radians(pos))*(10-distance[i][j])
	    pos=pos+deg
	    mes[i][j][0]=x[i][j]
	    mes[i][j][1]=y[i][j]
u=0
vertices=np.full(((z*xy),3),0,dtype=float)
for i in range(z):
    for g in range(xy):
     for b in range(3):
        vertices[u][b]=mes[i][g][b]
     u=u+1
faces=np.full(((z-1)*((xy-2)*2),3),0)
i=0
for l in range((z-1)*xy):
	if((l%xy!=0)):
		if(((l+1)%xy!=0)):
			faces[i][0]=l
			faces[i][1]=l+xy
			faces[i][2]=l+xy-1
			faces[i+1][0]=l
			faces[i+1][2]=l+xy
			faces[i+1][1]=l+1
			i=i+2
faces1=np.full(((z-1),3),0)
faces2=np.full(((z-1),3),0)
faces3=np.full(((z-1),3),0)
faces4=np.full(((z-1),3),0)
vertices=np.append(vertices,[[0,0,z3]],0)
vertices=np.append(vertices,[[0,0,0]],0)
facestop=np.full(((xy-1),3),0)
facesbottom=np.full((xy-1,3),0)
j=0
p=0
for l in range((z-1)*xy):
    if((l%xy==0)):
       faces1[j][0]=l
       faces1[j][1]=l+1
       faces1[j][2]=l+xy
       faces3[j][0]=l
       faces3[j][2]=l+xy-1
       faces3[j][1]=l+(2*xy)-1
       faces4[j][0]=l
       faces4[j][1]=l+xy
       faces4[j][2]=l+(2*xy)-1
       j=j+1
    if(((l+1)%xy==0)):
       faces2[p][0]=l
       faces2[p][1]=l+xy
       faces2[p][2]=l+xy-1
       p=p+1
i=0       
for l in range(z*xy):
    if(l>((z*xy)-xy-1) and l!=((z*xy)-1)):
        
           facestop[i][0]=l
           facestop[i][1]=l+1
           facestop[i][2]=(z*xy)
           i=i+1
facestop=np.append(facestop,[[(z*xy)-1,(z*xy)-xy,z*xy]],0)
for i in range(xy-1):
    facesbottom[i][0]=i
    facesbottom[i][1]=i+1
    facesbottom[i][2]=(z*xy)+1
facesbottom=np.append(facesbottom,[[i+1,0,(z*xy)+1]],0)    
faces=np.append(faces,faces1,0)
faces=np.append(faces,faces2,0)
faces=np.append(faces,faces3,0)
faces=np.append(faces,faces4,0)
faces=np.append(faces,facestop,0)
faces=np.append(faces,facesbottom,0)
print(faces)
layer=mesh.Mesh(np.zeros(faces.shape[0],dtype=mesh.Mesh.dtype))
for i,f in enumerate(faces):
       for j in range(3):
          layer.vectors[i][j]=vertices[f[j],:]
layer.save("semifinal.stl")       
			








