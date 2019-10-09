#include "TMath.h"
#include "TCanvas.h"
#include "TROOT.h"
#include <iostream>
#include "TFile.h"
#include "TH1I.h"
#include <sstream>

float hiEdge = 0;


void drawEnergy(int isotope){

    if (isotope == 0) {
        const char* fileName = "144cs02.root";
        const char* fileNameFits = "cs144_fitParams.txt";
        const char* spectraFile = "cs144_allSpectra.txt";
        double recoilMassIso = 142.920626719; // Ba-143 mass in amu. Later convert to keV/(us/mm)^2
        hiEdge = 2000;
    }
    if (isotope == 1) {
        const char* fileName = "145cs02.root";
        const char* fileNameFits = "cs145_fitParams.txt";
        const char* spectraFile = "cs145_allSpectra.txt";
        double recoilMassIso = 143.922952853; // Ba-144 mass
        hiEdge = 3000;
    }
//    if (isotope == 2){
//        const char* fileName = "137i07.root";
//        const char* fileNameFits = "i137_fitParams.txt";
//        const char* spectraFile = "i137_allSpectra.txt";
//        double recoilMassIso = 135.9072145; // Xe-136 mass
//        hiEdge = 1500;
//    }
    if (isotope == 2){
        const char* fileName = "137i07.root";
        const char* fileNameFits = "i137_fitParams.txt";
        const char* spectraFile = "i137_allSpectra.txt";
        double recoilMassIso = 135.9072145; // Xe-136 mass
        hiEdge = 1500;
    }
    if (isotope == 3) {
        const char* fileName = "138i06.root";
        const char* fileNameFits = "i138_fitParams.txt";
        const char* spectraFile = "i138_allSpectra.txt";
        double recoilMassIso = 136.911562125; // Xe-137 mass
        hiEdge = 1800; // or 1800
    }
    if (isotope == 4) {
        const char* fileName = "138i07.root";
        const char* fileNameFits = "i138_fitParams.txt";
        const char* spectraFile = "i138_2_allSpectra.txt";
        double recoilMassIso = 136.911562125; // Xe-137 mass
        hiEdge = 1800; // or 1800
    }
    if (isotope == 5){
        const char* fileName = "F:/Files_BarbaraWang/Work/ResearchProjects/IonTrapping/Data/135Sb/135sb08.root";
        const char* fileNameFits = "F:/Files_BarbaraWang/Work/ResearchProjects/IonTrapping/Analysis/Beta-DelayedNeutrons/Gen2IonTrap/FastEfficiencyCorrection/135Sb/sb135_fitParams.txt";
        const char* spectraFile = "sb135_allSpectra.txt";
        double recoilMassIso = 133.911394; // Te-134 mass
        hiEdge = 4600; //set to 4600 instead of Q-Sn (4775 keV) because spectrum blows up above 4600 keV (probably due to 
 		       //the fact the fast-efficiency curve is very steep above ~4000 keV).
    }
    if (isotope == 6){
        const char* fileName = "F:/Files_BarbaraWang/Work/ResearchProjects/IonTrapping/Data/136Sb/136sb01.root";
        const char* fileNameFits = "F:/Files_BarbaraWang/Work/ResearchProjects/IonTrapping/Analysis/Beta-DelayedNeutrons/Gen2IonTrap/FastEfficiencyCorrection/136Sb/sb136_fitParams.txt";
        const char* spectraFile = "sb136_allSpectra.txt";
        double recoilMassIso = 134.9165557; // Te-135 mass
        hiEdge = 5000;
    }

    TFile *tfile2 = new TFile(fileName);
    TH1F *h_En = (TH1F*)h_En->Clone("h_En");
    TH1F *h_En_LR = (TH1F*)h_En_LR->Clone("h_En_LR");
    TH1F *h_vInv_LR = (TH1F*)h_vInv_LR->Clone("h_vInv_LR");
    TH1F *h_tof_LR = (TH1F*)h_tof_LR->Clone("h_tof_LR");
    TH1F *h_En_LT = (TH1F*)h_En_LT->Clone("h_En_LT");
    TH1F *h_vInv_LT = (TH1F*)h_vInv_LT->Clone("h_vInv_LT");
    TH1F *h_tof_LT = (TH1F*)h_tof_LT->Clone("h_tof_LT");
    TH1F *h_En_BR = (TH1F*)h_En_BR->Clone("h_En_BR");
    TH1F *h_vInv_BR = (TH1F*)h_vInv_BR->Clone("h_vInv_BR");
    TH1F *h_tof_BR = (TH1F*)h_tof_BR->Clone("h_tof_BR");
    TH1F *h_En_BT = (TH1F*)h_En_BT->Clone("h_En_BT");
    TH1F *h_vInv_BT = (TH1F*)h_vInv_BT->Clone("h_vInv_BT");
    TH1F *h_tof_BT = (TH1F*)h_tof_BT->Clone("h_tof_BT");

    TH1F *h_bkgd_En_LR = (TH1F*)h_bkgd_En_LR->Clone("h_bkgd_En_LR");
    TH1F *h_bkgd_En_LT = (TH1F*)h_bkgd_En_LT->Clone("h_bkgd_En_LT");
    TH1F *h_bkgd_En_BR = (TH1F*)h_bkgd_En_BR->Clone("h_bkgd_En_BR");
    TH1F *h_bkgd_En_BT = (TH1F*)h_bkgd_En_BT->Clone("h_bkgd_En_BT");
    TH1F *h_bkgd_vInv_LR = (TH1F*)h_bkgd_vInv_LR->Clone("h_bkgd_vInv_LR");
    TH1F *h_bkgd_vInv_LT = (TH1F*)h_bkgd_vInv_LT->Clone("h_bkgd_vInv_LT");
    TH1F *h_bkgd_vInv_BR = (TH1F*)h_bkgd_vInv_BR->Clone("h_bkgd_vInv_BR");
    TH1F *h_bkgd_vInv_BT = (TH1F*)h_bkgd_vInv_BT->Clone("h_bkgd_vInv_BT");
    
    TH1F *h_vInvSum = (TH1F*)h_vInv->Clone("h_vInvSum");
    TH1F *h_bkgd_vInvSum = (TH1F*)h_bkgd_vInv->Clone("h_bkgd_vInvSum");
    
    float newBinV2 = h_vInvSum->GetBinLowEdge(h_vInv->GetSize()-2);
    float newBinV1 = h_vInvSum->GetBinLowEdge(0);
    int totBinsV = (newBinV2-newBinV1)/h_vInv->GetBinWidth(1);
    TH1F *invHistSum = new TH1F("invHistSum","invHistSum", totBinsV, newBinV1, newBinV2);
    TH1F *invHistBGSum = new TH1F("invHistBGSum","invHistBGSum", totBinsV, newBinV1, newBinV2);
    subAccInv(h_vInvSum, invHistSum);
    subAccInv(h_bkgd_vInvSum, invHistBGSum);
    
    TH1F *invHistBG_LR = new TH1F("invHistBG_LR","invHistBG_LR", totBinsV, newBinV1, newBinV2);
    TH1F *invHistBG_BR = new TH1F("invHistBG_BR","invHistBG_BR", totBinsV, newBinV1, newBinV2);
    TH1F *invHistBG_LT = new TH1F("invHistBG_LT","invHistBG_LT", totBinsV, newBinV1, newBinV2);
    TH1F *invHistBG_BT = new TH1F("invHistBG_BT","invHistBG_BT", totBinsV, newBinV1, newBinV2);
    subAccInv(h_bkgd_vInv_LR, invHistBG_LR);
    subAccInv(h_bkgd_vInv_LT, invHistBG_LT);
    subAccInv(h_bkgd_vInv_BR, invHistBG_BR);
    subAccInv(h_bkgd_vInv_BT, invHistBG_BT);
    
    int numBinsEnergy = h_En_LR->GetSize() - 2;

    TH1F *energyHistLR = new TH1F("energyHistLR","energyHistLR",numBinsEnergy,-1000,5000);
    TH1F *energyHistLT = new TH1F("energyHistLT","energyHistLT",numBinsEnergy,-1000,5000);
    TH1F *energyHistBR = new TH1F("energyHistBR","energyHistBR",numBinsEnergy,-1000,5000);
    TH1F *energyHistBT = new TH1F("energyHistBT","energyHistBT",numBinsEnergy,-1000,5000);

    TH1F *energyHistLR_BG = new TH1F("energyHistLR_BG","energyHistLR_BG",numBinsEnergy,-1000,5000);
    TH1F *energyHistLT_BG = new TH1F("energyHistLT_BG","energyHistLT_BG",numBinsEnergy,-1000,5000);
    TH1F *energyHistBR_BG = new TH1F("energyHistBR_BG","energyHistBR_BG",numBinsEnergy,-1000,5000);
    TH1F *energyHistBT_BG = new TH1F("energyHistBT_BG","energyHistBT_BG",numBinsEnergy,-1000,5000);
    
    TH1F *energyHistLR_accSub = new TH1F("energyHistLR_accSub","energyHistLR_accSub",numBinsEnergy,-1000,5000);
    TH1F *energyHistLR_lowTOFSub = new TH1F("energyHistLR_lowTOFSub","energyHistLR_lowTOFSub",numBinsEnergy,-1000,5000);
    TH1F *energyHistLR_shiftLepton = new TH1F("energyHistLR_shiftLepton","energyHistLR_shiftLepton",numBinsEnergy,-1000,5000);
    TH1F *energyHistLR_specCorr = new TH1F("energyHistLR_specCorr","energyHistLR_specCorr",numBinsEnergy,-1000,5000);

    // subtract accidentals, get statistical errors
    // bswang, 4/6/2017: This is the uncertainty in the total number of counts in the 
    // histogram after accidentals have been subtracted off.
    float errLR = subAcc(recoilMassIso, h_En_LR, h_vInv_LR, energyHistLR);
    float errBR = subAcc(recoilMassIso, h_En_BR, h_vInv_BR, energyHistBR);
    float errLT = subAcc(recoilMassIso, h_En_LT, h_vInv_LT, energyHistLT);
    float errBT = subAcc(recoilMassIso, h_En_BT, h_vInv_BT, energyHistBT);
    
    // subtract accidentals for the background spectrum
    subAcc(recoilMassIso, h_bkgd_En_LR, h_bkgd_vInv_LR, energyHistLR_BG);
    subAcc(recoilMassIso, h_bkgd_En_BR, h_bkgd_vInv_BR, energyHistBR_BG);
    subAcc(recoilMassIso, h_bkgd_En_LT, h_bkgd_vInv_LT, energyHistLT_BG);
    subAcc(recoilMassIso, h_bkgd_En_BT, h_bkgd_vInv_BT, energyHistBT_BG);
    
    // save fast-ion counts
    ofstream myfile3;
    myfile3.open ("NbR_counts.txt", ios::out | ios::app | ios::binary);
    myfile3 << fileName << endl;
    
    // Left-Right
    //TCanvas *c1 = new TCanvas("c1","c1");
    myfile3 << "LR" << "\t";
    //
    // Print out raw counts in spectrum and counts in spectrum after accidental subtraction.
    myfile3 << countEvents(h_En_LR, hiEdge) << "\t" << countEvents(energyHistLR, hiEdge) << "\t";
    //energyHistLR_accSub->Add(energyHistLR,1.0);
    //energyHistLR_accSub->SetLineColor(kRed);
    //energyHistLR_accSub->Draw();
    //
    float lowErrLR = subLowTOFNew(isotope, invHistBG_LR, invHistBGSum, energyHistLR);
    // Print out counts in spectrum after low-tof subtraction and uncertainty in number of
    // low-tof counts.
    //energyHistLR_lowTOFSub->Add(energyHistLR,1.0);
    //energyHistLR_lowTOFSub->SetLineColor(kBlack);
    //energyHistLR_lowTOFSub->Draw("same");
    myfile3 << countEvents(energyHistLR, hiEdge) << "\t" << lowErrLR << "\t";
    //
    shiftLepton(isotope, energyHistLR); // shift lepton for 180 combo
    //energyHistLR_shiftLepton->Add(energyHistLR,1.0);
    //energyHistLR_shiftLepton->SetLineColor(kBlue);
    //energyHistLR_shiftLepton->Draw("same");
    //
    spectrumCorr(fileNameFits, 0, energyHistLR);
    //energyHistLR_specCorr->Add(energyHistLR,1.0);
    //energyHistLR_specCorr->SetLineColor(kOrange);
    //energyHistLR_specCorr->Draw("same");
    myfile3 << countEvents(energyHistLR, hiEdge) << "\t" << errLR << endl;
    //c1->SaveAs("NeutronEnergySpectra_LR.C");
    
    // Left-Top
    myfile3 << "LT" << "\t";
    myfile3 << countEvents(h_En_LT, hiEdge) << "\t" << countEvents(energyHistLT, hiEdge) << "\t";
    float lowErrLT = subLowTOFNew(isotope, invHistBG_LT, invHistBGSum, energyHistLT);
    myfile3 << countEvents(energyHistLT, hiEdge) << "\t" << lowErrLT << "\t";
    shiftLepton90(isotope, energyHistLT); // shift lepton for 90 combo
    spectrumCorr(fileNameFits, 1, energyHistLT);
    myfile3 << countEvents(energyHistLT, hiEdge) << "\t" << errLT << endl;
    
    // Bottom-Right
    myfile3 << "BR" << "\t";
    myfile3 << countEvents(h_En_BR, hiEdge) << "\t" << countEvents(energyHistBR, hiEdge) << "\t";
    float lowErrBR = subLowTOFNew(isotope, invHistBG_BR, invHistBGSum, energyHistBR);
    myfile3 << countEvents(energyHistBR, hiEdge) << "\t" << lowErrBR << "\t";
    shiftLepton90(isotope, energyHistBR); // shift lepton for 90 combo
    spectrumCorr(fileNameFits, 2, energyHistBR);
    myfile3 << countEvents(energyHistBR, hiEdge) << "\t" << errBR << endl;
    
    // Bottom-Top
    myfile3 << "BT" << "\t";
    myfile3 << countEvents(h_En_BT, hiEdge) << "\t" << countEvents(energyHistBT, hiEdge) << "\t";
    float lowErrBT = subLowTOFNew(isotope, invHistBG_BT, invHistBGSum, energyHistBT);
    myfile3 << countEvents(energyHistBT, hiEdge) << "\t" << lowErrBT << "\t";
    shiftLepton(isotope, energyHistBT); // shift lepton for 180 combo
    spectrumCorr(fileNameFits, 3, energyHistBT);
    myfile3 << countEvents(energyHistBT, hiEdge) << "\t" << errBT << endl;

    myfile3.close();

    // correct efficiency
    // LR, LT, BR, BT (order in fits)
    // combo number:
    // 0 = LR
    // 1 = LT
    // 2 = BR
    // 3 = BT
    
    int rebinVal = 10;
    energyHistLR->Rebin(rebinVal);
    energyHistBR->Rebin(rebinVal);
    energyHistLT->Rebin(rebinVal);
    energyHistBT->Rebin(rebinVal);
    
    rebinVal = 10;
    h_En_LR->Rebin(rebinVal);
    h_En_BR->Rebin(rebinVal);
    h_En_LT->Rebin(rebinVal);
    h_En_BT->Rebin(rebinVal);
    
    TCanvas *c1 = new TCanvas("c1","c1");
    energyHistLR->Draw();
    energyHistBR->Draw("same");
    energyHistBT->Draw("same");
    energyHistLT->Draw("same");
    energyHistBR->SetLineColor(kRed);
    energyHistLT->SetLineColor(kBlue);
    energyHistBT->SetLineColor(kOrange);
    
    TCanvas *c2 = new TCanvas("c2","c2");
    h_En_LR->Draw();
    h_En_BR->Draw("same");
    h_En_LT->Draw("same");
    h_En_BT->Draw("same");
    h_En_BR->SetLineColor(kRed);
    h_En_LT->SetLineColor(kBlue);
    h_En_BT->SetLineColor(kOrange);
   
    // save spectra in allSpectra.txt
    ofstream myfile;
    myfile.open (spectraFile, ios::out | ios::trunc | ios::binary);

    for (int i = 0; i<numBinsEnergy; i++) {
        //if (h_En_LR->GetBinCenter(i) >= 0 && h_En_LR->GetBinCenter(i) < 2500) {
        if (h_En_LR->GetBinCenter(i) >= 0 && h_En_LR->GetBinCenter(i) < hiEdge) {
            myfile << h_En_LR->GetBinCenter(i) << "\t";
            myfile << h_En_LR->GetBinContent(i) << "\t" << h_En_BR->GetBinContent(i)  << "\t" <<  h_En_LT->GetBinContent(i)  << "\t" <<  h_En_BT->GetBinContent(i) << "\t";
            myfile << energyHistLR->GetBinCenter(i) << "\t";
            myfile << energyHistLR->GetBinContent(i)  << "\t" <<  energyHistBR->GetBinContent(i)  << "\t" <<  energyHistLT->GetBinContent(i)  << "\t" <<  energyHistBT->GetBinContent(i) << endl;
        }
    }
    myfile.close();
    
}
void drawEnergyAll(){
    
    drawEnergy(0);
    drawEnergy(1);
    drawEnergy(2);
    drawEnergy(3);
    drawEnergy(4);
    
}
void shiftLepton(int isotope, TH1F *energyHist180){
    
    // correct for lepton recoil
    int ncells = (energyHist180->GetSize())-2;
    float binCont, binVal, newEnergy;
    for (int i=0; i<ncells; i++) {
        binCont = energyHist180->GetBinContent(i);
        binVal = energyHist180->GetBinCenter(i);
        if (binVal > 50 && binVal < hiEdge) {
            newEnergy = leptonCorr(isotope, binVal);
            energyHist180->SetBinContent(i,0);
            energyHist180->Fill(newEnergy,binCont);
        }
    }
    
}

