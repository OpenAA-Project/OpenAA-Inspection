#include "XDataModelPageItem3D.h"
#include "swap.h"

	
AlgorithmInPage3DPI::AlgorithmInPage3DPI(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent)
{
}

class ItemPointerWithBox : public NPList<ItemPointerWithBox>
{
public:
	AlgorithmItem3DPI	*Pointer;
	Box3D				ItemBox;

	ItemPointerWithBox(AlgorithmItem3DPI *d)
		:Pointer(d){}
};



bool	AlgorithmInPage3DPI::GetColorForDraw(QImage &Img
											,const Canvas3D &CInfo,AlgorithmDrawAttr *ModePoint)
{
	double	XLen=CInfo.Data.CanvasXAxis.GetLength();
	double	YLen=CInfo.Data.CanvasYAxis.GetLength();

	double	Zx=XLen/((double)CInfo.Data.CanvasWidth);
	double	Zy=YLen/((double)CInfo.Data.CanvasHeight);

	UVector3D	DUx=CInfo.Data.CanvasXAxis.GetUnit();
	UVector3D	DUy=CInfo.Data.CanvasYAxis.GetUnit();

	Point3D	DCenter=CInfo.Data.CanvasOrigin+(CInfo.Data.CanvasXAxis/2)+(CInfo.Data.CanvasYAxis/2);

	Vector3D	VC=-Vector3D::CrossProduct(CInfo.Data.CanvasXAxis,CInfo.Data.CanvasYAxis);
	UVector3D	UVC=VC.GetUnit();
	int	CMinX=min(Img.width() ,CInfo.Data.CanvasWidth);
	int	CMinY=min(Img.height(),CInfo.Data.CanvasHeight);

	NPListPack<ItemPointerWithBox>	ItemPointerContanier;
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		AlgorithmItem3DPI	*ct=dynamic_cast<AlgorithmItem3DPI *>(c);
		if(ct!=NULL){
			ItemPointerWithBox	*k=new ItemPointerWithBox(ct);
			if(ct->GetXYZ(k->ItemBox)==true){
				ItemPointerContanier.AppendList(k);
			}
			else{
				delete	k;
			}
		}
	}

	if(CInfo.Data.EyeType==Canvas3D::_Parallel){
		for(int y=0;y<CMinY;y++){
			Vector3D	DVy=DUy*(Zy*y);
			Point3D	DPy=CInfo.Data.CanvasOrigin+DVy;
			QRgb	*d=(QRgb *)Img.scanLine(y);
			for(int x=0;x<CMinX;x++,d++){
				Vector3D	DVx=DUx*(Zx*x);
				Point3D	P=DPy+DVx;
				VectorLine	L(P,UVC);
				AlgorithmItem3DPI	*Item=NULL;
				double				MinVRate=99999999;
				for(ItemPointerWithBox *k=ItemPointerContanier.GetFirst();k!=NULL;k=k->GetNext()){
					double VRate;
					if(k->ItemBox.GetCross(L ,VRate)==true){
						if(VRate>0){
							if(MinVRate>VRate){
								MinVRate=VRate;
								Item=k->Pointer;
							}
						}
					}
				}
				if(Item!=NULL){
					Reflection3D	RetReflection;
					Surface3D		RetSurface;
					if(Item->GetColorForDraw(CInfo ,ModePoint ,P ,UVC,RetReflection,RetSurface)==true){
						QColor	C=MakeColor(RetReflection,RetSurface);
						*d=C.rgba();
					}
				}
			}
		}
	}
	else
	if(CInfo.Data.EyeType==Canvas3D::_Centerize){
		Point3D	EyePoint=DCenter+UVC;
		for(int y=0;y<CMinY;y++){
			Vector3D	DVy=DUy*(Zy*y);
			Point3D	DPy=CInfo.Data.CanvasOrigin+DVy;
			QRgb	*d=(QRgb *)Img.scanLine(y);
			for(int x=0;x<CMinX;x++,d++){
				Vector3D	DVx=DUx*(Zx*x);
				Point3D	P=DPy+DVx;
				Vector3D	V=P-EyePoint;
				VectorLine	L(P,V.GetUnit());
				AlgorithmItem3DPI	*Item=NULL;
				double				MinVRate=99999999;
				for(ItemPointerWithBox *k=ItemPointerContanier.GetFirst();k!=NULL;k=k->GetNext()){
					double VRate;
					if(k->ItemBox.GetCross(L ,VRate)==true){
						if(VRate>0){
							if(MinVRate>VRate){
								MinVRate=VRate;
								Item=k->Pointer;
							}
						}
					}
				}
				if(Item!=NULL){
					Reflection3D	RetReflection;
					Surface3D		RetSurface;
					if(Item->GetColorForDraw(CInfo ,ModePoint
											,P ,UVC,RetReflection,RetSurface)==true){
						QColor	C=MakeColor(RetReflection,RetSurface);
						*d=C.rgba();
					}
				}
			}
		}
	}
}

QColor	AlgorithmInPage3DPI::MakeColor(const Reflection3D &R,const Surface3D &RetSurface)
{
	Vector3D	VertS=Vector3D::CrossProduct(RetSurface.Sx,RetSurface.Sy);
	UVector3D	UVertS=VertS.GetUnit();
	double	s=UVertS*RetSurface.ForCamVector;
	double	Diffused=(1.0-fabs(s))*R.Data.DiffusionRate;
	QColor	Col=QColor(qRed  (R.Data.SurfaceColor)*(1.0-Diffused)
					  ,qGreen(R.Data.SurfaceColor)*(1.0-Diffused)
					  ,qBlue (R.Data.SurfaceColor)*(1.0-Diffused));
	return Col;
}