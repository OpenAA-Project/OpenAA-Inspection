/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Proofreader\ExecuteHalcon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "HalconCpp.h"
#include "ExecuteHalcon.h"

using namespace Halcon;

ExecuteHalcon::ExecuteHalcon()
{
}

ExecuteHalcon::~ExecuteHalcon()
{
}

void ExecuteHalcon::Hgen_image1(int iDotPerLine,int iMaxLines,unsigned char *image)
{
/*	Hobject  HalconImage;
	HTuple  WH;
	set_window_attr("background_color","black");
	open_window(0,0,iDotPerLine,iMaxLines,0,"","",&WH);
	open_window(0,0,246,1000,0,"","",&CPPExpDefaultWindow);

	gen_image1(&HalconImage,"byte",iDotPerLine,iMaxLines,(long)image);
	set_part(WH,0,0,-1,-1);
	disp_obj(HalconImage, CPPExpDefaultWindow);
	set_part(WH,0,0,-1,-1);
	disp_obj(HalconImage, CPPExpDefaultWindow);
*/

  // Local iconic variables 
  Hobject  Defects, Defects1, Defects2, Defects3;
  Hobject  Image, ImageZoom, ImageMean, ImageEmphasize, ImageInvert;
  Hobject  Region4, Region5, RegionDifference, RegionClosing;
  Hobject  RegionClosing2, ConnectedRegions4, SelectedRegions1;
  Hobject  SelectedRegions2, SelectedRegions3, ObjectSelected1;
  Hobject  RegionClosing1, ConnectedRegions5, SelectedRegions4;
  Hobject  SelectedRegions5, SelectedRegions6, ObjectSelected2;


  // Local control variables 
  HTuple  Files, H1, A1, A2, B1, F1, C1, D1, D2;
  HTuple  E1, G1, n, Min1, Max1, Range1, Min, Max, Range;
  HTuple  Area, Row, Column, MaxArea, Min2, Max2, Range2;
  HTuple  Number1, Sum1, Result1, s, Min5, Max5, Range5, Min3;
  HTuple  Max3, Range3, Area1, Row1, Column1, Number, MaxArea1;
  HTuple  Min4, Max4, Range4, Number2, Sum2, Result2, t, Min6;
  HTuple  Max6, Range6, Number3, Number4, Number5, Number6;
  HTuple  Result;


  // HDevelop default window handle 
  HTuple CPPExpDefaultWindow;

  // Open default window 
	open_window(0,0,246,1000,0,"","",&CPPExpDefaultWindow);
//  open_window(0,0,-1,-1,0,"","",&CPPExpDefaultWindow);
//  list_files("D:\\My Documents\\営業日誌　　\\分野別フォルダ\\その他関連\\セラミック関係\\三菱マテリアル\\0805192", 
//      "files", &Files);
  set_color(HTuple(CPPExpDefaultWindow),"red");
  set_draw(HTuple(CPPExpDefaultWindow),"margin");
  set_line_width(HTuple(CPPExpDefaultWindow),2);
  //選別輝度加算値
  H1 = 5;
  //大きな不良面積閾値
  A1 = 0.001;
  A2 = 40;
  //大きな不良輝度閾値
  B1 = 9;
  //大きな不良形状閾値
  F1 = 1.33;
  //小さな不良形状閾値
  C1 = 3.4;
  //小さな不良面積閾値
  D1 = 0.001;
  D2 = 243;
  //小さな不良輝度閾値
  E1 = 10;
  //画像圧縮度合
  G1 = 1.5;
//  for (n=1; n<=488; n+=1)
//  {
    gen_empty_obj(&Defects);
    gen_empty_obj(&Defects1);
    gen_empty_obj(&Defects2);
    gen_empty_obj(&Defects3);
//    read_image(&Image, HTuple(Files[n]));
	gen_image1(&Image,"byte",iDotPerLine,iMaxLines,(long)image);

	//ビットマップに保存
	write_image(Image,"bmp",0,"D:/Data/image.bmp");

	set_part(CPPExpDefaultWindow,0,0,-1,-1);
	disp_obj(Image, CPPExpDefaultWindow);
	set_part(CPPExpDefaultWindow,0,0,-1,-1);
	disp_obj(Image, CPPExpDefaultWindow);
    //
    // dev_update_pc(...); only in hdevelop
    // dev_update_time(...); only in hdevelop
    // dev_update_var(...); only in hdevelop
    // dev_update_window(...); only in hdevelop
    //
    //画像圧縮
    zoom_image_size(Image, &ImageZoom, 7400/G1, 30000/G1, "constant");
    copy_image(ImageZoom, &Image);
    //
    //平滑化
    mean_image(Image, &ImageMean, 3, 3);
    //
    //画像強調
    emphasize(ImageMean, &ImageEmphasize, 3, 3, 1);
    //
    //白黒反転
    invert_image(ImageEmphasize, &ImageInvert);
    min_max_gray(ImageInvert, ImageInvert, 1, &Min1, &Max1, &Range1);
    Min1 += H1;
    threshold(ImageInvert, &Region4, 0, Min1);
    threshold(ImageInvert, &Region5, 0, 0.75*Min1);
    difference(Region4, Region5, &RegionDifference);
    //
    //Region5の検査
    min_max_gray(Region5, Image, 2, &Min, &Max, &Range);
    //closing_rectangle1 (Region5, RegionClosing, 1, 1)
    closing_circle(Region5, &RegionClosing2, 6);
    connection(RegionClosing2, &ConnectedRegions4);
    select_shape(ConnectedRegions4, &SelectedRegions1, "anisometry", "and", F1, 60);
    area_center(ConnectedRegions4, &Area, &Row, &Column);
    tuple_max(Area, &MaxArea);
    //大きな不良　面積閾値
    select_shape(SelectedRegions1, &SelectedRegions2, "area", "and", A1*MaxArea, 
        999999);
    select_shape(SelectedRegions2, &SelectedRegions3, "area", "and", A2, 99999);
    min_max_gray(SelectedRegions3, Image, 7, &Min2, &Max2, &Range2);
    count_obj(SelectedRegions3, &Number1);
    tuple_sum(Max2, &Sum1);
    //大きな不良　輝度閾値
    Result1 = B1+(Sum1/Number1);
    if (Number1>1)
    {
      for (s=1; s<=Number1; s+=1)
      {
        select_obj(SelectedRegions3, &ObjectSelected1, s);
        //
        min_max_gray(ObjectSelected1, Image, 7, &Min5, &Max5, &Range5);
        if (Max5>Result1)
        {
          concat_obj(Defects, ObjectSelected1, &Defects);
        }
      }
    }
    else
    {
      concat_obj(Defects2, SelectedRegions3, &Defects2);
    }
    //
    //RegionDifferenceの検査
    closing_circle(RegionDifference, &RegionClosing1, 5.5);
    //closing_rectangle1 (RegionDifference, RegionClosing1, 5, 5)
    min_max_gray(RegionClosing1, Image, 2, &Min3, &Max3, &Range3);
    connection(RegionClosing1, &ConnectedRegions5);
    //小さな不良　形状による絞込み
    select_shape(ConnectedRegions5, &SelectedRegions4, "anisometry", "and", C1, 60);
    area_center(SelectedRegions4, &Area1, &Row1, &Column1);
    count_obj(SelectedRegions4, &Number);
    if (Number>0)
    {
      tuple_max(Area1, &MaxArea1);
      //小さな不良　面積閾値
      select_shape(SelectedRegions4, &SelectedRegions5, "area", "and", D1*MaxArea1, 
          99999);
      select_shape(SelectedRegions5, &SelectedRegions6, "area", "and", D2, 99999);
      min_max_gray(SelectedRegions6, Image, 7, &Min4, &Max4, &Range4);
      count_obj(SelectedRegions6, &Number2);
      tuple_sum(Max4, &Sum2);
      //小さな不良　輝度閾値
      Result2 = (Sum2/Number2)+E1;
      if (Number2>1)
      {
        for (t=1; t<=Number2; t+=1)
        {
          select_obj(SelectedRegions6, &ObjectSelected2, t);
          min_max_gray(ObjectSelected2, Image, 7, &Min6, &Max6, &Range6);
          if (Max6>Result2)
          {
            concat_obj(Defects1, ObjectSelected2, &Defects1);
          }
        }
      }
      else
      {
        concat_obj(Defects3, SelectedRegions6, &Defects3);
      }
    }
    //
    // dev_update_pc(...); only in hdevelop
    // dev_update_time(...); only in hdevelop
    // dev_update_var(...); only in hdevelop
    // dev_update_window(...); only in hdevelop
    //
    //表示
    disp_obj(Image, HTuple(CPPExpDefaultWindow));
    disp_obj(Defects, HTuple(CPPExpDefaultWindow));
    disp_obj(Defects1, HTuple(CPPExpDefaultWindow));
    disp_obj(Defects2, HTuple(CPPExpDefaultWindow));
    disp_obj(Defects3, HTuple(CPPExpDefaultWindow));
    count_obj(Defects, &Number3);
    count_obj(Defects1, &Number4);
    count_obj(Defects2, &Number5);
    count_obj(Defects3, &Number6);
    Result = ((Number3+Number4)+Number5)+Number6;
    //stop ()
//  }
  // Close default window 
//  close_window(CPPExpDefaultWindow);
}

void ExecuteHalcon::Hgen_image3(int iDotPerLine,int iMaxLines,unsigned char *image1,unsigned char *image2,unsigned char *image3)
{
	Hobject  HalconImage;
	HTuple  WH;
	set_window_attr("background_color","black");
//	open_window(0,0,iDotPerLine,iMaxLines,0,"","",&WH);
	open_window(0,0,1000,1000,0,"","",&WH);

	gen_image3(&HalconImage,"byte",iDotPerLine,iMaxLines,(long)image1,(long)image2,(long)image3);
	set_part(WH,0,0,-1,-1);
	disp_obj(HalconImage, WH);
	set_part(WH,0,0,-1,-1);
	disp_obj(HalconImage, WH);
}