void shiftLepton90(int isotope, TH1F *energyHist90){
    
    // correct for lepton recoil
    int ncells = (energyHist90->GetSize())-2;
    float binCont, binVal, newEnergy;
    for (int i=0; i<ncells; i++) {
        binCont = energyHist90->GetBinContent(i);
        binVal = energyHist90->GetBinCenter(i);
        if (binVal > 50 && binVal < hiEdge) {
            newEnergy = leptonCorr90(isotope, binVal);
            energyHist90->SetBinContent(i,0);
            energyHist90->Fill(newEnergy,binCont);
        }
    }
    
}

float leptonCorr(int isotope, float xVal){
    // all for 180 degree combo

    if (isotope == 0) { //Cs-144
        int maxInd = 25;
        float xArr180[25] = {0.0,115.385,221.045,325.438,428.939,530.016,631.592,733.619,833.662,935.184,1033.96,1135.13,1233.98,1333.96,1434.43,1531.54,1633.07,1731.72,1829.9,1928.48,2025.39,2124.02,2220.9,2318.57,2500.0};
        float multArr180[25] = {0.825024968,0.866663778,0.904793142,0.921834574,0.93253353,0.943367747,0.949980367,0.95417376,0.959621525,0.962377457,0.967155403,0.969052003,0.972463087,0.974541965,0.975997435,0.979406349,0.979749796,0.981682951,0.983660309,0.985231892,0.987464143,0.988691255,0.990589401,0.991990753,1.0};
    }
    if (isotope == 1) { //Cs-145
        int maxInd = 33;
        float xArr180[33] = {0,122.313,230.732,337.334,441.151,544.739,647.706,749.268,852.6,954.177,1052.76,1154.97,1255.3,1355.52,1457.12,1552.03,1654.16,1755.01,1853.48,1954.9,2049.79,2147.59,2248.83,2346.61,2445.18,2545.01,2641.24,2737.24,2838.42,2935.85,3035.62,3130.67,4000.00};
        float multArr180[33] = {0.762033536,0.817574583,0.866806511,0.889326306,0.906719015,0.91787076,0.926346213,0.934245157,0.938306357,0.943221226,0.949884114,0.95240569,0.955946786,0.959041549,0.960799385,0.966476163,0.967258306,0.968655449,0.971146168,0.971916722,0.975709707,0.977840277,0.978286487,0.980137304,0.981522833,0.982314411,0.984386122,0.986395055,0.986464301,0.987788886,0.988265988,0.990203375,1.0};
    }
    if (isotope == 2) { //I-137
        int maxInd = 20;
        float xArr180[20] = {0,112.944,217.067,320.354,422.285,523.816,624.221,724.888,824.105,924.654,1024.5,1125.73,1224.29,1322.08,1421.26,1521.92,1624.48,1717.73,1818.47,2500.0};
        float multArr180[20] = {0.828524113, 0.885394532,0.921374506, 0.936464037,0.947227583,0.954533653,0.961198037,0.96566642,0.970750086,0.973337054,0.976085896,0.97714372,0.980159929,0.983299044,0.985041442,0.98559714,0.984930562,0.989678238,0.98984311, 1.0};
    }
    if (isotope == 3 || isotope == 4) { //I-138
        int maxInd = 24;
        float xArr180[24] = {0,113.6,219.265,323.141,425.792,526.576,629.028,729.662,829.331,930.039,1029.64,1130.79,1229.28,1328.45,1428.24,1526.12,1626.29,1726.05,1824.32,1920.33,2018.7,2119.27,2217.77,2500.0};
        float multArr180[24] = {0.846032803,0.88028169,0.91213828,0.928387298,0.939425823,0.949530552,0.953852611,0.959348301,0.964632939,0.967701354,0.97121324,0.972771248,0.976181179,0.978584064,0.980227413,0.982884701,0.983834371,0.984907737,0.986669005,0.989413278,0.990736613,0.990907246,0.991987447,1.0};
    }
    if (isotope == 5) { //Sb-135
        int maxInd = 48;
        float xArr180[48] = {0.,129.083,238.759,346.311,453.102,558.528,661.444,768.592,868.977,971.111,1074.66,1178.53,1276.47,1379.26,1480.48,1580.59,1681.45,1780.76,1880.87,1982.38,2081.57,2182.46,2279.27,2381.38,2478.55,2582.2,2678.51,2777.43,2877.51,2974.89,3072.75,3171.09,3270.88,3367.82,3467.04,3560.47,3661.51,3758.33,3857.28,3954.5,4052.18,4151.15,4246.92,4345.11,4436.11,4535,4631.16,4800};
        float multArr180[48] = {0.700583604,0.774695351,0.837664758,0.866273379,0.882803431,0.895210267,0.907106271,0.910756292,0.920622755,0.926773561,0.930526864,0.933366143,0.940092599,0.942534403,0.945639252,0.94901271,0.951559666,0.954648577,0.95700394,0.958443891,0.960813232,0.962216948,0.965221321,0.965826538,0.968308083,0.96816668,0.970688928,0.97212171,0.973063517,0.97482596,0.97632414,0.977581841,0.978329991,0.979862344,0.980663621,0.983016287,0.98320092,0.984479809,0.985150158,0.986218232,0.987122981,0.987678113,0.988951993,0.989618214,0.991859985,0.992282249,0.993271664,1.};
    }
    if (isotope == 6) { //Sb-136
        int maxInd = 51;
        float xArr180[51] = {0,127.958,237.183,346.045,452.46,556.207,659.795,765.084,869.459,970.112,1072.17,1174.02,1276.9,1377.41,1480.67,1581.76,1682.83,1782.48,1881.78,1983.6,2084.51,2182.71,2284.11,2382.95,2484.92,2582.03,2682.56,2781.78,2881.94,2980.9,3082.55,3175.46,3276.21,3376.74,3477.59,3573.01,3669.37,3765.68,3864.59,3961.98,4058.79,4160.27,4265.45,4360.7,4457.28,4550.54,4655.29,4752.47,4849.99,4945.77,5040.05};
        float multArr180[51] = {0.709195872,0.781506432,0.843230754,0.866939271,0.884056049,0.898945896,0.909373366,0.914932217,0.920112392,0.927727932,0.932687913,0.93695167,0.93977602,0.943800321,0.945517907,0.948310742,0.950779342,0.953727391,0.956541147,0.957854406,0.959458098,0.962106739,0.963176029,0.965190205,0.965825862,0.968230423,0.969223428,0.970601557,0.971567763,0.972860545,0.973220224,0.976236514,0.976738365,0.977273939,0.977688572,0.979566248,0.981094847,0.982558263,0.983286713,0.984356307,0.985515388,0.985512959,0.984655781,0.986080216,0.987149113,0.988893626,0.988123189,0.988959425,0.989692762,0.990745627,0.99205365};
    }
    
    int theInd=-1;
    //find applicable index for x0 and x1, y0, y1
    for (int i = 0; i<maxInd; i++) {
        if (xVal >= xArr180[i] && xVal < xArr180[i+1]) theInd = i;
    }
    
    float x0 = xArr180[theInd];
    float x1 = xArr180[theInd+1];
    float y0 = multArr180[theInd];
    float y1 = multArr180[theInd+1];
    float yVal = y0 + (y1-y0)*(xVal-x0)/(x1-x0);
    
    //multiply the interpolated x value by the multArr value
    float correctedEnergy = yVal*xVal;
    return correctedEnergy;
    
}

