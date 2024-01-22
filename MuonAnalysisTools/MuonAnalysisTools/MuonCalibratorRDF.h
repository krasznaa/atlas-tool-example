// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#ifndef MUONANALYSISTOOLS_MUONCALIBRATORRDF_H
#define MUONANALYSISTOOLS_MUONCALIBRATORRDF_H

// Local include(s).
#include "MuonAnalysisTools/MuonCalibrator.h"

// EDM include(s).
#include <xAODMuon/MuonContainer.h>

// ROOT include(s).
#include <ROOT/RVec.hxx>

// System include(s).
#include <string>
#include <vector>

namespace ATE::RDF {

/// Functor that could be used directly with @c ROOT::RDataFrame::Define
class MuonCalibrator : public ATE::MuonCalibrator {

public:
    // Inherit the base class's constructor(s).
    using ATE::MuonCalibrator::MuonCalibrator;

    /// Operator applying the calibration to a single muon
    std::vector<float> operator()(const std::vector<float>& pt,
                                  const std::vector<float>& eta,
                                  const std::vector<float>& phi) const;

};  // class MuonCalibrator

/// Functor that could be used with @c ROOT::RDataFrame::Define, on an xAOD
class MuonCalibratorxAOD : public ATE::MuonCalibrator {

public:
    // Inherit the base class's constructor(s).
    using ATE::MuonCalibrator::MuonCalibrator;

    /// Operator applying the calibration to a single muon
    std::vector<float> operator()(const xAOD::MuonContainer& muon) const;

};  // class MuonCalibratorxAOD

/// Functor that could be used directly with @c ROOT::RDataFrame::Vary
class MuonVariator : public ATE::MuonCalibrator {

public:
    // Inherit the base class's constructor(s).
    using ATE::MuonCalibrator::MuonCalibrator;

    /// Operator applying the calibration to a single muon
    ROOT::RVec<std::vector<float> > operator()(
        const std::vector<float>& pt, const std::vector<float>& eta,
        const std::vector<float>& phi) const;

};  // class MuonVariator

/// Functor that could be used with @c ROOT::RDataFrame::Vary, on an xAOD
class MuonVariatorxAOD : public ATE::MuonCalibrator {

public:
    // Inherit the base class's constructor(s).
    using ATE::MuonCalibrator::MuonCalibrator;

    /// Operator applying the calibration to a single muon
    ROOT::RVec<std::vector<float> > operator()(
        const xAOD::MuonContainer& muon) const;

};  // class MuonVariatorxAOD

}  // namespace ATE::RDF

#endif  // MUONANALYSISTOOLS_MUONCALIBRATORRDF_H
