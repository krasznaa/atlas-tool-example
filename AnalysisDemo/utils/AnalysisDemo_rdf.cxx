// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "MuonAnalysisTools/MuonCalibratorRDF.h"

// Framework include(s).
#include <AsgMessaging/MessageCheck.h>
#include <xAODDataSource/MakeDataFrame.h>
#include <xAODRootAccess/Init.h>

// ROOT include(s).
#include <TCanvas.h>
#include <TROOT.h>
#include <TString.h>
#include <TSystem.h>

#include <ROOT/RDFHelpers.hxx>

// System include(s).
#include <cstdlib>

int main() {

    // Set up the environment.
    using namespace asg::msgUserCode;
    ANA_CHECK_SET_TYPE(int);
    ANA_CHECK(xAOD::Init());
    ROOT::EnableImplicitMT();

    // Create a data frame object.
    auto df = xAOD::MakeDataFrame(gSystem->Getenv("ASG_TEST_FILE_MC"));

    // Create the muon calibrator object(s).
    ATE::RDF::MuonCalibratorxAOD muCalibxAOD;
    ANA_CHECK(muCalibxAOD.initialize());
    ATE::RDF::MuonCalibrator muCalib;
    ANA_CHECK(muCalib.initialize());

    // Create the muon "variator" object(s).
    ATE::RDF::MuonVariatorxAOD muVarxAOD;
    ANA_CHECK(muVarxAOD.initialize());
    ATE::RDF::MuonVariator muVar;
    ANA_CHECK(muVar.initialize());

    // Create the calibrated muon pt as a new column, from the xAOD container.
    auto muon_pt_xaod = df.Define("muon_pt_calib", muCalibxAOD, {"Muons"})
                            .Vary("muon_pt_calib", muVarxAOD, {"Muons"},
                                  {"foo_up", "foo_down"});

    // Create the calibrated muon pt as a new column, from primitive columns.
    // For this, first set up the primitive columns from the xAOD container.
    auto muon_primitive = df.Define("muon_eta",
                                    [](const xAOD::MuonContainer& muons) {
                                        std::vector<float> result;
                                        result.reserve(muons.size());
                                        for (const xAOD::Muon* muon : muons) {
                                            result.push_back(muon->eta());
                                        }
                                        return result;
                                    },
                                    {"Muons"})
                              .Define("muon_phi",
                                      [](const xAOD::MuonContainer& muons) {
                                          std::vector<float> result;
                                          result.reserve(muons.size());
                                          for (const xAOD::Muon* muon : muons) {
                                              result.push_back(muon->phi());
                                          }
                                          return result;
                                      },
                                      {"Muons"})
                              .Define("muon_pt",
                                      [](const xAOD::MuonContainer& muons) {
                                          std::vector<float> result;
                                          result.reserve(muons.size());
                                          for (const xAOD::Muon* muon : muons) {
                                              result.push_back(muon->pt());
                                          }
                                          return result;
                                      },
                                      {"Muons"});

    // Now create the calibrated column.
    auto muon_pt_primitive =
        muon_primitive
            .Define("muon_pt_calib", muCalib,
                    {"muon_pt", "muon_eta", "muon_phi"})
            .Vary("muon_pt_calib", muVar, {"muon_pt", "muon_eta", "muon_phi"},
                  {"foo_up", "foo_down"});

    // Make a histogram of the calibrated muon pts.
    TCanvas canvas{"canvas", "canvas", 1600, 600};
    canvas.Divide(2);
    canvas.cd(1)->SetLogy();
    auto hist1 = muon_pt_xaod.Histo1D("muon_pt_calib");
    auto hist1_var = ROOT::RDF::Experimental::VariationsFor(hist1);
    hist1_var["nominal"].Draw();
    hist1_var["muon_pt_calib:foo_up"].Draw("SAME");
    hist1_var["muon_pt_calib:foo_down"].Draw("SAME");
    canvas.cd(2)->SetLogy();
    auto hist2 = muon_pt_primitive.Histo1D("muon_pt_calib");
    auto hist2_var = ROOT::RDF::Experimental::VariationsFor(hist2);
    hist2_var["nominal"].Draw();
    hist2_var["muon_pt_calib:foo_up"].Draw("SAME");
    hist2_var["muon_pt_calib:foo_down"].Draw("SAME");
    canvas.SaveAs("muon_pt.png");

    // Return gracefully.
    return EXIT_SUCCESS;
}