float leptonCorr90(int isotope, float xVal){
    // all for 90 degree combo
    
    if (isotope == 0) { //Cs-144
        int maxInd = 27;
        float xArr90[27] = {-1.931133333, 98.6804, 199.229, 299.872, 399.091, 498.968, 599.531, 700.778, 800.788, 899.935, 999.852, 1099.71, 1199.7, 1300.79, 1401.36, 1501.68, 1600.53, 1701.5, 1802.12, 1902.82, 2002.11, 2102.18, 2202.06, 2304.21, 2404.17, 2500.32, 2599.01};
        float multArr90[27] = {1.018, 1.013, 1.003, 1.000, 1.002, 1.002, 1.000, 0.999, 0.999, 1.000, 1.000, 1.000, 1.000, 0.999, 0.999, 0.999, 1.000, 0.999, 0.999, 0.999, 0.999, 0.999, 0.999, 0.998, 0.998, 1.000, 1.001};
    }
    if (isotope == 1) { //Cs-145
        int maxInd = 34;
        float xArr90[34] = {-0.187333333, 99.9145, 199.936, 300.078, 401.909, 500.618, 600.707, 701.997, 801.043, 900.969, 1000.19, 1100.74, 1200.94, 1302.17, 1399.9, 1500.84, 1600.0, 1701.69, 1803.46, 1900.86, 1999.76, 2103.99, 2201.99, 2301.44, 2400.82, 2499.54, 2601.6, 2699.07, 2803.44, 2900.02, 3002.65, 3104.33, 3196.15, 3294.54};
        float multArr90[34] = {0.999, 1.000, 0.999, 1.002, 0.995, 0.998, 0.999, 0.997, 0.999, 0.999, 0.999, 0.999, 0.999, 0.998, 1.000, 0.999, 1.000, 0.999, 0.998, 1.000, 1.000, 0.998, 0.999, 0.999, 1.000, 1.000, 1.000, 1.000, 0.999, 1.000, 0.999, 0.999, 1.001, 1.002};
    }
    if (isotope == 2) { //I-137
        int maxInd = 21;
        float xArr90[21] = {-2.55, 98.12, 198.60, 299.36, 399.25, 498.93, 599.29, 699.15, 799.07, 900.36, 999.70, 1099.25, 1201.28, 1302.32, 1401.09, 1502.36, 1600.82, 1702.09, 1799.73, 1903.10, 2000.00};
        float multArr90[21] = {1.025, 1.018, 1.006, 1.002, 1.002, 1.002, 1.001, 1.001, 1.001, 1.000, 1.000, 1.001, 0.999, 0.998, 0.999, 0.998, 0.999, 0.999, 1.000, 0.998, 1.000};
    }
    if (isotope == 3 || isotope == 4) { //I-138
        int maxInd = 24;
        float xArr90[24] = {-2.7272, 98.2291, 198.55, 299.824, 400.067, 498.93, 599.731, 700.71, 800.325, 900.459, 999.82, 1100.26, 1199.21, 1302.48, 1401.23, 1501.04, 1601.05, 1700.86, 1803.03, 1901.19, 2003.65, 2102.91, 2201.28, 2300.243333};
        float multArr90[24] = {1.025, 1.017, 1.008, 1.000, 1.000, 1.002, 1.000, 0.999, 0.999, 1.000, 1.000, 1.000, 1.001, 0.998, 0.999, 0.999, 0.999, 1.000, 0.998, 0.999, 0.998, 0.999, 0.999, 1.000};
    }
    if (isotope == 5) { //Sb-135
        int maxInd = 48;
        float xArr90[48] = {0,101.883,201.695,302.92,402.605,502.779,602.961,703.154,804.023,904.513,1002.81,1105.85,1204.72,1304.71,1406.78,1504.52,1605,1706,1807.87,1905.47,2006.03,2106.37,2202.9,2307.83,2407.22,2509.74,2604.75,2708.05,2808.39,2907.85,3009.07,3111.61,3212.85,3312.64,3409.96,3513.11,3614.39,3708.34,3816.49,3913.44,4012.44,4118.42,4215.45,4312.34,4416.82,4517.82,4627.33,4800};
        float multArr90[48] = {0.971230697,0.981518016,0.991596222,0.990360491,0.993529638,0.994472721,0.995089235,0.995514496,0.994996412,0.995010575,0.997197874,0.994709952,0.996082077,0.996390002,0.995180483,0.99699572,0.996884735,0.996483001,0.995646811,0.997129317,0.996994063,0.99697584,0.998683553,0.996607202,0.99700069,0.99611912,0.998176408,0.997027381,0.997012523,0.997300411,0.99698578,0.996268813,0.996000436,0.996184312,0.997079145,0.996268264,0.996018692,0.997751015,0.995679276,0.996565681,0.996899642,0.995527411,0.996334911,0.997138445,0.99619183,0.99605562,0.994093786,1};
    }
    if (isotope == 6) { //Sb-136
        int maxInd = 51;
        float xArr90[51] = {0,102.408,202.744,305.381,404.535,503.432,605.855,707.675,804.746,907.83,1005.54,1104.94,1208.32,1306.73,1409.45,1507.32,1607.83,1708.98,1807.45,1910.24,2005.98,2111.62,2211.47,2309.9,2412.68,2511.88,2609.76,2709.95,2809.11,2911.15,3014.4,3111.02,3215.37,3312.88,3413.52,3510.83,3616.73,3720.42,3819.18,3919.22,4013.92,4112.78,4224.42,4315.78,4421.08,4516,4625.5,4720.45,4812.72,4923.15,5019.88};
        float multArr90[51] = {0.966300651,0.976486212,0.986465691,0.982379388,0.988789598,0.993182793,0.990335971,0.989154626,0.994102487,0.991375037,0.994490523,0.995529169,0.993114407,0.994849739,0.993295257,0.995143699,0.995130082,0.994745404,0.995878171,0.994639417,0.997018913,0.994497116,0.994813405,0.9957141,0.994744434,0.995270475,0.996260193,0.996328346,0.99675698,0.996169898,0.99522293,0.996457753,0.995219835,0.996112144,0.996039279,0.996915259,0.995374275,0.994511372,0.99497798,0.995095963,0.996532068,0.996892613,0.994219325,0.996343651,0.995231934,0.996457042,0.994487082,0.995667786,0.997357004,0.995297726,0.996039746};
    }
    
    int theInd=-1;
    //find applicable index for x0 and x1, y0, y1
    for (int i = 0; i<maxInd; i++) {
        if (xVal >= xArr90[i] && xVal < xArr90[i+1]) theInd = i;
    }
    
    float x0 = xArr90[theInd];
    float x1 = xArr90[theInd+1];
    float y0 = multArr90[theInd];
    float y1 = multArr90[theInd+1];
    float yVal = y0 + (y1-y0)*(xVal-x0)/(x1-x0);
    
    //multiply the interpolated x value by the multArr value
    float correctedEnergy = yVal*xVal;
    return correctedEnergy;
    
}

