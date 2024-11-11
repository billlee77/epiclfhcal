#ifndef PLOTTHELPER_H
#define PLOTTHELPER_H

#include "TLegend.h"
#include "TAxis.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TFrame.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TGaxis.h"
#include "TSystem.h"
#include "TStyle.h"
  
  //__________________________________________________________________________________________________________
  //__________________________________________________________________________________________________________
  //__________________________________________________________________________________________________________
  TString ReturnDateStr(){
      TDatime today;
      int iDate           = today.GetDate();
      int iYear           = iDate/10000;
      int iMonth          = (iDate%10000)/100;
      int iDay            = iDate%100;
      return Form("%i_%02d_%02d",iYear, iMonth, iDay);
  }


  
  // ---------------------------- Function definiton --------------------------------------------------------------------------------------------
  // StyleSettingsBasics will make some standard settings for gStyle
  
  void StyleSettingsBasics( TString format = ""){
      //gStyle->SetOptTitle(kFALSE);
      gStyle->SetOptDate(0);   //show day and time
      gStyle->SetOptStat(0);  //show statistic
      gStyle->SetPalette(1,0);
      gStyle->SetFrameBorderMode(0);
      gStyle->SetFrameFillColor(0);
      gStyle->SetTitleFillColor(0);
      gStyle->SetTextSize(0.5);
      gStyle->SetLabelSize(0.03,"xyz");
      gStyle->SetLabelOffset(0.006,"xyz");
      gStyle->SetTitleFontSize(0.04);
      gStyle->SetTitleOffset(1,"y");
      gStyle->SetTitleOffset(0.7,"x");
      gStyle->SetCanvasColor(0);
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);
      gStyle->SetLineWidth(1);

      gStyle->SetPadTopMargin(0.03);
      gStyle->SetPadBottomMargin(0.09);
      gStyle->SetPadRightMargin(0.03);
      gStyle->SetPadLeftMargin(0.13);


      TGaxis::SetMaxDigits(4);
      gErrorIgnoreLevel=kError;

      if (format.CompareTo("eps") == 0 ||format.CompareTo("pdf") == 0  ) gStyle->SetLineScalePS(1);
  }

  //__________________________________________________________________________________________________________
  void SetPlotStyle() {
  // 	const Int_t nRGBs = 7;
      const Int_t nRGBs = 5;
      const Int_t nCont = 255;

      Double_t stops[nRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
      Double_t red[nRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
      Double_t green[nRGBs] = { 0.31, 0.81, 1.00, 0.20, 0.00 };
      Double_t blue[nRGBs]  = { 0.51, 1., 0.12, 0.00, 0.00};

      TColor::CreateGradientColorTable(nRGBs, stops, red, green, blue, nCont);
      gStyle->SetNumberContours(nCont);
  }

  //__________________________________________________________________________________________________________
  void SetPlotStyleNConts(    Int_t nCont = 255) {
      const Int_t nRGBs = 5;
      Double_t stops[nRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
      Double_t red[nRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
      Double_t green[nRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
      Double_t blue[nRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
      TColor::CreateGradientColorTable(nRGBs, stops, red, green, blue, nCont);
      gStyle->SetNumberContours(nCont);
  }

  //__________________________________________________________________________________________________________
  void DrawCanvasSettings( TCanvas* c1,
                          Double_t leftMargin,
                          Double_t rightMargin,
                          Double_t topMargin,
                          Double_t bottomMargin){

      c1->SetTickx();
      c1->SetTicky();
      c1->SetGridx(0);
      c1->SetGridy(0);
      c1->SetLogy(0);
      c1->SetLeftMargin(leftMargin);
      c1->SetRightMargin(rightMargin);
      c1->SetTopMargin(topMargin);
      c1->SetBottomMargin(bottomMargin);
      c1->SetFillColor(0);
  }

  //__________________________________________________________________________________________________________
  TCanvas *GetAndSetCanvas( TString name,
                            Double_t leftmargin = 0.11,
                            Double_t bottommargin = 0.1,
                            Double_t x = 1400,
                            Double_t y = 1000){

      TCanvas *canvas =  new TCanvas(name,name,x,y);
      canvas->SetLeftMargin(leftmargin);
      canvas->SetRightMargin(0.015);
      canvas->SetTopMargin(0.03);
      canvas->SetBottomMargin(bottommargin);
      canvas->SetFillColor(0);

      return canvas;

  }

  //__________________________________________________________________________________________________________
  TLegend *GetAndSetLegend( Double_t positionX,
                          Double_t positionY,
                          Double_t entries,
                          Int_t Columns = 1,
                          TString header =""){

      if(header.CompareTo("") != 0) entries++;
      Double_t positionYPlus = 0.04*1.1*(Double_t)entries;
      TLegend *legend = new TLegend(positionX,positionY,positionX+(0.25*Columns),positionY+positionYPlus);
      legend->SetNColumns(Columns);
      legend->SetLineColor(0);
      legend->SetLineWidth(0);
      legend->SetFillColor(0);
      legend->SetFillStyle(0);
      legend->SetLineStyle(0);
      legend->SetTextSize(0.04);
      legend->SetTextFont(42);
      if(header.CompareTo("") != 0)legend->SetHeader(header);
      return legend;
  }
  
  //__________________________________________________________________________________________________________
  TLegend *GetAndSetLegend2(  Double_t positionX,
                              Double_t positionY,
                              Double_t positionXRight,
                              Double_t positionYUp,
                              Size_t textSize,
                              Int_t columns               = 1,
                              TString header              = "",
                              Font_t textFont             = 43,
                              Double_t margin             = 0
  ){

      TLegend *legend = new TLegend(positionX,positionY,positionXRight,positionYUp);
      legend->SetNColumns(columns);
      legend->SetLineColor(0);
      legend->SetLineWidth(0);
      legend->SetFillColor(0);
      legend->SetFillStyle(0);
      legend->SetLineStyle(0);
      legend->SetBorderSize(0);
      legend->SetTextFont(textFont);
      legend->SetTextSize(textSize);
      if (margin != 0) legend->SetMargin(margin);
      if (header.CompareTo("")!= 0) legend->SetHeader(header);
      return legend;
  }

  //__________________________________________________________________________________________________________
  void SetHistogramm( TH1 *hist,
                      TString xLabel,
                      TString yLabel,
                      Double_t rangeYlow  = -99.,
                      Double_t rangeYhigh = -99.,
                      Double_t xOffset    = 1.0,
                      Double_t yOffset    = 1.15,
                      Font_t font         = 42
  ){

      Double_t scale = 1./gPad->GetAbsHNDC();
      //hist->GetXaxis()->SetRangeUser(rangeX[0],rangeX[1]);
      if(rangeYlow != -99.) hist->GetYaxis()->SetRangeUser(rangeYlow,rangeYhigh);
      hist->SetTitle("");
      hist->SetXTitle(xLabel);
      hist->SetYTitle(yLabel);
      hist->GetYaxis()->SetDecimals();
      hist->GetYaxis()->SetTitleOffset(yOffset/scale);
      hist->GetXaxis()->SetTitleOffset(xOffset);
      hist->GetXaxis()->SetTitleSize(0.04*scale);
      hist->GetYaxis()->SetTitleSize(0.04*scale);
      hist->GetXaxis()->SetLabelSize(0.035*scale);
      hist->GetYaxis()->SetLabelSize(0.035*scale);
      hist->GetXaxis()->SetLabelFont(font);
      hist->GetYaxis()->SetLabelFont(font);
      hist->SetMarkerSize(1.);
      hist->SetMarkerStyle(20);
  }

  //__________________________________________________________________________________________________________
  void SetGraph( TGraph *graph,
                  TString xLabel,
                  TString yLabel,
                  Double_t rangeYlow = -99.,
                  Double_t rangeYhigh = -99.,
                  Double_t xOffset = 1.0,
                  Double_t yOffset = 1.15){

      Double_t scale = 1./gPad->GetAbsHNDC();
      //graph->GetXaxis()->SetRangeUser(rangeX[0],rangeX[1]);
      if(rangeYlow != -99.) graph->GetYaxis()->SetRangeUser(rangeYlow,rangeYhigh);
      graph->GetXaxis()->SetTitle(xLabel);
      graph->GetYaxis()->SetTitle(yLabel);
      graph->GetYaxis()->SetDecimals();
      graph->GetYaxis()->SetTitleOffset(yOffset/scale);
      graph->GetXaxis()->SetTitleOffset(xOffset);
      graph->GetXaxis()->SetTitleSize(0.04*scale);
      graph->GetYaxis()->SetTitleSize(0.04*scale);
      graph->GetXaxis()->SetLabelSize(0.035*scale);
      graph->GetYaxis()->SetLabelSize(0.035*scale);
      graph->GetXaxis()->SetLabelFont(42);
      graph->GetYaxis()->SetLabelFont(42);
      graph->SetMarkerSize(1.);
      graph->SetMarkerStyle(20);
  }

  //__________________________________________________________________________________________________________
  void SetMarkerDefaults(    TH1* histo1,
                              Style_t markerStyle,
                              Size_t markerSize,
                              Color_t markerColor,
                              Color_t lineColor,
                              Bool_t setFont = kTRUE) {
      histo1->SetMarkerStyle(markerStyle);
      histo1->SetMarkerSize(markerSize);
      histo1->SetMarkerColor(markerColor);
      histo1->SetLineColor(lineColor);
      if (setFont){
        histo1->GetYaxis()->SetLabelFont(42);
        histo1->GetXaxis()->SetLabelFont(42);
        histo1->GetYaxis()->SetTitleFont(62);
        histo1->GetXaxis()->SetTitleFont(62);
      }
  }
  //__________________________________________________________________________________________________________
  void SetMarkerDefaults(    TH1* histo1,
                              TString xtitle = "",
                              TString ytitle = "",
                              Style_t markerStyle = 20,
                              Size_t markerSize = 1,
                              Color_t markerColor = kBlack,
                              Color_t lineColor = kBlack,
                              double textsize = 0.045,
                              double labelsize = 0.045,
                              double xoffset = 1.,
                              double yoffset = 1. ) {
      histo1->SetTitle("");
      histo1->SetStats(0);
      histo1->SetMarkerStyle(markerStyle);
      histo1->SetMarkerSize(markerSize);
      histo1->SetMarkerColor(markerColor);
      histo1->SetLineColor(lineColor);
      histo1->GetYaxis()->SetLabelFont(42);
      histo1->GetXaxis()->SetLabelFont(42);
      histo1->GetYaxis()->SetLabelSize(labelsize);
      histo1->GetXaxis()->SetLabelSize(labelsize);
      histo1->GetYaxis()->SetTitleFont(62);
      histo1->GetXaxis()->SetTitleFont(62);
      histo1->GetYaxis()->SetTitleSize(textsize);
      histo1->GetXaxis()->SetTitleSize(textsize);
      if(!xtitle.EqualTo("")) histo1->GetXaxis()->SetTitle(xtitle);
      if(!ytitle.EqualTo("")) histo1->GetYaxis()->SetTitle(ytitle);
      histo1->GetXaxis()->SetTitleOffset(xoffset);
      histo1->GetYaxis()->SetTitleOffset(yoffset);
  }
  //__________________________________________________________________________________________________________
  void SetMarkerDefaultsProfile( TProfile* prof,
                                  Style_t markerStyle,
                                  Size_t markerSize,
                                  Color_t markerColor,
                                  Color_t lineColor ) {
      prof->SetMarkerStyle(markerStyle);
      prof->SetMarkerSize(markerSize);
      prof->SetMarkerColor(markerColor);
      prof->SetLineColor(lineColor);
      prof->GetYaxis()->SetLabelFont(42);
      prof->GetXaxis()->SetLabelFont(42);
      prof->GetYaxis()->SetTitleFont(62);
      prof->GetXaxis()->SetTitleFont(62);
  }

  //__________________________________________________________________________________________________________
  void SetLineDefaults(    TH1* histo1,
                              Int_t LineColor,
                              Int_t LineWidth,
                              Int_t LineStyle ) {
      histo1->SetLineColor(LineColor);
      histo1->SetLineWidth(LineWidth);
      histo1->SetLineStyle(LineStyle);
  }

  //__________________________________________________________________________________________________________
  void SetLineDefaultsTF1(  TF1*  Fit1,
                              Int_t LineColor,
                              Int_t LineWidth,
                              Int_t LineStyle ) {
      Fit1->SetLineColor(LineColor);
      Fit1->SetLineWidth(LineWidth);
      Fit1->SetLineStyle(LineStyle);
  }
  

    //__________________________________________________________________________________________________________
  void DefaultCancasSettings( TCanvas* c1,
                              Double_t leftMargin,
                              Double_t rightMargin,
                              Double_t topMargin,
                              Double_t bottomMargin){
      c1->SetTickx();
      c1->SetTicky();
      c1->SetGridx(0);
      c1->SetGridy(0);
      c1->SetLogy(0);
      c1->SetLeftMargin(leftMargin);
      c1->SetRightMargin(rightMargin);
      c1->SetTopMargin(topMargin);
      c1->SetBottomMargin(bottomMargin);
      c1->SetFillColor(0);
  }

  //__________________________________________________________________________________________________________
  void DefaultPadSettings( TPad* pad1,
                          Double_t leftMargin,
                          Double_t rightMargin,
                          Double_t topMargin,
                          Double_t bottomMargin){
      pad1->SetFillColor(0);
      pad1->GetFrame()->SetFillColor(0);
      pad1->SetBorderMode(0);
      pad1->SetLeftMargin(leftMargin);
      pad1->SetBottomMargin(bottomMargin);
      pad1->SetRightMargin(rightMargin);
      pad1->SetTopMargin(topMargin);
      pad1->SetTickx();
      pad1->SetTicky();
  }

  //__________________________________________________________________________________________________________
  void SetMarkerDefaultsTGraph(  TGraph* graph,
                                  Style_t markerStyle,
                                  Size_t markerSize,
                                  Color_t markerColor,
                                  Color_t lineColor,
                                  Width_t lineWidth       = 1,
                                  Style_t lineStyle       = 1,
                                  Bool_t boxes            = kFALSE,
                                  Color_t fillColor       = 0,
                                  Bool_t isHollow         = kFALSE
                                ) {
      graph->SetMarkerStyle(markerStyle);
      graph->SetMarkerSize(markerSize);
      graph->SetMarkerColor(markerColor);
      graph->SetLineColor(lineColor);
      graph->SetLineWidth(lineWidth);
      graph->SetLineWidth(lineStyle);
      if (boxes){
          graph->SetFillColor(fillColor);
          if (fillColor!=0){
              if (!isHollow){
                  graph->SetFillStyle(1001);
              } else {
                  graph->SetFillStyle(0);
              }
          } else {
              graph->SetFillStyle(0);
          }
      }
  }

  //__________________________________________________________________________________________________________
  void SetMarkerDefaultsTGraphErr(   TGraphErrors* graph,
                                      Style_t markerStyle,
                                      Size_t markerSize,
                                      Color_t markerColor,
                                      Color_t lineColor,
                                      Width_t lineWidth       = 1,
                                      Bool_t boxes            = kFALSE,
                                      Color_t fillColor       = 0,
                                      Bool_t isHollow         = kFALSE) {
      graph->SetMarkerStyle(markerStyle);
      graph->SetMarkerSize(markerSize);
      graph->SetMarkerColor(markerColor);
      graph->SetLineColor(lineColor);
      graph->SetLineWidth(lineWidth);
      if (boxes){
          graph->SetFillColor(fillColor);
          if (fillColor!=0){
              if (!isHollow){
                  graph->SetFillStyle(1001);
              } else {
                  graph->SetFillStyle(0);
              }
          } else {
              graph->SetFillStyle(0);
          }
      }
  }

  //__________________________________________________________________________________________________________
  void SetMarkerDefaultsTGraphAsym(  TGraphAsymmErrors* graph,
                                      Style_t markerStyle,
                                      Size_t markerSize,
                                      Color_t markerColor,
                                      Color_t lineColor,
                                      Width_t lineWidth   =1,
                                      Bool_t boxes        = kFALSE,
                                      Color_t fillColor   = 0,
                                      Bool_t isHollow     = kFALSE
                                    ) {
      if (!graph) return;
      graph->SetMarkerStyle(markerStyle);
      graph->SetMarkerSize(markerSize);
      graph->SetMarkerColor(markerColor);
      graph->SetLineColor(lineColor);
      graph->SetLineWidth(lineWidth);
      if (boxes){
          graph->SetFillColor(fillColor);
          if (fillColor!=0){
              if (!isHollow){
                  graph->SetFillStyle(1001);
              } else {
                  graph->SetFillStyle(0);
              }
          } else {
              graph->SetFillStyle(0);
          }
      }
  }

  //__________________________________________________________________________________________________________
  void SetMarkerDefaultsTF1( TF1* fit1,
                              Style_t lineStyle,
                              Size_t lineWidth,
                              Color_t lineColor ) {
      if (!fit1) return;
      fit1->SetLineColor(lineColor);
      fit1->SetLineStyle(lineStyle);
      fit1->SetLineWidth(lineWidth);
  }

  //__________________________________________________________________________________________________________
  void SetStyleTLatex( TLatex* text,
                      Size_t textSize,
                      Width_t lineWidth,
                      Color_t textColor = 1,
                      Font_t textFont = 42,
                      Bool_t kNDC = kTRUE,
                      Short_t align = 11
                  ){
      if (kNDC) {text->SetNDC();}
      text->SetTextFont(textFont);
      text->SetTextColor(textColor);
      text->SetTextSize(textSize);
      text->SetLineWidth(lineWidth);
      text->SetTextAlign(align);
  }

  //__________________________________________________________________________________________________________
  void DrawLatex(const double  PosX = 0.5, const double  PosY = 0.5, TString text = "", const bool alignRight = false, const double TextSize = 0.044, const int font = 42, const double dDist = 0.05, const int color = 1){

      std::vector<TString> Latex;
      
      TObjArray *textStr = text.Tokenize(";");
      for(Int_t i = 0; i<textStr->GetEntries() ; i++){
          TObjString* tempObj     = (TObjString*) textStr->At(i);
          Latex.push_back( tempObj->GetString());
      }
      for(unsigned int i = 0; i < Latex.size(); ++i){
          TLatex l(PosX, PosY - i*dDist, Latex[i]);
          l.SetNDC();
          l.SetTextFont(font);
          l.SetTextColor(color);
          l.SetTextSize(TextSize);
          if(alignRight) l.SetTextAlign(31);
          l.DrawClone("same");
      }
  }

  //__________________________________________________________________________________________________________
  void SetStyleHisto( TH1* histo,
                      Width_t lineWidth,
                      Style_t lineStyle,
                      Color_t lineColor) {
      if (!histo) return;
      histo->SetLineWidth(lineWidth);
      histo->SetLineStyle(lineStyle);
      histo->SetLineColor(lineColor);
  }

  //__________________________________________________________________________________________________________
  void SetStyleFit(   TF1* fit,
                      Double_t xRangeStart,
                      Double_t xRangeEnd,
                      Width_t lineWidth,
                      Style_t lineStyle,
                      Color_t lineColor) {
      if (!fit) return;
      fit->SetRange(xRangeStart,xRangeEnd);
      fit->SetLineWidth(lineWidth);
      fit->SetLineStyle(lineStyle);
      fit->SetLineColor(lineColor);
  }

  //__________________________________________________________________________________________________________
  void SetStyleHistoTH2ForGraphs( TH2* histo,
                                  TString XTitle,
                                  TString YTitle,
                                  Size_t xLableSize,
                                  Size_t xTitleSize,
                                  Size_t yLableSize,
                                  Size_t yTitleSize,
                                  Float_t xTitleOffset    = 1,
                                  Float_t yTitleOffset    = 1,
                                  Int_t xNDivisions       = 510,
                                  Int_t yNDivisions       = 510,
                                  Font_t textFontLabel    = 42,
                                  Font_t textFontTitle    = 62
                                ){
      histo->SetXTitle(XTitle);
      histo->SetYTitle(YTitle);
      histo->SetTitle("");
      histo->SetStats(0);

      histo->GetXaxis()->SetLabelFont(textFontLabel);
      histo->GetYaxis()->SetLabelFont(textFontLabel);
      histo->GetXaxis()->SetTitleFont(textFontTitle);
      histo->GetYaxis()->SetTitleFont(textFontTitle);

      histo->GetXaxis()->SetLabelSize(xLableSize);
      histo->GetXaxis()->SetTitleSize(xTitleSize);
      histo->GetXaxis()->SetTitleOffset(xTitleOffset);
      histo->GetXaxis()->SetNdivisions(xNDivisions,kTRUE);

      histo->GetYaxis()->SetDecimals();
      histo->GetYaxis()->SetLabelSize(yLableSize);
      histo->GetYaxis()->SetTitleSize(yTitleSize);
      histo->GetYaxis()->SetTitleOffset(yTitleOffset);
      histo->GetYaxis()->SetNdivisions(yNDivisions,kTRUE);
  }

  //__________________________________________________________________________________________________________
  void SetStyleHistoTH1ForGraphs( TH1* histo,
                                  TString XTitle,
                                  TString YTitle,
                                  Size_t xLableSize,
                                  Size_t xTitleSize,
                                  Size_t yLableSize,
                                  Size_t yTitleSize,
                                  Float_t xTitleOffset    = 1,
                                  Float_t yTitleOffset    = 1,
                                  Int_t xNDivisions       = 510,
                                  Int_t yNDivisions       = 510,
                                  Font_t textFontLabel    = 42,
                                  Font_t textFontTitle    = 62
                                ){
      histo->SetXTitle(XTitle);
      histo->SetYTitle(YTitle);
      histo->SetTitle("");

      histo->GetYaxis()->SetLabelFont(textFontLabel);
      histo->GetXaxis()->SetLabelFont(textFontLabel);
      histo->GetYaxis()->SetTitleFont(textFontTitle);
      histo->GetXaxis()->SetTitleFont(textFontTitle);

      histo->GetXaxis()->SetLabelSize(xLableSize);
      histo->GetXaxis()->SetTitleSize(xTitleSize);
      histo->GetXaxis()->SetTitleOffset(xTitleOffset);
      histo->GetXaxis()->SetNdivisions(xNDivisions,kTRUE);

      histo->GetYaxis()->SetDecimals();
      histo->GetYaxis()->SetLabelSize(yLableSize);
      histo->GetYaxis()->SetTitleSize(yTitleSize);
      histo->GetYaxis()->SetTitleOffset(yTitleOffset);
      histo->GetYaxis()->SetNdivisions(yNDivisions,kTRUE);
  }

  //********************************************************************************************************************************
  //********************** Returns default labeling strings  ***********************************************************************
  //********************************************************************************************************************************    
  TString GetStringFromRunInfo(RunInfo currRunInfo, Int_t option = 1){
      if (option == 1){
          if (currRunInfo.species.Contains("cosmics")){
              return  Form("cosmics, Run %d, #it{V}_{#it{op}} = %1.1f V", currRunInfo.runNr, currRunInfo.vop  );
          } else if (currRunInfo.species.CompareTo("g") == 0){
              return  Form("LED, Run %d, #it{V}_{#it{op}} = %1.1f V", currRunInfo.runNr, currRunInfo.vop  );
          } else {
              return  Form("%s-beam, #it{E}_{#it{b}}= %.0f GeV, Run %d, #it{V}_{#it{op}} = %1.1f V", currRunInfo.species.Data(), currRunInfo.energy, currRunInfo.runNr, currRunInfo.vop  );
          }
      } else if (option == 2){
          if (currRunInfo.species.CompareTo("cosmics") == 0){
              return  "cosmics";
          } else if (currRunInfo.species.CompareTo("g") == 0){
              return  "LED";
          } else {
              return  Form("%s-beam, #it{E}_{#it{b}}= %.0f GeV", currRunInfo.species.Data(), currRunInfo.energy);
          }
      } else if (option == 3){
          return Form("Run %d, #it{V}_{#it{op}} = %1.1f V", currRunInfo.runNr, currRunInfo.vop  )   ;
      } else if (option == 4){
          if (currRunInfo.species.CompareTo("cosmics") == 0){
              return Form("cosmics, Run %d, #it{V}_{#it{op}} = %1.1f V, HG = %1d, LG = %1d", currRunInfo.runNr, currRunInfo.vop, currRunInfo.hgSet, currRunInfo.lgSet);
          } else if (currRunInfo.species.CompareTo("g") == 0){
              return Form("LED, Run %d, #it{V}_{#it{op}} = %1.1f V, HG = %1d, LG = %1d", currRunInfo.runNr, currRunInfo.vop, currRunInfo.hgSet, currRunInfo.lgSet);
          } else{
              return Form("%s-beam, #it{E}_{#it{b}}= %.0f GeV, Run %d, #it{V}_{#it{op}} = %1.1f V, HG = %1d, LG = %1d", currRunInfo.species.Data(), currRunInfo.energy, currRunInfo.runNr, currRunInfo.vop, currRunInfo.hgSet, currRunInfo.lgSet);
          }
      } else if (option == 5){
          return Form("pedestal, Run %d, #it{V}_{#it{op}} = %1.1f V", currRunInfo.runNr, currRunInfo.vop  )   ;
      }
      
      return "";
  }


  
  //__________________________________________________________________________________________________________
  // Plot 2D fit variables overview
  //__________________________________________________________________________________________________________  
  void PlotSimple2D( TCanvas* canvas2D, TH2* hist, Int_t maxy, Int_t maxx, Float_t textSizeRel, TString nameOutput, RunInfo currRunInfo, int labelOpt = 1, Bool_t hasNeg = kFALSE, TString drwOpt ="colz"  ){
      canvas2D->cd();
      SetStyleHistoTH2ForGraphs( hist, hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), 0.85*textSizeRel, textSizeRel, 0.85*textSizeRel, textSizeRel,0.9, 1.05);  
      hist->GetZaxis()->SetLabelSize(0.85*textSizeRel);
      hist->GetZaxis()->SetTitleOffset(1.05);
      hist->GetZaxis()->SetTitleSize(textSizeRel);
      // if (hist->GetYaxis()->GetTitle().CompareTo("") != 0)
        
      if (maxy > -10000)hist->GetYaxis()->SetRangeUser(-0.5,maxy+0.1);
      if (maxx > -10000)hist->GetXaxis()->SetRangeUser(0.5,maxx+0.1);
      if (!hasNeg)
        hist->GetZaxis()->SetRangeUser(hist->GetMinimum(0),hist->GetMaximum());
      else 
        hist->GetZaxis()->SetRangeUser(hist->GetMinimum(),hist->GetMaximum());
      hist->Draw(drwOpt.Data());
      
      DrawLatex(0.85, 0.92, GetStringFromRunInfo(currRunInfo,labelOpt), true, textSizeRel, 42);

    canvas2D->SaveAs(nameOutput.Data());
  }

    
#endif