float countEvents(TH1F *hist, float hiEdge){
    
    float totEvents = 0;
    for (int k=0; k<hist->GetSize()-2; k++) {
        if(hist->GetBinLowEdge(k) > 100.0 && hist->GetBinLowEdge(k) < hiEdge){
            totEvents = totEvents + hist->GetBinContent(k);
        }
    }
    return totEvents;
}

float countHisto(TH1F *hist, float bin1, float bin2){
    
    float totEvents = 0;
    for (int k=0; k<hist->GetSize()-2; k++) {
        if(hist->GetBinLowEdge(k) > bin1 && hist->GetBinLowEdge(k) < bin2){
            totEvents = totEvents + hist->GetBinContent(k);
        }
    }
    return totEvents;
}
    
    
double calcTofBin(float EnBin, double recoilMassIso){
    
    // En bin given in keV, result given in ns
    double factor = 931494.061/89875517900.0;  // convert amu/c2 to keV
    double recoilMass = recoilMassIso*factor; // Ba-143 mass in keV/(us/mm)^2
    
    double neutronMass = 1.0087010*factor;
    double distToMCP = 48.0; // this is min distance (distance to grid)
    double distToMCP2 = 58.0; // this is max distance
    
    // convert neutron energy to recoil energy:
    double EnRecoil = EnBin*(neutronMass/recoilMass);
    
    double tofBin = 1000.0*sqrt((recoilMass*distToMCP*distToMCP)/(2.0*EnRecoil));
    double tofBin2 = 1000.0*sqrt((recoilMass*distToMCP2*distToMCP2)/(2.0*EnRecoil));
    
    return tofBin;
    
}

// sum over the function from bin1 to bin2 of the histogram it fit (hist1)
float countFunc(TH1F *hist1, TF1 *func, float bin1, float bin2){
    
    float totVal = 0;
    float binCont = 0;
    for (int i=0; i<(hist1->GetSize()-1); i++) {
        if (hist1->GetBinLowEdge(i) >= bin1 && hist1->GetBinLowEdge(i) <= bin2) {
            //cout << hist1->GetBinCenter(i) << "\t" << func(hist1->GetBinCenter(i)) << endl;
            totVal = totVal + (func(hist1->GetBinCenter(i)));
        }
    }
    cout << "function integral" << "\t" << totVal << endl;
    return (totVal);
}

// count counts between 50 and 200 ns in the TOF region
float countRegion(TH1F *hist1){
    
    float totVal = 0;
    float binCont = 0;
    for (int i=0; i<(hist1->GetSize()-1); i++) {
        if (hist1->GetBinLowEdge(i) >= 50 && hist1->GetBinLowEdge(i) <= 200) {
            binCont = hist1->GetBinContent(i);
            totVal = totVal + hist1->GetBinContent(i);
        }
    }
    return totVal;
}

void subAcc3(TH1F *h_bkgd, TH1F *newHist){
    
    float oldBinOffset = h_bkgd->GetBinLowEdge(1)/h_bkgd->GetBinWidth(1);
    float totVal = 0;
    int numBins = 0;
    for (int i=0; i<(h_bkgd->GetSize()-1); i++) {
        
        newHist->SetBinContent(i,h_bkgd->GetBinContent(i-oldBinOffset));
        
        if (h_bkgd->GetBinCenter(i) > 15000 && h_bkgd->GetBinCenter(i) < 20000) {
            
            totVal = totVal + h_bkgd->GetBinContent(i);
            numBins++;
            
        }
    }
    float binAcc = (float)totVal/(float)numBins;
    float oldVal = 0;
    for (i=0; i<(newHist->GetSize()-1); i++) {
        
        oldVal = newHist->GetBinContent(i);
        newHist->SetBinContent(i,oldVal-binAcc);
        
    }
    
}

float subAcc(double recoilMassIso, TH1F *h_En, TH1F *h_vInv, TH1F *energyHist){
    
    double factor = 931494.061/89875517900.0;  // convert amu/c2 to keV
    double recoilMass = recoilMassIso*factor; // Xe-136 mass in keV/(us/mm)^2
    double neutronMass = 1.0087010*factor;
    
    // get accidentals in the flat inverse velocity spectrum, 0.3 to 0.4:
    int numBins = h_vInv->GetSize() - 2;
 
    float kVal;
    int binsUsed = 0;
    float totAccidentals = 0;
    
    for (int i=0; i<numBins; i++) {
        
        kVal = h_vInv->GetBinLowEdge(i);
        if (kVal >= 0.3 && kVal < 0.4) {
            totAccidentals = totAccidentals + h_vInv->GetBinContent(i);
            binsUsed++;
        }
    }
    
    float totalK = (float)binsUsed*h_vInv->GetBinWidth(1);
    float aScaling = (float)totAccidentals/totalK;
    
    // draw accidentals curve in the energy spectrum
    //h_En->Rebin(rebinVal); // 10 keV bins
    int numBins2 = h_En->GetSize() - 2;
    int firstBin = h_En->GetBinLowEdge(0);
    int lastBin = h_En->GetBinLowEdge(numBins2);
    
    float nEnergy, nAcc, nWidth;
    TH1F *nAccHist = new TH1F("nAccHist","nAccHist",numBins2,-1000,5000);
 
    for (i=0; i<numBins2; i++) {
        
        nEnergy = h_En->GetBinLowEdge(i);
        nWidth = h_En->GetBinWidth(i);
        
        if (nEnergy > 0) {
            
            nAcc = aScaling * sqrt( ((recoilMass*recoilMass)/(neutronMass)) / (8.0*nEnergy*nEnergy*nEnergy) ) * nWidth;
            nAccHist->SetBinContent(i,nAcc);
            
        }
    }

    energyHist->Add(h_En, 1.0);
    energyHist->Add(nAccHist, -1.0);
    
    // find statistical error
    float rawCounts = countEvents(h_En, hiEdge);
    float accCounts = countEvents(nAccHist, hiEdge);
    float scaleAcc = accCounts/totAccidentals;
    float totErr = sqrt( rawCounts + scaleAcc*scaleAcc*totAccidentals );

    /*
    h_En->Draw();
    nAccHist->Draw("Lsame");
    nAccHist->SetLineColor(kRed);
    h_En->SetTitle("I-137 Neutron Energy Spectrum, Left-Right Combination");
    h_En->GetXaxis()->SetTitle("Neutron Energy (keV)");
    h_En->GetYaxis()->SetTitle("Counts/10 keV");
    */
    //h_En->Draw();
    //energyHist->Draw("same");
    //energyHist->SetLineColor(kRed);
    
    nAccHist->Delete();
    
    return totErr;
    
}

void spectrumCorr(const char* fileName, int combo, TH1F *energyHistLR){
    
    int numBinsEnergy = energyHistLR->GetSize() - 2;

    float binCenter = 0;
    float corrVal, oldVal, newVal;
    
    for (int i=0; i<numBinsEnergy; i++) {
        
        binCenter = energyHistLR->GetBinCenter(i);
        if (binCenter>0.0) {
            corrVal = applyEffCorr(fileName,combo,binCenter);
            oldVal = energyHistLR->GetBinContent(i);
            newVal = (float)oldVal/corrVal; // divide by correction
            energyHistLR->SetBinContent(i,newVal);
        }
    }
}

float applyEffCorr(const char* fileName, int combo, float xval){

    //cout << "xval = " << xval << " keV" << endl;    
    xval = xval/1000.0;
    
    // equations for x-axis in MeV (convert keV to MeV)
    // f1(x) = a + b*x + c*x**2 + d*x**3 + e*x**4 + f*x**5
    // LR, LT, BR, BT (order of parameters)
    
    ifstream inFile2;
    //inFile2.open ("137i_fitParams.txt");
	inFile2.open (fileName);
    
    double pars[4][6];
	for(int i=0; i<4; i++) {
        inFile2 >> pars[i][0] >> pars[i][1] >> pars[i][2] >> pars[i][3] >> pars[i][4] >> pars[i][5];
        //cout << pars[i][0] << pars[i][1] << pars[i][2] << pars[i][3] << pars[i][4] << pars[i][5] << endl;
	}
	inFile2.close();
    
    float func = pars[combo][0] + xval*pars[combo][1] + xval*xval*pars[combo][2] + xval*xval*xval*pars[combo][3] + xval*xval*xval*xval*pars[combo][4] + xval*xval*xval*xval*xval*pars[combo][5];
    //cout << "w_br = " << func << endl;
    
    return func;
    
}

double calcEn(double recoilMassIso, char theMCP, double tofVal, float mcpPhysX){
    
    double c = 299792.458;	// mm/us
    double dDaughterMass = 1000000.0*recoilMassIso; // I-137 neutron decay daughter
    
    double dDaughterMassKeV = 931494.0023*0.000001*dDaughterMass;
    double dTopGridDistance = 48.0;
    double dRightGridDistance = 48.25;
    double dElectronMassKeV = 510.998459259;
	double dNeutronMassKeV = 939565.319445;
    double dFastIonMassKeV = dDaughterMassKeV - 2.0*dElectronMassKeV;
    double dNeutronEnergyMassFactorKeV = (dFastIonMassKeV/c/c)*(dFastIonMassKeV/dNeutronMassKeV);
    
    TRandom3 *r3 = new TRandom3();
    float rando = r3->Rndm();

    float mcpPhysY;
    mcpPhysY = mcpPhysX;
    double t1, t2, z1, z2, s1, s2, vs, vz, x2, y2;
    double v_LT, En=0;
    
    // this is for Top detector!
    if (theMCP == 'T'){
        
        t1			= 0.001 * tofToMCPGrid (dDaughterMass, 'T', tofVal); // need times in us
        //t1			= 0.001 * (tofVal - 0.5 + rando); // need times in us
        z1			= dTopGridDistance;
        t2			= 0.001 * (tofVal - 0.5 + rando); // need times in us
        x2			= mcpPhysX;
        y2			= mcpPhysY;
        s2			= sqrt(x2*x2 + y2*y2);
        vs			= s2/t2;
        vz			= z1/t1;//stBDNCase.dTopMCPDistance/t2;//z1/t1;
        
        v_LT	= sqrt(vs*vs + vz*vz);
        En	= 0.5 * dNeutronEnergyMassFactorKeV * v_LT * v_LT;
        
        
    }
    if (theMCP == 'R'){
        
        t1			= 0.001 * tofToMCPGrid (dDaughterMass, 'R', tofVal); // need times in us
        //t1			= 0.001 * (tofVal - 0.5 + rando); // need times in us
        z1			= dRightGridDistance;
        t2			= 0.001 * (tofVal - 0.5 + rando); // need times in us
        x2			= mcpPhysX;
        y2			= mcpPhysY;
        s2			= sqrt(x2*x2 + y2*y2);
        vs			= s2/t2;
        vz			= z1/t1;//stBDNCase.dTopMCPDistance/t2;//z1/t1;
        
        v_LT	= sqrt(vs*vs + vz*vz);
        En = 0.5 * dNeutronEnergyMassFactorKeV * v_LT * v_LT;
    }
    
    /*
     TF1 *f2 = new TF1("f2","([0]/([2]*2.50662827463))*exp(-0.5*((x-[1])/[2])**2)",0,2000);
     f2->SetParameters(10,(j+1)*100,20);
     
     EnHist->Fit(f2, "Q+");
     cout << EnHistOrig->GetMean() << "\t" << f2->GetParameter(1) << "\t" << f2->GetParameter(2) << endl;
     */
    return En;
    
}

double tofToMCPGrid(double dDaughterMass, char whichMCP, double t2) {
	
	using namespace TMath;
    
    const double c						= 299792.458;	// mm/us
	const double keVperAMU				= 931494.0023;
	const double dElectronMassAMU		= 0.0005485794411963045; // amu
	const double dNeutronMassAMU		= 1.00866491585; // neutron mass in amu
	const double dNeutronMassKeV		= keVperAMU*dNeutronMassAMU;
	const double dElectronMassKeV		= keVperAMU*dElectronMassAMU;
	const double charge					= 2;
    
    double dTopMCPDistance = 52.5;
    double dTopGridDistance = 48.0;
    double dRightMCPDistance = 52.85;
    double dRightGridDistance = 48.25;
    
    double dDaughterMassAMU = 0.000001*dDaughterMass;
    double dDaughterMassKeV = keVperAMU*dDaughterMassAMU;
    double dFastIonMassKeV = dDaughterMassKeV - charge*dElectronMassKeV;
    
    double dMCPBiasKV = 2.5;
    
    double dTopGridGap = dTopMCPDistance - dTopGridDistance;
	double dTopGridAcceleration	= charge*dMCPBiasKV/dTopGridGap/(dFastIonMassKeV/c/c);
    double dRightGridGap = dRightMCPDistance - dRightGridDistance;
	double dRightGridAcceleration	= charge*dMCPBiasKV/dRightGridGap/(dFastIonMassKeV/c/c);
    
	Double_t a, z1, z2;
	if (whichMCP == 'R') {
		a		= dRightGridAcceleration;
		z1		= dRightGridDistance;
		z2		= dRightMCPDistance;
	}
	if (whichMCP == 'T') {
		a		= dTopGridAcceleration;
		z1		= dTopGridDistance;
		z2		= dTopMCPDistance;
	}
	
	t2 = t2/1000.0; // convert ns to us
	
	Double_t A		= - 9.0*Power(a,2.0)*(3.0*z1-2.0*z2)*t2 - Power(a,3.0)*Power(t2,3.0);
	Double_t B		= 27.0*Power(a,3.0)*(8.0*Power(z2,3.0) - a*(27.0*Power(z1,2.0)-36.0*z1*z2+8.0*Power(z2,2.0))*Power(t2,2.0) + 2.0*Power(a,2.0)*(z2-z1)*Power(t2,4.0));
	Double_t theta	= ATan(Sqrt(B)/A)+Pi();
	Double_t t1		= (1.0/6.0)*(4.0*t2-((6*z2+a*t2*t2)/Power(A*A+B,1.0/6.0)+Power(A*A+B,1.0/6.0)/a)*(Cos(theta/3)-Sqrt(3)*Sin(theta/3)));
	
    // Diagnostics
    //	printf("%s MCP\n", &whichMCP);
    //	printf("a = %f\n", a);
    //	printf("z1 = %f\n", z1);
    //	printf("z2 = %f\n", z2);
    //	printf("A = %f\n", A);
    //	printf("B = %f\n", B);
    //	printf("theta = %f\n", theta);
    //	printf("t1 = %f\n", t1);
	
	return 1000.0 * t1; // return in ns
}

// low TOF functions
float subLowTOFNew(int isotope, TH1F *invHistBG, TH1F *invHistBGSum, TH1F *energyHist){
    
    int totBinsV = invHistBG->GetSize()-2;
    
    // Scale the fit function so it matches vInv Sum of 4 combos
    if (isotope == 0 || isotope == 1 || isotope == 2 || isotope == 3 || isotope ==4) {
    	float countsCombo = countHisto(invHistBG, 0.005, 0.032);
    	float countsSum = countHisto(invHistBGSum, 0.005, 0.032);
    }
    if (isotope == 5) {
    	float countsCombo = countHisto(invHistBG, 0.0045, 0.032);
    	float countsSum = countHisto(invHistBGSum, 0.0045, 0.032);
    }
    if (isotope == 6) {
    	float countsCombo = countHisto(invHistBG, 0.0045, 0.032);
    	float countsSum = countHisto(invHistBGSum, 0.0045, 0.032);
    }
    float comboScale = float(countsCombo/countsSum);

    cout << "countsCombo = " << countsCombo << endl;
    cout << "countsSum = " << countsSum << endl;
    cout << "comboScale = " << comboScale << endl;
    
    // 2a) Get vInv fit function,  scale by comboScale
    
    float pars[4] = {0,0,0,0};
    getPars(isotope, pars);
    
    char funcName[256];
    int n = sprintf(funcName, "([0]*exp([1]*x)+([0]*[2]*exp([3]*x)))*%f", comboScale);

    if (isotope == 0 || isotope == 1 || isotope == 2 || isotope == 3 || isotope ==4) {
    	TF1 *f_main = new TF1("f_main", funcName, 0.005, 0.032);
    }
    if (isotope == 5) {
    	TF1 *f_main = new TF1("f_main", funcName, 0.0043, 0.032);
    }
    if (isotope == 6) {
    	TF1 *f_main = new TF1("f_main", funcName, 0.0042, 0.032);
    }

    for (int i=0; i<4; i++) f_main->FixParameter(i, pars[i]);
    
    // 2b) convert vInv fit to the energy histogram, using BG vInv fit
    
    float bb2 = energyHist->GetBinLowEdge(energyHist->GetSize()-1);
    float bb1 = energyHist->GetBinLowEdge(1);
    int bSum = (bb2-bb1)/energyHist->GetBinWidth(1);
    TH1F *EnHistFit = new TH1F("EnHistFit","EnHistFit", bSum, bb1, bb2);
    
    TH1F *EnHistFitUp = new TH1F("EnHistFitUp","EnHistFitUp", bSum, bb1, bb2);
    TH1F *EnHistFitDown = new TH1F("EnHistFitDown","EnHistFitDown", bSum, bb1, bb2);
    
    int maxBins;
    float vInvBin, vInvBin1, vInvBin2;
    float energyBin, energyBin1, energyBin2;
    float vInvValNew, vInvVal;
    for (int i=0; i<totBinsV; i++) {
        
        vInvBin = invHistBG->GetBinCenter(i);
        energyBin = convertEn(isotope, vInvBin);
        
        if (isotope == 0 || isotope == 1 || isotope == 2 || isotope == 3 || isotope ==4) {
        	if (vInvBin < 0.005 || vInvBin > 0.032) continue;
	}
    	if (isotope == 5) {
        	if (vInvBin < 0.0043 || vInvBin > 0.032) continue;
	}
    	if (isotope == 6) {
        	if (vInvBin < 0.0042 || vInvBin > 0.032) continue;
	}
        
        vInvBin1 = invHistBG->GetBinLowEdge(i);
        vInvBin2 = invHistBG->GetBinLowEdge(i+1);
        energyBin1 = convertEn(isotope, vInvBin2);
        energyBin2 = convertEn(isotope, vInvBin1);
        
        vInvVal = f_main(vInvBin);
        
        if ((energyBin2-energyBin1) < 1.0) {
            EnHistFit->Fill(energyBin, vInvVal);
        }
        if ((energyBin2-energyBin1) >= 1.0) {
            vInvValNew = vInvVal/(energyBin2-energyBin1);
            maxBins = TMath::Ceil(energyBin2-energyBin1);
            for (int k=0; k<maxBins; k++) {
                if ((energyBin1+k) > energyBin2) continue;
                EnHistFit->Fill(energyBin1+k, vInvValNew);
            }
        }
    }
    
    
    EnHistFitUp->Add(EnHistFit, 1.0);
    EnHistFitDown->Add(EnHistFit, 1.0);
    
    // 3) scale by subFactor and subtract from energy histogram
    
    float subFactor = getSubFactor(isotope, 0); // second par: error, vary by -1.0, 1.0, or 0
    EnHistFit->Scale(subFactor);
    energyHist->Add(EnHistFit, -1.0);
    
    float subFactorUp = getSubFactor(isotope, 1.0);
    EnHistFitUp->Scale(subFactorUp);
    float subFactorDown = getSubFactor(isotope, -1.0);
    EnHistFitDown->Scale(subFactorDown);
    
    // spit out error here based on different subFactors
    float totLowTOFErr = (countEvents(EnHistFitUp, hiEdge) - countEvents(EnHistFitDown, hiEdge))/2.0;
    
    cout << countEvents(EnHistFit, hiEdge) << "\t" << totLowTOFErr << endl;
    
    return totLowTOFErr;
    
}

float getSubFactor(int isotope, int ifErr){
    
    // updated values from July 28th, 2016
    float subFactorArr[7] = {4.90, 5.07, 6.98, 6.46, 10.44, 4.35, 4.25}; // weighted average  (bswang, 4/7/2017: The last two values were
									 // obtained using the counts ratio method)
    float subFactorArrErr[7] = {0.27, 0.48, 0.72, 0.91, 2.38, 1.47, 1.65}; // this is from scaling  (bswang, 4/7/2017: The last two values were
									   // obtained using the counts ratio method)
    
   // old values:
  //  float subFactorArr[5] = {4.54, 5.71, 5.90, 9.712, 9.712}; // this is from scaling

    float subFactor = subFactorArr[isotope] + ifErr*subFactorArrErr[isotope];
    return subFactor;
    
}

void getPars(int isotope, float *pars){
    
    // parameters for the function that fits the BG inverse-velocity spectrum
    pars[0] = 2.07254e+02;
    pars[1] = -1.95421e+03;
    pars[2] = 2.13981e-02;
    pars[3] = -1.13293e+02;
    
    if (isotope == 0) {
        pars[0] = 2.07254e+02*0.86;
        pars[1] = -1.95421e+03;
        pars[2] = 2.13981e-02;
        pars[3] = -1.13293e+02;
    }
    if (isotope == 1) {
        pars[0] =  7.46871e+01*1.37;
        pars[1] = -3.90227e+03;
        pars[2] = 1.19846e-02;
        pars[3] = -1.00514e+02;
    }
    if (isotope == 2) {
        pars[0] = 38.5373;
        pars[1] = -1954.21;
        pars[2] = 0.0213981;
        pars[3] = -113.293;
    }
    if (isotope == 3) {
        pars[0] = 28.5;
        pars[1] = -1954.21;
        pars[2] = 0.0213981;
        pars[3] = -113.293;
    }
    if (isotope == 4) {
        pars[0] = 6.7*0.81;
        pars[1] = -1954.21;
        pars[2] = 0.0213981;
        pars[3] = -113.293;
    }
    if (isotope == 5) {
    	pars[0] = 56.2712;	//(56.2712 +/- 7.42729) Obtained from fit using rebin = 10 (Chisquare/NDF = 1950.6)
    	//pars[0] = 60.5193;	//(60.5193 +/- 7.51343) Obtained from fit using rebin = 1 (Chisquare/NDF = 2104.82)
    	pars[1] = -1.95421e+03;
    	pars[2] = 2.13981e-02;
    	pars[3] = -1.13293e+02;
    }
    if (isotope == 6) {  //Chisquare/NDF for fit was 550.294
    	pars[0] = 24.3516;	//(24.5316 +/- 4.88598) Obtained from fit using rebin = 10 (Chisquare/NDF = 1218.92)
    	//pars[0] = 31.6137;	//(31.6137 +/- 5.43033) Obtained from fit using rebin = 1 (Chisquare/NDF = 651.013)
    	pars[1] = -1.95421e+03;
    	pars[2] = 2.13981e-02;
    	pars[3] = -1.13293e+02;
    }
    
}

double convertEn(int isotope, double inverseVel){
    
    double dNeutronEnergyMassFactorKeV = getFactor(isotope);
    double v_LT = 1.0/inverseVel;
    double EnVal = 0.5 * dNeutronEnergyMassFactorKeV * v_LT * v_LT;
    
    return EnVal;
    
}

double getFactor(int isotope){
    
    double theCharge = 2.0; // could use average charge?
    double dDaughterMass = getMass(isotope);
    double c = 299792.458;	// mm/us
    double dDaughterMassKeV = 931494.0023*dDaughterMass;
    double dElectronMassKeV = 510.998459259;
	double dNeutronMassKeV = 939565.319445;
    double dFastIonMassKeV = dDaughterMassKeV - theCharge*dElectronMassKeV;
    double dNeutronEnergyMassFactorKeV = (dFastIonMassKeV/c/c)*(dFastIonMassKeV/dNeutronMassKeV);
    
    return dNeutronEnergyMassFactorKeV;
    
}

double getMass(int isotope){
    
    if (isotope == 0) double recoilMassIso = 142.920626719; // Ba-143 (from Cs-144)
    if (isotope == 1) double recoilMassIso = 143.922952853; // Ba-144 (from Cs-145)
    if (isotope == 2) double recoilMassIso = 135.9072145; // Xe-136 mass (from I-137)
    if (isotope == 3) double recoilMassIso = 136.911562125; // Xe-137 mass (from I-138)
    if (isotope == 4) double recoilMassIso = 136.911562125; // Xe-137 mass (from I-138)
    if (isotope == 5) double recoilMassIso = 133.911394; // Te-134 mass (from Sb-135)
    if (isotope == 6) double recoilMassIso = 134.9165557; // Te-135 mass (from Sb-136)
    
    return recoilMassIso;
    
}

// accidental subtraction for vInverse
void subAccInv(TH1F *h_inv, TH1F *newHist){
    
    // get number of accidentals/bin
    float totVal = 0;
    int numBins = 0;
    for (int i=0; i<(h_inv->GetSize()-1); i++) {
        if (h_inv->GetBinCenter(i) > 0.3 && h_inv->GetBinCenter(i) < 0.4) {
            totVal = totVal + h_inv->GetBinContent(i);
            numBins++;
        }
    }
    // float nsRegion = (float)(numBins*h_inv->GetBinWidth(1));
    float binAcc = (float)totVal/numBins; // accidentals per bin
    float binAccErr = sqrt((float)totVal)/numBins;
    
    // fill out the new histogram with values from the old
    float oldBinCenter, newBinCenter, oldBinContent, newBinContent, newBinError;
    int oldBin;
    for (i=0; i<(h_inv->GetSize()-1); i++) {
        
        oldBinContent = h_inv->GetBinContent(i);
        oldBinCenter = h_inv->GetBinCenter(i);
        newHist->Fill(oldBinCenter, oldBinContent);
        
    }
    // subtract accidentals
    for (i=0; i<(newHist->GetSize()-1); i++) {
        
        oldBinContent = (newHist->GetBinContent(i));
        newBinContent = oldBinContent - binAcc;
        newBinError = sqrt( oldBinContent + binAccErr*binAccErr );
        
        newHist->SetBinContent(i,newBinContent);
        newHist->SetBinError(i, newBinError);
        
    }
    
}
